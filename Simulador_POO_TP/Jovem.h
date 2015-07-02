#pragma once

#include "Pessoa.h"
#include <iostream>
#include <string>



using namespace std;

class Mundo;

class Jovem : public Pessoa
{
	static int tempoDeImunidade;
	static int tempoDeInfecao;
	static int probImune;
	int meuTempoDeInfecao;
	int meuTempoDeImunidade;
	virtual bool geraId();
	void setMeuTempoDeInfecao(int t);
	void setMeuTempoDeImunidade(int t);

public:

	Jovem(Mundo* md);
	
	static int getTempoDeImunidade();
	static void setTempoDeImunidade(int t);
	static int getTempoDeInfecao();
	static void setTempoDeInfecao(int t);
	static int getProbImune();
	static void setProbImune(int pr);

	int getMeuTempoDeInfecao();
	int getMeuTempoDeImunidade();

	~Jovem(void);

	virtual Pessoa * duplica(Mundo* md)const;

	virtual string getAsString();

	virtual void mov();
	virtual void accao();
	bool verPAdjacentes();
	

};

