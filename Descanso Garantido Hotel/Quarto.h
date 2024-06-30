#ifndef QUARTO_H_INCLUDED
#define QUARTO_H_INCLUDED

#include <iostream>
#include <cstdio>
#include <string>
/*classe Quarto
Representa um quarto, com seus atributos número, quantidade de hóspedes
valor da diária e se está ou não ocupado
*/
class Quarto
{
private:
    std::string numeroQuarto;
    int quantidadeHospedes;
    double valorDiaria;
    bool ocupado;
    std::string codigoEstadia;

public:
    Quarto()//Construtor parametrizado(ou personalizado)
        : numeroQuarto(""), quantidadeHospedes(0), valorDiaria(0.0), ocupado(false), codigoEstadia("") {}
//define o número do quarto
    void setNumeroQuarto(const std::string& num)
    {
        this->numeroQuarto = num;
    }
//Define a quantidade de Hospedes
    void setQuantidadeHospedes(int hospedes)
    {
        this->quantidadeHospedes = hospedes;
    }
//Define o Valor da diária
    void setValorDiaria(double valor)
    {
        this->valorDiaria = valor;
    }
//Define se está ocupado ou não
    void setOcupado(bool estado)
    {
        this->ocupado = estado;
    }
//Define o código da estadia
    void setCodigoEstadia(const std::string& cod)
    {
        this->codigoEstadia = cod;
        ocupado = !cod.empty(); // Se há código de estadia, o quarto está ocupado
    }

    std::string getNumeroQuarto() const
    {
        return numeroQuarto;
    }
//Obtém a quantidade de hóspedes
    int getQuantidadeHospedes() const
    {
        return quantidadeHospedes;
    }
//Obtém o valor da Diária
    double getValorDiaria() const
    {
        return valorDiaria;
    }
//Obtém o status se está ocupado ou não
    bool getOcupado() const
    {
        return ocupado;
    }

    std::string getCodigoEstadia() const
    {
        return codigoEstadia;
    }
//Salva os dado no quarto no arquivo binário
    void saveToFile(const std::string& filename)
    {
        FILE* outFile = fopen(filename.c_str(), "ab");
        if (!outFile)
        {
            std::cerr << "Erro ao abrir o arquivo para escrita." << std::endl;
            return;
        }

        writeString(outFile, numeroQuarto);
        fwrite(&quantidadeHospedes, sizeof(quantidadeHospedes), 1, outFile);
        fwrite(&valorDiaria, sizeof(valorDiaria), 1, outFile);
        fwrite(&ocupado, sizeof(ocupado), 1, outFile);
        writeString(outFile, codigoEstadia);

        fclose(outFile);
        std::cout << "Dados do quarto salvos com sucesso no arquivo " << filename << std::endl;
    }
//Lê os dados do quarto em um arquivo binário
    void readFromFile(const std::string& filename)
    {
        FILE* inFile = fopen(filename.c_str(), "rb");
        if (!inFile)
        {
            std::cerr << "Erro ao abrir o arquivo para leitura." << std::endl;
            return;
        }

        while (!feof(inFile))
        {
            numeroQuarto = readString(inFile);
            fread(&quantidadeHospedes, sizeof(quantidadeHospedes), 1, inFile);
            fread(&valorDiaria, sizeof(valorDiaria), 1, inFile);
            fread(&ocupado, sizeof(ocupado), 1, inFile);
            codigoEstadia = readString(inFile);
        }

        fclose(inFile);
    }

private:
    //Escreve os dados no arquivo binário
    void writeString(FILE* file, const std::string& str)
    {
        size_t length = str.size();
        fwrite(&length, sizeof(length), 1, file);
        fwrite(str.c_str(), sizeof(char), length, file);
    }
//LÊ os dados do quarto do arquivo binário
    std::string readString(FILE* file)
    {
        size_t length;
        fread(&length, sizeof(length), 1, file);
        char* buffer = new char[length + 1];
        fread(buffer, sizeof(char), length, file);
        buffer[length] = '\0';
        std::string str(buffer);
        delete[] buffer;
        return str;
    }
};

#endif // QUARTO_H_INCLUDED
