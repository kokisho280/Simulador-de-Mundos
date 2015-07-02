#include <iostream>
#include <string>
#include <sstream>

#include "Simulador.h"

using namespace std;




void main(){

	
	Simulador s;
	s.inicio();
	

	/*
	Mundo *a = new Mundo("Rv",10,10);
	a->acrescentaNPessoas(2);
	//a->acrescentaNMosquitos(2);
	//a->acrescentaNTerrenos(4);
	Mundo *b= new Mundo(*a);
	Mundo *c = new Mundo("VR", 2 ,2);

	cout << "Mundo a: " << a->getAsString() << endl;
	cout << "Mundo b: " << b->getAsString() << endl;

	b->acrescentaNIdosos(2);
	b->acrescentaNJovens(2);

	cout << "Mundo b: " << b->getAsString() << endl;
	
	a->libertarMemoriaSeresVivos();
	c->acrescentaNJovens(2);
	//c->acrescentaNTerrenos(4);
	cout << "Mundo a: " << a->getAsString() << endl;
	cout << "Mundo b: " << b->getAsString() << endl;
	cout << "Mundo c: " << c->getAsString() << endl;
	*a=*c;
	//c->libertarMemoriaTotal(c->getNumPessoas(), c->getNumMosquitos());
	//*c = *b;
	delete c;
	cout << "Mundo a: " << a->getAsString() << endl;
	cout << "Mundo b: " << b->getAsString() << endl;
	//cout << "Mundo c: " << c->getAsString() << endl;
	cout << "\nfim";
	*/
}





















//trataComandos(Mundo m);
//mostrarMundo(Mundo m);






/*
	Mundo a("Rv",10,10);
	a.acrescentaNIdosos(5);
	
	Mundo b(a);
	Mundo c("VR", 2 ,2);

	cout << "Mundo a: " << a.getAsString() << endl;
	cout << "Mundo b: " << b.getAsString() << endl;

	b.acrescentaNIdosos(2);

	cout << "Mundo b: " << b.getAsString() << endl;
	a.libertarMemoria(a.getNumIdoso());
	c.acrescentaNIdosos(2);

	cout << "Mundo a: " << a.getAsString() << endl;
	cout << "Mundo b: " << b.getAsString() << endl;
	a=c;
	c = b;
	cout << "Mundo a: " << a.getAsString() << endl;
	cout << "Mundo b: " << b.getAsString() << endl;
	cout << "Mundo c: " << c.getAsString() << endl;
	cout << "\nfim";*/
	
	/*
	istringstream iss(comando);
	getline(iss, cm , ' ');
	cmd.push_back(cm);*/

	/*
	for(int j = 0; j < i; j ++)
		cout << cmd[j]; */

	//cout << s.getAsString();
	

	
	//cout << m1.getAsString();
	

	/*

	do{
		c.clrscr();
		cout << "\n\tCriar mundo: >mundo Nome NumLinhas NumColunas \n\n\t( linhas e colunas de 50 a 100 )\n\n>";
		cin.ignore(cin.rdbuf()->in_avail());
		getline(cin, nome, ' ');
		cin >> linhas;
		cin >> colunas;
	}while((linhas < 50 || colunas < 50) || (linhas > 100 || colunas > 100));
	Mundo m1(nome , linhas, colunas);

	cout << nome << linhas << colunas ;
	//ciclo
	//mostrarMundo();

	*/

