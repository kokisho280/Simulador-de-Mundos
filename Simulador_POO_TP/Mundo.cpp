#include "Mundo.h"
#include <sstream>
#include <string>

#include "Idoso.h"
#include "Jovem.h"
#include "Pantano.h"
#include "Hospital.h"

Mundo::Mundo(string n, int l, int c)
{
	setNome(n);
	setNLinhas(l);
	setNColunas(c);
	tempo = 0;
	numMinPessoas = 0;
	numMortos = 0;
	
}

Mundo::Mundo( const Mundo & ob){
	copiar(ob);

}

void Mundo::copiar( const Mundo & ob){
	nome = ob.nome;
	nLinhas = ob.nLinhas;
	nColunas = ob.nColunas;
	tempo = ob.tempo;
	numMinPessoas = ob.numMinPessoas;
	numMortos = ob.numMortos;

	for (unsigned int i = 0 ; i < ob.pessoas.size() ; i++){
		Pessoa * p = ob.pessoas[i]->duplica(this);
		if( !p){
			libertarMemoriaPessoas(i);
			return;
		}
		pessoas.push_back(p);
	}
	for (unsigned int i = 0 ; i < ob.mosquitos.size() ; i++){
		Mosquito * p = ob.mosquitos[i]->duplica(this);
		if( !p){
			libertarMemoriaMosquitos(i);
			return;
		}
		mosquitos.push_back(p);
	}
	for (unsigned int i = 0 ; i < ob.terrenos.size() ; i++){
		Terreno * p = ob.terrenos[i]->duplica(this);
		if( !p){
			libertarMemoriaTerrenos(i);
			return;
		}
		terrenos.push_back(p);
	}


}

void Mundo::setNome(string n){
	nome = n;
}

void Mundo::setNLinhas(int nLin){
	nLinhas = nLin;
}

void Mundo::setNColunas(int nCol){
	nColunas = nCol;
}


bool Mundo::acrescentaPessoa(void){
	
	int prob;

	prob = rand() % 100 + 1;

	if(prob <= 50)
		return acrescentaIdoso();
	else
		return acrescentaJovem();
}

bool Mundo::acrescentaIdoso(void){
	Idoso * i = new Idoso(this);
	if(i->getValido()){
		pessoas.push_back(i);
		return true;
	}else {
		delete i;
		return false;
	}
}

bool Mundo::acrescentaJovem(void){
	Jovem * i = new Jovem(this);
	if(i->getValido()){
		pessoas.push_back(i);
		return true;
	}else {
		delete i;
		return false;
	}
}

void Mundo::acrescentaNIdosos(int n){
	for(int i = 0 ; i < n ; i++){
		if(!acrescentaIdoso())
			i--;
	}
}

void Mundo::acrescentaNJovens(int n){
	for(int i = 0 ; i < n ; i++){
		if(!acrescentaJovem())
			i--;
	}
}

void Mundo::acrescentaNPessoas(int n){//acrescenta/cria 'N' idosos
	for(int i = 0 ; i < n ; i++){
		if(!acrescentaPessoa())
			i--;
	}
}

void Mundo::eliminarSerVivosVida(){

	for(unsigned int i = 0 ; i < pessoas.size() ; i++){
		if(pessoas[i]->getTempoDeVida() == 0){////////////////////////////////////////////////////////////////////////////////////////////////////////
			delete pessoas[i];
			pessoas.erase(pessoas.begin() + i);
			numMortos++;
			i--;
		}
	}
	for(unsigned int i = 0 ; i < mosquitos.size() ; i++){
		if(mosquitos[i]->getTempoDeVida() == 0){////////////////////////////////////////////////////////////////////////////////////////////////////////
			delete mosquitos[i];
			mosquitos.erase(mosquitos.begin() + i);
			//numMortos++;
			i--;
		}
	}
}

void Mundo::eliminarSerVivos(){

	for(unsigned int i = 0 ; i < pessoas.size() ; i++){
			delete pessoas[i];
			pessoas.erase(pessoas.begin() + i);
			numMortos++;
			i--;
	}
	for(unsigned int i = 0 ; i < mosquitos.size() ; i++){
			delete mosquitos[i];
			mosquitos.erase(mosquitos.begin() + i);
			//numMortos++;
			i--;
	}
}

bool Mundo::acrescentaMosquito(void){
	Mosquito * i = new Mosquito(this);
	if(i->getValido()){
		mosquitos.push_back(i);
		return true;
	}else {
		delete i;
		return false;
	}
}

bool Mundo::acrescentaMosquitoPantano(int lin, int col){
	Mosquito * i = new Mosquito(this,lin,col);
	if(i->getValido()){
		mosquitos.push_back(i);
		return true;
	}else {
		delete i;
		return false;
	}
}


void Mundo::acrescentaNMosquitos(int n){//acrescenta/cria 'N' Mosquitos
	for(int i = 0 ; i < n ; i++){
		if(!acrescentaMosquito())
			i--;
	}
}
/*
bool Mundo::acrescentaTerreno(void){
	
	int prob;

	prob = rand() % 100 + 1;

	if(prob <= 50)
		return acrescentaPantano();
	else
		return acrescentaHospital();
}
*/
bool Mundo::acrescentaPantano(int lin, int col){

		Pantano * i = new Pantano(this, lin, col);

		if(i->getValido()){
			terrenos.push_back(i);
			return true;
		}else {
			delete i;
			return false;
		}
}

bool Mundo::acrescentaHospital(int lin, int col){

		Hospital * i = new Hospital(this, lin, col);

		if(i->getValido()){
			terrenos.push_back(i);
			return true;
		}else {
			delete i;
			return false;
		}
}
/*
void Mundo::acrescentaNTerrenos(int n){
	for(int i = 0 ; i < n ; i++){
		if(!acrescentaTerreno())
			i--;
	}
}*/


