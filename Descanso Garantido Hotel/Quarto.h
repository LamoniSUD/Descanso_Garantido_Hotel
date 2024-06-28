#ifndef QUARTO_H_INCLUDED
#define QUARTO_H_INCLUDED

#include <iostream>
#include <cstdio>
#include <string>

class Quarto
{
private:
    std::string numeroQuarto;
    int quantidadeHospedes;
    double valorDiaria;
    bool ocupado;
    std::string codigoEstadia;

public:
    Quarto()
        : numeroQuarto(""), quantidadeHospedes(0), valorDiaria(0.0), ocupado(false), codigoEstadia("") {}

    void setNumeroQuarto(const std::string& num)
    {
        numeroQuarto = num;
    }

    void setQuantidadeHospedes(int hospedes)
    {
        quantidadeHospedes = hospedes;
    }

    void setValorDiaria(double valor)
    {
        valorDiaria = valor;
    }

    void setOcupado(bool estado)
    {
        ocupado = estado;
    }

    void setCodigoEstadia(const std::string& cod)
    {
        codigoEstadia = cod;
        ocupado = !cod.empty(); // Se há código de estadia, o quarto está ocupado
    }

    std::string getNumeroQuarto() const
    {
        return numeroQuarto;
    }

    int getQuantidadeHospedes() const
    {
        return quantidadeHospedes;
    }

    double getValorDiaria() const
    {
        return valorDiaria;
    }

    bool getOcupado() const
    {
        return ocupado;
    }

    std::string getCodigoEstadia() const
    {
        return codigoEstadia;
    }

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
    void writeString(FILE* file, const std::string& str)
    {
        size_t length = str.size();
        fwrite(&length, sizeof(length), 1, file);
        fwrite(str.c_str(), sizeof(char), length, file);
    }

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
