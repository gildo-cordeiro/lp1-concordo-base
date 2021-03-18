#ifndef USUARIO_H
#define USUARIO_H

#include <istream>
using namespace std;

class Usuario{
    private:
        int id;
        string nome;
        string email;
        string senha;
        bool ativo;

    public:
        Usuario();
        Usuario(int id, string nome, string email, string senha);
        ~Usuario();
        
        string getNome();
        string getEmail();
        string getSenha();
        void setAtivo(bool ativo);
        bool getAtivo();
        int getId();
};


#endif