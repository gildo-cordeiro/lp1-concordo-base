#ifndef SERVIDOR_H
#define SERVIDOR_H

#include <iostream>
#include <vector>
#include "canal.hpp"

using namespace std;

class Servidor{
    private:
        int idUser;
        string nome;
        string descricao;
        string codigoConvite;
        vector<Canal> canais;
        vector<int> participantesIDs;
            
    public:
        Servidor();
        ~Servidor();
};

#endif