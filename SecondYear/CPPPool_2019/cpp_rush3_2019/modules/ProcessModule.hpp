/*
** EPITECH PROJECT, 2020
** cpp_rush3_2019
** File description:
** Process
*/

#ifndef PROCESS_HPP_
#define PROCESS_HPP_

#include "IMonitorModule.hpp"

class ProcessModule : public IMonitorModule {
	public:
		class Process {
			public:
				Process(const std::string & pid) : _pid {pid} {}

				const std::string getPid() const { return _pid; }
				std::string getName() const { return _name; }

				void setName(const std::string & name) { _name = name; }

				void setUser(const std::string& user) { _user = user;}
				std::string getUser() const { return _user;}

				std::string getState() const { return _state;}
				void setState(const std::string & state) { _state = state; }

				void setVirtual(int state)  { _virtual = state; }
				int getVirtual() const { return _virtual; }

				void setPriority(int state) { _priority = state; }
				int getPriority() const { return _priority; }

				void setNice(int state) { _nice = state; }
				int getNice() const { return _nice; }

				void setTime(int time) { _time = time; }
				int getTime() const { return _time; }

				void setUpTime(double uptime) { _uptime = uptime; }
				int getUpTime() const { return _time; }

				void setSTime(int stime) { _stime = stime; }
				int getSTime(void) const { return this->_stime; }

				void setUTime(int utime) { _utime = utime; }
				int getUTime(void) const { return this->_utime; }

				void setCSTime(int utime) { _cstime = utime; }
				int getCSTime(void) const { return this->_cstime; }

				void setCUTime(int utime) { _cutime = utime; }
				int getCUTime(void) const { return this->_cutime; }

				void setMemTotal(int memtotal) { _memTotal = memtotal; }
				int getMemTotal(void) const { return this->_memTotal; }
				
				void setRes(long int res) { _res = res; }
				long int getRes(void) const { return this->_res; }

				void setShr(long int shr) { _shr = shr; }
				long int getShr(void) const { return this->_shr; }

				void display() const;

			private:
				const std::string _pid;
				std::string _name;
				std::string _user;
				std::string _state;
				int _virtual = 0;
				int _nice = 0;
				int _priority = 0;
				int _time = 0;
				double _uptime = 0;
				int _stime = 0;
				int _utime = 0;
				int _cutime = 0;
				int _cstime = 0;
				int _memTotal = 0;
				long int _res = 0;
				long int _shr = 0;
		};
		ProcessModule();
		~ProcessModule();
        bool parsing() override;
		bool findUser();
		bool findUserWithUid(const std::string&, const std::string&, Process& i);
		std::vector<ProcessModule::Process> getList() const;
		void fullDisplay() const;
	private:
		std::vector<ProcessModule::Process> _processes;
};

#endif /* !PROCESS_HPP_ */