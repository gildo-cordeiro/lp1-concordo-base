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
  if(usuarioLogadoId != 0){
    for (auto &u: usuarios){
      if(u.getId() == usuarioLogadoId && u.getServer() != nullptr){
        msg += "#CANAIS DE TEXTO\n";
        for (auto &ct : u.getServer()->getCanaisTexto()){
          msg += ct.getNome() + (!ct.getDesc().empty() ? ct.getDesc() : "") + "\n"; 
        }  

        msg += "\n\n";

        msg += "#CANAIS DE VOZ\n";
        for (auto &cv : u.getServer()->getCanaisVoz()){
          msg += cv.getNome() + (!cv.getDesc().empty() ? cv.getDesc() : "") + "\n";
        }
              
      }else{
        msg = "voce nao esta conectado em nenhum servidor";
      }
    }
  }else{
    msg = "É preciso estar logado para executar esse comando.";
  }

  return msg;
}

string Sistema::create_channel(const string nome, const string tipo) {
  if(usuarioLogadoId != 0){
    CanalTexto inser_ct;
    CanalVoz   inser_cv;
    bool flag = false;
    
    for (auto &u: usuarios){
      if(u.getId() == usuarioLogadoId && u.getServer() != nullptr){
        if(tipo == "texto"){
          for (auto &ct : u.getServer()->getCanaisTexto()){
            if(ct.getNome() == nome)
              flag = true;
          }

          if(!flag){
            inser_ct.setNome(nome);
            inser_ct.setDesc("");
            u.getServer()->addCanalTexto(inser_ct);
            msg = "Canal de texto "+ nome +" criado";
          }else{
            msg = "Canal de texto "+nome+" já existe";
          }

        }else if(tipo == "voz"){
          for (auto &cv : u.getServer()->getCanaisVoz()){
            if(cv.getNome() == nome)
              flag = true;
          }
          
          if(!flag){
            inser_ct.setNome(nome);
            inser_ct.setDesc("");
            u.getServer()->addCanalVoz(inser_cv);
            msg = "Canal de voz "+ nome + "criado";
            
          }else{
            msg = "Canal de voz "+nome+" já existe";
          }
        
        }else{
          msg = "Esse tipo de canal não existe no sistema.";
        }

      }else{
        msg = "voce nao esta conectado em nenhum servidor";
      }
    }
  }else{
    msg = "É preciso estar logado para executar esse comando."; 
  }
  return msg;
}

string Sistema::enter_channel(const string nome) {
  if(usuarioLogadoId != 0){
    bool channel = false;
    for (auto &u: usuarios){
      if(u.getId() == usuarioLogadoId && u.getServer() != nullptr){
        for (auto &ct : u.getServer()->getCanaisTexto()){
          if(ct.getNome() == nome)
            channel = true;
        }

        if(!channel){
          for (auto &cv : u.getServer()->getCanaisVoz()){
            if(cv.getNome() == nome)
              channel = true;
          }          
        }

        channel ? nomeCanalConectado = nome : nomeCanalConectado = "";
        nomeCanalConectado.empty() ? msg = "Entrou no canal "+ nome : msg = "Canal "+ nome + " não existe";
                     
      }else{
        msg = "voce nao esta conectado em nenhum servidor";
      }
    }
  }else{
    msg = "É preciso estar logado para executar esse comando."; 
  }
  return msg;
}

string Sistema::leave_channel() {
  if(usuarioLogadoId != 0){
    for (auto &u: usuarios){
      if(u.getId() == usuarioLogadoId && u.getServer() != nullptr){
        nomeCanalConectado.empty() ? msg = "Saindo do canal" : "";
        nomeCanalConectado = "";
      }else{
        msg = "voce nao esta conectado em nenhum servidor";
      }
    }
  }else{
    msg = "É preciso estar logado para executar esse comando."; 
  }
  return msg;
}

string Sistema::send_message(const string mensagem) {
  if(usuarioLogadoId != 0){
    return mensagem;
  }else{
    msg = "É preciso estar logado para executar esse comando."; 
  }
  return msg;
}

string Sistema::list_messages() {
  if(usuarioLogadoId != 0){

  }else{
    msg = "É preciso estar logado para executar esse comando."; 
  }
  return msg;
}




/* IMPLEMENTAR MÉTODOS PARA OS COMANDOS RESTANTES */