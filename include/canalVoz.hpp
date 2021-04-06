#ifndef CANALVOZ_H
#define CANALVOZ_H

#include "mensagem.hpp"
#include "canal.hpp"

class CanalVoz: public Canal{
    private:
        Mensagem ultimaMensagem;
        
    public:
        CanalVoz();
        ~CanalVoz();
        
        void setNome(string nome);
        void setDesc(string desc);

        string getNome();
        string getDesc();
};

#endif