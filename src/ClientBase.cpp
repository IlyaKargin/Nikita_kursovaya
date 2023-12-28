#include "ClientBase.h"
#include "ServerError.h"

#include <fstream>

std::map <std::string,std::string> ClientBase::read(std::string pathToFile)
{
    std::map <std::string,std::string> all;
    std::string line;
    std::ifstream file(pathToFile,std::ios_base::app|std::ios_base::in);

    if(!file.is_open()){
        throw ServerError("Invalid file");
    }

    if (file.peek() == EOF){
        throw ServerError("File is empty");
    }
    
    while(std::getline(file,line)) {
        auto index = line.find_first_of(':');
        std::string first = line.substr(0,index);
        std::string second = line.substr(index+1,line.size());
        all.insert({first,second});
    }
        file.close();
    return all;
}
std::string ClientBase::find(std::string &name, std::map< std::string, std::string > &all)
{
    auto res = all.find(name);
    if(res != all.end())
        return res->second;
    return "";
}
