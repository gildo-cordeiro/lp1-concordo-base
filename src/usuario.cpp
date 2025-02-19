#include "usuario.hpp"

Usuario::Usuario(){ }

Usuario::~Usuario(){ }

Usuario::Usuario(int id, string nome, string email, string senha){
    this->nome  = nome;
    this->email = email;
    this->senha = senha;
    this->id    = id;
}

string Usuario::getNome(){
    return this->nome;
}

string Usuario::getEmail(){
    return this->email;
}

string Usuario::getSenha(){
    return this->senha;
}

int Usuario::getId(){
    return this->id;
}

bool Usuario::getAtivo(){
    return this->ativo;
}

void Usuario::setAtivo(bool ativo){
    this->ativo = ativo;
}

void Usuario::addServer(Servidor* servidor){
    this->servidor = servidor;
}

Servidor* Usuario::getServer(){
    return servidor;
}

void Usuario::addCanal(Canal* canal){
    this->canal = canal;
}

Canal* Usuario::getCanal(){
    return canal;
}