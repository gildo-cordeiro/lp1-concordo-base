#include "sistema.hpp"
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

string Sistema::quit() {
  return "Saindo do Concordo";
}

/**
 * Verifica se o usuario já esxiste no sistema, caso não exista a função ira criar o usuario 
 * com base nos parametros recebidos.
 **/
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

/**
 * Permite um usuario previamente existente logar no sistema, se suas credencias 
 * forem iguaias as que estão sendo recebidas por parametro.
 **/
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

/**
 * desconecta o usuaro logado atualmente
 **/
string Sistema::disconnect() {
  if(usuarioLogadoId != 0){
    for (auto &usuario : usuarios){
      if(usuario.getId() == usuarioLogadoId){
          msg = "Desconectando usuário " + usuario.getEmail();
          break;
      }
    }
    //variavel que guarda o id do usuario logado recebe zero indicando que será deslogado  
    usuarioLogadoId = 0;  
  }else{
    msg = "Não está conectado";
  }
  return msg;
}

/**
 * Permite ao usuario logado criar um servidor
 **/
string Sistema::create_server(const string nome) {
  if(usuarioLogadoId != 0){
    for (auto &servidor : servidores){ // percorre o vetor de servidores
      if(servidor.getNome() == nome)
        msg = "Servidor com esse nome já existe";
    }

    if(msg != ""){
      Servidor server(nome, usuarioLogadoId);
      servidores.push_back(server);
      msg = "Servidor criado";
    }
    
  }else{
    msg = "É preciso estar logado para criar um servidor"; 
  }
  return msg;
}

/**
 * insere uma decrição em determinado sevidor
 * */
