#include "canal.hpp"

Canal::Canal(){}

Canal::~Canal(){}

void Canal::setNome(string nome){
    this->nome = nome;
}

void Canal::setDesc(string desc){
    this->descricao = desc;
}

string Canal::getNome(){
    return this->nome;
}

string Canal::getDesc(){
    return this->descricao;
}