#pragma once

#include <string>
using namespace std;

class Objeto
{
	/* 
	* Es una clase abstracta de la cual se debe derivar implementando:
	* 	el constructor estándar,  
	* 	el constructor de copias,
	* 	sus métodos abstractos 
	* para obtener clases derivadas concretas.
	*/

public:

	/* CLONADOR VIRTUAL PURO */

	//EFE: realiza la misma función del constructor de copias, pero a diferencia del constructor
	//	   este método sí permite el enlace dinámico, el constructor sólo permite el enlace estático.
	virtual Objeto& clonar() const = 0;

	/* SERIALIZADOR VIRTUAL PURO */

	// EFE: genera una hilera que representa el estado de *this.
	virtual string toString() const = 0;

	/* ASIGNADOR VIRTUAL PURO */
	virtual Objeto& operator=(Objeto& ro) = 0;
};
