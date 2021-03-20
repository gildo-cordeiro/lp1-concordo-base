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
    for (auto &servidor : servidores){
      if(servidor.getNome() == nome)
        msg = "Servidor com esse nome já existe";
    }

    Servidor server(nome, usuarioLogadoId);
    servidores.push_back(server);
    msg = "Servidor criado";
    
  }else{
    msg = "É preciso estar logado para criar um servidor"; 
  }
  return msg;
}

string Sistema::set_server_desc(const string nome, const string descricao) {
  if(usuarioLogadoId != 0){
    for (auto &s: servidores){
      if(s.getNome() == nome){
        if(s.getIdUser() == usuarioLogadoId){
          s.setDescricao(descricao);
          msg = "Descrição do servidor '" +s.getNome()+ "' modificada!";
        
        }else{
          msg = "Você não pode alterar a descrição de um servidor que não foi criado por você";
        }
      }else{
        msg = "Servidor '"+ nome +"'  não existe";
      }
    }    
  }else{
    msg = "É preciso estar logado para criar um servidor"; 
  }
  return msg;
}

string Sistema::set_server_invite_code(const string nome, const string codigo) {
  if(usuarioLogadoId != 0){
    for (auto &s: servidores){
      if(s.getNome() == nome){
        if(s.getIdUser() == usuarioLogadoId){
          s.setCodigoConvite(codigo);
          codigo != "" 
            ? msg = "Código de convite do servidor '" +s.getNome()+ "' modificado!"
            : msg = "Código de convite do servidor '" +s.getNome()+ "' removido!";
        
        }else{
          msg = "Você não pode alterar a descrição de um servidor que não foi criado por você";
        }
      }else{
        msg = "Servidor '"+ nome +"'  não existe";
      }
    }    
  }else{
    msg = "É preciso estar logado para criar um servidor"; 
  }
  return msg;
}

string Sistema::list_servers() {
  string msg_completa = "";
  if(usuarioLogadoId != 0){
    if(servidores.empty())
      msg = "Não há servidores cadastrados";
    else{
      msg_completa += "Lista de Servidores\n";
      for (auto &servidor : servidores){
        msg_completa += 
          "Nome: " + servidor.getNome() + 
          "\nDescrição: " + servidor.getDescricao() + 
          "\nCodigo: " + 
          servidor.getCodigoConvite() != "" 
              ? "Servidore Fechado" 
              : "Servidor Aberto";
            
        msg_completa += "\n----------------------------------------\n";
        cout << servidor.getDescricao() << endl;
      } 
      msg = msg_completa;     
    }
  }else{
    msg = "É preciso estar logado para listar servidores"; 
  }
  return msg;
}

string Sistema::remove_server(const string nome) {
  if(usuarioLogadoId != 0){
    if(servidores.empty())
      msg = "Não há servidores cadastrados";
    else{
      for(auto s = servidores.begin(); s != servidores.end(); ++s){
        if(s->getNome() == nome){
          if(s->getIdUser() == usuarioLogadoId){
            servidores.erase(s);
            msg = "Servidor '"+nome+"' removido";
          }else{
            msg = "Você não é o dono do servidor "+nome;
          }
        }else{
          msg = "Servidor '"+nome+"' não encontrado";
        }
      }
    }
  }else{
    msg = "É preciso estar logado para remover um servidor"; 
  }
  return msg;
}

string Sistema::enter_server(const string nome, const string codigo) {
  if(usuarioLogadoId != 0){
    for (auto &s : servidores){
      if(s.getNome() == nome){
        if(usuarioLogadoId == s.getIdUser()){
				  s.addParticipante(usuarioLogadoId);
				  usuarios[usuarioLogadoId-1].addServer(&s);
				  msg = "Entrou no servidor com sucesso";
			  }else {
          for (auto p : s.getParticipantesIDs()){
              if(p == usuarioLogadoId)
                msg = "Você ja esta neste servidor";
          }
				
          if(s.getCodigoConvite() == "" || s.getCodigoConvite() == codigo){
            s.addParticipante(usuarioLogadoId);
            usuarios[usuarioLogadoId-1].addServer(&s);
            msg = "Entrou no servidor com sucesso";
          }else if(s.getCodigoConvite() != "" && codigo == ""){
            msg = "Servidor requer código de convite";
          }	
		  	}
      }
    }       
  }else{
    msg = "É preciso estar logado para entrar em um servidor"; 
  }
  
  return msg;
}

string Sistema::leave_server() {
  usuarios[usuarioLogadoId-1].addServer(nullptr);
	for(auto& s : servidores){
		for(auto u = s.getParticipantesIDs().begin(); u != s.getParticipantesIDs().end(); ++u){
			if(usuarios[(*u)-1].getId() == usuarioLogadoId){
				s.getParticipantesIDs().erase(u);
				msg = "Saindo do servidor "+s.getNome();
			}
		}
	}
	msg = "voce nao esta conectado em nenhum servidor";
  return msg;
}

string Sistema::list_participants() {
  string msg_completa = "";
  if(usuarios[usuarioLogadoId-1].getServer() == nullptr){
		msg = "Voce nao esta conectado a nenhum servidor";
	}
	msg_completa += "lista de participantes";
	for(auto &p : usuarios[usuarioLogadoId-1].getServer()->getParticipantesIDs()){
		msg_completa += usuarios[p-1].getNome()+"\n";
	}
  msg = msg_completa;
  return msg;
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