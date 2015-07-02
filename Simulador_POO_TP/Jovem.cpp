#include "Jovem.h"

#include "Mundo.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

Jovem::Jovem(Mundo* md): Pessoa (md)
{
	setValido(geraId());
	geraCoord(md->getNLinhas(), md->getNColunas());
	meuTempoDeInfecao=-1;
	meuTempoDeImunidade=-1;
	setTempoDeVida(1);
}

int Jovem::tempoDeImunidade=10;
int Jovem::tempoDeInfecao=8;
int Jovem::probImune=40;

bool Jovem::geraId(){
	
	int num = getNumSeresVivos();
	int resto = 0, resto2 = 0;
	char iId[4];

	if(num < 10){
		strcpy(iId,"J00");
		iId[2] += num;
		setId(iId);
		return true;
	}else{
		if(num < 100)
		{
			strcpy(iId,"J00");
			resto = num%10;
			num = num/10;

			iId[1] += num;
			iId[2] += resto;
			setId(iId);
			return true;
		}else{
			strcpy(iId,"J00");
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

int Jovem::getTempoDeImunidade(){
	return tempoDeImunidade;
}

void Jovem::setTempoDeImunidade(int t){
	tempoDeImunidade = t;
}

int Jovem::getTempoDeInfecao(){
	return tempoDeInfecao;
}

void Jovem::setTempoDeInfecao(int t){
	tempoDeInfecao = t;
}

int Jovem::getProbImune(){
	return probImune;
}

void Jovem::setProbImune(int pr){
	probImune = pr;
}

Pessoa * Jovem::duplica(Mundo* md)const{
	Jovem * i = new Jovem( *this);
	i->setMundo(md);
	i->setValido(i->geraId());
	return i;
}

Jovem::~Jovem(void)
{
}

string Jovem::getAsString( ){
	ostringstream oss;
	oss << Pessoa::getAsString()
		<< "\n Tempo Imunidade:" << tempoDeImunidade 
		<< "\n Tempo de Infecao: " << tempoDeInfecao
		<< "\n Probabilidade de ficar Imune: " << probImune;
	return oss.str();
}


void Jovem::mov(){//Movimento aleatorio para a primeira fase, 23% para se mover em qualquer uma das direçoes(se possivel por limites ou posicao preenchida) e 8% de ficar na mesma posição
	int prob, x, y, x_or, y_or;
	bool mov = 0;
	
	x = getCoord_c();
	y = getCoord_l();
	x_or = x;
	y_or = y;


	//while(!mov){
		srand (time (NULL));
		prob = rand() % 100 + 1;//movimento do jovem

		if( prob <= 65 ){//Aproxima-se de pessoa

			for(int i = -2 ; i < 3 ; i++){//ver vizinhanca se existe alguma pessoa

				for(int j = -2 ; j < 3 ; j++){

					if((i < -1 || i > 1) || (j < -1 || j > 1)){
						
						if(getPMundo()->pesquisaPosicaoPessoa(x+j,y+i) != -1){//se existir pessoa

						
								if(x<x+j && posicaoPessoa(x_or+1,y_or)){//direita
									++x;
									mov=1;
								}else{
									if(x>x+j && posicaoPessoa(x_or-1,y_or)){//esquerda
										--x;
										mov=1;
									}
								}

								if(y<y+i && posicaoPessoa(x,y_or+1)){//baixo
									++y;
									mov=1;
								}else{
									if(y>y+i && posicaoPessoa(x,y_or-1)){//cima
										--y;
										mov=1;
									}
								}

								if(x==x_or){
									if(x<x+j && posicaoPessoa(x+1,y)){//direita
										++x;
										mov=1;
									}else{
										if(x>x+j && posicaoPessoa(x-1,y)){//esquerda
											--x;
											mov=1;
										}
									}
								}

								setCoord_c(x);
								setCoord_l(y);

								if(mov == 1)
									return;

						}					
					}
				}
			}
	
		}else{
			if(prob <= 90){//afasta-se de pessoa

				for(int i = -2 ; i < 3 ; i++){//ver vizinhanca se existe alguma pessoa

					for(int j = -2 ; j < 3 ; j++){

						if((i < -1 || i > 1) || (j < -1 || j > 1)){

							if(getPMundo()->pesquisaPosicaoPessoa(x+j,y+i) != -1){//se existir pessoa
						
											
									if((x<x+j && posicaoPessoa(x_or-1,y_or)) && x_or > 0 ){//afasta-se esquerda 
										--x;
										mov=1;
									}else{
										if(x>x+j && (posicaoPessoa(x_or+1,y_or) && x_or < getPMundo()->getNColunas()-1)){//afasta-se direita
											++x;
											mov=1;
										}
									}

									if((y<y+i && posicaoPessoa(x,y_or-1)) && y_or > 0){//afasta-se cima
										--y;
										mov=1;
									}else{
										if(y>y+i && ((posicaoPessoa(x,y_or+1)) && y_or < getPMundo()->getNLinhas()-1)){//afasta-se baixo
											++y;
											mov=1;
										}
									}

									if(x==x_or){
										if((x<x+j && posicaoPessoa(x-1,y)) && x_or > 0 ){
											--x;
											mov=1;
										}else{
											if(x>x+j && (posicaoPessoa(x+1,y) && x_or < getPMundo()->getNColunas()-1)){
												++x;
												mov=1;
											}
										}
									}

									setCoord_c(x);
									setCoord_l(y);
									if(mov == 1)
										return;

							}					
						}
					}
				}



			}else{//fica quieto
				mov = 1;
				//setCoord_l(5);
				return;

			}
		}

	//}//while

}

void Jovem::accao(){//comportamento do jovem em cada iteracao, pode reagir a infecao, ser infectado ou movimentar-se
	int prob;


	if(getEstadoDeSaude() == "VERMELHO"){
		if(meuTempoDeInfecao < tempoDeInfecao-1){
			++meuTempoDeInfecao;
		}else{
			meuTempoDeInfecao=-1;
			prob = rand() % 100 + 1;//probabilidade de morrer ou ficar imune durante um certo tempo

			if(prob <= probImune){//fico imune
				setEstadoDeSaude("AZUL");
				setMeuTempoDeImunidade(0);
				return;

			}else{//se nao morro
				setTempoDeVida(0);
				return;
			}
		}
	}


	if(getEstadoDeSaude() == "AZUL"){
		if(meuTempoDeImunidade < tempoDeImunidade-1){
			++meuTempoDeImunidade;
		}else{
			setMeuTempoDeImunidade(-1);
			setEstadoDeSaude("VERDE");
			return;
		}	
	}


	if(verPAdjacentes())
		return;

	mov();


}

void Jovem::setMeuTempoDeInfecao(int t){
	meuTempoDeInfecao = t;
}

int Jovem::getMeuTempoDeInfecao(){
	return meuTempoDeInfecao;
}

void Jovem::setMeuTempoDeImunidade(int t){
	meuTempoDeImunidade = t;
}

int Jovem::getMeuTempoDeImunidade(){
	return meuTempoDeImunidade;
}

bool Jovem::verPAdjacentes(){
	int x, y;
	x = getCoord_c();
	y = getCoord_l();


	for(int i = -1 ; i < 2 ; i++){

		for(int j = -1 ; j < 2 ; j++){

			if(x+j != x || y+i != y){
				if(getPMundo()->pesquisaPosicaoPessoa(x+j,y+i) != -1){
					if(getPMundo()->getPessoa(getPMundo()->pesquisaPosicaoPessoa(x+j,y+i))->getEstadoDeSaude() == "VERMELHO" && getEstadoDeSaude() == "VERDE"){
						setEstadoDeSaude("VERMELHO");
						setMeuTempoDeInfecao(0);
						return 1;


					}
				}
			}
		}
	}

	if(getPMundo()->pesquisaPosicaoMosquito(x,y) != -1 && getEstadoDeSaude() == "VERDE"){
		setEstadoDeSaude("VERMELHO");
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