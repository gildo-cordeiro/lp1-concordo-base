#include "mensagem.hpp"

Mensagem::Mensagem(){}

Mensagem::~Mensagem(){}

Mensagem::Mensagem(const string& dataHora, const string& conteudo, int idUsuario)
:dataHora(dataHora),conteudo(conteudo),idUsuario(idUsuario){}

string Mensagem::getDataHora(){
    return dataHora;
}

string Mensagem::getConteudo(){
    return conteudo;
}

int Mensagem::getIdUsuario(){
    return this->idUsuario;
}
