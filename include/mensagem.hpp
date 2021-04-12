#ifndef MENSAGEM_H
#define MENSAGEM_H

#include <iostream>
using namespace std;

class Mensagem{
   private:
        string dataHora;
        string conteudo;
        int idUsuario;

    public:
        Mensagem();
        string getDataHora();
        string getConteudo();
        int getIdUsuario();
        Mensagem(const string &dataHora, const string &conteudo, int idUser);
        ~Mensagem();

};


#endif