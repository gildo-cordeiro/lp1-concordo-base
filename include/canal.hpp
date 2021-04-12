#ifndef CANAL_H
#define CANAL_H

#include  <iostream>
using namespace std;

class Canal{
    protected:
        string nome;
        string tipo;

    public:
        Canal();
        string getNome();
        Canal(const string& nome, const string & tipo);
        string getTipo();
        virtual ~Canal();
};

#endif