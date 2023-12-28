#pragma once
/** @file
* @author Каргин Н.С.
* @version 1.0
* @date 28.12.2023
* @copyright ИБСТ ПГУ
* @warning Курсовая работа студента
* @brief Заголовочный файл для модуля Calculator
*/


/** @brief Класс Calculator
* @details Класс Calculator считает математические операции.
* @warning Реализация только для типа данных uint16_t
*/
class Calculator {
public:
	/**
     * @brief Статический метод для выполнения математических операций
     * @param work_sock рабочий сокет для обработки операций
    */
    static void math(int work_sock);
};
