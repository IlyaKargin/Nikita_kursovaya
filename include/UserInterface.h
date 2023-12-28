#pragma once
/** @file
* @author Каргин Н.С.
* @version 1.0
* @date 20.12.2023
* @copyright ИБСТ ПГУ
* @warning Курсовая работа студента
* @brief Заголовочный файл для модуля UsersInterface
*/


/** @brief Класс UsersInterface
* @details Класс UsersInterface отвечает за инициализацию и запуск сервера.
* @warning Реализация только для типа данных uint16_t
*/
#include "Calculator.h"
#include "ClientBase.h"
#include "Logs.h"

#include <boost/program_options.hpp>


namespace po = boost::program_options;

class UserInterface
{
public:
	/**
     * @brief Конструктор по умолчанию для класса UserInterface.
    */
    UserInterface(){}
    /**
     * @brief Конструктор для класса UserInterface.
     * @param argc Количество аргументов командной строки.
     * @param argv Аргументы командной строки.
    */
    UserInterface(int argc, char **argv);
    /**
     * @brief Перегруженный оператор вызова функции.
     * Эта функция является точкой входа в класс UserInterface.
    */
    void operator()();

private:
    po::options_description m_descr;
    po::variables_map m_vm;
    
    std::string m_UsersFile;
    std::string m_logFilePath;

    Logs m_logs;

    std::map <std::string,std::string> m_users;

    int port;
};
