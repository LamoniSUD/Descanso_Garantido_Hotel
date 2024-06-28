/*H**********************************************************************
* Name : 
*
* DESCRIPTION :
* Sistema de Controle do Hotel Descanso Garantido
*
* PUBLIC FUNCTIONS :
* 
* INPUTS :
*
* OUTPUTS:
* 
* PROCESS:
*    [1]
*    [2]
*    [3]
* NOTES :
* 
* 
*
* 
*
* AUTHORS : Luan Henrique / Pereira, Lamôni Leal
*     START DATE : 17 Jun 2024
*
* 
*
* 
*H*/


#include <iostream>
#include "Funcionario.h" //Classes criadas para uso dentro do código main(principal)
#include "Client.h"
#include "Quarto.h"
    //chamadas de procedimentos posteriormente indicados com seu determinado código
void menu();                    //Menu a ser Exibido na tela para o Usuário
void cadastrarCliente();        //Cadastro de Cliente novo
void cadastrarFuncionario();    //Cadastro de Funcionário novo
void registrarDiaria();        //Registrando Estadia do Cliente

int main()
{
    int opt;        //varável para gravar seleção de comandos dentro do menu
    do            //iniciando repetição para manter o sistema conectado até o comando "sair" do usuário
    {
        menu();            //Exibindo Menu para o usuário
        std::cout << "Inserir opção: ";    //imprimindo na tela solicitação de informação
        std::cin >> opt;                    //Lendo valor digitado e guardando na variável criada
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpa o buffer de entrada

        switch (opt)            //Abrindo menu lógico de opções
        {
        case 1:                        //Separando caso a caso as opções impressas no menu para o usuário
            cadastrarCliente();        /Cchamando procedimento
            break;                    //Finalizando caso selecionado
            cout << "\n\nSeja bem vindo\n" << std::endl;
            //Repetindo processo para os demais casos
        case 2:                    
            cadastrarFuncionario();
            cout << "\n\nSeja bem vindo ao time!\n" << std::endl;
            break;
        case 3:
            registrarDiaria();
            cout << "\n\nSua Estadia foi Registrada!\nGarantimos o seu bom descanso\n" << std::endl;
            break;
        case 0: 
            cout << "Volte Sempre!" << std::endl;
        default:    //Condição de erro para a informação recebida
            std::cout << "Opção inválida. Tente novamente." << std::endl;
        }
    } while (opt != 0);    //Condição de repetição para manter usuário conectado até selecionar a opção de saída ("0")

    return 0;
}

void menu()
{
            //Imprimindo Menu interativo com o usuário
    std::cout << "Bem Vindo ao Descanso Garantido Hotel\n" << std::endl;
    std::cout << "--------------------------------------\n" << std::endl;
    std::cout << "Opção 1 - Cadastrar Cliente\n" << std::endl;
    std::cout << "Opção 2 - Cadastrar Funcionário\n" << std::endl;
    std::cout << "Opção 3 - Registrar diária\n" << std::endl;
    std::cout << "Opção 0 - Sair\n" << std::endl;
    std::cout << "--------------------------------------" << std::endl;
}

void cadastrarCliente()
{
    Client cliente;                //Declarando variável dentro da classe Cliente
    cliente.cadastrarCliente();    //Utilizando método expecífico da classe

    std::string filename = "clientes.dat";    //Declarando String com nome do arquivo
    cliente.saveToFile(filename);            //Salvando dados do cliente, por meio de metodo, dentro do arquivo com o nome declarado
}

void cadastrarFuncionario()
{
        /*Funcionamento semelhante ao cadastro de clientes, porém utiliza a 
        classe de funcionário com seus respectivos dados e métodos*/
    Funcionario funcionario;
    funcionario.cadastrarFuncionario();

    std::string filename = "funcionarios.dat";
    funcionario.saveToFile(filename);
}

void registrarDiaria()
{
    Quarto quarto;           //Variável da Classe quarto
    std::string num;        //Caractere que define número do quarto, utiliza string pois o código do quarto possui letras e números
    int hospedes;           //Valor intero de pessoas ligadas a estadia
    double diaria;            //Valor em moeda de cada dia de estadia comprado pelo cliente
    bool estado;              //Condicionador booleano para definir quartos que estão ocupados e quartos vazios 
    std::string codigo;       //Variável para armazenar código da estadia a ser registrada no sistema

    std::cout << "Digite o número do quarto: ";    //Imprimindo solicitação do quarto a ser selacionado
    std::getline(std::cin, num);                //
    quarto.setNumeroQuarto(num);                //

    std::cout << "Digite a quantidade de hóspedes: ";
    std::cin >> hospedes;
    quarto.setQuantidadeHospedes(hospedes);

    std::cout << "Digite o valor da diária: ";
    std::cin >> diaria;
    quarto.setValorDiaria(diaria);

    std::cout << "O quarto está ocupado? (1 para sim, 0 para não): ";
    std::cin >> estado;
    quarto.setOcupado(estado);

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpa o buffer de entrada

    std::cout << "Digite o código de estadia: ";
    std::getline(std::cin, codigo);
    quarto.setCodigoEstadia(codigo);

    std::string filename = "quartos.dat";
    quarto.saveToFile(filename);
}
