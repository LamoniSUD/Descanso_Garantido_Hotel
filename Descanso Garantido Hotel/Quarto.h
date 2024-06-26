#ifndef QUARTO_H_INCLUDED
#define QUARTO_H_INCLUDED

#include <iostream>
#include <fstream>
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
    {
        numeroQuarto = "";
        quantidadeHospedes = 0;
        valorDiaria = 0.0;
        ocupado = false;
        codigoEstadia = "";
    }

    void setNumeroQuarto(std::string& num)
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

    void setCodigoEstadia(string& cod)
    {
        codigoEstadia = cod;
    }

    string getNumeroQuarto()
    {
        return numeroQuarto;
    }

    int getQuantidadeHospedes()
    {
        return quantidadeHospedes;
    }

    double getValorDiaria()
    {
        return valorDiaria;
    }

    bool getOcupado()
    {
        return ocupado;
    }

    string getCodigoEstadia()
    {
        return codigoEstadia;
    }

    void saveToFile(string& filename)
    {
        std::ofstream outFile(filename, std::ios::binary | std::ios::app);
        if (!outFile)
        {
            std::cerr << "Erro ao abrir o arquivo para escrita." << std::endl;
            return;
        }

        writeString(outFile, numeroQuarto);
        outFile.write(reinterpret_cast<const char*>(&quantidadeHospedes), sizeof(quantidadeHospedes));
        outFile.write(reinterpret_cast<const char*>(&valorDiaria), sizeof(valorDiaria));
        outFile.write(reinterpret_cast<const char*>(&ocupado), sizeof(ocupado));
        writeString(outFile, codigoEstadia);

        outFile.close();
        cout << "Dados do quarto salvos com sucesso no arquivo " << filename <<endl;
    }

private:
    void writeString(ofstream& outFile,string& str)
    {
        size_t length = str.size();
        outFile.write(reinterpret_cast<const char*>(&length), sizeof(length));
        outFile.write(str.c_str(), length);
    }
};

#endif // QUARTO_H_INCLUDED
