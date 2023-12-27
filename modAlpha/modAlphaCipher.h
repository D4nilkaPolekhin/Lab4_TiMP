/** @file
* @author Стригин А.В.
* @version 1.0
* @date 22.12.2019
* @copyright ИБСТ ПГУ
* @brief Заголовочный файл для модуля Gronsfeld
*/
#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <map>
#include <cctype>
#include <locale>
/** @brief Шифрование методом Гронсфельда
* @details Ключ устанавливается в конструкторе.
* Для зашифровывания и расшифровывания предназначены методы encrypt и decrypt.
* @warning Реализация только для русского языка
*/
class modAlphaCipher
{
private:
    /**
    * @brief Алфавит по порядку
    */
    std::wstring numAlpha = L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
    /**
    * @brief Ассоциативный массив "номер по символу"
    */
    std::map <wchar_t,int> alphaNum;
    /**
    * @brief Ключ
    */
    std::vector <int> key;
    /**
    * @brief Преобразование строка-вектор
    */ 
    std::vector<int> convert(const std::wstring& s); 
    /**
    * @brief Преобразование вектор-строка
    */
    std::wstring convert(const std::vector<int>& v); 
    /**
    * @brief Обработка ошибок ключа
    * @details Строчные символы автоматически преобразуются к
    прописным.
    * Все не-буквы удаляются
    * @param [in] key Ключ. Не должен быть пустой строкой
    * @return Обработаный ключ
    * @throw cipher_error, если ключ пустой или присутствуют символы, не входящие в алфавит
    */
    std::wstring getValidKey(const std::wstring & s); //обработка ошибок при инициализации ключа
    /**
    * @brief Обработка ошибок открытого текста
    * @details Строчные символы автоматически преобразуются к
    прописным.
    * Все не-буквы удаляются
    * @param [in] open_text Открытый текст. Не должен быть пустой строкой.
    * @return Обработаный открытый текст
    * @throw cipher_error, если открытый текст пустой или присутствуют символы, не входящие в алфавит
    */
    std::wstring getValidOpenText(const std::wstring & s);//обработка ошибок при вводе открытого текста
    /**
    * @brief Обработка ошибок шифро текста
    * @details Строчные символы автоматически преобразуются к
    прописным.
    * Все не-буквы удаляются
    * @param [in] cipher_text Шифро текст. Не должен быть пустой строкой.
    * @return Обработаный шифро текст
    * @throw cipher_error, если шифро текст пустой или присутствуют символы, не входящие в алфавит
    */
    std::wstring getValidCipherText(const std::wstring & s);//обработка ошибок при вводе шифро текста
public:
    /**
    * @brief Запретим конструктор без параметров
    */
    modAlphaCipher()=delete;
    /**
    * @brief Конструктор для установки ключа
    */
    modAlphaCipher(const std::wstring& skey);
    /**
    * @brief Зашифрование
    * @details Строчные символы автоматически преобразуются к
    прописным.
    * Все не-буквы удаляются
    * @param [in] open_text Открытый текст. Не должен быть пустой строкой.
    * @return Зашифрованная строка
    * @throw cipher_error, если текст пустой или присутствуют символы, не входящие в алфавит
    */
    std::wstring encrypt(const std::wstring& open_text); //зашифрование
    /**
    * @brief Расшифрование
    * @details Строчные символы автоматически преобразуются к
    прописным.
    * Все не-буквы удаляются
    * @param [in] cipher_text Шифро текст. Не должен быть пустой строкой.
    * @return Расшифрованная строка
    * @throw cipher_error, если текст пустой или присутствуют символы, не входящие в алфавит
    */
    std::wstring decrypt(const std::wstring& cipher_text);//расшифрование
    
};
/** @brief Класс ошибок для шифрования методом Гронсфельда
* @details Используется для указания специфических ошибок при работе с шифром
* @warning Вывод сообщений об ошибках только на английском языке
*/
class cipher_error: public std::invalid_argument
{
public:
    explicit cipher_error (const std::string& what_arg):
        std::invalid_argument(what_arg) {}
    explicit cipher_error (const char* what_arg):
        std::invalid_argument(what_arg) {}
};
