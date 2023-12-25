/** @file
* @author Полехин Даниил
* @version 1.0
* @date 20.12.2023
* @warning Тренировочная работа
* @brief Заголовочный файл для модуля шифрования методом перестановки
*/
#pragma once
#include <vector>
#include <string>
#include <map>
#include <codecvt>
#include <iostream>
#include <locale>
/** @brief Шифрование методом маршрутной перестановки
* @details Ключ устанавливается в конструкторе.
* Для зашифровывания и расшифровывания предназначены методы encrypt и decrypt.
* @warning Ипользуется только для русского текста
*/
class Table
{
private:
    std::wstring numAlpha =
        L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"; ///<Русский алфавит заглавными буквами
    std::wstring lnumAlpha =
        L"абвгдеёжзийклмнопрстуфхцчшщъыьэюя"; ///<Русский алфавит заглавными буквами
    uint key; ///<ключ
    std::map <int, std::wstring> subNum; ///<словарь "субстрока по номеру"(для зашифровки)
    std::map <int, std::wstring> resubNum; ///<словарь "субстрока по номеру"(для расшифровки)
    /**
    * @brief Проверка символа на принадлежность к русскому алфавиту
    * @param [in] wc Символ wchar
    * @return Да или нет
    */
    bool is_rus(wchar_t wc);
    /**
    * @brief Проверка символа на принадлежность к строчным буквам р. алфавита
    * @details Находит позицию, на которой стоит в русском
    * алфавите указанный символ
    * @param [in] wch Символ wchar
    * @return Позиция символа
    */
    int is_low_rus(wchar_t wch);
    /**
       * @brief Метод валидации строки
       * @details Может преобразовывать строчные буквы в заглавные
       * @param [in] s Строка текста. Не может быть пустой.
       * Также в ней не должны присутствовать пробелы,
       * цифры и знаки пунктуации
       * @return Валидированная строка
       * @throw cipher_error, если строка не соответствует
       * требованиям, описанным выше
       */
    std::wstring toValidtext(const std::wstring& s);
public:

    Table()=delete; ///<Запрет конструктора без параметров
    /**
    * @brief Констркутор для установки ключа
    * @details Записывает в переменную класса
    * ключ в виде цифры
    * @param [in] skey Целочисленный ключ
    * @throw cipher_error, если ключ меньше, либо равен единице
    */
    Table(const int skey);
    /**
    * @brief Функция зашифрования
    * @details Шифрует строку методом маршрутной перестановки
    * @param [in] open_text Строка с текстом для зашифрования
    * @throw cipher_error, если возбуждается исключение
    * в методе валидации toValidtext
    */
    std::wstring encrypt(const std::wstring& open_text);
    /**
    * @brief Функция расшифрования
    * @details Расшифровывает сроку по методу маршрутной перестановки
    * @param [in] cipher_text Строка с зашифрованным текстом
    * @throw cipher_error, если возбуждается исключение
    * в методе валидации toValidtext
    */
    std::wstring decrypt(const std::wstring& cipher_text);//расшифрование

};
/** @brief Пользовательский класс исключений
* @details Класс-наследник класса invalid_argument.
* Создан для того чтобы специально отслеживать исключения,
* возбуждаемые в процессе шифрования
*/
class cipher_error: public std::invalid_argument
{
public:
    explicit cipher_error (const std::string& what_arg):
        std::invalid_argument(what_arg) {}
    explicit cipher_error (const char* what_arg):
        std::invalid_argument(what_arg) {}
};
