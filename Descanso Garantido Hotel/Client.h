#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Pessoa.h"

using namespace std;

class Client : public Pessoa
{
private:
    string code;
    string address;
    string contact;
    static int clientCounter;

public:
    Client()
    {
        code = "";
        address = "";
        contact = "";
    }

    void setCode(string &c)
    {
        code = c;
    }

    void setAddress(string &a)
    {
        address = a;
    }

    void setContact(string &c)
    {
        contact = c;
    }

    string getCode()
    {
        return code;
    }

    string getAddress()
    {
        return address;
    }

    string getContact()
    {
        return contact;
    }

    void generateClientCode()
    {
        ostringstream oss;
        oss << "CL" << ++clientCounter;
        code = oss.str();
    }

    void saveToFile(string &filename)
    {
        ofstream outFile(filename, ios::binary | ios::app);
        if (!outFile)
        {
            cerr << "Erro ao abrir o arquivo para escrita." << endl;
            return;
        }

        writeString(outFile, getNome());
        int idade = getIdade();
        outFile.write(reinterpret_cast<const char*>(&idade), sizeof(idade));
        writeString(outFile, code);
        writeString(outFile, address);
        writeString(outFile, contact);

        outFile.close();
        cout << "Dados salvos com sucesso no arquivo " << filename << endl;
    }

    void cadastrarCliente()
    {
        cadastrar();
        generateClientCode();

        cout << "Digite o endereço do cliente: ";
        getline(cin, address);

        cout << "Digite o contato do cliente: ";
        getline(cin, contact);

        cout << "\nCadastro de cliente realizado com sucesso!" << endl;
    }

private:
    void writeString(ofstream &outFile, string &str)
    {
        size_t length = str.size();
        outFile.write(reinterpret_cast<const char*>(&length), sizeof(length));
        outFile.write(str.c_str(), length);
    }
};

int Client::clientCounter = 0;

#endif // CLIENT_H_INCLUDED
