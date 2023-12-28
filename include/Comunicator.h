#pragma once

#include <iostream>
#include <map>
/** @file
* @author Каргин Н.С.
* @version 1.0
* @date 28.12.2023
* @copyright ИБСТ ПГУ
* @warning Курсовая работа студента
* @brief Заголовочный файл для модуля Comunicator
*/


/** @brief Класс Comunicator
* @details Класс Comunicator отвечает за связь между клиентом и сервером.
* @warning Реализация только для типа данных uint16_t
*/
class Comunicator
{
public:
   	/**
     * @brief Инициализирует коммуникатор
     * @param port - порт для подключения
     */
    void Initialize(int port);
     /**
     * @brief Ожидает клиента и получает все имена
     * @param all_names - словарь со всеми именами
     * @return возвращает код результата
     */
    int WaitClient(std::map<std::string, std::string> &all_names);
	  /**
     * @brief Возвращает сокет клиента
     * @return сокет клиента
     */
    int getClientSocket(){return m_clientSock;}

private:
	  /**
     * @brief Проверяет авторизацию клиента
     * @param work_sock - сокет клиента
     * @param file_name - имя файла
     * @param all_names - словарь со всеми именами
     * @return возвращает код результата
     */
    int autorized(int work_sock, std::string file_name,std::map <std::string,std::string> &all_names);
    
    int m_socket = 0;
    int m_clientSock = 0;
};
