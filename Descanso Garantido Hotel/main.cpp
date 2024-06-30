#include <iostream>
#include <limits>
#include "Funcionario.h"
#include "Client.h"
#include "Quarto.h"
#include "Estadia.h"

void menu();
void cadastrarCliente();
void cadastrarFuncionario();
void registrarDiaria(Quarto quartos[], int numQuartos);
void pesquisarCliente();
void pesquisarFuncionario();
// Lamoni Fez essa parte
int main()
{
    Quarto quartos[20];
    for (int i = 0; i < 20; ++i)
    {
        std::string num = "Q" + std::to_string(i + 1);
        quartos[i].setNumeroQuarto(num);
        quartos[i].setQuantidadeHospedes(2); // Exemplo de capacidade
        quartos[i].setValorDiaria(100.0); // Exemplo de valor da diária
    }

    int opt;
    do
    {
        menu();
        std::cout << "Inserir opção: ";
        std::cin >> opt;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpa o buffer de entrada

        switch (opt)
        {
        case 1:
            cadastrarCliente();
            break;
        case 2:
            cadastrarFuncionario();
            break;
        case 3:
            registrarDiaria(quartos, 20);
            break;
        case 4:
            pesquisarCliente();
            break;
        case 5:
            pesquisarFuncionario();
            break;
        case 0:
            std::cout << "Saindo do programa." << std::endl;
            break;
        default:
            std::cout << "Opção inválida. Tente novamente." << std::endl;
        }
    } while (opt != 0);

    return 0;
}

void menu()
{
    std::cout << "Bem Vindo ao Descanso Garantido Hotel" << std::endl;
    std::cout << "--------------------------------------" << std::endl;
    std::cout << "Opção 1 - Cadastrar Cliente" << std::endl;
    std::cout << "Opção 2 - Cadastrar Funcionário" << std::endl;
    std::cout << "Opção 3 - Registrar diária" << std::endl;
    std::cout << "Opção 4 - Pesquisar Cliente" << std::endl;
    std::cout << "Opção 5 - Pesquisar Funcionário" << std::endl;
    std::cout << "Opção 0 - Sair" << std::endl;
    std::cout << "--------------------------------------" << std::endl;
}

void cadastrarCliente()
{
    Client cliente;
    cliente.cadastrarCliente();

    std::string filename = "clientes.dat";
    cliente.saveToFile(filename);
}

void cadastrarFuncionario()
{
    Funcionario funcionario;
    funcionario.cadastrarFuncionario();

    std::string filename = "funcionarios.dat";
    funcionario.saveToFile(filename);
}

void registrarDiaria(Quarto quartos[], int numQuartos)
{
    Estadia estadia;
    std::string dataEntrada, dataSaida, codigoCliente;
    int quantidadeDiarias;
    std::string numeroQuarto;

    estadia.generateCodigoEstadia();

    std::cout << "Digite a data de entrada (dd/mm/aaaa): ";
    std::getline(std::cin, dataEntrada);
    estadia.setDataEntrada(dataEntrada);

    std::cout << "Digite a data de saída (dd/mm/aaaa): ";
    std::getline(std::cin, dataSaida);
    estadia.setDataSaida(dataSaida);

    std::cout << "Digite o código do cliente: ";
    std::getline(std::cin, codigoCliente);
    estadia.setCodigoCliente(codigoCliente);

    std::cout << "Digite a quantidade de diárias: ";
    std::cin >> quantidadeDiarias;
    estadia.setQuantidadeDiarias(quantidadeDiarias);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Digite o número do quarto: ";
    std::getline(std::cin, numeroQuarto);

    bool quartoEncontrado = false;
    for (int i = 0; i < numQuartos; ++i)
    {
        if (quartos[i].getNumeroQuarto() == numeroQuarto)
        {
            if (quartos[i].getOcupado())
            {
                std::cout << "Quarto já está ocupado." << std::endl;
            }
            else
            {
                quartos[i].setCodigoEstadia(estadia.getCodigoEstadia());
                quartos[i].setOcupado(true);
                std::cout << "Estadia registrada com sucesso para o quarto " << numeroQuarto << std::endl;
            }
            quartoEncontrado = true;
            break;
        }
    }

    if (!quartoEncontrado)
    {
        std::cout << "Número do quarto não encontrado." << std::endl;
    }

    std::string filename = "estadias.dat";
    estadia.saveToFile(filename);

    // Adicionar pontos de fidelidade para o cliente
    Client cliente;
    cliente.readFromFile("clientes.dat");
    cliente.addPontosFidelidade(quantidadeDiarias * 10); // Exemplo: 10 pontos por diária
    cliente.saveToFile("clientes.dat");
}

void pesquisarCliente()
{
    std::string keyword;
    std::cout << "Digite o nome ou código do cliente: ";
    std::getline(std::cin, keyword);

    Client cliente;
    if (cliente.searchClient(keyword))
    {
        std::cout << "\nCliente encontrado:" << std::endl;
        cliente.showInfo();
    }
    else
    {
        std::cout << "\nCliente não encontrado." << std::endl;
    }
}

void pesquisarFuncionario()
{
    std::string keyword;
    std::cout << "Digite o nome ou matrícula do funcionário: ";
    std::getline(std::cin, keyword);

    Funcionario funcionario;
    if (funcionario.searchFuncionario(keyword))
    {
        std::cout << "\nFuncionário encontrado:" << std::endl;
        funcionario.showInfo();
    }
    else
    {
        std::cout << "\nFuncionário não encontrado." << std::endl;
    }
}
