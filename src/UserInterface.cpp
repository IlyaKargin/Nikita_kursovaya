#include "UserInterface.h"

#include "Comunicator.h"
#include "ServerError.h"



UserInterface::UserInterface(int argc, char **argv)
{
    m_descr.add_options()
        ("help,h", "Помощь")
        ("file,f", po::value<std::string>(&m_UsersFile), "введите имя файла с базой клиентов")
        ("logwrite,l", po::value<std::string>(&m_logFilePath), "введите имя файла с журналом работы")
        ("port,p", po::value<int>(&port), "введите номер порта");
        
    po::store(po::command_line_parser(argc, argv).options(m_descr).run(), m_vm);
    po::notify(m_vm);

    if (m_vm.count("help") or m_vm.empty())
    {
        m_descr.print(std::cout);
        exit(0);
    }
}

void UserInterface::operator()()
{
    Comunicator com;
    ClientBase clientBase;

    try{

        m_logs = Logs(m_logFilePath);
        m_users = clientBase.read(m_UsersFile);
        com.Initialize(port);

    }catch(ServerError err){
        m_logs.Error(err.what());   
        return;
    }

    m_logs.Info("Initialization succsessfull");

    while (true)
    {
        try{
            auto clientSock =  com.WaitClient(m_users);
            Calculator::math(clientSock);
        }
        catch(ServerError err){
            m_logs.Warning(err.what());
            close(com.getClientSocket()); 
        }
    }
}
