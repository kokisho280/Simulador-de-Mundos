#include "Hospital.h"
#include <iostream>
#include <string>
#include <sstream>
#include "Mundo.h"

using namespace std;

Hospital::Hospital(Mundo *md, int lin, int col) : Terreno(md)
{
	
	
	setCoord_l(lin);
	setCoord_c(col);
	

	setCor("AMARELO_CLARO");
	setValido(true);
}

Terreno * Hospital::duplica(Mundo* md)const{
	Hospital * i = new Hospital( *this);
	i->setMundo(md);
	return i;
}

string Hospital::getAsString( ){
	ostringstream oss;
	oss << Terreno::getAsString()
		<< "\n Cor:" << getCor();
	return oss.str();
}


Hospital::~Hospital(void)
{
}
