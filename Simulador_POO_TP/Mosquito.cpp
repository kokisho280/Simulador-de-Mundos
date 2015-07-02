#include "Mosquito.h"
#include "Mundo.h"

#include <iostream>
#include <string>
#include <sstream>


Mosquito::Mosquito(Mundo* md): Servivo (md)
{
	setValido(geraId());
	geraCoord(md->getNLinhas(), md->getNColunas());
	setTempoDeVida(tempoDeVidaM);
}

Mosquito::Mosquito(Mundo* md, int lm, int cm): Servivo (md)
{
	setValido(geraId());
	setCoord_l(lm);
	setCoord_c(cm);
	setTempoDeVida(tempoDeVidaM);
}

int Mosquito::tempoDeVidaM=10;

Mosquito * Mosquito::duplica(Mundo* md)const{
	Mosquito * i = new Mosquito( *this);
	i->setMundo(md);
	i->setValido(i->geraId());
	return i;
}


bool Mosquito::geraId(){
	
	int num = getNumSeresVivos();
	int resto = 0, resto2 = 0;
	char iId[4];

	if(num < 10){
		strcpy(iId,"M00");
		iId[2] += num;
		setId(iId);
		return true;
	}else{
		if(num < 100)
		{
			strcpy(iId,"M00");
			resto = num%10;
			num = num/10;

			iId[1] += num;
			iId[2] += resto;
			setId(iId);
			return true;
		}else{
			strcpy(iId,"M00");
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

void Mosquito::geraCoord(int lm, int cm){
	int x, y;
	bool fg = 0;
	srand (time (NULL));
	do{
		x = rand() % cm;
		y = rand() % lm;

		if(posicaoMosquito(x,y)){
			 setCoord_l(y);
			 setCoord_c(x);
			 fg = 1;
		}
	}while(!fg);
}

bool Mosquito::posicaoMosquito(int x, int y){//se posicao NAO tem pessoa(idoso neste caso) devolve verdadeiro
	if(getPMundo()->getNumMosquitos() < 1)
		return true;


	for(int i = 0 ; i < getPMundo()->getNumMosquitos() ; i++){
		if(x == getPMundo()->getMosquito(i)->getCoord_c() && y == getPMundo()->getMosquito(i)->getCoord_l())
			return false;
	}
	return true;

}

Mosquito::~Mosquito(void)
{
}

string Mosquito::getAsString( ){
	ostringstream oss;
	oss << Servivo::getAsString()
		<< "\n Tempo de Vida M:" << tempoDeVidaM;
	return oss.str();
}

void Mosquito::mov(){//Movimento aleatorio para a primeira fase, 23% para se mover em qualquer uma das direçoes(se possivel por limites ou posicao preenchida) e 8% de ficar na mesma posição
	int prob, x, y;
	bool mov = 0;
	
	int liml = getPMundo()->getNLinhas()-1;
	int limc = getPMundo()->getNColunas()-1;

	x = getCoord_c();
	y = getCoord_l();

	while(!mov){
		prob = rand() % 100 + 1;

		if(( prob <= 23 && x > 0 ) && posicaoMosquito(x-1,y)){//Esq
			//x = getCoord_c();
			setCoord_c(--x);
			mov=1;
		}else{
			if(( prob <= 46 && x < limc ) && posicaoMosquito(x+1,y)){//Dir
				//x = getCoord_c();
				setCoord_c(++x);
				mov=1;
			}else{
				if(( prob <= 69 && y < liml ) && posicaoMosquito(x,y+1)){//baixo
					//y = getCoord_l();
					setCoord_l(++y);
					mov=1;
				}else{
					if((prob <= 92 && y > 0) && posicaoMosquito(x,y-1)){//cima
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

void Mosquito::accao(){
	int vida;
	
	vida = getTempoDeVida();
	setTempoDeVida(--vida);

	


	/*if(verPAdjacentes())
		return;*/
	verPAdjacentes();




	//mov();
}

bool Mosquito::verPAdjacentes(){
	int x, y, x_or, y_or, prob, probm;
	bool mov=0;
	x = getCoord_c();
	y = getCoord_l();
	x_or = x;
	y_or = y;
	srand (time (NULL));

	for(int i = -1 ; i < 2 ; i++){

		for(int j = -1 ; j < 2 ; j++){

			if(x+j != x || y+i != y){
				if(getPMundo()->pesquisaPosicaoMosquito(x+j,y+i) != -1){//se existir mosquito a volta
					
					prob = rand() % 100 + 1;//prob de o mov ser de 1 casa ou de 2

					if(prob <= 100){

					probm = rand() % 2 + 1;//prob de o mov ser de 1 casa ou de 2

					if(probm == 1){
						if((x<x+j && posicaoMosquito(x_or-1,y_or)) && x_or > 0 ){//afasta-se esquerda 
							--x;
							mov=1;
						}else{
							if(x>x+j && ((posicaoMosquito(x_or+1,y_or)) && x_or < getPMundo()->getNColunas()-1)){//afasta-se direita
								++x;
								mov=1;
							}
						}
					}else{
						if((x<x+j && posicaoMosquito(x_or-2,y_or)) && x_or-1 > 0 ){//afasta-se esquerda 
							x-=2;
							mov=1;
						}else{
							if(x>x+j && ((posicaoMosquito(x_or+2,y_or)) && x_or+1 < getPMundo()->getNColunas()-1)){//afasta-se direita
								x+=2;
								mov=1;
							}
						}

					}

					probm = rand() % 2 + 1;//prob de o mov ser de 1 casa ou de 2

					if(probm == 1){
						if((y<y+i && posicaoMosquito(x,y_or-1)) && y_or > 0){//afasta-se cima
							--y;
							mov=1;
							}else{
								if(y>y+i && ((posicaoMosquito(x,y_or+1)) && y_or < getPMundo()->getNLinhas()-1)){//afasta-se baixo
									++y;
									mov=1;
								}
							}
					}else{
						if((y<y+i && posicaoMosquito(x,y_or-2)) && y_or-1 > 0){//afasta-se cima
							y-=2;
							mov=1;
							}else{
								if(y>y+i && ((posicaoMosquito(x,y_or+2)) && y_or+1 < getPMundo()->getNLinhas()-1)){//afasta-se baixo
									y+=2;
									mov=1;
								}
							}

					}


					if(x==x_or){

						probm = rand() % 2 + 1;//prob de o mov ser de 1 casa ou de 2

						if(probm == 1){
							if((x<x+j && posicaoMosquito(x_or-1,y_or)) && x_or > 0 ){//afasta-se esquerda 
								--x;
								mov=1;
							}else{
								if(x>x+j && ((posicaoMosquito(x_or+1,y_or)) && x_or < getPMundo()->getNColunas()-1)){//afasta-se direita
									++x;
									mov=1;
								}
							}
						}else{
							if((x<x+j && posicaoMosquito(x_or-2,y_or)) && x_or-1 > 0 ){//afasta-se esquerda 
								x-=2;
								mov=1;
							}else{
								if(x>x+j && ((posicaoMosquito(x_or+2,y_or)) && x_or+1 < getPMundo()->getNColunas()-1)){//afasta-se direita
									x+=2;
									mov=1;
								}
							}

						}

					}

					setCoord_c(x);
					setCoord_l(y);
					if(mov == 1)
						return 1;

					}else{
						mov = 1;
						return 1;
					}					
				}
			}
		}
	}





	for(int i = -3 ; i < 4 ; i++){

		for(int j = -3 ; j < 4 ; j++){

			if(x+j != x || y+i != y){
				if(getPMundo()->pesquisaPosicaoTerreno(x+j,y+i) != -1){//se existir terreno na vizinhanca
					if(getPMundo()->getTerreno(getPMundo()->pesquisaPosicaoTerreno(x+j,y+i))->getCor() == "AMARELO"){//e se esse terreno for pantano

						prob = rand() % 100 + 1;

						if(prob <= 50){//aproxima-se do pantano

							probm = abs(x-(x+j));

							if(probm == 1){
								if((x<x+j && posicaoMosquito(x_or+1,y_or)) && x_or < getPMundo()->getNColunas()-1){//aproxima-se dir
									++x;
									mov=1;
								}else{
									if(x>x+j && ((posicaoMosquito(x_or-1,y_or)) && x_or > 0 )){//aproxima-se esq
										--x;
										mov=1;
									}
								}
							}else{
								if((x<x+j && posicaoMosquito(x_or+2,y_or)) && x_or+1 < getPMundo()->getNColunas()-1){
									x+=2;
									mov=1;
								}else{
									if(x>x+j && ((posicaoMosquito(x_or-2,y_or)) && x_or-1 > 0  )){
										x-=2;
										mov=1;
									}
								}

								if(mov == 0){//se a distancia e maior k 1 mas nao consegue ir pa uma casa 2 distancia pelo - aproxima-se uma casa
									if((x<x+j && posicaoMosquito(x_or+1,y_or)) && x_or < getPMundo()->getNColunas()-1){
										++x;
										mov=1;
									}else{
										if(x>x+j && ((posicaoMosquito(x_or-1,y_or)) &&  x_or > 0)){
											--x;
											mov=1;
										}
									}
								}

							}

							probm = abs(y-(y+i));

							if(probm == 1){
								if((y<y+i && posicaoMosquito(x,y_or+1)) && y_or < getPMundo()->getNLinhas()-1){//aproxima-se cima
									++y;
									mov=1;
									}else{
										if(y>y+i && ((posicaoMosquito(x,y_or-1)) && y_or > 0)){//aproxima-se baixo
											--y;
											mov=1;
										}
									}
							}else{
								if((y<y+i && posicaoMosquito(x,y_or+2)) && y_or+1 < getPMundo()->getNLinhas()-1){
									y+=2;
									mov=1;
									}else{
										if(y>y+i && ((posicaoMosquito(x,y_or-2)) && y_or-1 > 0)){
											y-=2;
											mov=1;
										}
									}

								if(mov == 0){
									if((y<y+i && posicaoMosquito(x,y_or+1)) && y_or < getPMundo()->getNLinhas()-1){//afasta-se cima
									++y;
									mov=1;
									}else{
										if(y>y+i && ((posicaoMosquito(x,y_or-1)) && y_or > 0)){//afasta-se baixo
											--y;
											mov=1;
										}
									}
								}

							}


							setCoord_c(x);
							setCoord_l(y);
							if(mov == 1)
								return 1;

							}else{
								if(prob <=90){

									if((x<x+j && posicaoMosquito(x_or-2,y_or)) &&  x_or-1 > 0 ){
										x-=2;
										mov=1;
									}else{
										if(x>x+j && ((posicaoMosquito(x_or+2,y_or)) && x_or+1 < getPMundo()->getNColunas()-1)){
											x+=2;
											mov=1;
										}
									}

									if(mov == 0){//se a distancia e maior k 1 mas nao consegue ir pa uma casa 2 distancia pelo - afasta-se uma casa
										if((x<x+j && posicaoMosquito(x_or-1,y_or)) && x_or > 0){
											--x;
											mov=1;
										}else{
											if(x>x+j && ((posicaoMosquito(x_or+1,y_or)) &&  x_or < getPMundo()->getNColunas()-1)){
												++x;
												mov=1;
											}
										}


										if((y<y+i && posicaoMosquito(x,y_or-2)) && y_or+1 > 0){
											y-=2;
											mov=1;
											}else{
												if(y>y+i && ((posicaoMosquito(x,y_or+2)) && getPMundo()->getNLinhas()-1 )){
													y+=2;
													mov=1;
												}
											}

										if(mov == 0){
											if((y<y+i && posicaoMosquito(x,y_or-1)) && y_or > 0){//afasta-se cima
											--y;
											mov=1;
											}else{
												if(y>y+i && ((posicaoMosquito(x,y_or+1)) && y_or < getPMundo()->getNLinhas()-1)){//afasta-se baixo
													++y;
													mov=1;
												}
											}
										}
									}


								}else{
									mov = 1;
									return 1;
								}

							}
						}//if
				}//if
			}//if
		}//for
	}//for
	


	if(getPMundo()->pesquisaPosicaoTerreno(x,y) != -1){
		if(getPMundo()->getTerreno(getPMundo()->pesquisaPosicaoTerreno(x,y))->getCor() == "AMARELO_CLARO"){
			setTempoDeVida(0);
			return 1;
		}
	}


	return 0;

}