string Sistema::set_server_desc(const string nome, const string descricao) {
  if(usuarioLogadoId != 0){ // verifica se o usuario esta logado
    for (auto &s: servidores){ // percorre a lista de servidores
      if(s.getNome() == nome){
        if(s.getIdUser() == usuarioLogadoId){
          s.setDescricao(descricao); // muda a descrição do servidor
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

/**
 * insere um codigo em determinado sevidor
 * */
string Sistema::set_server_invite_code(const string nome, const string codigo) {
  if(usuarioLogadoId != 0){
    for (auto &s: servidores){
      if(s.getNome() == nome){
        if(s.getIdUser() == usuarioLogadoId){
          s.setCodigoConvite(codigo); // muda o codigo do servidor
          //if ternario para indicar qual mensagem devera ser retornado ao usuario
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

/**
 * lista todos os servidores
 * */
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
          servidor.getCodigoConvite() != "" // if ternario retornando o status do servidor
              ? "Servidor Fechado" 
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

/**
 * remove um servidor a partir do nome recebido por parametro
 * */
string Sistema::remove_server(const string nome) {
  if(usuarioLogadoId != 0){
    if(servidores.empty())
      msg = "Não há servidores cadastrados";
    else{
      for(auto s = servidores.begin(); s != servidores.end(); ++s){ //percorre a lsta de servidores 
        if(s->getNome() == nome){
          if(s->getIdUser() == usuarioLogadoId){
            servidores.erase(s); // remove o servidor da lista
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

/**
 * insere o usuario logado em um servidor de acordo com os parametros
 * */
string Sistema::enter_server(const string nome, const string codigo) {
  if(usuarioLogadoId != 0){
    for (auto &s : servidores){
      if(s.getNome() == nome){
        if(usuarioLogadoId == s.getIdUser()){ // se usuario logado for o dono do servidor é apenas inserido na lista de participantes 
				  s.addParticipante(usuarioLogadoId);
				  usuarios[usuarioLogadoId-1].addServer(&s); // adiciona o servidor no usuario logado, uma vez que ele é o proprietario
				  msg = "Entrou no servidor com sucesso";
			  }else {
          for (auto p : s.getParticipantesIDs()){ // se ele não é dono verifica-se se o usuario já está no servidor ou não
              if(p == usuarioLogadoId)
                msg = "Você ja esta neste servidor";
          }
				
          if(s.getCodigoConvite() == "" || s.getCodigoConvite() == codigo){ //verificação atraves do codigo de acesso
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

/**
 * retira o usuario logado do servidor
 * */
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
	msg = "Você não esta conectado em nenhum servidor";
  return msg;
}

/**
 * lista todos os participantes do servidor pertencente ao usuario logado
 * */
string Sistema::list_participants() {
  string msg_completa = "";
  if(usuarios[usuarioLogadoId-1].getServer() == nullptr){
		msg = "Você não esta conectado a nenhum servidor";
	}
	msg_completa += "lista de participantes";
	for(auto &p : usuarios[usuarioLogadoId-1].getServer()->getParticipantesIDs()){
		msg_completa += usuarios[p-1].getNome()+"\n";
	}
  msg = msg_completa;
  return msg;
}

/**
 * lista todos os participantes dos canais do servidor pertencente ao usuario logado
 * */
string Sistema::list_channels() {
  if(usuarioLogadoId != 0){
    if(usuarios[usuarioLogadoId-1].getServer() != nullptr){
      msg = "#CANAIS DE TEXTO\n";
      for (auto &ct : usuarios[usuarioLogadoId-1].getServer()->getCanais()){
        if(ct.getTipo() == "texto")
          msg += ct.getNome() + "\n"; 
      }  

      msg += "\n\n";

      msg += "#CANAIS DE VOZ\n";
      for (auto &cv : usuarios[usuarioLogadoId-1].getServer()->getCanais()){
        if(cv.getTipo() == "voz")
          msg += cv.getNome() + "\n";          
      }
    }else{
      msg = "Você não esta conectado em nenhum servidor";
    }
  }else{
    msg = "É preciso estar logado para executar esse comando.";
  }

  return msg;
}

/**
 * cria um canal no servidor do usuario logado de acordo com os parametros passados para 
 * a função
 * */
string Sistema::create_channel(const string nome, const string tipo) {
  if(usuarioLogadoId != 0){
    if(usuarios[usuarioLogadoId-1].getServer() != nullptr){
      Canal c(nome, tipo);
      usuarios[usuarioLogadoId-1].getServer()->addCanal(c);
    }else{
      msg = "Você não esta conectado a nenhum servidor";
    }
  }else{
    msg = "É preciso estar logado para executar esse comando."; 
  }
  return msg;
}

/**
 * permite ao usuario logado entrar em um canal do servidor
 * */
string Sistema::enter_channel(const string nome) {
  if(usuarioLogadoId != 0){
    if(usuarios[usuarioLogadoId-1].getServer() != nullptr){
      for(auto& canal : usuarios[usuarioLogadoId-1].getServer()->getCanais()){
        if(canal.getNome() == nome){
          usuarios[usuarioLogadoId-1].addCanal(&canal);
          msg = "Entrou no canal "+nome;
        }
      }
    }else{
      msg = "Você não esta conectado a nenhum servidor";
    }
  }else{
    msg = "É preciso estar logado para executar esse comando."; 
  }
  return msg;
}

/**
 * permite ao usuario logado deixar o canal do servidor
 * */
string Sistema::leave_channel() {
  if(usuarioLogadoId != 0){
    if(usuarios[usuarioLogadoId-1].getServer() != nullptr){
      usuarios[usuarioLogadoId-1].getServer()->addCanal(*(new Canal()));
    }else{
      msg = "É preciso estar logado para executar esse comando."; 
    }
  }else{
    msg = "É preciso estar logado para executar esse comando."; 
  }
  return msg;
}

/**
 * permite ao usuario enviar mensagens em um canal do servidor. Essas mesnagens são 
 * são gravadas para serem listadas depois
 * */
string Sistema::send_message(const string mensagem) {
  if(usuarios[usuarioLogadoId-1].getServer() != nullptr){
      if(usuarios[usuarioLogadoId-1].getCanal() != nullptr){        
        if(usuarios[usuarioLogadoId-1].getCanal()->getTipo() == "texto"){
          time_t data_t;
          time(&data_t);

          struct tm *t = localtime(&data_t);
          struct tm *d = localtime(&data_t);

          string dataHora(to_string(d->tm_mday) + "/" + to_string(d->tm_mon + 1) + "/" + to_string(d->tm_year + 1900) + " - " + to_string(t->tm_hour)
          + ":" + to_string(t->tm_min));

          Mensagem texto(dataHora, mensagem, usuarioLogadoId);
          CanalTexto *canal = dynamic_cast <CanalTexto*>(usuarios[usuarioLogadoId-1].getCanal());
          canal->getMensagens().emplace_back(texto);
        }
      }else{
        msg = "Você não esta conectado a nenhum canal";
      }
  }else{
    msg = "Você não esta conectado a nenhum servidor";
  }
  return msg;
}

/**
 * permite ao usuario logado exibir as mensagens enviadas acompanhadas de data e hora
 * */
string Sistema::list_messages() {
  if(usuarioLogadoId != 0){
    if(usuarios[usuarioLogadoId-1].getCanal()->getTipo() == "texto"){
      CanalTexto *canal = dynamic_cast <CanalTexto*>(usuarios[usuarioLogadoId-1].getCanal());
      if(canal != nullptr){
        for(auto &mensagem : canal->getMensagens()){
          msg += usuarios[mensagem.getIdUsuario()].getNome() + "[" + mensagem.getDataHora() + "]: " + mensagem.getConteudo() + "\n";
        }
      }else{
        msg = "Você não possui canal de texto.";
      }
    }
  }else{
    msg = "É preciso estar logado para executar esse comando."; 
  }
  return msg;
}
