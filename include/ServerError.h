#pragma once
/** @file
* @author Каргин Н.С.
* @version 1.0
* @date 20.12.2023
* @copyright ИБСТ ПГУ
* @warning Курсовая работа студента
* @brief Заголовочный файл для модуля ServerError
*/


/** @brief Класс ServerError
* @details Класс ServerError отвечает за обработку ошибок сервера.
* @warning Реализация только для типа данных uint16_t
*/
#include <stdexcept>

class ServerError : public std::runtime_error{
public:
  	/**
     * @brief Конструктор класса ServerError
     * @param msg - сообщение об ошибке
    */
    ServerError(const char *msg) : std::runtime_error(msg){};
};
