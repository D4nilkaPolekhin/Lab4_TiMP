/** @file
* @author Стригин А.В.
* @version 1.0
* @date 22.12.2019
* @copyright ИБСТ ПГУ
* @brief Заголовочный файл для модуля Table_cipher
*/
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
/** @brief Шифрование методом табличной маршрутной перестановки
* @details Ключ устанавливается в конструкторе.
* Для зашифровывания и расшифровывания предназначены методы encrypt и decrypt.
* @warning Реализация только для английского языка
*/
class table_cipher{
    private:
    uint key;
    double rows;
    std::string i_value;
    std::string t;
    std::vector<std::vector<std::string>> st_to_vec;
    /**
    * @brief Запись строки в двумерный массив для метода encrypt
    * @details Строчные символы автоматически преобразуются к
    прописным.
    * @details Вектор, переданный по ссылке заполняется значениями
    * @param [in] open_text Открытый текст. Не должен быть пустой строкой.
    * @param [in] vector Двумерный массив для записи строки
    * @return Функция ничего не возвращает
    * @throw table_error, если текст пустой или присутствуют символы не-бувы
    */
    void write_str_to_v(std::string st,std::vector<std::vector<std::string>> &v);
    /**
    * @brief Запись строки в двумерный массив для метода decrypt
    * @details Вектор, переданный по ссылке заполняется значениями
    * @param [in] vector Двумерный массив для записи строки
    * @return Функция ничего не возвращает
    * @throw table_error, если текст пустой или присутствуют символы не-бувы
    */
    void write_str_to_v(std::vector<std::vector<std::string>> &v);
    public:
    /**
    * @brief Шифрование 
    * @details Строка для операции инициализируется в конструкторе класса
    * @return Функция возвращает зашифрованную строку
    */
    std::string encrypt();
    /**
    * @brief Расшифрование 
    * @details Строка для операции инициализируется в конструкторе класса
    * @return Функция возвращает расшифрованную строку
    */
    std::string decrypt();
    /**
    * @brief Обработка ошибок в строке для операции 
    * @details Строчные буквы в строке преобразует в заглавные
    * @param [in] text Обрабатываемая строка
    * @return Функция ничего не возвращает
    * @throw table_error, если текст пустой или присутствуют символы не-бувы
    */
    void text_validation(std::string &text);
    /**
    * @brief Обработка ошибок ключа 
    * @details Просиходит проверка длины ключа
    * @param [in] key Обрабатываемый ключ
    * @param [in] text Обрабатываемая строка
    * @return Функция ничего не возвращает
    * @throw table_error, если ключ = 1 или ключ больше длины строки
    */
    void key_validation(uint &key,std::string &text);
    /**
    * @brief Конструктор для установки обрабатываемой строки, ключа и начального значения двумерного вектора
    */
    table_cipher(std::string text,double k,std::string& initial_value);
    
};
/** @brief Класс ошибок для модуля Table_cipher
* @details Класс ошибок для специфичных исключений, возникающих при работе шифра
* @warning Реализация только для английского языка
*/
class table_error: public std::invalid_argument
{
public:
    explicit table_error (const std::string& what_arg):
        std::invalid_argument(what_arg) {}
    explicit table_error (const char* what_arg):
        std::invalid_argument(what_arg) {}
};
