#include "canalVoz.hpp"

CanalVoz::CanalVoz(){}

CanalVoz::CanalVoz(const string& nome, const string& tipo):Canal(nome,tipo){
    //Construtor parametrizado
}
CanalVoz::~CanalVoz(){}

Mensagem& CanalVoz::getUltimaMensagem(){
    return ultimaMensagem;
}

void CanalVoz::setUltimaMensagem(Mensagem msg){
    this->ultimaMensagem = msg;
}