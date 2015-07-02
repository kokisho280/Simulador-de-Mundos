#pragma once

#include "Servivo.h"


class Mundo;

class Pessoa : public Servivo
{
	string estadoDeSaude;

protected:
	virtual void geraCoord(int lm, int cm);
	virtual bool geraId()=0;

public:

	Pessoa(Mundo* md);

	string getEstadoDeSaude();
	int getTempoDeInfecao();

	bool posicaoPessoa(int x, int y);//se posicao no mundo tem pessoa

	void setEstadoDeSaude(string estado);
	void setTempoDeInfecao(int t);

	virtual Pessoa * duplica(Mundo* md)const=0;
	
	

	virtual string getAsString();

	virtual void mov()=0;//movimento das pessoas, concretizado em idosos e jovens
	virtual void accao()=0;

	~Pessoa(void);


};

