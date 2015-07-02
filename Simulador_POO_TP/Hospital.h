#pragma once
#include"Terreno.h"
#include <iostream>
#include <string>

using namespace std;

class Mundo;

class Hospital : public Terreno
{
public:
	Hospital(Mundo *md, int lin, int col);

	virtual Terreno * duplica(Mundo* md)const;

	virtual string getAsString();
	virtual void accao(){};
	~Hospital(void);
};

