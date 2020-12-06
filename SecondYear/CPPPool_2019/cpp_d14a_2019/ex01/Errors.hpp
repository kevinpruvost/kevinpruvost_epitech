
#ifndef ERRORS_HPP_
#define ERRORS_HPP_

#include <string>

class NasaError : virtual public std::exception
{
    public:
        NasaError(std::string const &message,
                  std::string const &component = "Unknown");

        const char * what() const noexcept override;
        const std::string &getComponent() const;
    private:
        std::string _message;
        const std::string _component;
};

class MissionCriticalError : virtual public NasaError
{
    public:
        MissionCriticalError(std::string const &message,
                std::string const &component = "Unknown");
};

class LifeCriticalError : virtual public NasaError
{
    public:
        LifeCriticalError(std::string const &message,
                std::string const &component = "Unknown");
};

class UserError : virtual public NasaError
{
    public:
        UserError(std::string const &message,
                std::string const &component = "Unknown");
};

class CommunicationError : virtual public NasaError
{
    public:
        CommunicationError(std::string const &message);
};

#endif
