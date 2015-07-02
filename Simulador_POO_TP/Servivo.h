#pragma once

#include <iostream>
#include <string>



using namespace std;

class Mundo;


class Servivo
{
	static int numSeresVivos;
	int coord_l;
	int coord_c;
	char id[4];
	bool valido;
	int tempoDeVida;

	Mundo *mundo;

protected:

	void setId(char *i);
	virtual bool geraId()=0;
	Mundo *getPMundo();
	
	void setCoord_l(int l);
	void setCoord_c(int c);
	virtual void geraCoord(int lm, int cm)=0;
	void setMundo(Mundo *md);
	int getNumSeresVivos();
	void setValido(bool v);

public:

	Servivo(Mundo* md);

	int getTempoDeVida();
	void setTempoDeVida(int t);

	int getCoord_l();
	int getCoord_c();
	char* getId();
	bool getValido();
	
	virtual string getAsString();

	virtual void mov()=0;
	virtual void accao()=0;

	~Servivo(void);

};

