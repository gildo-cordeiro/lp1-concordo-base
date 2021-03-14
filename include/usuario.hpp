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
        bool status;

    public:
        Usuario();
        ~Usuario();
};


#endif