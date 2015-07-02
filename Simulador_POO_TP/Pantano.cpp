#include "Pantano.h"
#include <iostream>
#include <string>
#include <sstream>
#include "Mundo.h"

using namespace std;

Pantano::Pantano(Mundo *md, int lin, int col) : Terreno(md)
{
		setCoord_l(lin);
		setCoord_c(col);

	setCor("AMARELO");
	setValido(true);
	setLibertaMosquito(0);
}

int Pantano::getLibertaMosquito(){
	return libertaMosquito;
}

void Pantano::setLibertaMosquito(int t){
	libertaMosquito = t;
}

Terreno * Pantano::duplica(Mundo* md)const{
	Pantano * i = new Pantano( *this);
	i->setMundo(md);
	return i;
}

string Pantano::getAsString( ){
	ostringstream oss;
	oss << Terreno::getAsString()
		<< "\n Cor:" << getCor();
	return oss.str();
}

Pantano::~Pantano(void)
{
}

void Pantano::accao(){
	int x, y;
	x = getCoord_c();
	y = getCoord_l();

	if(libertaMosquito == 0){
		if(getPMundo()->pesquisaPosicaoMosquito(x,y) == -1)
			getPMundo()->acrescentaMosquitoPantano(y,x);
		setLibertaMosquito(9);
		return;
	}

	int lib = getLibertaMosquito();
	setLibertaMosquito(--lib);

}