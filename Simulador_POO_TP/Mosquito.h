#pragma once
#include "Servivo.h"


class Mundo;


class Mosquito : public Servivo
{
	static int tempoDeVidaM;


	virtual bool geraId();
	virtual void geraCoord(int lm, int cm);

public:

	Mosquito(Mundo* md);
	Mosquito(Mundo* md, int lm, int cm);

	virtual string getAsString();

	virtual void mov();
	virtual void accao();

	bool posicaoMosquito(int x, int y);//se posicao no mundo tem mosquito

	Mosquito * duplica(Mundo* md)const;

	~Mosquito(void);
	bool verPAdjacentes();
};

