#pragma once
#include"Terreno.h"
#include <iostream>
#include <string>

using namespace std;

class Mundo;

class Pantano: public Terreno
{
	int libertaMosquito;
	void setLibertaMosquito(int t);
public:


	Pantano(Mundo *md, int lin, int col);
	int getLibertaMosquito();
	virtual Terreno * duplica(Mundo* md)const;

	virtual string getAsString();
	virtual void accao();

	~Pantano(void);
};