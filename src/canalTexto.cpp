#include "canalTexto.hpp"

CanalTexto::CanalTexto(){}

CanalTexto::CanalTexto(const string& nome, const string& tipo):Canal(nome,tipo){}

CanalTexto::~CanalTexto(){}

vector<Mensagem>& CanalTexto::getMensagens(){
    return mensagens;
}
