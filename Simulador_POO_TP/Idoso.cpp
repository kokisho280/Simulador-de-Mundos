#include "Idoso.h"


#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include "Mundo.h"

using namespace std;




Idoso::Idoso(Mundo* md): Pessoa (md)
{
	setValido(geraId());
	
	geraCoord(md->getNLinhas(), md->getNColunas());
	
	setTempoDeVida(tempoDeVidaI);
	meuTempoDeInfecao=-1;
}

int Idoso::tempoDeInfecao=8;
int Idoso::tempoDeVidaI=20;


bool Idoso::geraId(){
	
	int num = getNumSeresVivos();
	int resto = 0, resto2 = 0;
	char iId[4];

	if(num < 10){
		strcpy(iId,"I00");
		iId[2] += num;
		setId(iId);
		return true;
	}else{
		if(num < 100)
		{
			strcpy(iId,"I00");
			resto = num%10;
			num = num/10;

			iId[1] += num;
			iId[2] += resto;
			setId(iId);
			return true;
		}else{
			strcpy(iId,"I00");
			resto = num%10;
			num = num/10;
			resto2 = num%10;
			iId[1] += resto2;
			iId[2] += resto;
			setId(iId);
			return true;
		}
	
	
	}
	
	
	return false;

}

int Idoso::getTempoDeInfecao(){
	return tempoDeInfecao;
}

void Idoso::setTempoDeInfecao(int t){
	tempoDeInfecao = t;
}

int Idoso::getTempoDeVidaI(){
	return tempoDeVidaI;
}

void Idoso::setTempoDeVidaI(int t){
	tempoDeVidaI = t;
}

Pessoa * Idoso::duplica(Mundo* md)const{
	Idoso * i = new Idoso( *this);
	i->setMundo(md);
	i->setValido(i->geraId());
	return i;
}

string Idoso::getAsString( ){
	ostringstream oss;
	oss << Pessoa::getAsString()
		<< "\n Tempo de Infecao: " << tempoDeInfecao
		<< "\n Tempo de Vida I: " << tempoDeVidaI;
	return oss.str();
}


Idoso::~Idoso(void)
{
}


void Idoso::mov(){//Movimento aleatorio para a primeira fase, 23% para se mover em qualquer uma das direçoes(se possivel por limites ou posicao preenchida) e 8% de ficar na mesma posição
	int prob, x, y;
	bool mov = 0;

	int liml = getPMundo()->getNLinhas()-1; 
	int limc = getPMundo()->getNColunas()-1;

	x = getCoord_c();
	y = getCoord_l();

	while(!mov){
		prob = rand() % 100 + 1;

		if(( prob <= 23 && x > 0 ) && posicaoPessoa(x-1,y)){//Esq
			//x = getCoord_c();
			setCoord_c(--x);
			mov=1;
		}else{
			if(( prob <= 46 && x < limc ) && posicaoPessoa(x+1,y)){//Dir
				//x = getCoord_c();
				setCoord_c(++x);
				mov=1;
			}else{
				if(( prob <= 69 && y < liml ) && posicaoPessoa(x,y+1)){//baixo
					//y = getCoord_l();
					setCoord_l(++y);
					mov=1;
				}else{
					if((prob <= 92 && y > 0) && posicaoPessoa(x,y-1)){//cima
					//y = getCoord_l();
					setCoord_l(--y);
					mov=1;
					}else{
						if(prob <= 100)
						mov = 1;
					}
				}
			}
		}
	}


}

void Idoso::accao(){
	int vida;
	if(getEstadoDeSaude() == "VERDE"){
		vida = getTempoDeVida();
		setTempoDeVida(--vida);

	}

	

	if(getEstadoDeSaude() == "VERMELHO"){
		if(meuTempoDeInfecao < tempoDeInfecao-1){
			++meuTempoDeInfecao;
		}else{
			meuTempoDeInfecao=-1;
			
			setTempoDeVida(0);
			return;
		}
	}

	if(verPAdjacentes())
		return;

	mov();
}



bool Idoso::verPAdjacentes(){
	int x, y;
	x = getCoord_c();
	y = getCoord_l();


	for(int i = -1 ; i < 2 ; i++){

		for(int j = -1 ; j < 2 ; j++){

			if(x+j != x || y+i != y){
				if(getPMundo()->pesquisaPosicaoPessoa(x+j,y+i) != -1){
					if(getPMundo()->getPessoa(getPMundo()->pesquisaPosicaoPessoa(x+j,y+i))->getEstadoDeSaude() == "VERMELHO" && getEstadoDeSaude() == "VERDE"){
						setEstadoDeSaude("VERMELHO");
						setTempoDeVida(-1);
						setMeuTempoDeInfecao(0);
						return 1;


					}
				}
			}
		}
	}

	if(getPMundo()->pesquisaPosicaoMosquito(x,y) != -1 && getEstadoDeSaude() == "VERDE"){
		setEstadoDeSaude("VERMELHO");
		setTempoDeVida(-1);
		setMeuTempoDeInfecao(0);
		return 1;
	}

	if(getPMundo()->pesquisaPosicaoTerreno(x,y) != -1){
		if(getPMundo()->getTerreno(getPMundo()->pesquisaPosicaoTerreno(x,y))->getCor() == "AMARELO_CLARO" && getEstadoDeSaude() == "VERMELHO"){
			setEstadoDeSaude("VERDE");
			meuTempoDeInfecao=-1;
			return 1;
		}else{
			if(getPMundo()->getTerreno(getPMundo()->pesquisaPosicaoTerreno(x,y))->getCor() == "AMARELO" && getEstadoDeSaude() == "VERMELHO"){
				setTempoDeVida(0);
				return 1;
			}
		}
	}

	return 0;

}

void Idoso::setMeuTempoDeInfecao(int t){
	meuTempoDeInfecao = t;
}

int Idoso::getMeuTempoDeInfecao(){
	return meuTempoDeInfecao;
}