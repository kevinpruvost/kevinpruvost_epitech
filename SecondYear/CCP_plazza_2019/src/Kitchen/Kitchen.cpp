/*
** EPITECH PROJECT, 2020
** Kitchen.cpp
** File description:
** kitchen
*/

#include "Kitchen.hpp"

// Project includes
#include "CondVar.hpp"

// C++ includes
#include <iostream>

static std::mutex mutex;
static std::condition_variable cond;

static std::mutex m;
static std::condition_variable condPizzas;

Kitchen::Kitchen(unsigned int cooksNumber, double cookingTimeMultiplier, bool passive)
	: _markedForAfkManaging { false }
	, _dead { false }
	, _cookingTimeMultiplier { cookingTimeMultiplier}
	, _cooksNumber { cooksNumber }
	, _newCookedPizzas { false }
	, _afkTimeStart { std::chrono::system_clock::now() }
	, _afkTime { 0 }
	, _threadsReadyToDie { 0 }
	, _passive { passive }
{
	if (passive)
		return;
	std::string msg;

	if (cooksNumber <= 0)
		msg = "Wrong cook number.";
	if (cookingTimeMultiplier < 0)
	{
		msg += ((msg.empty()) ? "" : "\nBut also ");
		msg += "Wrong cooking time multiplier.";
	}
	if (!msg.empty())
		throw EXCEPTION(msg);

	for (unsigned int i = 0; i < cooksNumber; ++i)
		_cooks.emplace_back(_cookingTimeMultiplier);

	_process.init();

	if (_process.isChild())
	{
		DEBUG("\033[1;32m" << "Kitchen child " << getpid() << " constructed.\033[0m");
		try {
			exec();
		} catch(const std::exception& e) {
			std::cerr << e.what() << std::endl;
			_process.write("stop()");
			return;
		}
	}
	else if (!isChildProcess)
	{
		++_threadsReadyToDie;
		_threads.emplace_back(new std::thread([&]
		{
			while (workingProcess && !_dead)
			{
				std::string response = _process.read();
				if (!response.empty())
					identifyOrder(response);
				for (auto it = _pizzas.begin(); it != _pizzas.end(); ++it)
				{
					if (_pizzas.empty())
						break;
					if (it->get()->isCooked())
					{
						_pizzas.erase(it);
						it = _pizzas.begin();
					}
				}
			}
			mutex.lock();
			--_threadsReadyToDie;
			mutex.unlock();
			std::unique_lock<std::mutex> lock(mutex);
			cond.notify_all();
		}));
		_threads.back()->detach();

		++_threadsReadyToDie;
		_threads.emplace_back(new std::thread([&]{
			while (workingProcess && !_dead)
			{
				this->afkTimeRefresh();
				std::this_thread::sleep_for(std::chrono::milliseconds(200));
			}
			mutex.lock();
			--_threadsReadyToDie;
			mutex.unlock();
			std::unique_lock<std::mutex> lock(mutex);
			cond.notify_all();
		}));
		_threads.back()->detach();

		DEBUG(YELLOW_START << "Kitchen Parent starts reading thread" << END_COLOR);
	}
}

Kitchen::Kitchen(unsigned int cooksNumber, double cookingTimeMultiplier, std::vector<Pizza> & pizzas, bool passive)
	: Kitchen(cooksNumber, cookingTimeMultiplier, passive)
{
	addPizzas(pizzas);
}

Kitchen::~Kitchen()
{
	if (_passive)
		return;
	_dead = true;
	_process.closeFds();
	for (auto & thread : _threads)
		thread.reset();
	if (isParent() && !isChildProcess)
		_process.write("stop()");
    if (isChildProcess && !isChild())
		return;
	while (!readyToDie())
	{
		std::unique_lock<std::mutex> lock(mutex);
		cond.wait(lock);
	}
	if (isChildProcess && _process.isChild())
		DEBUG("\033[1;31mKitchen " << ((_process.isChild()) ? "Child" : "Parent") << " " << getpid() << " destroyed.\033[0m")
}

