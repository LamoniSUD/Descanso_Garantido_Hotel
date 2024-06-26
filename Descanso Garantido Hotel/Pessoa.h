#ifndef PESSOA_H_INCLUDED
#define PESSOA_H_INCLUDED
#include <iostream>
#include <string>

class Pessoa
{
    private:
        string nome;
        int idade;
    public:
        Pessoa()
        {
            nome="Sem nome";
            idade=0;

        }
        void setNome(string n)
        {
            this->nome=n;

        }
        void setAge(int a)
        {
            if (a < 0 || a < 18)
            {
                throw std::invalid_argument("Idade invalida. Deve ser maior ou igual a 18.");
            }
            this->idade = a;
        }
        string getNome()
        {
            return nome;
        }
        int getAge()
        {
            return age;
        }
        void cadastrarC()
        {
            cout<<"Digite o nome da pessoa:"<<endl;
            getline(cin,nome);

            bool ageValid=false;
            while(!ageValid)
            {
                try
                {
                    cout<<"Digite a idade:"<<endl;
                    cin>>idade;
                    cin.ignore();
                    setAge(idade);
                    ageValid=true;
                }
            }
        }
};
#endif // PESSOA_H_INCLUDED
