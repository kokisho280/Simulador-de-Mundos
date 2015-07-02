#include "Pessoa.h"
#include <iostream>
#include <string>
#include <sstream>
#include "Mundo.h"

void Pessoa::geraCoord(int lm, int cm){
	int x, y;
	bool fg = 0;
	srand (time (NULL));
	do{
		x = rand() % cm;
		y = rand() % lm;

		if(posicaoPessoa(x,y)){
			 setCoord_l(y);
			 setCoord_c(x);
			 fg = 1;
		}
	}while(!fg);
}

Pessoa::Pessoa(Mundo* md) : Servivo (md)
{
	estadoDeSaude = "VERDE";

}

string Pessoa::getEstadoDeSaude(){
	return estadoDeSaude;
}

//int Pessoa::getTempoDeInfecao(){
//	return tempoDeInfecao;
//}

bool Pessoa::posicaoPessoa(int x, int y){//se posicao NAO tem pessoa devolve verdadeiro
	if(getPMundo()->getNumPessoas() < 1)
		return true;


	for(int i = 0 ; i < getPMundo()->getNumPessoas() ; i++){
		if(x == getPMundo()->getPessoa(i)->getCoord_c() && y == getPMundo()->getPessoa(i)->getCoord_l())
			return false;
	}
	return true;

}

void Pessoa::setEstadoDeSaude(string estado){
	if(estado == "VERDE")
		estadoDeSaude = estado;
	if(estado == "VERMELHO")
		estadoDeSaude = estado;
	if(estado == "AZUL")
		estadoDeSaude = estado;
}

//void Pessoa::setTempoDeInfecao(int t){
//	tempoDeInfecao = t;
//}

string Pessoa::getAsString( ){
	ostringstream oss;
	oss << Servivo::getAsString()
		<< "\n Estado:" << estadoDeSaude;
	return oss.str();
}

Pessoa::~Pessoa(void)
{
}

