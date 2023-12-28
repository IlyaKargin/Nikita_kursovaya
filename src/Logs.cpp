#include "Logs.h"

#include "ServerError.h"

#include <ctime>
#include <memory>
#include <string>

void Logs::Info(std::string str)
{
    auto msg = makeTimestamp() + " INFO " + str + "\n";

    std::cout<<msg;
    m_logFile<<msg;
}

void Logs::Warning(std::string str)
{
    auto msg = makeTimestamp() + " WARNING " + str + "\n";

    std::cout<<msg;
    m_logFile<<msg;
}

void Logs::Error(std::string str)
{
    auto msg = makeTimestamp() + " ERROR " + str + "\n";

    std::cout<<msg;
    m_logFile<<msg;
}

std::string Logs::makeTimestamp()
{

    std::time_t now;
    std::time(&now);
    
    std::string buffer = "yyyy-mm-dd-hh-mm-ss";

    std::strftime((char*)buffer.data(), buffer.length(), "%F%T", std::localtime(&now));
    
    return buffer;
}

Logs::Logs(std::string pathToFile)
{
    m_logFile.open(pathToFile, std::ios_base::app | std::ios_base::out);

    if (!m_logFile.is_open())
        throw ServerError("Invalid file");
}
