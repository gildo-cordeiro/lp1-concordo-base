#include "sistema.hpp"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <memory>

using namespace std;

string Sistema::quit() {
  salvar();
  return "Saindo do Concordo";
}

/**
 * Verifica se o usuario já esxiste no sistema, caso não exista a função ira criar o usuario 
 * com base nos parametros recebidos.
 **/
string Sistema::create_user (const string email, const string senha, const string nome) {
  msg = "";
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
  salvar();
  return msg;
}

/**
 * Permite um usuario previamente existente logar no sistema, se suas credencias 
 * forem iguaias as que estão sendo recebidas por parametro.
 **/
string Sistema::login(const string email, const string senha) {
  msg = "";
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
  msg = "";
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
  msg = "";
  bool find = false;
  if(usuarioLogadoId != 0){
    for (auto &servidor : servidores){ // percorre o vetor de servidores
      if(servidor.getNome() == nome)
        find = true;
    }

    if(!find){
      Servidor server(nome, usuarioLogadoId);
      servidores.push_back(server);
      msg = "Servidor criado";
    }else{
        msg = "Servidor com esse nome já existe";
    }
    
  }else{
    msg = "É preciso estar logado para criar um servidor"; 
  }
  salvar();
  return msg;
}

/**
 * insere uma decrição em determinado sevidor
 * */
string Sistema::set_server_desc(const string nome, const string descricao) {
  msg = "";
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
  salvar();
  return msg;
}

/**
 * insere um codigo em determinado sevidor
 * */
string Sistema::set_server_invite_code(const string nome, const string codigo) {
  msg = "";
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

  salvar();
  return msg;
}

/**
 * lista todos os servidores
 * */
