    #ifndef ESTADIA_H_INCLUDED
#define ESTADIA_H_INCLUDED

#include <iostream>
#include <cstdio>
#include <cstring>

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

    void setCodigoEstadia(const std::string &codigo)
    {
        codigoEstadia = codigo;
    }

    void setDataEntrada(const std::string &data)
    {
        dataEntrada = data;
    }

    void setDataSaida(const std::string &data)
    {
        dataSaida = data;
    }

    void setQuantidadeDiarias(int dias)
    {
        quantidadeDiarias = dias;
    }

    void setCodigoCliente(const std::string &codigo)
    {
        codigoCliente = codigo;
    }

    std::string getCodigoEstadia() const
    {
        return codigoEstadia;
    }

    std::string getDataEntrada() const
    {
        return dataEntrada;
    }

    std::string getDataSaida() const
    {
        return dataSaida;
    }

    int getQuantidadeDiarias() const
    {
        return quantidadeDiarias;
    }

    std::string getCodigoCliente() const
    {
        return codigoCliente;
    }

    void generateCodigoEstadia()
    {
        codigoEstadia = "EST" + std::to_string(++estadiaCounter);
    }

    void saveToFile(const std::string &filename)
    {
        FILE *outFile = fopen(filename.c_str(), "ab");
        if (!outFile)
        {
            std::cerr << "Erro ao abrir o arquivo para escrita." << std::endl;
            return;
        }

        writeString(outFile, codigoEstadia);
        writeString(outFile, dataEntrada);
        writeString(outFile, dataSaida);
        fwrite(&quantidadeDiarias, sizeof(int), 1, outFile);
        writeString(outFile, codigoCliente);

        fclose(outFile);
        std::cout << "Dados de estadia salvos com sucesso no arquivo " << filename << std::endl;
    }

private:
    void writeString(FILE *outFile, const std::string &str)
    {
        size_t length = str.size();
        fwrite(&length, sizeof(length), 1, outFile);
        fwrite(str.c_str(), sizeof(char), length, outFile);
    }
};

int Estadia::estadiaCounter = 0;

#endif // ESTADIA_H_INCLUDED
