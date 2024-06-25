#include <iostream>
#include <string>

class Pessoa
{
private:
    std::string nome;
    int idade;

public:
    Pessoa()
    {
        nome = "Sem nome";
        idade = 0;
    }

    Pessoa(std::string nome, int idade)
    {
        this->nome = nome;
        this->idade = idade;
    }

    void setNome(std::string nome)
    {
        this->nome = nome;
    }

    void setIdade(int idade)
    {
        this->idade = idade;
    }

    std::string getNome()
    {
        return nome;
    }

    int getIdade()
    {
        return idade;
    }

    void showData()
    {
        std::cout << "Nome: " << nome << std::endl;
        std::cout << "Idade: " << idade << std::endl;
    }
};

class Cliente : public Pessoa
{
private:
    int codigo;
    std::string endereco;
    std::string telefone;

public:
    Cliente(int codigo, std::string& nome, std::string& endereco, std::string& telefone)
        : Pessoa(nome, 0), codigo(codigo), endereco(endereco), telefone(telefone) {}

    // Métodos getters
    int getCodigo() { return codigo; }
    std::string getEndereco() { return endereco; }
    std::string getTelefone() { return telefone; }

    void showData()
    {
        Pessoa::showData(); // Chama o método showData da classe base Pessoa
        std::cout << "Código: " << codigo << std::endl;
        std::cout << "Endereço: " << endereco << std::endl;
        std::cout << "Telefone: " << telefone << std::endl;
    }
};

class Funcionario : public Pessoa
{
private:
    std::string cargo;
    double salario;

public:
    Funcionario() : Pessoa()
    {
        cargo = "Sem cargo";
        salario = 0.0;
    }

    Funcionario(std::string& nome, int idade, std::string& cargo, double salario)
        : Pessoa(nome, idade), cargo(cargo), salario(salario) {}

    void setCargo(std::string& cargo)
    {
        this->cargo = cargo;
    }

    void setSalario(double salario)
    {
        this->salario = salario;
    }

    std::string getCargo()
    {
        return cargo;
    }

    double getSalario()
    {
        return salario;
    }

    void showData()
    {
        Pessoa::showData();
        std::cout << "Cargo: " << cargo << std::endl;
        std::cout << "Salário: " << salario << std::endl;
    }
};

class Quarto
{
private:
    int numeroQuarto;
    int quantidadeHospedes;
    double valorDiaria;
    std::string status;

public:
    Quarto(int numeroQuarto, int quantidadeHospedes, double valorDiaria, const std::string& status)
        : numeroQuarto(numeroQuarto), quantidadeHospedes(quantidadeHospedes), valorDiaria(valorDiaria), status(status) {}

    int getNumeroQuarto() { return numeroQuarto; }
    int getQuantidadeHospedes() { return quantidadeHospedes; }
    double getValorDiaria() { return valorDiaria; }
    std::string getStatus() { return status; }

    void setQuantidadeHospedes(int quantidadeHospedes)
    {
        this->quantidadeHospedes = quantidadeHospedes;
    }

    void setValorDiaria(double valorDiaria)
    {
        this->valorDiaria = valorDiaria;
    }

    void setStatus(const std::string& status)
    {
        this->status = status;
    }

    void mostrarDados()
    {
        std::cout << "Número do Quarto: " << numeroQuarto << std::endl;
        std::cout << "Quantidade de Hóspedes: " << quantidadeHospedes << std::endl;
        std::cout << "Valor da Diária: " << valorDiaria << std::endl;
        std::cout << "Status: " << status << std::endl;
    }
};

class Estadia
{
private:
    int codigoEstadia;
    std::string dataEntrada;
    std::string dataSaida;
    int quantidadeDiarias;
    int codigoCliente;
    int numeroQuarto;
    Quarto* quartos[10]; // Array de ponteiros para quartos, máximo 10 quartos
    int totalQuartos;

public:
    Estadia(int codigoEstadia, const std::string& dataEntrada, const std::string& dataSaida,
            int quantidadeDiarias, int codigoCliente, int numeroQuarto)
        : codigoEstadia(codigoEstadia), dataEntrada(dataEntrada), dataSaida(dataSaida),
          quantidadeDiarias(quantidadeDiarias), codigoCliente(codigoCliente), numeroQuarto(numeroQuarto), totalQuartos(0) {}

    int getCodigoEstadia() const { return codigoEstadia; }
    std::string getDataEntrada() const { return dataEntrada; }
    std::string getDataSaida() const { return dataSaida; }
    int getQuantidadeDiarias() const { return quantidadeDiarias; }
    int getCodigoCliente() const { return codigoCliente; }
    int getNumeroQuarto() const { return numeroQuarto; }

    void setCodigoEstadia(int codigoEstadia) { this->codigoEstadia = codigoEstadia; }
    void setDataEntrada(const std::string& dataEntrada) { this->dataEntrada = dataEntrada; }
    void setDataSaida(const std::string& dataSaida) { this->dataSaida = dataSaida; }
    void setQuantidadeDiarias(int quantidadeDiarias) { this->quantidadeDiarias = quantidadeDiarias; }
    void setCodigoCliente(int codigoCliente) { this->codigoCliente = codigoCliente; }
    void setNumeroQuarto(int numeroQuarto) { this->numeroQuarto = numeroQuarto; }

    void addQuarto(Quarto* quarto)
    {
        if (totalQuartos < 10)
        {
            quartos[totalQuartos++] = quarto;
        }
        else
        {
            std::cout << "Não é possível adicionar mais quartos. Capacidade máxima atingida." << std::endl;
        }
    }

    void removeQuarto(Quarto* quarto)
    {
        for (int i = 0; i < totalQuartos; ++i)
        {
            if (quartos[i] == quarto)
            {
                for (int j = i; j < totalQuartos - 1; ++j)
                {
                    quartos[j] = quartos[j + 1];
                }
                quartos[--totalQuartos] = nullptr;
                break;
            }
        }
    }

    Quarto** getQuartos()
    {
        return quartos;
    }

    int getTotalQuartos() const
    {
        return totalQuartos;
    }

    void mostrarDados()
    {
        std::cout << "Código da Estadia: " << codigoEstadia << std::endl;
        std::cout << "Data de Entrada: " << dataEntrada << std::endl;
        std::cout << "Data de Saída: " << dataSaida << std::endl;
        std::cout << "Quantidade de Diárias: " << quantidadeDiarias << std::endl;
        std::cout << "Código do Cliente: " << codigoCliente << std::endl;
        std::cout << "Número do Quarto: " << numeroQuarto << std::endl;
        std::cout << "Quartos: " << std::endl;
        for (int i = 0; i < totalQuartos; ++i)
        {
            quartos[i]->mostrarDados();
            std::cout << std::endl;
        }
    }
};