// KITCHEN INTERACTIONS --------------------------------------------------------

bool Kitchen::addPizzas(const std::shared_ptr<Pizza> & pizza)
{
	if (_pizzas.size() >= MAX_PIZZAS)
		return false;
	if (isParent())
	{
		std::string toWrite = "addPizzas(";
		toWrite += CreateStringFromPizzas(*pizza);
		toWrite += ")";
		_process.write(toWrite);
	}
	_pizzas.push_back(pizza);
	return true;
}

bool Kitchen::addPizzas(const Pizza & pizza)
{
	if (_pizzas.size() >= MAX_PIZZAS)
		return false;
	if (isParent())
	{
		std::string toWrite = "addPizzas(";
		toWrite += CreateStringFromPizzas(pizza);
		toWrite += ")";
		_process.write(toWrite);
	}
	_pizzas.push_back(std::make_shared<Pizza>(Pizza(pizza)));
	return true;
}

bool Kitchen::addPizzas(const std::vector<Pizza> & pizzas)
{
	if (_pizzas.size() + pizzas.size() > MAX_PIZZAS)
		return false;
	for (const auto pizza : pizzas)
		if (!addPizzas(pizza))
			return false;
	return true;
}

bool Kitchen::addPizzas(const std::vector<std::shared_ptr<Pizza>> & pizzas)
{
	if (_pizzas.size() + pizzas.size() > MAX_PIZZAS)
		return false;
	if (isParent())
	{
		std::string toWrite = "addPizzas(";
		toWrite += CreateStringFromPizzas(pizzas);
		toWrite += ")";
		_process.write(toWrite);
	}
	for (const auto & pizza : pizzas)
		_pizzas.push_back(pizza);
	return true;
}

void Kitchen::restock()
{
	if (isParent())
		_process.write("restock()");
	_stock.restock();
}

void Kitchen::sendCookedPizzas(const std::vector<int> & indexes)
{
	if (isChild())
	{
		std::string msg = "sendCookedPizzas(";
		for (unsigned int i = 0; i < indexes.size(); ++i)
		{
			msg += std::to_string(indexes[i]);
			if (i != indexes.size() - 1)
				msg += ";";
		}
		msg += ")";
		_process.write(msg);
		removeThesePizzas(indexes);
	}
	else
	{
		try {
			for (const auto & index : indexes)
				_pizzas[index]->setCooked();
			removeThesePizzas(indexes);
		} catch (const std::exception & e) {
			std::cerr << "Problem with sendCookedPizzas() " << e.what() << std::endl;
		}
	}
}

void Kitchen::sendStatePizzas(const std::vector<Pizza::PizzaState> & states)
{
	if (isChild())
	{
		std::string msg = "sendStatePizzas(";
		msg += CreateStringFromStates(states);
		msg += ")";
		_process.write(msg);
		auto sstates = states;
		for (size_t i = 0; i < sstates.size(); ++i)
		{
			if (_pizzas.empty())
				break;
			if (sstates[i] == Pizza::PizzaState::Cooked)
			{
				mutex.lock();
				_pizzas.erase(_pizzas.begin() + i);
				mutex.unlock();
				sstates.erase(sstates.begin() + i);
				--i;
			}
		}
	}
	else
	{
		for (size_t i = 0; i < states.size(); ++i)
		{
			if (i >= _pizzas.size())
			{
				DEBUG("sendStatesPizzas() sent a weird state.");
				continue;
			}
			_pizzas[i]->setState(states[i]);
		}
		auto sstates = states;
		for (size_t i = 0; i < sstates.size(); ++i)
		{
			if (_pizzas.empty())
				break;
			if (sstates[i] == Pizza::PizzaState::Cooked)
			{
				mutex.lock();
				std::cout << "A " << CreateStringFromPizzas(*_pizzas[i]) << " has been cooked !" << std::endl;
				_pizzas.erase(_pizzas.begin() + i);
				mutex.unlock();
				sstates.erase(sstates.begin() + i);
				--i;
			}
		}
	}
}

