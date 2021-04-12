#include "mensagem.hpp"

Mensagem::Mensagem(){}

Mensagem::~Mensagem(){}

Mensagem::Mensagem(const string& dataHora, const string& conteudo, int idUser)
:dataHora(dataHora),conteudo(conteudo),idUser(idUser){}

string Mensagem::getDataHora(){
    return dataHora;
}

string Mensagem::getConteudo(){
    return conteudo;
}
