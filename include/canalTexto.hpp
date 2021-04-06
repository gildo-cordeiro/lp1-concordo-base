#ifndef CANALTEXTO_H
#define CANALTEXTO_H

#include <vector>
#include "mensagem.hpp"
#include "canal.hpp"

using namespace std;

class CanalTexto: public Canal{
    private:
    vector<Mensagem> mensagens;

    public:
        CanalTexto();
        ~CanalTexto();

        void setNome(string nome);
        void setDesc(string desc);

        string getNome();
        string getDesc();
};

#endif