#pragma once


#include "Pessoa.h"
#include <iostream>
#include <string>



using namespace std;

class Mundo;


class Idoso : public Pessoa
{
	
	static int tempoDeInfecao;
	static int tempoDeVidaI;//tempo de vida caracteristica do idoso
	int meuTempoDeInfecao;

	void setMeuTempoDeInfecao(int t);

	virtual bool geraId();
	
	

public:
	
	Idoso(Mundo* md);

	

	int getMeuTempoDeInfecao();
	static int getTempoDeInfecao();
	static void setTempoDeInfecao(int t);
	static int getTempoDeVidaI();
	static void setTempoDeVidaI(int t);

	
	bool verPAdjacentes();

	virtual Pessoa * duplica(Mundo* md)const;

	//

	virtual string getAsString();

	//

	~Idoso(void);

	

	virtual void mov();
	
	virtual void accao();

};

