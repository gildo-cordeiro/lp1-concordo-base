#ifndef CANAL_H
#define CANAL_H

#include  <iostream>
using namespace std;

class Canal{
    private:
        string nome;
        string descricao;

    public:
        Canal();
        ~Canal();

        void setNome(string nome);
        void setDesc(string desc);

        string getNome();
        string getDesc();

};

#endif