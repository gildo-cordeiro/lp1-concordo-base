#ifndef SERVIDOR_H
#define SERVIDOR_H

#include <iostream>
#include <vector>
#include "canalTexto.hpp"
#include "canalVoz.hpp"

using namespace std;

class Servidor{
    private:
        int idUser;
        string nome;
        string descricao;
        string codigoConvite;
        vector<CanalTexto> canaisTexo;
        vector<CanalVoz> canaisVoz;
        vector<int> participantesIDs;
            
    public:
        Servidor();
        Servidor(string nome, int idUser);
        ~Servidor();

        int getIdUser();
        string getNome();
        string getDescricao();
        string getCodigoConvite();
        vector<CanalTexto> getCanaisTexto();
        vector<CanalVoz> getCanaisVoz();
        vector<int> getParticipantesIDs();

        void setCodigoConvite(string codigo);
        void setDescricao(string desc);
        void addCanalTexto(CanalTexto canalTexto);
        void addCanalVoz(CanalVoz canalVoz);
        void addParticipante(int p);
};      

#endif