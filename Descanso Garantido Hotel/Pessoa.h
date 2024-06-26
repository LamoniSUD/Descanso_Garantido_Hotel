#ifndef PESSOA_H_INCLUDED
#define PESSOA_H_INCLUDED

#include <iostream>
#include <string>
#include <stdexcept>  // Necessário para std::invalid_argument
#include <limits>     // Necessário para std::numeric_limits

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

    void setNome(std::string n)
    {
        this->nome = n;
    }

    void setAge(int a)
    {
        if (a < 0 || a < 18)
        {
            throw std::invalid_argument("Idade inválida. Deve ser maior ou igual a 18.");
        }
        this->idade = a;
    }

    std::string getNome()
    {
        return nome;
    }

    int getAge()
    {
        return idade;  // Corrigido: retornar 'idade' em vez de 'age'
    }

    void cadastrarC()
    {
        std::cout << "Digite o nome da pessoa:" << std::endl;
        std::getline(std::cin >> std::ws, nome);  // std::ws ignora espaços em branco iniciais

        bool ageValid = false;
        while (!ageValid)
        {
            try
            {
                std::cout << "Digite a idade:" << std::endl;
                std::cin >> idade;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Limpa o buffer de entrada
                setAge(idade);
                ageValid = true;
            }
            catch (const std::invalid_argument &e)
            {
                std::cout << e.what() << std::endl;  // Imprime a mensagem de erro
            }
        }
    }
};

#endif // PESSOA_H_INCLUDED
