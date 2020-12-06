/*
** EPITECH PROJECT, 2020
** cpp_rush3_2019
** File description:
** Process
*/

#include "ProcessModule.hpp"

#include <time.h>

ProcessModule::~ProcessModule()
{
}

ProcessModule::ProcessModule()
{
}

static std::string find_elem(const std::string& s)
{
    std::string save;
    for (int i = 0; s[i]; ++i) {
        if (s[i] <= '9' && s[i] >= '0')
            save += s[i];
        if (!save.empty() && (s[i] > '9' || s[i] < '0'))
            return save;
    }
    return save;
}

std::string readfile(const std::string& f)
{
    std::string buff;
    std::ifstream myfile (f);

    if (!myfile.is_open()) {
        std::cerr << "Can't open " << f << std::endl;
        return nullptr;
    }
    std::getline(myfile, buff, '\n');
    myfile.close();
    return buff;
}

bool isStringDigit(const std::string& file)
{
    for (int i = 0; file[i]; ++i)
        if (file[i] < '0' || file[i] > '9')
            return false;
    return true;
}

std::vector<ProcessModule::Process> ProcessModule::getList() const
{
    return _processes;
}

bool ProcessModule::parsing()
{
    this->_processes.clear();
    const char* PATH = "/proc/";
    DIR *dir = opendir(PATH);

    struct dirent *entry = readdir(dir);
    if (entry == nullptr) {
        std::cerr << "Can't open directory /proc"  << std::endl;
        return false;
    }
    while (entry != nullptr)
    {
        if (entry->d_type == DT_DIR)
            if (isStringDigit(entry->d_name))
                _processes.push_back(Process(entry->d_name));
        entry = readdir(dir);
    }
    closedir(dir);


    for (auto & process : _processes)
    {
        std::string fileName = "/proc/";
        fileName += process.getPid();
        fileName += "/cmdline";

        std::ifstream stream(fileName);

        if (!stream.is_open())
        {
            std::cerr << "Can't get process cmdline." << std::endl;
            return false;
        }

        std::string buffer;
        std::getline(stream, buffer, '\0');
        process.setName(buffer);
        stream.close();
    }
    for (auto & process : _processes)
    {
        std::string fileName = "/proc/";
        fileName += process.getPid();
        fileName += "/stat";

        std::ifstream stream(fileName);

        if (!stream.is_open())
        {
            std::cerr << "Can't get process " << process.getPid() << "stat." << std::endl;
            return false;
        }

        std::string buff;


        std::getline(stream, buff, '\0');
        buff.erase(buff.find("("), buff.find(")") - buff.find("(") + 1);
        char *parsed = strtok((char *)buff.c_str(), ": \t");

        std::vector<char *> lParsed;
        while (parsed != NULL)
        {
            lParsed.push_back(parsed);
            parsed = std::strtok(NULL, " \t");
        }
        process.setTime(atoi(lParsed[22-2]));
        process.setState(lParsed[3-2]);
        process.setVirtual(atoi(lParsed[23-2]));
        process.setNice(atoi(lParsed[19-2]));
        process.setPriority(atoi(lParsed[18-2]));
        process.setUTime(atoi(lParsed[14-2]));
        process.setSTime(atoi(lParsed[15-2]));
        stream.close();
    }
    for (auto & process : _processes)
    {
        std::string fileName = "/proc/";
        fileName += process.getPid();
        fileName += "/status";

        std::ifstream stream(fileName);

        if (!stream.is_open())
        {
            std::cerr << "Can't get process " << process.getPid() << "stat." << std::endl;
            return false;
        }
        std::string buff;

        std::vector<std::string> lParsed;
        while (std::getline(stream, buff, '\n')) {
            if (buff.find("VmRSS") != std::string::npos  ||
            buff.find("RssFile")   != std::string::npos ||
            buff.find("RssShmem")  != std::string::npos) 
            {
                lParsed.push_back(buff);
            }
        }

        for (auto & line: lParsed)
        {
            char *parsed = strtok((char *)line.c_str(), ": \t");
            if (std::string(parsed).find("VmRSS") != std::string::npos) {
                parsed = std::strtok(NULL, ": \t");
                process.setRes(atol(parsed));
            } else if (std::string(parsed).find("RssFile") != std::string::npos
                    || std::string(parsed).find("RssShmem") != std::string::npos) {
                parsed = std::strtok(NULL, ": \t");
                process.setShr(process.getShr() + atol(parsed));
            }
        }
        
        stream.close();
    }

    for (auto & process : _processes)
    {
        std::string str("/sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_max_freq");
        std::ifstream streamCore(str);

        if (!streamCore.is_open())
        {
            std::cerr << "Cannot access " << str << std::endl;
            return false;
        }

        std::string buff;
        std::getline(streamCore, buff, '\0');

        streamCore.close();

        std::string str1("/proc/uptime");
        std::ifstream streamCor(str1);

        if (!streamCor.is_open())
        {
            std::cerr << "Cannot access " << str1 << std::endl;
            return false;
        }

        std::string buffer;
        std::getline(streamCor, buffer, '\0');

        process.setUpTime(stod(buffer.substr(0, buffer.find(" "))));
        streamCor.close();
    }

    findUser();
    return true;
}

bool ProcessModule::findUserWithUid(const std::string& s, const std::string& buff, Process& i)
{
    char *pch = strtok ((char*)buff.c_str(),":");
    pch = strtok (NULL, ":");
    pch = strtok (NULL, ":");

    if (pch == s) {
        i.setUser((std::string)(strtok((char*)buff.c_str(),":")));
        return true;
    }
    return false;
}

bool ProcessModule::findUser()
{
    std::string buff;
    std::string save;

    for (auto & i : _processes) {
        std::string file = "/proc/";
        file += i.getPid();
        file += "/status";

        std::ifstream sstream(file);

        if (!sstream.is_open()) {
            std::cerr << "Can't get process " << i.getPid() << "stat." << std::endl;
            return false;
        }
        while (std::getline(sstream, buff, '\n')) {
            if (buff.find("Uid", 0) != std::string::npos) {
                save = find_elem(buff);
                break;
            }
        }

        sstream.close();
        std::ifstream f("/etc/passwd");

        if (!f.is_open()) {
            std::cout << "Can't get process " << "/etc/passwd" << std::endl;
            return false;
        }
        while (std::getline(f, buff, '\n')) {
            if (findUserWithUid(save, buff, i)) {
                break;
            }
        }
        f.close();
    }
    return true;
}

void ProcessModule::Process::display() const
{
    std::cout << "PID: " << _pid << std::endl;
    std::cout << "\tName: " << _name << std::endl;
    std::cout << "\tUser: " << _user << std::endl;
    std::cout << "\tState: " << _state << std::endl;
    std::cout << "\tVirtual: " << _virtual << std::endl;
    std::cout << "\tNice: " << _nice << std::endl;
    std::cout << "\tPriority: " << _priority << std::endl;
    std::cout << "\tTime: " << _time << std::endl;
    std::cout << "\tUpTime: " << _uptime << std::endl;
    std::cout << "\tSTime: " << _stime << std::endl;
    std::cout << "\tUTime: " << _utime << std::endl;
    std::cout << "\tMemTotal: " << _memTotal << std::endl;
    std::cout << "\tres: " << _res << std::endl;
    std::cout << "\tshr: " << _shr << std::endl;
}

void ProcessModule::fullDisplay() const
{
    for (const auto process : _processes)
        process.display();
}