string Sistema::list_servers() {
  msg = "";
  string msg_completa = "";
  if(usuarioLogadoId != 0){
    if(servidores.empty())
      msg = "Não há servidores cadastrados";
    else{
      cout << "#LISTA DE SERVIDORES#" << endl;
      for (auto &servidor : servidores){
        cout << "Nome: " << servidor.getNome() << endl;
        cout << "Descrição: " << servidor.getDescricao() << endl;
        cout << "Codigo: " << (servidor.getCodigoConvite() != "" ? "Servidor Fechado" : "Servidor Aberto") << endl;
        cout << "----------------------------------------" << endl;
      }     
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
  msg = "";
  if(usuarioLogadoId != 0){
    if(servidores.empty())
      msg = "Não há servidores cadastrados";
    else{
      for(auto server = servidores.begin(); server != servidores.end(); server++) {
        if(server->getNome() == nome && server->getIdUser() == usuarioLogadoId) {
          servidores.erase(server);
          msg = "Servidor '"+nome+"' removido";
          break;
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
  msg = "";
  if(usuarioLogadoId != 0){
    for (auto &s : servidores){
      if(s.getNome() == nome){
        if(usuarioLogadoId == s.getIdUser()){ // se usuario logado for o dono do servidor é apenas inserido na lista de participantes 
				  for(auto &server : servidores) {
            if(server.getNome() == nome && (server.getCodigoConvite().empty() || server.getCodigoConvite() == codigo)) {
              server.addParticipante(usuarioLogadoId);      
              nomeServidorConectado = server.getNome();
              msg = "Entrou no servidor com sucesso";
              break;
            }  
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
  msg = "";
  if(nomeServidorConectado.empty()) {
	  msg = "Você não esta conectado a nenhum servidor";
  }

  msg = "Saindo do servidor "+ nomeServidorConectado;

  nomeServidorConectado = "";

  return msg;
}

/**
 * lista todos os participantes do servidor pertencente ao usuario logado
 * */
string Sistema::list_participants() {
  msg = "";
  string msg_completa = "";
  if(usuarios[usuarioLogadoId-1].getServer() != nullptr){
    if(usuarios[usuarioLogadoId-1].getServer()->getParticipantesIDs().size() > 0){
      msg_completa += "lista de participantes";
      for(auto &p : usuarios[usuarioLogadoId-1].getServer()->getParticipantesIDs()){
        msg_completa += usuarios[p-1].getNome()+"\n";
      }
      msg = msg_completa;
    }else{
    	msg = "Não há participantes no servidor";
    }
  }else{
		msg = "Você não esta conectado a nenhum servidor";
  }
  return msg;
}

/**
 * lista todos os participantes dos canais do servidor pertencente ao usuario logado
 * */
string Sistema::list_channels() {
  msg = "";
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
      msg = "Você não esta conectado a nenhum servidor";
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
  msg = "";
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
  salvar();
  return msg;
}

/**
 * permite ao usuario logado entrar em um canal do servidor
 * */
string Sistema::enter_channel(const string nome) {
  msg = "";
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
  msg = "";
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
  msg = "";
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
  salvar();
  return msg;
}

/**
 * permite ao usuario logado exibir as mensagens enviadas acompanhadas de data e hora
 * */
string Sistema::list_messages() {
  msg = "";
  if(!servidores.empty() || !nomeServidorConectado.empty() || !nomeCanalConectado.empty() || usuarioLogadoId != 0) {
    for(auto &server : servidores) {
      if(server.getNome() == nomeServidorConectado) {

        string output = "";

        for(auto chn = server.getCanais().begin(); chn != server.getCanais().end(); chn++) {
          CanalTexto *canal_texto = dynamic_cast <CanalTexto*>(usuarios[usuarioLogadoId-1].getCanal());
          
          if(canal_texto != nullptr) {
            if(canal_texto->getMensagens().size() > 0) {
              for(auto &mensagem : canal_texto->getMensagens()) {
                msg += usuarios[mensagem.getIdUsuario()].getNome() + "[" + mensagem.getDataHora() + "]: " + mensagem.getConteudo() + "\n";
              }
            }
          }
          CanalVoz *canal_voz = dynamic_cast <CanalVoz*>(usuarios[usuarioLogadoId-1].getCanal());

          if (canal_voz != nullptr) {
            Mensagem mensagem = canal_voz->getUltimaMensagem();
            
            if(!mensagem.getConteudo().empty()) {
              msg += usuarios[mensagem.getIdUsuario()].getNome() + "[" + mensagem.getDataHora() + "]: " + mensagem.getConteudo() + "\n";
            }
          }
        }

        if(msg.empty()) {
          return "Não há mensagens!";
        }else{
          return msg;
        }
      }
    }
  }else{
    msg = "É preciso estar logado para executar esse comando."; 
  }
  return msg;
}

void Sistema::salvar_usuarios() {
  fstream usuarios_texto;
  
  usuarios_texto.open("usuarios.txt", ios::out | ios::app);

  usuarios_texto << usuarios.size() << "\n";

  for (auto user: usuarios) {
    usuarios_texto << user.getId() << "\n";
    usuarios_texto << user.getNome() << "\n";
    usuarios_texto << user.getEmail() << "\n";
    usuarios_texto << user.getSenha() << "\n";
  }  

  usuarios_texto.close();
}

void Sistema::salvar_servidores() {
  fstream servidor_texto;
  
  servidor_texto.open("servidores.txt", ios::out | ios::app);

  servidor_texto << servidores.size() << "\n";

  for (auto server: servidores) {
    servidor_texto << server.getIdUser() << "\n";
    servidor_texto << server.getNome() << "\n";
    servidor_texto << server.getDescricao() << "\n";
    servidor_texto << server.getCodigoConvite() << "\n";

    servidor_texto << server.getParticipantesIDs().size() << "\n";

    for (auto participante_id: server.getParticipantesIDs()){
      servidor_texto << participante_id << "\n";
    }

    servidor_texto << server.getCanais().size() << "\n";

    for(auto it = server.getCanais().begin(); it != server.getCanais().end(); it++) {
      CanalTexto *canal_texto = dynamic_cast<CanalTexto*>(usuarios[server.getIdUser()].getCanal());
      if(canal_texto!= nullptr) {
        if(canal_texto->getMensagens().size() > 0) {
          servidor_texto << canal_texto->getNome() << "\n";
          servidor_texto << "TEXTO" << "\n";
          servidor_texto << canal_texto->getMensagens().size() << "\n";
          
          for(auto &mensagem : canal_texto->getMensagens()) {
            servidor_texto << mensagem.getIdUsuario() << "\n";
            servidor_texto << mensagem.getDataHora() << "\n";
            servidor_texto << mensagem.getConteudo() << "\n";
          }
        }
      }
      
      CanalVoz *canal_voz = dynamic_cast <CanalVoz*>(usuarios[server.getIdUser()].getCanal());
      if (canal_voz != nullptr) {
        Mensagem mensagem = canal_voz->getUltimaMensagem();
        servidor_texto << canal_voz->getNome() << "\n";
        servidor_texto << "VOZ" << "\n";
        servidor_texto << 1 << "\n";
        servidor_texto << mensagem.getIdUsuario() << "\n";
        servidor_texto << mensagem.getDataHora() << "\n";
        servidor_texto << mensagem.getConteudo() << "\n";
      }
    }
  }
  
  servidor_texto.close();
}

void Sistema::salvar() {
  remove("usuarios.txt");
  remove("servidores.txt");

  salvar_usuarios();
  salvar_servidores();
}

void Sistema::carregar_usuarios() {
  ifstream usuarios_texto;
  
  usuarios_texto.open("usuarios.txt");

  if (usuarios_texto.is_open()) {
    string linha;

    getline(usuarios_texto, linha);

    int size, usuario_id;

    stringstream sizeStringStream;  
    sizeStringStream << linha;  
    sizeStringStream >> size;

    if(size > 0) {
      while (!usuarios_texto.eof()) {
        getline(usuarios_texto, linha);
        stringstream idStringStream; 
        idStringStream << linha;  
        idStringStream >> usuario_id;
        getline(usuarios_texto, linha);
        string name = linha;
        getline(usuarios_texto, linha);
        string email = linha;
        getline(usuarios_texto, linha);
        string password = linha;

        Usuario usuario(usuario_id, name, email, password);
        usuarios.push_back(usuario);
      }
    }

    usuarios_texto.close();
  }  
}

void Sistema::carregar_servidores() {
  ifstream servidor_texto;
  
  servidor_texto.open("servidores.txt");

  if (servidor_texto.is_open()) {
    string linha;

    getline(servidor_texto, linha);

    int size, user_id, total_particiapantes, participante_id, total_canais, total_mensagens, userId;

    stringstream sizeStringStream;  
    sizeStringStream << linha;  
    sizeStringStream >> size;

    if(size > 0) {
      for(int i = 0; i < size; i++) {
        getline(servidor_texto, linha);
        stringstream user_idStringStream;  
        user_idStringStream << linha;  
        user_idStringStream >> user_id;
        getline(servidor_texto, linha);
        string servidor_nome = linha;
        getline(servidor_texto, linha);
        string servidor_desc = linha;
        getline(servidor_texto, linha);
        string servidor_codigo = linha;

        Servidor server(servidor_nome, user_id);
        server.setDescricao(servidor_desc);
        server.setCodigoConvite(servidor_codigo);

        getline(servidor_texto, linha);
        stringstream total_particiapantes_stringStream; 
        total_particiapantes_stringStream << linha;  
        total_particiapantes_stringStream >> total_particiapantes;

        if (total_particiapantes > 0) {
          for (int i = 0; i < total_particiapantes; i++) {
            getline(servidor_texto, linha);
            stringstream participante_id_StringStream; 
            participante_id_StringStream << linha;  
            participante_id_StringStream >> participante_id;

            server.addParticipante(participante_id);
          }
        }

        getline(servidor_texto, linha);
        stringstream total_canais_StringStream; 
        total_canais_StringStream << linha;  
        total_canais_StringStream >> total_canais;

        if (total_canais > 0) {
          for (int i = 0; i < total_canais; i++) {
            getline(servidor_texto, linha);
            string nome_canal = linha;
            getline(servidor_texto, linha);
            string tipo_canal = linha;

            Canal novo_canal(nome_canal, tipo_canal);
            server.addCanal(novo_canal);

            getline(servidor_texto, linha);
            stringstream total_mensagens_StringStream; 
            total_mensagens_StringStream << linha;  
            total_mensagens_StringStream >> total_mensagens;

            for (int j = 0; j < total_mensagens; j++) {
              getline(servidor_texto, linha);
              stringstream user_id_StringStream; 
              user_id_StringStream << linha;  
              user_id_StringStream >> userId;
              getline(servidor_texto, linha);
              string dataHora = linha;
              getline(servidor_texto, linha);
              string conteudo = linha;

              for(auto chn = server.getCanais().begin(); chn != server.getCanais().end(); chn++){
                if(chn->getNome() == nome_canal) {
                  if(tipo_canal == "TEXTO") {
                      Mensagem texto(dataHora, conteudo, userId);
                      CanalTexto *canal_texto = dynamic_cast <CanalTexto*>(usuarios[userId].getCanal());
                      canal_texto->getMensagens().push_back(texto);
                  }else if (tipo_canal == "VOZ") {
                    Mensagem voz(dataHora, conteudo, userId);
                    CanalVoz *canal_texto = dynamic_cast <CanalVoz*>(usuarios[userId].getCanal());
                    canal_texto->setUltimaMensagem(voz);
                  }
                }
              }  
            }
          }
        }
        servidores.push_back(server);
      }
    }

    servidor_texto.close();
  }  
}

void Sistema::carragar() {
  carregar_usuarios();
  carregar_servidores();
}