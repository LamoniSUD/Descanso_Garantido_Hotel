#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Pessoa.h"

class Client : public Pessoa
{
private:
    std::string code;
    std::string address;
    std::string contact;
    static int clientCounter;

public:
    Client()
    {
        code = "";
        address = "";
        contact = "";
    }

    void setCode(const std::string &c)
    {
        code = c;
    }

    void setAddress(const std::string &a)
    {
        address = a;
    }

    void setContact(const std::string &c)
    {
        contact = c;
    }

    std::string getCode() const
    {
        return code;
    }

    std::string getAddress() const
    {
        return address;
    }

    std::string getContact() const
    {
        return contact;
    }

    void generateClientCode()
    {
        std::ostringstream oss;
        oss << "CL" << ++clientCounter;
        code = oss.str();
    }

    void saveToFile(const std::string &filename)
    {
        std::ofstream outFile(filename, std::ios::binary | std::ios::app);
        if (!outFile)
        {
            std::cerr << "Erro ao abrir o arquivo para escrita." << std::endl;
            return;
        }

        writeString(outFile, getNome());
        int idade = getAge();
        outFile.write(reinterpret_cast<const char*>(&idade), sizeof(idade));
        writeString(outFile, code);
        writeString(outFile, address);
        writeString(outFile, contact);

        outFile.close();
        std::cout << "Dados salvos com sucesso no arquivo " << filename << std::endl;
    }

    void cadastrarCliente()
    {
        cadastrarC();
        generateClientCode();

        std::cout << "Digite o endereço do cliente: ";
        std::getline(std::cin, address);

        std::cout << "Digite o contato do cliente: ";
        std::getline(std::cin, contact);

        std::cout << "\nCadastro de cliente realizado com sucesso!" << std::endl;
    }

private:
    void writeString(std::ofstream &outFile, const std::string &str)
    {
        size_t length = str.size();
        outFile.write(reinterpret_cast<const char*>(&length), sizeof(length));
        outFile.write(str.c_str(), length);
    }
};

int Client::clientCounter = 0;

#endif // CLIENT_H_INCLUDED
