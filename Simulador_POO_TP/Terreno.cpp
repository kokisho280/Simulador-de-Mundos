#include"Terreno.h"

#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include "Mundo.h"


using namespace std;

Terreno::Terreno(Mundo* md)
{	
	setMundo(md);
	
}

bool Terreno::posicaoterreno(int cm, int lm){
	if(mundo->getNumTerrenos() < 1)
		return true;
	for (int i=0; i < mundo->getNumTerrenos(); i++)
	{
		if (cm == mundo->getTerreno(i)->getCoord_c() && lm == mundo->getTerreno(i)->getCoord_l())
			return false;
	}
	return true;
}

Mundo *Terreno::getPMundo(){
	return mundo;
}

/*
void Terreno::geraCoord(int lm, int cm){
	int x,y;
	bool flag = 0;

	do{
		x = rand() % cm;
		y = rand() % lm;
		if(posicaoterreno(x,y))
		{
			setCoord_l(y);
			setCoord_c(x);
			flag=1;
		}
	}while(!flag);
}*/

void Terreno::setMundo(Mundo *md){
	mundo = md;
}

void Terreno::setValido(bool v){
	valido = v;
}

void Terreno::setCor(string corT){
		cor = corT;
}

void Terreno::setCoord_l(int l){
	coord_l = l;
}

void Terreno::setCoord_c( int c){
	coord_c = c;
}


string Terreno::getCor(){
	return cor;
}

int Terreno::getCoord_c(){
	return coord_c;
}

int Terreno::getCoord_l(){
	return coord_l;
}

bool Terreno::getValido(){
	return valido;
}

string Terreno::getAsString( ){
	ostringstream oss;
	oss << "\nPosicao: (" << coord_l 
		<< "," << coord_c << ")"
		<< "\nSou do " << mundo->getNome();
	return oss.str();
}

Terreno::~Terreno(void){
}