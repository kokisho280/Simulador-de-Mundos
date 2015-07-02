#pragma once

#include "Consola.h"
#include "Mundo.h"

#include <iostream>
#include <string>



using namespace std;


class Simulador
{
	vector <Mundo *> Universo;
	Consola con;

public:

	Simulador(void);

	

	void atribuiM(Mundo * mdDest, Mundo * mdOri, string n);
	void acrescentaMundoCopia(string n, Mundo * md);
	void acrescentaMundo(string n, int l, int c);
	Mundo * pesquisaMundoNome(string n);
	bool pesquisaMundo(string n);
	void simula(string n);
	string getAsString();

	~Simulador(void);


	void inicio();
	bool comando(int & ite, int & fg, int & nl, int & nc);
	int escolheOpcao( vector<string> opcoes, string nCom);
	bool verificaMundo(string para1, int op1, int op2);
	bool verificaLimites(int op1, int op2);
	bool verificaTerreno(int op1, int op2);
	bool verificaCriai(int op1);
	bool verificaPositivo(int op1);
	//void opCriarMundoInicial();
	void instrucoes();
	void apagaMundo(string n);


	void desenhaGrelha(int nl, int nc, int fg);
	void desenhaEntidades(int nl, int nc);

	bool load(string nfile);

};

