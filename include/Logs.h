#pragma once
/** @file
* @author Каргин Н.С.
* @version 1.0
* @date 20.12.2023
* @copyright ИБСТ ПГУ
* @warning Курсовая работа студента
* @brief Заголовочный файл для модуля Logs
*/


/** @brief Класс Logs
* @details Класс Logs отвечает за регистрацию информации и ошибок сервера.
* @warning Реализация только для типа данных uint16_t
*/
#include <iostream>
#include <fstream>

class Logs{

public:
	/**
     * @brief Конструктор по умолчанию для класса Logs
    */
    Logs(){}
    /**
     * @brief Конструктор для класса Logs
     * @param pathToFile Путь к файлу журнала.
    */
    Logs(std::string pathToFile);
	/**
     * @brief Регистрирует данное информационное сообщение.
     * @param str Информационное сообщение, которое необходимо записать в журнал.
    */
    void Info(std::string str);
    /**
     * @brief Регистрирует данное предупреждающее сообщение.
     * @param str Предупреждающее сообщение, которое необходимо записать в журнал.
    */
    void Warning(std::string str);
    /**
     * @brief Регистрирует данное сообщение об ошибке
     * @param str Сообщение об ошибке, которое необходимо записать в журнал.
    */
    void Error(std::string str);
private:
	/**
     * @brief Генерирует временную метку для сообщения журнала.
     * @return Временная метка в виде строки.
    */
    std::string makeTimestamp();
    std::fstream m_logFile;
};
