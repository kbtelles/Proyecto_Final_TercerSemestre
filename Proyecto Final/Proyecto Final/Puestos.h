#pragma once

#include <iostream>
using namespace std;
class Puestos
{
		//ATRIBUTOS
protected:short idPuestos;  
		 string Puesto;

		 public:

			 //CONSTRUCTOR
			 Puestos() {}
			 Puestos(short id_puesto, string puesto) {
				 idPuestos = id_puesto;
				 Puesto = puesto;
			 }




};

