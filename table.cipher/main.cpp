/** @file
* @author Стригин А.В.
* @version 1.0
* @date 22.12.2019
* @copyright ИБСТ ПГУ
* @brief Главный файл для модуля Table_cipher
*/
#include <iostream>
#include <cctype>
#include <clocale>
#include <string>
#include "table_cipher.h"
#include <boost/program_options.hpp>
namespace po = boost::program_options;
class UI
{
public:

    po::options_description desc;
    po::variables_map vm;
    /**
    * @brief Обрабатываемая строка
    */
    std::string st;
    /**
    * @brief Тип операции
    */
    uint action;
    /**
    * @brief Ключ
    */
    double key;
    /**
    * @brief Конструктор инициализации
    * @details Происходит разбор комстроки, инициализируются st,action,key
    * На основе полученных данных вызывается соответствующий метод table_cipher
    * @param [in] argc Количество параметров комстроки
    * @param [in] argv Значения параметров комстроки
    * @throw table_error, если создании оъекта класса будет выявлена ошибка: текст содержит не буквы, ключ слишком длинный или короткий
    */
    UI(int argc, char* argv[]);
    /**
    * @brief Метод получения типа операции
    * @details Если значение параметра не введено, то выводится справка
    * @return Численное значение типа операции
    */
    uint get_action();
    /**
    * @brief Метод получения ключа
    * @details Если значение параметра не введено, то выводится справка
    * @return Значение ключа
    */
    double get_key();
    /**
    * @brief Метод получения строки
    * @details Если значение параметра не введено, то выводится справка
    * @return Строка для обработки
    */
    std::string get_string();
};
namespace po = boost::program_options;
UI::UI(int argc, char* argv[])
{
    desc.add_options()
    ("help,h", "Помощь")
    ("string,s", po::value<std::vector<std::string>>()->multitoken(), "Строка для проведения операции")
    ("action,a", po::value<std::vector<uint>>()->multitoken(), "1-encrypt, 2-decrypt")
    ("key,k", po::value<std::vector<double>>()->multitoken(), "Количество столбцов в таблице");
    try {
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);
        st=get_string();
        action=get_action();
        key=get_key();
        std::string i_value=" ";
        table_cipher cipher(st,key,i_value);
        if (action==1){
            std::cout<<"Зашифрованная строка: "<<cipher.encrypt()<<std::endl;
        }
        else if (action==2){
            std::cout<<"Расшифрованная строка: "<<cipher.decrypt()<<std::endl;
        }
        else{
            std::cout << desc << std::endl;
            std::exit(1);
        }
    } catch (po::error& e) {
        std::cout << e.what() << std::endl;
        exit(1);
    }
    catch(const table_error & e){
        std::cerr<<"Error: "<<e.what()<<std::endl;
        exit(1);
    }
}
uint UI::get_action()
{
    if (vm.count("action")) {
        const std::vector<uint>& action = vm["action"].as<std::vector<uint>>();
        return action.back();
    } else {
        std::cout << desc << std::endl;
        std::exit(1);
    }
}
double UI::get_key()
{
    if (vm.count("key")) {
        const std::vector<double>& key = vm["key"].as<std::vector<double>>();
        return key.back();
    } else {
        std::cout << desc << std::endl;
        std::exit(1);
    }
}
std::string UI::get_string()
{
    if (vm.count("string")) {
        const std::vector<std::string>& string = vm["string"].as<std::vector<std::string>>();
        return string.back();
    } else {
        std::cout << desc << std::endl;
        return "";
        std::exit(1);
    }
}
int main(int argc, char **argv)
{
    UI interface(argc,argv);
    return 0;
}
