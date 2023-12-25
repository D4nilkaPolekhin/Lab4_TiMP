#include <iostream>
#include <table.h>
#include <locale>
#include <typeinfo>
// проверка, чтобы строка состояла только из прописных букв

int main(int argc, char **argv)
{
    try {
        std::locale loc("ru_RU.UTF-8");
        std::locale::global(loc);
        int key;
        std::wstring text;
        unsigned op;
        std::wcout<<"Cipher ready. Input key: ";
        std::wcin>>key;
        std::wcout<<"Key loaded\n";
        Table cipher(key); //конструктор
        do {
            std::wcout<<"Cipher ready. Input operation (0-exit, 1-encrypt, 2-decrypt): ";
            std::wcin>>op;
            if (op > 2) {
                throw(cipher_error("Illegal operation\n"));
            } else if (op >0) {
                std::wcout<<"Cipher ready. Input text: ";
                std::wcin.ignore();
                std::getline(std::wcin,text);
                if (op==1) {
                    std::wcout<<"Encrypted text: "<<cipher.encrypt(text)<<std::endl;
                } else {
                    std::wcout<<"Decrypted text: "<<cipher.decrypt(text)<<std::endl;
                }
            }
        } while (op!=0);

    } catch(const cipher_error& e) {
        std::wcerr<<e.what()<<std::endl;
    }
    return 0;
}