string Mundo::getNome(){
	return nome;
}

int Mundo::getNLinhas(){
	return nLinhas;
}

int Mundo::getNColunas(){
	return nColunas;
}

int Mundo::getTempo(){
	return tempo;
}

int Mundo::getNumMinPessoas(){
	return numMinPessoas;
}

int Mundo::getNumPessoas(){
	return pessoas.size();
}

int Mundo::getNumMosquitos(){
	return mosquitos.size();
}

int Mundo::getNumMortos(){
	return numMortos;
}

int Mundo::getNumTerrenos(){
	return terrenos.size();
}

int Mundo::getNumInfetados(){
	int containf = 0;
	for(unsigned int i = 0 ; i < pessoas.size() ; i++){
		if(pessoas[i]->getEstadoDeSaude() == "VERMELHO")
			containf++;
	}
	return containf;
}

void Mundo::setNumMinPessoas(int nmi){
	numMinPessoas = nmi;
}

void Mundo::setTempo(int t){
	tempo = t;
}

void Mundo::actualizaNumPessoas(){
	if(int(pessoas.size()) < numMinPessoas)
		acrescentaPessoa();
}



void Mundo::actualizaTempoPessoas(){

	for(unsigned int i = 0; i < pessoas.size() ; i++){
		pessoas[i]->setTempoDeVida(pessoas[i]->getTempoDeVida()-1);
	}
}

Pessoa * Mundo::getPessoa(unsigned int i){
	if(i> pessoas.size())
		return 0;

	return pessoas[i];
	
}

Mosquito * Mundo::getMosquito(unsigned int i){
	if(i> mosquitos.size())
		return 0;

	return mosquitos[i];
	
}

Terreno * Mundo::getTerreno(unsigned int i){
	if(i> terrenos.size())
		return 0;

	return terrenos[i];
	
}

void Mundo::movEntidades(){

	for(unsigned int i = 0 ; i < pessoas.size() ; i++){
		pessoas[i]->accao();

	}
	for(unsigned int i = 0 ; i < mosquitos.size() ; i++){
		mosquitos[i]->accao();

	}
	for(unsigned int i = 0 ; i < terrenos.size() ; i++){
		terrenos[i]->accao();

	}


}


string Mundo::getAsString(){
	ostringstream oss;
	oss << nome << "\tNumPessoas:"<< pessoas.size() << "\t Limites ("<< nLinhas << ","<< nColunas << ")"<< endl;
	
	for( unsigned int i = 0 ; i < pessoas.size() ; i++){
		oss << endl << pessoas[i]->getAsString();
	}
	for( unsigned int i = 0 ; i < mosquitos.size() ; i++){
		oss << endl << mosquitos[i]->getAsString();
	}
	for( unsigned int i = 0 ; i < terrenos.size() ; i++){
		oss << endl << terrenos[i]->getAsString();
	}

	return oss.str();
}

void Mundo::libertarMemoriaPessoas(int k){
	if (k > int(pessoas.size()))
		k = int(pessoas.size());
	for( int i = 0 ; i < k ; i++){
		delete pessoas[i];
	}
	pessoas.clear();
}

void Mundo::libertarMemoriaMosquitos(int k){
	if (k > int(mosquitos.size()))
		k = int(mosquitos.size());
	for( int i = 0 ; i < k ; i++){
		delete mosquitos[i];
	}
	mosquitos.clear();
}

void Mundo::libertarMemoriaTerrenos(int k){
	if (k > int(terrenos.size()))
		k = int(terrenos.size());
	for( int i = 0 ; i < k ; i++){
		delete terrenos[i];
	}
	terrenos.clear();
}

void Mundo::libertarMemoriaSeresVivos(){
	libertarMemoriaPessoas(pessoas.size());
	libertarMemoriaMosquitos(mosquitos.size());
}


Mundo & Mundo::operator=(const Mundo & ob){
		if (this != &ob){
			libertarMemoriaPessoas(pessoas.size());
			libertarMemoriaMosquitos(mosquitos.size());
			libertarMemoriaTerrenos(terrenos.size());
			copiar(ob);
		}
		return *this;
}



Mundo::~Mundo(void)
{
	for(unsigned int i = 0 ; i < pessoas.size() ; i++){
		delete pessoas[i];
	}
	pessoas.clear();
	for(unsigned int i = 0 ; i < mosquitos.size() ; i++){
		delete mosquitos[i];
	}
	mosquitos.clear();
	for(unsigned int i = 0 ; i < terrenos.size() ; i++){
		delete terrenos[i];
	}
	terrenos.clear();
}


int Mundo::pesquisaPosicaoTerreno(int cm, int lm){

	if(getNumTerrenos() < 1)
		return -1;
	for ( int i=0; i < getNumTerrenos(); i++)
	{
		if (cm == getTerreno(i)->getCoord_c() && lm == getTerreno(i)->getCoord_l())
			return i;
	}
	return -1;

}

int Mundo::pesquisaPosicaoPessoa(int cm, int lm){

	if(getNumPessoas() < 1)
		return -1;
	for ( int i=0; i < getNumPessoas(); i++)
	{
		if (cm == getPessoa(i)->getCoord_c() && lm == getPessoa(i)->getCoord_l())
			return i;
	}
	return -1;

}

int Mundo::pesquisaPosicaoMosquito(int cm, int lm){

	if(getNumMosquitos() < 1)
		return -1;
	for ( int i=0; i < getNumMosquitos(); i++)
	{
		if (cm == getMosquito(i)->getCoord_c() && lm == getMosquito(i)->getCoord_l())
			return i;
	}
	return -1;

}