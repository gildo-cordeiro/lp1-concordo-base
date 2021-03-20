#ifndef USUARIO_H
#define USUARIO_H

#include <istream>
#include "servidor.hpp"
using namespace std;

class Usuario{
    private:
        int id;
        string nome;
        string email;
        string senha;
        Servidor *servidor = nullptr;
        bool ativo;

    public:
        Usuario();
        Usuario(int id, string nome, string email, string senha);
        ~Usuario();
        
        string getNome();
        string getEmail();
        string getSenha();
        void addServer(Servidor *s);
        Servidor* getServer();
        void setAtivo(bool ativo);
        bool getAtivo();
        int getId();
};


#endif