#ifndef ESTADIA_H_INCLUDED
#define ESTADIA_H_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

class Estadia
{
private:
    std::string codigoEstadia;
    std::string dataEntrada;
    std::string dataSaida;
    int quantidadeDiarias;
    std::string codigoCliente;
    static int estadiaCounter;

public:
    Estadia()
    {
        codigoEstadia = "";
        dataEntrada = "";
        dataSaida = "";
        quantidadeDiarias = 0;
        codigoCliente = "";
    }

    void setCodigoEstadia(std::string &codigo)
    {
        codigoEstadia = codigo;
    }

    void setDataEntrada(std::string &data)
    {
        dataEntrada = data;
    }

    void setDataSaida(std::string &data)
    {
        dataSaida = data;
    }

    void setQuantidadeDiarias(int dias)
    {
        quantidadeDiarias = dias;
    }

    void setCodigoCliente(std::string &codigo)
    {
        codigoCliente = codigo;
    }

    std::string getCodigoEstadia()
    {
        return codigoEstadia;
    }

    std::string getDataEntrada()
    {
        return dataEntrada;
    }

    std::string getDataSaida()
    {
        return dataSaida;
    }

    int getQuantidadeDiarias()
    {
        return quantidadeDiarias;
    }

    std::string getCodigoCliente()
    {
        return codigoCliente;
    }

    void generateCodigoEstadia()
    {
        std::ostringstream oss;
        oss << "EST" << ++estadiaCounter;
        codigoEstadia = oss.str();
    }

    void saveToFile(std::string &filename)
    {
        std::ofstream outFile(filename, std::ios::binary | std::ios::app);
        if (!outFile)
        {
            std::cerr << "Erro ao abrir o arquivo para escrita." << std::endl;
            return;
        }

        writeString(outFile, codigoEstadia);
        writeString(outFile, dataEntrada);
        writeString(outFile, dataSaida);
        outFile.write(reinterpret_cast<const char*>(&quantidadeDiarias), sizeof(quantidadeDiarias));
        writeString(outFile, codigoCliente);

        outFile.close();
        std::cout << "Dados de estadia salvos com sucesso no arquivo " << filename << std::endl;
    }

private:
    void writeString(std::ofstream &outFile, std::string &str)
    {
        size_t length = str.size();
        outFile.write(reinterpret_cast<const char*>(&length), sizeof(length));
        outFile.write(str.c_str(), length);
    }
};

int Estadia::estadiaCounter = 0;

#endif // ESTADIA_H_INCLUDED
