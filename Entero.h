#pragma once

#include <random>
#include <ostream>
#include <string>
using namespace std;

#include "Objeto.h"

class Entero : public Objeto 
{
public:
    /* Representa un nodo con un entero. */
    
    Entero();
    Entero(const Entero& orig);
    Entero(int e);
    virtual ~Entero();
    
    // EFE: retorna el valor del ent  del nodo.
    int obtInt() const;
        
    // MOD: *this.
    // EFE: cambia el ent  del nodo a ne.
    void modInt(int ne);

    /* CLONADOR sobre-escrito */

    //EFE: realiza la misma función del constructor de copias, pero a diferencia del constructor
    //	   este método sí permite el enlace dinámico, el constructor sólo permite el enlace estático.
    virtual Objeto& clonar() const override;

    /* ASIGNADOR sobre-escrito */
    virtual Objeto& operator=(Objeto& ro) override;

    /* SERIALIZADOR sobre-escrito */
    // EFE: genera una hilera que representa el ent  de *this.
    virtual string toString() const override;

private:
    int ent ; // representa el ent  del nodo
};

Entero::Entero() : ent(0) 
{}

Entero::Entero(const Entero& orig) : ent(orig.obtInt())
{}

Entero::Entero(int e) : ent(e)
{}

Entero::~Entero() 
{}

int Entero::obtInt() const 
{
    return ent ;
}

void Entero::modInt(int ne) 
{
    ent  = ne;
}

Objeto& Entero::clonar() const
{
    Entero* pe = new Entero(*this);
    return *pe;
}

string Entero::toString() const 
{ 
    return to_string(this->ent);
}

Objeto& Entero::operator=(Objeto& n) 
{
    Entero* pm = dynamic_cast<Entero*>(&n);
    this->ent = pm->ent;
    return *this;
}