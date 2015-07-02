#pragma once

#include <iostream>
#include <string>

using namespace std;

class Mundo;

class Terreno {

	int coord_l;
	int coord_c;
	bool valido;
	string cor; // AMARELO = pantano     AMARELO_CLARO = hospital
	Mundo *mundo;

protected:
	Mundo *getPMundo();
	void setCor(string corT);
	void setCoord_l(int l);
	void setCoord_c(int c);
	//virtual void geraCoord(int lm, int cm);
	void setMundo(Mundo *md);
	void setValido(bool v);

public:

	
	Terreno(Mundo *md);
	//Terreno(int lm, int cm, Mundo *md);

	// -----------  GETTERS  --------------
	bool getValido();
	int getCoord_l();
	int getCoord_c();
	string getCor();

	bool posicaoterreno(int cm, int lm);


	virtual Terreno * duplica(Mundo* md)const=0;
	virtual void accao()=0;

	virtual string getAsString();

	~Terreno(void);

};