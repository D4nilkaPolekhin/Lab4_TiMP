/** @file
* @author Полехин Даниил
* @version 1.0
* @date 20.12.2023
* @warning Тренировочная работа
* @brief Заголовочный файл для модуля шифрования методом Гронсфельда
*/
#pragma once
#include <vector>
#include <string>
#include <map>
#include <stdexcept>
#include <locale>
#include <codecvt>
#include <cwctype>
/** @brief Шифрование методом Гронсфельда
* @details Ключ устанавливается в конструкторе.
* Для зашифровывания и расшифровывания предназначены методы encrypt и decrypt.
* Ключ преобразовавается методом convert
* @warning Ипользуется только для русского текста
*/
class modAlphaCipher
{
private:
    std::wstring numAlpha =
        L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"; ///<Русский алфавит заглавными буквами
    std::wstring lnumAlpha =
        L"абвгдеёжзийклмнопрстуфхцчшщъыьэюя"; ///<Русский алфавит заглавными буквами
    std::map <char,int> alphaNum; ///<словарь "номер по символу"
    std::vector <int> key; ///<ключ
    /**
    * @brief Метод для преобразования строка-вектор
    * @details Каждой букве ставится в соответствие
    * номер по порядку согласно алфавиту
    * @param [in] s Строка для преобразования
    * @return Вектор пизиций букв из исходной строки
    */
    std::vector<int> convert(const std::wstring& s);
    /**
    * @brief Метод для преобразования вектор-строка
    * @details Согласно каждой позиции в векторе
    * подбирается соотв. буква из алфавита
    * @param [in] v Вектор с алфав. позициями букв
    * @return Строка
    */
    std::wstring convert(const std::vector<int>& v);
    /**
    * @brief Метод валидации строки
    * @details Может преобразовывать строчные буквы в заглавные
    * @param [in] s Строка текста. Не может быть пустой.
    * Также в ней не должны присутствовать пробелы,
    * цифры и знаки пунктуации.
    * @param [in] obj объект со значением "ключ" или "строка",
    * имеет косметическое назначение, вставляется в строку описания
    * исключения, чтобы не делать 2 метода валидации для ключа и
    * для строки
    * @return Валидированная строка
    * @throw cipher_error, если строка не соответствует
    * требованиям, описанным выше
    */
    std::wstring toValidtext(const std::wstring& s, std::string obj);
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
public:
    modAlphaCipher()=delete; ///<Запрет конструктор без параметров
    /**
    * @brief Конструктор для установки ключа
    * @details Записывает в переменную класса вектор
    * позиций букв, полученный из строки с помощью convert
    * @param [in] skey Строка-ключ, валидируется с
    * помощью метода toValidtext
    * @throw cipher_error, если строка не
    * проходит валидацию метода toValidtext
    */
    modAlphaCipher(const std::wstring& skey) 
    {
        for (unsigned i=0; i<numAlpha.size(); i++) {
            alphaNum[numAlpha[i]]=i;
        }
        key = convert(toValidtext(skey, "key"));
    }
    /**
    * @brief Функция зашифрования
    * @details Шифрует строку методом Гронсфельда
    * @param [in] open_text Строка с текстом для шифрования,
    * валидируется с помощью toValidtext
    * @throw cipher_error, если строка не
    * проходит валидацию метода toValidtext
    */
    std::wstring encrypt(const std::wstring& open_text); //зашифрование
    /**
    * @brief Функция расшифрования
    * @details Расшифровывает строку по методу Гронсфельда
    * @param [in] cipher_text Строка с зашифрованным текстом,
    * валидируется с помощью toValidtext
    * @throw cipher_error, если строка не
    * проходит валидацию метода toValidtext
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