std::vector<Pizza::PizzaState> Kitchen::prepareStatePizzas()
{
	std::vector<Pizza::PizzaState> states;

	for (const auto & pizza : _pizzas)
		states.push_back(pizza->getState());
	return states;
}

// KITCHEN CHILD LOOP ----------------------------------------------------------

int Kitchen::exec()
{
	bool usingPizzas = false;
	std::condition_variable usingCondPizzas;
	++_threadsReadyToDie;
	_threads.emplace_back(new std::thread([&]
	{
		while (workingProcess && !_dead)
		{
			while (usingPizzas)
			{
				std::unique_lock<std::mutex> lock(mutex);
				usingCondPizzas.wait(lock);
			}
			usingPizzas = true;
			if (!isPizzasCookedOrCooking())
				cookingRepartition();
			if (!_pizzas.empty())
				sendStatePizzas(prepareStatePizzas());
			usingPizzas = false;
			std::unique_lock<std::mutex> lock(mutex);
			usingCondPizzas.notify_all();
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
		mutex.lock();
		--_threadsReadyToDie;
		mutex.unlock();
		std::unique_lock<std::mutex> lock(mutex);
		cond.notify_all();
	}));
	_threads.back()->detach();

	while (workingProcess && !_dead)
	{
		std::string order = _process.read();
		while (usingPizzas)
		{
			std::unique_lock<std::mutex> lock(mutex);
			usingCondPizzas.wait(lock);
		}
		usingPizzas = true;
		if (!order.empty())
			identifyOrder(order);
		usingPizzas = false;
		std::unique_lock<std::mutex> lock(mutex);
		usingCondPizzas.notify_all();
	}
	workingProcess = false;
	while (!readyToDie())
	{
		std::unique_lock<std::mutex> lock(mutex);
		cond.wait(lock);
	}
	return EXIT_SUCCESS;
}

bool Kitchen::launchOrder(const std::string & funcName, const std::vector<std::string> & params)
{
	DEBUG_FLUSH("\033[1;33mOrder towards kitchen " << ((isChild()) ? "child " : "parent ") << getpid() << ":\n\t[")
	DEBUG_FLUSH(funcName << " : ")
	for (const auto & param : params)
		DEBUG_FLUSH(param)
	DEBUG("]\033[0m\n")

	/****/ if (funcName == "restock") {
		restock();
	} else if (funcName == "addPizzas") {
		if (params.empty())
			throw EXCEPTION("addPizzas() format is wrong.");
		addPizzas(CreatePizzasFromSring(params[0]));
	} else if (funcName == "stop") {
		_dead = true;
		workingProcess = false;
	} else if (funcName == "sendCookedPizzas") {
		if (params.empty())
			throw EXCEPTION("sendCookedPizzas() format is wrong.");
		sendCookedPizzas(CreateIntsFromString(params[0]));
	} else if (funcName == "takeIngredientsInStock") {
		if (params.empty())
			throw EXCEPTION("takeIngredientsInStock() format is wrong.");
		takeIngredientsInStock(CreateIngredientsFromString(params[0]));
	} else if (funcName == "sendStatePizzas") {
		if (params.empty())
			throw EXCEPTION("sendStatePizzas() format is wrong.");
		sendStatePizzas(CreateStatesFromString(params[0]));
	}
	return true;
}

void Kitchen::identifyOrder(std::string & order)
{
	std::string oofOrder = order;
	DEBUG("Order received : " << order)
	while (!order.empty())
	{
		try {
			std::string functionName = order.substr(0, order.find_first_of('('));
			order = order.substr(order.find_first_of('('));
			order = order.substr(1);
			std::string params = order.substr(0, order.find_first_of(')'));
			order = order.substr(order.find_first_of(')'));
			order = order.substr(1);
			if (!launchOrder(functionName, split(params, ',')))
				throw EXCEPTION("Message does not correspond to any orders.");
		} catch (const std::exception & e) {
			workingProcess = false;
		}
	}
}

// LOOP TOOLS ------------------------------------------------------------------

void Kitchen::cookingRepartition()
{
	for (auto & pizza : _pizzas)
	{
		if (pizza->isCooked() || pizza->isCooking() || pizza->isAssigned())
			continue;
		if (!_stock.verifyIngredientsInStock(pizza->getIngredients()))
		{
			DEBUG("Not enough ingredients for : " << CreateStringFromPizzas(*pizza))
			continue;
		}
		auto cook = _cooks.begin();
		if (_cooks.size() > 1)
		{
			for (auto cmp = _cooks.begin() + 1; cmp != _cooks.end(); ++cmp)
			{
				if (cmp->isFull())
					continue;
				if (cmp->isEmpty() || cook->isFull() ||
					cmp->getRemainingCookingTotalTime() < cook->getRemainingCookingTotalTime())
					cook = cmp;
			}
		}
		if (!cook->isFull())
		{
			if (cook->cookPizza(std::ref(*pizza)))
				takeIngredientsInStock((*pizza).getIngredients());
		}
	}
}

void Kitchen::takeIngredientsInStock(const std::vector<Ingredient::IngredientType> & ing)
{
	if (ing.empty())
		return;
	if (isChild())
	{
		std::string toWrite = "takeIngredientsInStock(";
		toWrite += CreateStringFromIngredients(ing);
		toWrite += ")";
		_process.write(toWrite);
	}
	_stock.takeIngredientsInStock(ing);
}

bool Kitchen::isPizzasCookedOrCooking() const
{
	for (const auto & pizza : _pizzas)
		if (!pizza->isAssigned())
			return false;
	return true;
}

// GETTERS ---------------------------------------------------------------------

std::vector<std::shared_ptr<Pizza>> & Kitchen::getPizzas() { return _pizzas; }

const Stock & Kitchen::getStock() const { return _stock; }

bool Kitchen::isChild() { return _process.isChild(); }

bool Kitchen::isParent() { return _process.isParent(); }

// TOOLS -----------------------------------------------------------------------

std::vector<std::string> split(const std::string & s, char seperator)
{
  	std::vector<std::string> output;
    std::string::size_type prev_pos = 0, pos = 0;

    while ((pos = s.find(seperator, pos)) != std::string::npos)
    {
        std::string substring( s.substr(prev_pos, pos-prev_pos) );
        output.push_back(substring);
        prev_pos = ++pos;
    }

    output.push_back(s.substr(prev_pos, pos-prev_pos));
    return output;
}

bool Kitchen::isWorking() const
{
	if (!_pizzas.empty())
		return true;
	return false;
}

void Kitchen::removeThesePizzas(const std::vector<int> & indexes)
{
	unsigned int malus = 0;

	for (auto & index : indexes)
	{
		auto it = _pizzas.begin() + index - malus;
		_pizzas.erase(it);
		++malus;
	}
}

int Kitchen::afkTime() const
{
	if (isWorking())
		return 0;
	return _afkTime;
}

void Kitchen::afkTimeRefresh()
{
	if (!_beginAfk)
		return;
	auto now = std::chrono::system_clock::now();
	if (isWorking())
	{
		_afkTimeStart = now;
		_afkTime = 0;
	}
	else
	{
		_afkTime = (std::chrono::duration_cast<std::chrono::milliseconds>(now - _afkTimeStart).count());
	}
}

void Kitchen::kill()
{
	_dead = true;
	_process.write("stop()");
	for (auto & thread : _threads)
		thread.reset();
}

bool Kitchen::readyToDie()
{
	return _threadsReadyToDie <= 0;
}

void Kitchen::beginAfk()
{
	_beginAfk = true;
	_afkTimeStart = std::chrono::system_clock::now();
}

void Kitchen::checkForCookedPizza()
{
	for (size_t i = 0; i < _pizzas.size();)
	{
		if (_pizzas.empty())
			break;
		if (_pizzas[i]->isCooked())
		{
			std::cout << "A " << CreateStringFromPizzas(*_pizzas[i]) << " has been cooked !" << std::endl;
			_pizzas.erase(_pizzas.begin() + i);
			i = 0;
		}
		else
		{
			++i;
		}
	}
}