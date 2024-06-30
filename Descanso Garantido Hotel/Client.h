#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED

#include <iostream>
#include <cstdio>
#include <string>
#include "Pessoa.h"

class Client : public Pessoa
{
private:
    std::string code;
    std::string address;
    std::string contact;
    int pontosFidelidade;
    static int clientCounter;

public:
    Client()
    {
        code = "";
        address = "";
        contact = "";
        pontosFidelidade = 0;
    }

    void setCode(const std::string &c)
    {
        this->code = c;
    }

    void setAddress(const std::string &a)
    {
        this->address = a;
    }

    void setContact(const std::string &c)
    {
        this->contact = c;
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

    int getPontosFidelidade() const
    {
        return pontosFidelidade;
    }

    void addPontosFidelidade(int pontos)
    {
        pontosFidelidade += pontos;
    }

    void generateClientCode()
    {
        clientCounter++;
        code = "CL" + std::to_string(clientCounter);
    }

    void saveToFile(const std::string &filename)
    {
        FILE *outFile = fopen(filename.c_str(), "ab");
        if (!outFile)
        {
            std::cerr << "Erro ao abrir o arquivo para escrita." << std::endl;
            return;
        }

        writeString(outFile, getNome());
        int idade = getAge();
        fwrite(&idade, sizeof(idade), 1, outFile);
        writeString(outFile, code);
        writeString(outFile, address);
        writeString(outFile, contact);
        fwrite(&pontosFidelidade, sizeof(pontosFidelidade), 1, outFile);

        fclose(outFile);
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

    void readFromFile(const std::string &filename)
    {
        FILE *inFile = fopen(filename.c_str(), "rb");
        if (!inFile)
        {
            std::cerr << "Erro ao abrir o arquivo para leitura." << std::endl;
            return;
        }

        while (!feof(inFile))
        {
            std::string nome = readString(inFile);
            setNome(nome);

            int idade;
            fread(&idade, sizeof(idade), 1, inFile);
            setAge(idade);

            std::string code = readString(inFile);
            setCode(code);

            std::string address = readString(inFile);
            setAddress(address);

            std::string contact = readString(inFile);
            setContact(contact);

            int pontosFidelidade;
            fread(&pontosFidelidade, sizeof(pontosFidelidade), 1, inFile);
            addPontosFidelidade(pontosFidelidade);
        }

        fclose(inFile);
    }

    void showInfo()
    {
        std::cout << "Informações do Cliente:" << std::endl;
        std::cout << "Nome: " << getNome() << std::endl;
        std::cout << "Idade: " << getAge() << std::endl;
        std::cout << "Código: " << code << std::endl;
        std::cout << "Endereço: " << address << std::endl;
        std::cout << "Contato: " << contact << std::endl;
        std::cout << "Pontos de Fidelidade: " << pontosFidelidade << std::endl;
    }

    bool searchClient(const std::string &searchTerm)
    {
        // Implemente a lógica de busca aqui
        // Exemplo simples: busca por código ou nome
        return (code == searchTerm || getNome() == searchTerm);
    }

private:
    void writeString(FILE *file, const std::string &str)
    {
        size_t length = str.size();
        fwrite(&length, sizeof(length), 1, file);
        fwrite(str.c_str(), sizeof(char), length, file);
    }

    std::string readString(FILE *file)
    {
        size_t length;
        fread(&length, sizeof(length), 1, file);
        char *buffer = new char[length + 1];
        fread(buffer, sizeof(char), length, file);
        buffer[length] = '\0';
        std::string str(buffer);
        delete[] buffer;
        return str;
    }
};

int Client::clientCounter = 0;

#endif // CLIENT_H_INCLUDED
