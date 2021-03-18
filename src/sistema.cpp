#include "sistema.hpp"
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

/* COMANDOS */
string Sistema::quit() {
  return "Saindo do Concordo";
}

string Sistema::create_user (const string email, const string senha, const string nome) {
  if(nome != "" && email != "" && senha != ""){
    if(usuarioLogadoId != 0){
      msg = "Usuario logado";
    }else{
      for(auto &usuario : usuarios){
        if(usuario.getEmail() == email)
          msg = "Usuário já existe!";
      }

      qtd_usuarios++;
      Usuario user(qtd_usuarios, nome, email, senha);

      usuarios.push_back(user);
      msg = "Usuário criado";
    }
  }else{
    msg = "Informe os parametros corretos para utilizar o comando.";
  }

  return msg;
}

string Sistema::login(const string email, const string senha) {
  if(email != "" && senha != ""){
    for(auto &usuario: usuarios){
      if(usuario.getEmail() == email && usuario.getSenha() == senha){
        msg = "Usuario " + usuario.getNome() + "("+usuario.getEmail()+")" +" logado com sucesso";
        usuarioLogadoId = usuario.getId();
      }else  
        msg = "Usuario não encontrado.";
    }
  }else{
    msg = "Senha ou usuário inválidos!";
  }
  return msg;
}

string Sistema::disconnect() {
  if(usuarioLogadoId != 0){
    for (auto &usuario : usuarios){
      if(usuario.getId() == usuarioLogadoId){
          msg = "Desconectando usuário " + usuario.getEmail();
          break;
      }
    }
    usuarioLogadoId = 0;    
  }else{
    msg = "Não está conectado";
  }
  return msg;
}

string Sistema::create_server(const string nome) {
  if(usuarioLogadoId != 0){
    
  }else{
    msg = "É preciso estar logado para criar um servidor"; 
  }
  return "create_server NÃO IMPLEMENTADO";
}

string Sistema::set_server_desc(const string nome, const string descricao) {
  return "set_server_desc NÃO IMPLEMENTADO";
}

string Sistema::set_server_invite_code(const string nome, const string codigo) {
  return "set_server_invite_code NÃO IMPLEMENTADO";
}

string Sistema::list_servers() {
  return "list_servers NÃO IMPLEMENTADO";
}

string Sistema::remove_server(const string nome) {
  return "remove_server NÃO IMPLEMENTADO";
}

string Sistema::enter_server(const string nome, const string codigo) {
  return "enter_server NÃO IMPLEMENTADO";
}

string Sistema::leave_server() {
  return "leave_server NÃO IMPLEMENTADO";
}

string Sistema::list_participants() {
  return "list_participants NÃO IMPLEMENTADO";
}

string Sistema::list_channels() {
  return "list_channels NÃO IMPLEMENTADO";
}

string Sistema::create_channel(const string nome, const string tipo) {
  return "create_channel NÃO IMPLEMENTADO";
}

string Sistema::enter_channel(const string nome) {
  return "enter_channel NÃO IMPLEMENTADO";
}

string Sistema::leave_channel() {
  return "leave_channel NÃO IMPLEMENTADO";
}

string Sistema::send_message(const string mensagem) {
  return "send_message NÃO IMPLEMENTADO";
}

string Sistema::list_messages() {
  return "list_messages NÃO IMPLEMENTADO";
}




/* IMPLEMENTAR MÉTODOS PARA OS COMANDOS RESTANTES */