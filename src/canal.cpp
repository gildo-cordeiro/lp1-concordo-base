#include "canal.hpp"
#include "canal.hpp"

Canal::Canal(){
    this->nome = nullptr;
    this->tipo = nullptr;
}

string Canal::getNome(){
    return this->nome;
}
Canal::Canal(const string& nome, const string& tipo):nome(nome),tipo(tipo){
    this->nome = nome;
    this->tipo = tipo;
}
string Canal::getTipo(){ return this->tipo; }

Canal::~Canal(){}
