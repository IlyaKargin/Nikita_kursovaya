#include "Comunicator.h"
#include "ClientBase.h"
#include "ServerError.h"

#include <unistd.h>
#include <netinet/in.h>
#include <random>


#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1

#include <cryptopp/cryptlib.h>
#include <cryptopp/hex.h>
#include <cryptopp/md5.h>

using namespace CryptoPP;

std::string MD(std::string sah)
{
    Weak::MD5 hash;
    std::string digest;
    StringSource(sah, true, new HashFilter(hash, new HexEncoder(new StringSink(digest)))); // строка-приемник
    return digest;
}

int Comunicator::autorized(int work_sock, std::string file_name, std::map<std::string, std::string> &all_names) // аутентификация
{

    std::string ok = "OK";
    std::random_device rnd;
    std::mt19937_64 rnd_generator(rnd());
    uint64_t rnd_number = rnd_generator();
    std::string salt;
    StringSource((const byte *)&rnd_number, 8, true, new HexEncoder(new StringSink(salt)));
    std::string err = "ERR";
    std::vector<char> buffer(256);

    // Авторизация
    int size_m = recv(work_sock, buffer.data(), buffer.size(), 0);
    std::string login(buffer.data(), size_m);

    std::string password = ClientBase::find(login, all_names);
    if (password == "")
    {
        throw ServerError("Неверный логин");
    }
    if (password.empty())
    {
        send(work_sock, err.c_str(), err.length(), 0);
        close(work_sock);
        return 1;
    }

    send(work_sock, salt.c_str(), salt.length(), 0);
    size_m = recv(work_sock, buffer.data(), buffer.size(), 0);
    std::string sah = salt + password;
    std::string digest;
    digest = MD(sah);
    std::string new_msg(buffer.data(), size_m);
    // СВЕРКА HASH
    if (digest != new_msg)
    {
        send(work_sock, err.c_str(), err.length(), 0);
        close(work_sock);
        return 1;
    }
    else
    {
        send(work_sock, ok.c_str(), ok.length(), 0);
    }

    return 1;
}

void Comunicator::Initialize(int port){

    m_socket = socket(AF_INET,SOCK_STREAM,0);

    sockaddr_in sockAddr = {};

    sockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    sockAddr.sin_port = htons(port);
    sockAddr.sin_family = AF_INET;

    auto b = bind(m_socket,(sockaddr*)&sockAddr,sizeof(sockAddr));
    if(b == -1)
        throw ServerError("Binding error\n");
    
    listen(m_socket, SOMAXCONN);
}

int Comunicator::WaitClient(std::map<std::string, std::string> &all_names){
    
    std::unique_ptr<sockaddr_in> client_addr(new sockaddr_in);
    socklen_t len = sizeof(sockaddr_in);
    int m_clientSock = accept(m_socket, reinterpret_cast<sockaddr *>(client_addr.get()), &len); // создание сокета для клиента

    if (m_clientSock == -1)
        throw ServerError("Connection error");

    std::cout << "Successfull client connection!\n";

    autorized(m_clientSock,"logs",all_names);
    return m_clientSock;
}