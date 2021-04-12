#include "servidor.hpp"

Servidor::Servidor(){}

Servidor::~Servidor(){}

Servidor::Servidor(string nome, int idUser){
    this->nome   = nome;
    this->idUser = idUser;
}

int Servidor::getIdUser(){
    return this->idUser;
}

string Servidor::getNome(){
    return this->nome;
}

string Servidor::getDescricao(){
    return this->descricao;
}

string Servidor::getCodigoConvite(){
    return this->codigoConvite;
}

vector<Canal>& Servidor::getCanais(){
    return this->canais;
}

vector<int> Servidor::getParticipantesIDs(){
    return this->participantesIDs;
}

void Servidor::setCodigoConvite(string codigo){
    this->codigoConvite = codigo;
}

void Servidor::setDescricao(string desc){
    this->descricao = desc;
}

void Servidor::addCanal(Canal c){
    this->canais.push_back(c);   
}

void Servidor::addParticipante(int p){
    this->participantesIDs.push_back(p);  
}