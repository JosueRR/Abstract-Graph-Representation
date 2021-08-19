#pragma once

#include <string>
using namespace std;

class Objeto
{
	/* 
	* Es una clase abstracta de la cual se debe derivar implementando:
	* 	el constructor est�ndar,  
	* 	el constructor de copias,
	* 	sus m�todos abstractos 
	* para obtener clases derivadas concretas.
	*/

public:

	/* CLONADOR VIRTUAL PURO */

	//EFE: realiza la misma funci�n del constructor de copias, pero a diferencia del constructor
	//	   este m�todo s� permite el enlace din�mico, el constructor s�lo permite el enlace est�tico.
	virtual Objeto& clonar() const = 0;

	/* SERIALIZADOR VIRTUAL PURO */

	// EFE: genera una hilera que representa el estado de *this.
	virtual string toString() const = 0;

	/* ASIGNADOR VIRTUAL PURO */
	virtual Objeto& operator=(Objeto& ro) = 0;
};
