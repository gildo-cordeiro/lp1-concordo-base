#ifndef MENSAGEM_H
#define MENSAGEM_H

#include <iostream>
using namespace std;

class Mensagem{
   private:
        string dataHora;
        string conteudo;
        int idUser;

    public:
        Mensagem();
        string getDataHora();
        string getConteudo();
        int getIdUser();
        Mensagem(const string &dataHora, const string &conteudo, int idUser);
        ~Mensagem();

};


#endif