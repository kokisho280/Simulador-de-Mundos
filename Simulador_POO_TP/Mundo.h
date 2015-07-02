#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "Pessoa.h"
#include "Mosquito.h"
#include "Terreno.h"
#include <stdlib.h>
#include <time.h>

using namespace std;


class Mundo
{
	string nome;
	int nLinhas;
	int nColunas;
	int tempo;
	vector <Pessoa *> pessoas;
	vector <Mosquito*> mosquitos;
	vector <Terreno*> terrenos;
	int numMinPessoas;
	int numMortos;

	
	void setNLinhas(int nLin);
	void setNColunas(int nCol);
	void copiar(const Mundo & ob);

public:
	void setNome(string n);
	Mundo(string n, int l, int c);
	Mundo( const Mundo & ob);

	bool acrescentaPessoa(void);
	bool acrescentaIdoso(void);
	bool acrescentaJovem(void);
	void acrescentaNIdosos(int n);
	void acrescentaNJovens(int n);
	void acrescentaNPessoas(int n);//acrescenta/cria 'N' Pessoas
	void eliminarSerVivosVida();
	void eliminarSerVivos();
	bool acrescentaMosquitoPantano(int lin, int col);
	bool acrescentaMosquito(void);
	void acrescentaNMosquitos(int n);

	//bool acrescentaTerreno(void);
	bool acrescentaPantano(int lin, int col);
	bool acrescentaHospital(int lin, int col);
	//void acrescentaNTerrenos(int n);

	int pesquisaPosicaoTerreno(int cm, int lm);
	int pesquisaPosicaoPessoa(int cm, int lm);
	int pesquisaPosicaoMosquito(int cm, int lm);

	string getNome();
	int getNLinhas();
	int getNColunas();
	int getTempo();
	int getNumMinPessoas();
	int getNumPessoas();
	int getNumMosquitos();
	int getNumMortos();
	int getNumTerrenos();
	int getNumInfetados();

	void setNumMinPessoas(int nmi);
	void setTempo(int t);
	void actualizaNumPessoas();
	void actualizaTempoPessoas();

	Pessoa * getPessoa(unsigned int i);
	Mosquito * getMosquito(unsigned int i);
	Terreno * getTerreno(unsigned int i);
	
	void movEntidades();

	string getAsString();

	void libertarMemoriaPessoas(int k);
	void libertarMemoriaMosquitos(int k);
	void libertarMemoriaTerrenos(int k);
	void libertarMemoriaSeresVivos();

	Mundo & operator=(const Mundo & ob);

	~Mundo(void);

};

