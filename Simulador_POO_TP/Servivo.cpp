#include "Servivo.h"


#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include "Mundo.h"


Servivo::Servivo(Mundo* md)
{
	
	setMundo(md);
	
}

int Servivo::numSeresVivos=0;

void Servivo::setId(char *i){
	strcpy(id,i);
}

Mundo *Servivo::getPMundo(){
	return mundo;
}

void Servivo::setCoord_l(int l){
	coord_l = l;
}

void Servivo::setCoord_c(int c){
	coord_c = c;
}

void Servivo::setMundo(Mundo *md){
	mundo = md;
}

int Servivo::getNumSeresVivos(){
	return ++numSeresVivos;
}

void Servivo::setValido(bool v){
	valido = v;
}

int Servivo::getCoord_l(){
	return coord_l;
}

int Servivo::getCoord_c(){
	return coord_c;
}

char* Servivo::getId(){
	return id;
}

bool Servivo::getValido(){
	return valido;
}
	
string Servivo::getAsString( ){
	ostringstream oss;
	oss << "\n\tID: " << id
		<< "\nPosicao: (" << coord_l 
		<< "," << coord_c << ")"
		<< "\nSou do " << mundo->getNome()
		<< "\n Tempo vida:" << tempoDeVida;
	return oss.str();
}

int Servivo::getTempoDeVida(){
	return tempoDeVida;
}

void Servivo::setTempoDeVida(int t){
	tempoDeVida = t;
}

Servivo::~Servivo(void)
{
}
