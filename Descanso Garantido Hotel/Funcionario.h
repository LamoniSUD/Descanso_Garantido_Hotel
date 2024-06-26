#ifndef FUNCIONARIO_H_INCLUDED
#define FUNCIONARIO_H_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Pessoa.h"

using namespace std;

class Funcionario : public Pessoa
{
private:
    string matricula;
    string cargo;
    double salario;
    static int employeeCounter;

public:
    Funcionario()
    {
        matricula = "";
        cargo = "";
        salario = 0.0;
    }

    void setMatricula(string &m)
    {
        matricula = m;
    }

    void setCargo(string &c)
    {
        cargo = c;
    }

    void setSalario(double s)
    {
        salario = s;
    }

    string getMatricula()
    {
        return matricula;
    }

    string getCargo()
    {
        return cargo;
    }

    double getSalario()
    {
        return salario;
    }

    void generateEmployeeMatricula()
    {
        ostringstream oss;
        oss << "EMP" << ++employeeCounter;
        matricula = oss.str();
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
        writeString(outFile, matricula);
        writeString(outFile, cargo);
        outFile.write(reinterpret_cast<const char*>(&salario), sizeof(salario));

        outFile.close();
        cout << "Dados salvos com sucesso no arquivo " << filename << endl;
    }

    void cadastrarFuncionario()
    {
        cadastrar();
        generateEmployeeMatricula();

        cout << "Digite o cargo do funcionário: ";
        getline(cin, cargo);

        cout << "Digite o salário do funcionário: ";
        cin >> salario;
        cin.ignore();

        cout << "\nCadastro de funcionário realizado com sucesso!" << endl;
    }

private:
    void writeString(ofstream &outFile, string &str)
    {
        size_t length = str.size();
        outFile.write(reinterpret_cast<const char*>(&length), sizeof(length));
        outFile.write(str.c_str(), length);
    }
};

// Inicialização do contador estático
int Funcionario::employeeCounter = 0;

#endif // FUNCIONARIO_H_INCLUDED
