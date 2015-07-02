#include "Simulador.h"
#include <sstream>
#include <fstream>
#include "Jovem.h"
#include "Idoso.h"


const static int maxLinha = 100;
const static int maxColuna = 100;

Simulador::Simulador(void)
{
	
	con.setScreenSize(50,78);
	con.setTextSize(8,8);
}




void Simulador::acrescentaMundo(string n, int l, int c){
	
	Mundo * m = new Mundo(n ,l, c);
	
	Universo.push_back(m);
	
}

void Simulador::apagaMundo(string n){

	for(unsigned int i = 0 ; i < Universo.size(); i++){
		if(Universo[i]->getNome() == n){
			delete Universo[i];
			Universo.erase(Universo.begin() + i);
		}
	}
	

}

void Simulador::acrescentaMundoCopia(string n, Mundo * md){
	
	Mundo * m = new Mundo(*md);
	m->setNome(n);
	
	Universo.push_back(m);
	
}

void Simulador::atribuiM(Mundo * mdDest, Mundo * mdOri, string n){
	
	*mdDest = *mdOri;
	mdDest->setNome(n);
	
}

void Simulador::simula(string n){
	vector <Mundo *> UniversoAux;

	UniversoAux.push_back(pesquisaMundoNome(n));

	for(unsigned int i = 0 ; i < Universo.size(); i++){
		if(Universo[i]->getNome() == n)
			continue;
		else
			UniversoAux.push_back(Universo[i]);
	}
	Universo.clear();
	for(unsigned int i = 0 ; i < UniversoAux.size(); i++){
		Universo.push_back(UniversoAux[i]);
	}
	UniversoAux.clear();
}

Mundo * Simulador::pesquisaMundoNome(string n){

	for( unsigned int i = 0 ; i < Universo.size() ; i++){
		if(Universo[i]->getNome() == n)
			return Universo[i];
	}
	return 0;

}

bool Simulador::pesquisaMundo(string n){
	for( unsigned int i = 0 ; i < Universo.size() ; i++){
		if(Universo[i]->getNome() == n)
			return 1;
	}
	return 0;
}


string Simulador::getAsString()
{
	ostringstream oss;
	
	for( unsigned int i = 0 ; i < Universo.size() ; i++){
		oss << endl << Universo[i]->getAsString();
	}

	return oss.str();

}





Simulador::~Simulador(void)
{
	for( unsigned int i = 0 ; i < Universo.size() ; i++){
		delete Universo[i];
	}
	Universo.clear();
	
}



void Simulador::inicio(){
	int nl = 0, nc = 0, ite = 0, cont = 0, fg = 0;
	bool b;

	
	do{
		con.clrscr();
		con.gotoxy(20,5);
		cout << "Simulador realizado no ambito da disciplina de\n\n\t\t\t\t";
		con.setTextColor(con.VERMELHO_CLARO);
	
		cout << "PROGRAMACAO ORIENTADA A OBJECTOS\n\n\n\t";
	

		con.setTextColor(con.VERMELHO);
		con.gotoxy(50,35);
		con.setBackgroundColor(con.CINZENTO);
		cout << " ISEC ";
		con.setTextColor(con.CINZENTO);
		con.setBackgroundColor(con.VERMELHO);
		cout << " DEIS ";
		con.setTextColor(con.CINZENTO);
		con.setBackgroundColor(con.PRETO);
		cout << "   2012 - 2013";
		con.gotoxy(25,45);
		cout << "Listar comandos <instrucoes>";
		con.setTextColor(con.BRANCO);
		con.gotoxy(0,15);
		b = comando(ite,fg, nl, nc);

	}while(Universo.size()<1 && b );
	if(Universo.size()>0){
		do{
			con.clrscr();
		
			desenhaGrelha(nl, nc, fg);
			desenhaEntidades(nl, nc);

			
			con.setBackgroundColor(con.PRETO);
			cout << "\t";
			for(int x = 0; x < 60 ; x++)
				cout << "=";
			cout << endl << endl << endl;
			con.setBackgroundColor(con.AZUL_CLARO);
			cout << " " <<  Universo[0]->getNome() << " ";
			con.setBackgroundColor(con.PRETO);
		
			
		
			if(ite == cont){
				b = comando(ite, fg, nl, nc);
				if(cont > ite)
					cont = ite;
			}
			while(ite != cont){
			Universo[0]->setTempo(ite);				
			Universo[0]->movEntidades();
			Universo[0]->eliminarSerVivosVida();		
			Universo[0]->actualizaNumPessoas();
			cont++;
			}

			//Universo[0]->actualizaNumPessoas();
		}while(b);
	}
}


bool Simulador::comando(int & ite, int & fg, int & nl, int & nc){
	
	stringstream strcmd;
	string nCom, para1, para2, com;
	int op1,op2;
	char tecla;

	int l = nl, c = nc;

	vector<string> opcoes, divcmd;


	opcoes.push_back("sair");
	opcoes.push_back("load");
	opcoes.push_back("criai");
	opcoes.push_back("minimodepessoas");
	opcoes.push_back("prox");
	opcoes.push_back("simples");
	opcoes.push_back("completo");
	opcoes.push_back("mundo");
	opcoes.push_back("exec");
	opcoes.push_back("scroll");
	opcoes.push_back("instrucoes");
	opcoes.push_back("cls");
	opcoes.push_back("criam");
	opcoes.push_back("criaj");
	opcoes.push_back("hospital");
	opcoes.push_back("pantano");
	opcoes.push_back("criacopia");
	opcoes.push_back("simula");
	opcoes.push_back("apaga");
	opcoes.push_back("atribui");
	opcoes.push_back("imun");
	opcoes.push_back("infej");
	opcoes.push_back("infei");
	opcoes.push_back("matasv");

	int opcao =0;
	do {
		
		
		cin.ignore(cin.rdbuf()->in_avail());
		

		cout << " >";
		getline(cin,com);
		if(com == "")com = "x";
		divcmd.clear();
		strcmd.clear();
		strcmd<<com;

		while (strcmd >> nCom)
			divcmd.push_back(nCom);
		
		nCom = divcmd[0];
	
		opcao = escolheOpcao( opcoes, nCom);
		
		switch (opcao){

			case 0: if(divcmd.size()!=1){
						cout << "\nPor favor insira um comando valido\n>sair\n\n";
						opcao = -1;
						break;
					}
					do{
						cout << "\n\tTem a certeza que pretende sair da simulacao?\n\n\t\tSim[s]\t\t\tNao[n]\n\n\t";
						tecla = con.getch();
						tecla = toupper(tecla);
							if(tecla == 'S')
									return false;
							if(tecla == 'N')
									return true;
					}while(tecla != 'S' || tecla != 'N');
					

			case 1: if(divcmd.size()!=2){
						cout << "\nPor favor insira um comando valido\n>load nomedoficheiro\n\n";
						break;
					}
					//if(Universo.size()>0){
						if(load(divcmd[1]))
							return true;
					/*}else{
						cout << "\nNao existe nenhum mundo para executar os \nos comandos lidos\n\n";
						break;					
					}*/
					
					cout << "\nErro ao ler do ficheiro\n\n";
					break;
					
			case 2: if(divcmd.size()!=2){
						cout << "\nPor favor insira um comando valido\n>criai numero\n\n";
						break;
					}
					op1=atoi(divcmd[1].c_str());
					if(!verificaCriai(op1)){
						cout << "\nPor favor insira um valor positivo valido\n\n";
						break;
					}
					if(Universo.size()>0){
						if(Universo[0]->getNColunas()*Universo[0]->getNLinhas()-Universo[0]->getNumPessoas() >= op1){
							Universo[0]->acrescentaNIdosos(op1);
							return true;
						}else{
							cout << "\nNumero de idosos que pretende criar nao cabe no mundo\n\n";
						break;
						}

					}else{
						cout << "\nNao existe nenhum mundo onde colocar os idosos\n\n";
						break;
					}
					
			
			case 3: if(divcmd.size()!=2){
						cout << "\nPor favor insira um comando valido\n>minimodepessoas numero\n\n";
						break;
					}
					op1=atoi(divcmd[1].c_str());
					if(!verificaPositivo(op1)){
						cout << "\nPor favor insira um valor positivo valido\n\n";
						
						break;
					}
					if(Universo.size()>0){
						if(Universo[0]->getNColunas()*Universo[0]->getNLinhas() >= op1){
							Universo[0]->setNumMinPessoas(op1);
							return true;
						}else{
							cout << "\nNumero minimodepessoas maior que espaco no mundo\n\n";
						break;
						}
											
					}else{
						cout << "\nNao existe nenhum mundo onde definir o \nnumero minimo de pessoas\n\n";
						break;
					}

			case 4: if(divcmd.size()!=1){
						cout << "\nPor favor insira um comando valido\n>prox\n\n";
						break;
					}
					if(Universo.size()>0){
						ite++;
						return true;
					}else{
						cout << "\nNao existe nenhum mundo para simular\n\n";
						break;
					}
					
			case 5: if(divcmd.size()!=1){
						cout << "\nPor favor insira um comando valido\n>simples\n\n";
						break;
					}
					if(Universo.size()>0){
						fg = 0;
						return true;
					}else{
						cout << "\nNao existe nenhum mundo para se puder \nvisualizar a simulacao\n\n";
						break;					
					}

			case 6: if(divcmd.size()!=1){
						cout << "\nPor favor insira um comando valido\n>completo\n\n";
						break;
					}
					if(Universo.size()>0){
						fg = 1;
						return true;
					}else{
						cout << "\nNao existe nenhum mundo para se puder \nvisualizar a simulacao\n\n";
						break;					
					}

			case 7: if(divcmd.size()!=4){
						cout << "\nPor favor insira um comando valido\n>mundo nome numerolinhas numerocolunas\n\n";
						break;
					}
					para1 = divcmd[1];
					op1=atoi(divcmd[2].c_str());
					op2=atoi(divcmd[3].c_str());
					if(!verificaMundo(para1, op1, op2)){
						cout << "\nLimites do mundo errados, por favor insira \nvalores para o numero de linhas e colunas \nentre 50 e 100\n\n";
						break;
					}

					if(!pesquisaMundo(para1)){
						acrescentaMundo( para1, op1, op2);
						return true;
					}
					cout << "\nJa existe um mundo com esse nome\n\n";
					break;

			case 8: if(divcmd.size()!=2){
						cout << "\nPor favor insira um comando valido\n>exec numero\n\n";
						break;
					}
					op1=atoi(divcmd[1].c_str());
					if(!verificaPositivo(op1)){
						cout << "\nPor favor insira um valor positivo valido\n\n";
						break;
					}
					if(Universo.size()>0){
						ite+=op1;
						return true;
					}else{
						cout << "\nNao existe nenhum mundo para se simular\n\n";
						break;					
					}
					

			case 9:	if(divcmd.size()!=1){
						cout << "\nPor favor insira um comando valido\n>scroll\n\n";
						break;
					}
					if(Universo.size()>0){	
					con.clrscr();
					
					do{
						if(l != nl || c != nc){
							con.clrscr();
							l = nl;
							c = nc;
						}


						desenhaGrelha(nl, nc, fg);
						desenhaEntidades(nl, nc);
						cout << "\n\tPode movimentar a grelha com as setas\t\tESC - Voltar\n\n ";
						tecla = con.getch();
						if (tecla == con.ESQUERDA && nc-1>=0) nc--;
						if (tecla == con.DIREITA && nc+24<Universo[0]->getNColunas()) nc++;
						if (tecla == con.CIMA && nl-1 >= 0) nl--;
						if (tecla == con.BAIXO && nl+10<Universo[0]->getNLinhas()) nl++;

					
					}while(tecla != con.ESCAPE);
					return true;
					}else{
						cout << "\nNao pode fazer scroll sem existir um mundo \npara se visualizar\n\n";
						break;		
					}

			case 10: if(divcmd.size()!=1){
						cout << "\nPor favor insira um comando valido\n>instrucoes\n\n";
						break;
					 }
					 instrucoes();
					 return true;

			case 11: if(divcmd.size()!=1){
						cout << "\nPor favor insira um comando valido\n>cls\n\n";
						break;
					}
					 return true;

			case 12: if(divcmd.size()!=2){
						cout << "\nPor favor insira um comando valido\n>criam numero\n\n";
						break;
					}
					op1=atoi(divcmd[1].c_str());
					if(!verificaCriai(op1)){
						cout << "\nPor favor insira um valor positivo valido\n\n";
						break;
					}
					if(Universo.size()>0){
						if(Universo[0]->getNColunas()*Universo[0]->getNLinhas()-Universo[0]->getNumMosquitos() >= op1){
							Universo[0]->acrescentaNMosquitos(op1);
							return true;
						}else{
							cout << "\nNumero de mosquitos que pretende criar nao cabe no mundo\n\n";
						break;
						}						
					}else{
						cout << "\nNao existe nenhum mundo onde colocar os Mosquitos\n\n";
						break;
					}
					

			case 13: if(divcmd.size()!=2){
						cout << "\nPor favor insira um comando valido\n>criaj numero\n\n";
						break;
					}
					op1=atoi(divcmd[1].c_str());
					if(!verificaCriai(op1)){
						cout << "\nPor favor insira um valor positivo valido\n\n";
						break;
					}
					if(Universo.size()>0){
						if(Universo[0]->getNColunas()*Universo[0]->getNLinhas()-Universo[0]->getNumPessoas() >= op1){
							Universo[0]->acrescentaNJovens(op1);
							return true;
						}else{
							cout << "\nNumero de jovens que pretende criar nao cabe no mundo\n\n";
						break;
						}		
						
					}else{
						cout << "\nNao existe nenhum mundo onde colocar os Jovens\n\n";
						break;
					}

			case 14: if(divcmd.size()!=3){
						cout << "\nPor favor insira um comando valido\n>hospital linha coluna\n\n";
						break;
					}
					if(Universo.size()>0){
						op1=atoi(divcmd[1].c_str());
						op2=atoi(divcmd[2].c_str());
						if(!verificaLimites(op1, op2)){
							cout << "\nImpossivel criar hospital fora dos limites do mundo\n Linhas(0-" << Universo[0]->getNLinhas()-1 <<"d) Colunas(0-" << Universo[0]->getNColunas()-1 << ")\n";
							break;
						}
						if(!verificaTerreno(op1,op2)){
							cout << "\nImpossivel criar hospital nestas coordenadas\n";
							break;
						}
					
						Universo[0]->acrescentaHospital(op1,op2);
						return true;
					}else{
						cout << "\nNao existe nenhum mundo onde colocar o Hospital\n\n";
						break;
					}
					
			case 15: if(divcmd.size()!=3){
						cout << "\nPor favor insira um comando valido\n>Pantano linha coluna\n\n";
						break;
					}
					if(Universo.size()>0){
						op1=atoi(divcmd[1].c_str());
						op2=atoi(divcmd[2].c_str());
						if(!verificaLimites(op1, op2)){
							cout << "\nImpossivel criar hospital fora dos limites do mundo\n Linhas(0-" << Universo[0]->getNLinhas()-1 <<"d) Colunas(0-" << Universo[0]->getNColunas()-1 << ")\n";
							break;
						}
						if(!verificaTerreno(op1,op2)){
							cout << "\nImpossivel criar hospital nestas coordenadas\n";
							break;
						}
					
						Universo[0]->acrescentaPantano(op1,op2);
						return true;
						}else{
						cout << "\nNao existe nenhum mundo onde colocar o Pantano\n\n";
						break;
					}
					
			case 16: if(divcmd.size()!=3){
						cout << "\nPor favor insira um comando valido\n>criacopia novo outro\n\n";
						break;
					}
					 if(Universo.size()>0){//cria um mundo com o nome novo como cópia do mundo com o nome outro
						para1=divcmd[1].c_str();
						para2=divcmd[2].c_str();

						if(pesquisaMundo(para2) == 1){//se encontrar mundo com esse nome
							if(!pesquisaMundo(para1)){
								acrescentaMundoCopia(para1,pesquisaMundoNome(para2));
								return true;
							}
							cout << "\nJa existe um mundo com esse nome(novo)\n\n";
							break;
						

						}else{
							cout << "\nNao existe nenhum mundo com esse nome(outro)\n\n";
						break;
						}

					 }else{
						cout << "\nNao existe nenhum mundo para copiar\n\n";
						break;
					}

			case 17: if(divcmd.size()!=2){
						cout << "\nPor favor insira um comando valido\n>simula nome\n\n";
						break;
					}
					  if(Universo.size()>0){
						  para1=divcmd[1].c_str();
						  if(pesquisaMundo(para1) == 1){//se encontrar mundo com esse nome
							  simula(para1);
							  ite=Universo[0]->getTempo();
							  
							  return true;
							}else{
							cout << "\nNao existe nenhum mundo com esse nome\n\n";
						break;
						}
					  }else{
						cout << "\nNao existe nenhum mundo para simular\n\n";
						break;
					}

			case 18: if(divcmd.size()!=2){
						cout << "\nPor favor insira um comando valido\n>apaga nome\n\n";
						break;
					}
					 if(Universo.size()>0){
						  para1=divcmd[1].c_str();
						  if(pesquisaMundo(para1) == 1){//se encontrar mundo com esse nome
							  if(para1 == Universo[0]->getNome()){
									cout << "\nMundo que pretende apagar e o k esta a ser simulado\n\n";
									break;
								}
							  apagaMundo(para1);

							  return true;
							}else{
							cout << "\nNao existe nenhum mundo com esse nome\n\n";
						break;
						}

					}else{
						cout << "\nNao existe nenhum mundo para apagar\n\n";
						break;
					}

			case 19: if(divcmd.size()!=3){
						cout << "\nPor favor insira um comando valido\n>atribui destino origem\n\n";
						break;
					}
					 if(Universo.size()>0){
						para1=divcmd[1].c_str();
						para2=divcmd[2].c_str();

						if(pesquisaMundo(para2) == 1){//se encontrar mundo com nome origem
							if(pesquisaMundo(para1) == 1){//se encontrar mundo com nome destino
								atribuiM(pesquisaMundoNome(para1),pesquisaMundoNome(para2), para1);
								return true;
							}else{
							cout << "\nNao existe nenhum mundo com esse nome(destino)\n\n";
							break;
						}

						}else{
							cout << "\nNao existe nenhum mundo com esse nome(origem)\n\n";
						break;
						}

					}else{
						cout << "\nNao existe nenhum mundo para se fazer atribuicao\n\n";
						break;
					}

			case 20: if(divcmd.size()!=2){
						cout << "\nPor favor insira um comando valido\n>imun numero\n\n";
						break;
					}
					 if(Universo.size()>0){
						op1=atoi(divcmd[1].c_str());
						if(!verificaPositivo(op1)){
							cout << "\nPor favor insira um valor positivo valido\n\n";
							break;
						}
						Jovem::setTempoDeImunidade(op1);
						return 1;

					}else{
						cout << "\nNao existe nenhum mundo com jovens\n\n";
						break;
					}

			case 21: if(divcmd.size()!=2){
						cout << "\nPor favor insira um comando valido\n>infej numero\n\n";
						break;
					}
					 if(Universo.size()>0){
						op1=atoi(divcmd[1].c_str());
						if(!verificaPositivo(op1)){
							cout << "\nPor favor insira um valor positivo valido\n\n";
							break;
						}
						Jovem::setTempoDeInfecao(op1);
						return 1;

					}else{
						cout << "\nNao existe nenhum mundo com jovens\n\n";
						break;
					}

			case 22: if(divcmd.size()!=2){
						cout << "\nPor favor insira um comando valido\n>infei numero\n\n";
						break;
					}
					 if(Universo.size()>0){
						op1=atoi(divcmd[1].c_str());
						if(!verificaPositivo(op1)){
							cout << "\nPor favor insira um valor positivo valido\n\n";
							break;
						}
						Idoso::setTempoDeInfecao(op1);
						return 1;

					}else{
						cout << "\nNao existe nenhum mundo com jovens\n\n";
						break;
					}

			case 23: if(divcmd.size()!=1){
						cout << "\nPor favor insira um comando valido\n>matasv\n\n";
						break;
					}
					 if(Universo.size()>0){
						 Universo[0]->eliminarSerVivos();
						 return 1;

					}else{
						cout << "\nNao existe nenhum mundo\n\n";
						break;
					}

			case -1: cout << "\nComando invalido\n\n";
					 break;
					
		}
		
		
	}while (opcao != 0);
}

bool Simulador::verificaMundo(string para1, int op1, int op2){
	if((op1 < 50 || op1 > maxLinha) || (op2 < 50 || op2 > maxColuna))
		return false;
	return true;
	
}

bool Simulador::verificaLimites(int op1, int op2){
	if((op1 < 0 || op1 > Universo[0]->getNLinhas()-1) || (op2 < 0 || op2 > Universo[0]->getNColunas()-1))
		return false;
	return true;
}

bool Simulador::verificaTerreno(int op1, int op2){

	if(Universo[0]->pesquisaPosicaoTerreno(op2,op1) == -1)
		return true;
	return false;
}

bool Simulador::verificaCriai(int op1){
	if(op1 <= 0)
		return false;
	return true;
}

bool Simulador::verificaPositivo(int op1){
	if(op1 < 0)
		return false;
	return true;
}


int Simulador::escolheOpcao( vector<string> opcoes, string nCom){
	int opcao = -1;
	
	
	for ( unsigned int i = 0 ; i < opcoes.size() ; i++){
		if(nCom == opcoes[i]){
			return i;
			
		}
	}
	
	return opcao;
}

void Simulador::desenhaGrelha(int nl, int nc, int fg){

	int x = 3, y = 1,n, i, resto, resto2;
	int nct = nc, nlt = nl;
	int cc = nc, ll = nl;
	char numc[4] = "000", numl[4] = "000";
	//string str("216");
	if(nlt < 10){ 
		numl[2]+=nl;
	}else{
		if(nlt < 100)
			{			
			resto = nl%10;
			nlt =nlt/10;

			numl[1] += nlt;
			numl[2] += resto;
			
			}else{
			resto = nlt%10;
			nlt = nlt/10;
			resto2 = nlt%10;
			numl[1] += resto2;
			numl[2] += resto;
			
		}

	}

	if(nct < 10){ 
		numc[2]+=nc;
	}else{
		if(nct < 100)
			{			
			resto = nct%10;
			nct =nct/10;

			numc[1] += nct;
			numc[2] += resto;
			
			}else{
			resto = nct%10;
			nct = nct/10;
			resto2 = nct%10;
			numc[1] += resto2;
			numc[2] += resto;
			
		}

	}
	
	int nlin = Universo[0]->getNLinhas();
	int ncol = Universo[0]->getNColunas();

	if (nlin > 10)
		nlin = 10;
	if (ncol > 24)
		ncol = 24;

	con.gotoxy(x,y);
	for(n=0;n<ncol;n++)
	{
		if(n%2 == 0){
			y = 1;
			con.gotoxy(x,y);
		}else{
			y = 2;
			con.gotoxy(x,y);
		}

		if(numc[2]<'9'){
		cout << numc;
		numc[2] += 1;
		}else{
			if(numc[1]<'9'){
			cout << numc;
			numc[1] += 1;
			numc[2] = '0';	
			}else{
				cout << numc;
				numc[0] += 1;
				numc[1] = '0';
				numc[2] = '0';	
			}
		}
		x+=3;

	}
	x = 0;
	y = 3;
	con.gotoxy(x,y);
	for(n=0;n<nlin;n++)
	{/*
		if(n%2 == 0){
			y = 1;
			c.gotoxy(x,y);
		}else{
			y = 2;
			c.gotoxy(x,y);
		}*/

		if(numl[2]<'9'){
		cout << numl;
		numl[2] += 1;
		}else{
			if(numl[1]<'9'){
			cout << numl;
			numl[1] += 1;
			numl[2] = '0';	
			}else{
				cout << numl;
				numl[0] += 1;
				numl[1] = '0';
				numl[2] = '0';	
			}
		}
		y+=3;
		con.gotoxy(x,y);

	}
	x = 3;
	y = 3;
	for(n=0;n<nlin;n++){

		for(i=0;i<ncol;i++){

			if(n%2 == 0){
				if(i%2 == 0){
					con.gotoxy(x,y);
					con.setBackgroundColor(con.CINZENTO);
					cout << "   ";
					y++;
					con.gotoxy(x,y);
					cout << "   ";
					y++;
					con.gotoxy(x,y);
					cout << "   ";
					y -= 2;
					x += 3;
				
				}else{
				
					con.gotoxy(x,y);
					con.setBackgroundColor(con.BRANCO);
					cout << "   ";
					y++;
					con.gotoxy(x,y);
					cout << "   ";
					y++;
					con.gotoxy(x,y);
					cout << "   ";
					y -= 2;
					x += 3;
				
				}
			}else{
				if(i%2 != 0){
					con.gotoxy(x,y);
					con.setBackgroundColor(con.CINZENTO);
					cout << "   ";
					y++;
					con.gotoxy(x,y);
					cout << "   ";
					y++;
					con.gotoxy(x,y);
					cout << "   ";
					y -= 2;
					x += 3;
				
				}else{
				
					con.gotoxy(x,y);
					con.setBackgroundColor(con.BRANCO);
					cout << "   ";
					y++;
					con.gotoxy(x,y);
					cout << "   ";
					y++;
					con.gotoxy(x,y);
					cout << "   ";
					y -= 2;
					x += 3;
				
				}

			}
		}

		y += 3;
		x = 3;
	}
	con.setBackgroundColor(con.PRETO);
	if(cc+24<Universo[0]->getNColunas()){
		con.gotoxy(74, 34);
		cout << ">";
	}
	if(cc>0){
		con.gotoxy(3,34);
		cout << "<";
	}
	if(ll+10<Universo[0]->getNLinhas()){
		con.gotoxy(76, 32);
		cout << "v";
	}
	if(ll>0){
		con.gotoxy(76,3);
		cout << "^";
	}




	if(fg){
		con.gotoxy(8, 34);
		cout << "N pessoas: " << Universo[0]->getNumPessoas();
		con.gotoxy(29, 34);
		cout << "N mortos: " << Universo[0]->getNumMortos();
		con.gotoxy(50, 34);
		cout << "Tempo decorrido: " << Universo[0]->getTempo();
		con.gotoxy(8, 36);
		cout << "N mosquitos: " << Universo[0]->getNumMosquitos();
		con.gotoxy(29, 36);
		cout << "N min pessoas: " << Universo[0]->getNumMinPessoas();
		con.gotoxy(50, 36);
		cout << "N infetados: " << Universo[0]->getNumInfetados();
	}

	
}



void Simulador::desenhaEntidades(int nl, int nc){
	int i, x , y, coordc, coordl;


	for(i = 0 ; i < Universo[0]->getNumTerrenos() ; i++){
		
		coordc = Universo[0]->getTerreno(i)->getCoord_c();
		coordl = Universo[0]->getTerreno(i)->getCoord_l();

		x = (coordc*3)+3-(nc*3);
		y = (coordl*3)+3-(nl*3);
		
		if((Universo[0]->getTerreno(i)->getCoord_c() >= nc+24 || Universo[0]->getTerreno(i)->getCoord_l() >= nl+10) || (Universo[0]->getTerreno(i)->getCoord_c() <= nc-1 || Universo[0]->getTerreno(i)->getCoord_l() <= nl-1))
			continue;
		con.gotoxy(x,y);
		if(Universo[0]->getTerreno(i)->getCor() == "AMARELO_CLARO"){
			con.setBackgroundColor(con.AMARELO_CLARO);
		}else
			con.setBackgroundColor(con.AMARELO);
			
		cout << "   ";
		y++;
		con.gotoxy(x,y);
		cout << "   ";
		y++;
		con.gotoxy(x,y);
		cout << "   ";
		y++;
	}


	
	
	
	for(i = 0 ; i < Universo[0]->getNumPessoas() ; i++){
		
		coordc = Universo[0]->getPessoa(i)->getCoord_c();
		coordl = Universo[0]->getPessoa(i)->getCoord_l();

		x = (coordc*3)+3-(nc*3);
		y = (coordl*3)+3-(nl*3);
		//con.gotoxy(40,40+i);
		//cout << Universo[0]->getIdoso(i)->getCoord_c() << ","<< Universo[0]->getIdoso(i)->getCoord_l();
		//cout << "\n" << Universo[0]->getIdoso(i)->getCoord_c() <<","<< Universo[0]->getIdoso(i)->getCoord_l()<< endl;
		if((Universo[0]->getPessoa(i)->getCoord_c() >= nc+24 || Universo[0]->getPessoa(i)->getCoord_l() >= nl+10) || (Universo[0]->getPessoa(i)->getCoord_c() <= nc-1 || Universo[0]->getPessoa(i)->getCoord_l() <= nl-1))
			continue;
		y++;
		con.gotoxy(x,y);
		if(Universo[0]->getPessoa(i)->getEstadoDeSaude() == "VERDE"){
			con.setTextColor(con.VERDE);
		}else{
			if(Universo[0]->getPessoa(i)->getEstadoDeSaude() == "VERMELHO")
				con.setTextColor(con.VERMELHO);
			else
				con.setTextColor(con.AZUL);
		}

		if((nc % 2 == 0 && nl % 2 == 0) || (nc % 2 != 0 && nl % 2 != 0)){

			if((coordc % 2 == 0 && coordl % 2 == 0) || (coordc % 2 != 0 && coordl % 2 != 0))//se par/par ou se impar/impar
				con.setBackgroundColor(con.CINZENTO);
			else		
				con.setBackgroundColor(con.BRANCO);
		}else{
			if((coordc % 2 == 0 && coordl % 2 == 0) || (coordc % 2 != 0 && coordl % 2 != 0))//se par/par ou se impar/impar
				con.setBackgroundColor(con.BRANCO);
			else		
				con.setBackgroundColor(con.CINZENTO);
		}
		
		if(Universo[0]->pesquisaPosicaoTerreno(coordc, coordl) != -1){
			if(Universo[0]->getTerreno(Universo[0]->pesquisaPosicaoTerreno(coordc, coordl))->getCor() == "AMARELO_CLARO"){//getposicao do terreno nessa coordenada
				con.setBackgroundColor(con.AMARELO_CLARO);
			}else
				con.setBackgroundColor(con.AMARELO);

		}
		cout <<  Universo[0]->getPessoa(i)->getId();
		
		//con.gotoxy(40,40+i);
		//cout <<Universo[0]->getIdoso(i)->getCoord_c() << "," << Universo[0]->getIdoso(i)->getCoord_l();


	}


	
	for(i = 0 ; i < Universo[0]->getNumMosquitos() ; i++){
		
		coordc = Universo[0]->getMosquito(i)->getCoord_c();
		coordl = Universo[0]->getMosquito(i)->getCoord_l();

		x = (coordc*3)+3-(nc*3);
		y = (coordl*3)+3-(nl*3);
		//con.gotoxy(40,40+i);
		//cout << Universo[0]->getIdoso(i)->getCoord_c() << ","<< Universo[0]->getIdoso(i)->getCoord_l();
		//cout << "\n" << Universo[0]->getIdoso(i)->getCoord_c() <<","<< Universo[0]->getIdoso(i)->getCoord_l()<< endl;
		if((Universo[0]->getMosquito(i)->getCoord_c() >= nc+24 || Universo[0]->getMosquito(i)->getCoord_l() >= nl+10) || (Universo[0]->getMosquito(i)->getCoord_c() <= nc-1 || Universo[0]->getMosquito(i)->getCoord_l() <= nl-1))
			continue;
		//y++;
		con.gotoxy(x,y);
		con.setTextColor(con.ROXO);
		/*if(Universo[0]->getMosquito(i)->getEstadoDeSaude() == "VERDE"){
			con.setTextColor(con.VERDE);
		}else{
			if(Universo[0]->getPessoa(i)->getEstadoDeSaude() == "VERMELHO")
				con.setTextColor(con.VERMELHO);
			else
				con.setTextColor(con.AZUL);
		}*/

		if((nc % 2 == 0 && nl % 2 == 0) || (nc % 2 != 0 && nl % 2 != 0)){

			if((coordc % 2 == 0 && coordl % 2 == 0) || (coordc % 2 != 0 && coordl % 2 != 0))//se par/par ou se impar/impar
				con.setBackgroundColor(con.CINZENTO);
			else		
				con.setBackgroundColor(con.BRANCO);
		}else{
			if((coordc % 2 == 0 && coordl % 2 == 0) || (coordc % 2 != 0 && coordl % 2 != 0))//se par/par ou se impar/impar
				con.setBackgroundColor(con.BRANCO);
			else		
				con.setBackgroundColor(con.CINZENTO);
		}
		
		
		if(Universo[0]->pesquisaPosicaoTerreno(coordc, coordl) != -1){
			if(Universo[0]->getTerreno(Universo[0]->pesquisaPosicaoTerreno(coordc, coordl))->getCor() == "AMARELO_CLARO"){//getposicao do terreno nessa coordenada
				con.setBackgroundColor(con.AMARELO_CLARO);
			}else
				con.setBackgroundColor(con.AMARELO);

		}
		

		
		cout <<  Universo[0]->getMosquito(i)->getId();
		
		//con.gotoxy(40,40+i);
		//cout <<Universo[0]->getIdoso(i)->getCoord_c() << "," << Universo[0]->getIdoso(i)->getCoord_l();


	}

	con.setBackgroundColor(con.PRETO);
	con.setTextColor(con.BRANCO);
	con.gotoxy(0,38);

}

void Simulador::instrucoes(){
	con.clrscr();
	char tecla;

	cout << "\n\n  Lista de comandos(1-fase):\n\t\t* Comandos criados para facilitar a utilizacao do simulador\n\n"
		<< "\t<sair>\nSai do programa\n\n"
		<< "\t<load nomeficheiro>\nCarrega do \"nomeficheiro\" comandos com o estado inicial do mundo em simulacao\n\n"
		<< "\t<criai numero>\nCria \"numero\" de idosos no mundo em simulacao\n\n"
		<< "\t<minimodepessoas numero>\nDefine \"numero\" como valor minimo de pessoas no mundo em simulacao\n\n"
		<< "\t<prox>\nPassa para o instante seguinte da simulacao\n\n"
		<< "\t<simples>\nMuda o modo de visualizacao para simples, apenas mostra grelha do mundo\n\n"
		<< "\t<completo>\nMuda o modo de visualizacao para completo, mostra grelha mais dados do mundo\n\n"
		<< "\t<mundo nome numerolinhas numerocolunas>\nCria um mundo com \"nome\" e com tamanho de \"numerolinhas\" e \"numerocolunas\"\n\n"
		<< "\t<exec numero>\nPassa \"numero\" de instantes da simulacao\n\n"
		<< "\t<scroll>*\nModo de movimento do mapa atravez das setas\n\n"
		<< "\t<instrucoes>*\nLista os comandos com breve descricao dos mesmos...Como pode ver nesta pagina\n\n"
		<< "\t<cls>*\nLimpa ultimos comandos invalidos inseridos\n\n"
		<< "\n\n\n\n Comece por criar um mundo e prossiga com a simulacao dos seus habitantes\n\nESC - Voltar\n";
	do{
	tecla = con.getch();
	
		
	}while(tecla != con.ESCAPE);
}

bool Simulador::load(string nfile){
	ifstream dados(nfile);
	string comandolido, nCom, para1, para2;
	vector<string> op, divcmd;
	stringstream ss;
	int opcao =0, op1, op2;


	if(!dados.is_open()){
		return false;
	}

	

	op.push_back("sair");
	op.push_back("load");
	op.push_back("criai");
	op.push_back("minimodepessoas");
	op.push_back("prox");
	op.push_back("simples");
	op.push_back("completo");
	op.push_back("mundo");
	op.push_back("exec");
	op.push_back("scroll");
	op.push_back("instrucoes");
	op.push_back("cls");
	op.push_back("criam");
	op.push_back("criaj");
	op.push_back("hospital");
	op.push_back("pantano");
	op.push_back("criacopia");
	op.push_back("simula");
	op.push_back("apaga");
	op.push_back("atribui");
	op.push_back("imun");
	op.push_back("infej");
	op.push_back("infei");
	op.push_back("matasv");
	

	

	

	while(!dados.eof()){ 
		// ler comando completo
		getline(dados, comandolido);

		if (comandolido == "") continue; //Skip blank line

		divcmd.clear();
		ss.clear();

		ss << comandolido;

		while (ss >> nCom)
			divcmd.push_back(nCom);

		nCom = divcmd[0];

		opcao = escolheOpcao( op, nCom);


		if(dados){ // basic_ios::operator void *  The operator returns a null pointer only if fail.
			
			switch (opcao){//o mesmo switch de comandos

			case 0: break;//sair

			case 1: if(divcmd.size()!=2){
						//cout << "\nPor favor insira um comando valido\n>load nomedoficheiro\n\n";
						break;
					}
					//if(Universo.size()>0){
						if(load(divcmd[1]))
							//return true;
					/*}else{
						cout << "\nNao existe nenhum mundo para executar os \nos comandos lidos\n\n";
						break;					
					}*/
					
					//cout << "\nErro ao ler do ficheiro\n\n";
					break;
					
			case 2: if(divcmd.size()!=2){
						//cout << "\nPor favor insira um comando valido\n>criai numero\n\n";
						break;
					}
					op1=atoi(divcmd[1].c_str());
					if(!verificaCriai(op1)){
						//cout << "\nPor favor insira um valor positivo valido\n\n";
						break;
					}
					if(Universo.size()>0){
						if(Universo[0]->getNColunas()*Universo[0]->getNLinhas()-Universo[0]->getNumPessoas() >= op1){
							Universo[0]->acrescentaNIdosos(op1);
							//return true;
							continue;
						}else{
							//cout << "\nNumero de idosos que pretende criar nao cabe no mundo\n\n";
						break;
						}

					}else{
						//cout << "\nNao existe nenhum mundo onde colocar os idosos\n\n";
						break;
					}
					
			
			case 3: if(divcmd.size()!=2){
						//cout << "\nPor favor insira um comando valido\n>minimodepessoas numero\n\n";
						break;
					}
					op1=atoi(divcmd[1].c_str());
					if(!verificaPositivo(op1)){
						//cout << "\nPor favor insira um valor positivo valido\n\n";
						
						break;
					}
					if(Universo.size()>0){
						if(Universo[0]->getNColunas()*Universo[0]->getNLinhas() >= op1){
							Universo[0]->setNumMinPessoas(op1);
							//return true;
							continue;
						}else{
							//cout << "\nNumero minimodepessoas maior que espaco no mundo\n\n";
						break;
						}
											
					}else{
						//cout << "\nNao existe nenhum mundo onde definir o \nnumero minimo de pessoas\n\n";
						break;
					}

			case 4: /*if(divcmd.size()!=1){
						cout << "\nPor favor insira um comando valido\n>prox\n\n";
						break;
					}
					if(Universo.size()>0){
						ite++;
						return true;
					}else{
						cout << "\nNao existe nenhum mundo para simular\n\n";
						break;
					}*/ break;//prox
					
			case 5: /*if(divcmd.size()!=1){
						//cout << "\nPor favor insira um comando valido\n>simples\n\n";
						break;
					}
					if(Universo.size()>0){
						fg = 0;
						return true;
					}else{
						cout << "\nNao existe nenhum mundo para se puder \nvisualizar a simulacao\n\n";
						break;					
					}*/break; //simples

			case 6: /*if(divcmd.size()!=1){
						cout << "\nPor favor insira um comando valido\n>completo\n\n";
						break;
					}
					if(Universo.size()>0){
						fg = 1;
						return true;
					}else{
						cout << "\nNao existe nenhum mundo para se puder \nvisualizar a simulacao\n\n";
						break;					
					}*/break;//completo

			case 7: if(divcmd.size()!=4){
						//cout << "\nPor favor insira um comando valido\n>mundo nome numerolinhas numerocolunas\n\n";
						break;
					}
					para1 = divcmd[1];
					op1=atoi(divcmd[2].c_str());
					op2=atoi(divcmd[3].c_str());
					if(!verificaMundo(para1, op1, op2)){
						//cout << "\nLimites do mundo errados, por favor insira \nvalores para o numero de linhas e colunas \nentre 50 e 100\n\n";
						break;
					}
					acrescentaMundo( para1, op1, op2);
					//return true;
					continue;

			case 8: /*if(divcmd.size()!=2){
						cout << "\nPor favor insira um comando valido\n>exec numero\n\n";
						break;
					}
					op1=atoi(divcmd[1].c_str());
					if(!verificaPositivo(op1)){
						cout << "\nPor favor insira um valor positivo valido\n\n";
						break;
					}
					if(Universo.size()>0){
						ite+=op1;
						return true;
					}else{
						cout << "\nNao existe nenhum mundo para se simular\n\n";
						break;					
					}*/break;//exec
					

			case 9:	/*if(divcmd.size()!=1){
						cout << "\nPor favor insira um comando valido\n>scroll\n\n";
						break;
					}
					if(Universo.size()>0){	
					con.clrscr();
					
					do{
						if(l != nl || c != nc){
							con.clrscr();
							l = nl;
							c = nc;
						}


						desenhaGrelha(nl, nc, fg);
						desenhaEntidades(nl, nc);
						cout << "\n\tPode movimentar a grelha com as setas\t\tESC - Voltar\n\n ";
						tecla = con.getch();
						if (tecla == con.ESQUERDA && nc-1>=0) nc--;
						if (tecla == con.DIREITA && nc+24<Universo[0]->getNColunas()) nc++;
						if (tecla == con.CIMA && nl-1 >= 0) nl--;
						if (tecla == con.BAIXO && nl+10<Universo[0]->getNLinhas()) nl++;

					
					}while(tecla != con.ESCAPE);
					return true;
					}else{
						cout << "\nNao pode fazer scroll sem existir um mundo \npara se visualizar\n\n";
						break;		
					}*/break;//scrool

			case 10: /*if(divcmd.size()!=1){
						cout << "\nPor favor insira um comando valido\n>instrucoes\n\n";
						break;
					 }
					 instrucoes();
					 return true;*/break;//instrucoes

			case 11: /*if(divcmd.size()!=1){
						cout << "\nPor favor insira um comando valido\n>cls\n\n";
						break;
					}
					 return true;*/break;//cls

			case 12: if(divcmd.size()!=2){
						//cout << "\nPor favor insira um comando valido\n>criam numero\n\n";
						break;
					}
					op1=atoi(divcmd[1].c_str());
					if(!verificaCriai(op1)){
						//cout << "\nPor favor insira um valor positivo valido\n\n";
						break;
					}
					if(Universo.size()>0){
						if(Universo[0]->getNColunas()*Universo[0]->getNLinhas()-Universo[0]->getNumMosquitos() >= op1){
							Universo[0]->acrescentaNMosquitos(op1);
							//return true;
							continue;
						}else{
							//cout << "\nNumero de mosquitos que pretende criar nao cabe no mundo\n\n";
						break;
						}						
					}else{
						//cout << "\nNao existe nenhum mundo onde colocar os Mosquitos\n\n";
						break;
					}
					

			case 13: if(divcmd.size()!=2){
						//cout << "\nPor favor insira um comando valido\n>criaj numero\n\n";
						break;
					}
					op1=atoi(divcmd[1].c_str());
					if(!verificaCriai(op1)){
						//cout << "\nPor favor insira um valor positivo valido\n\n";
						break;
					}
					if(Universo.size()>0){
						if(Universo[0]->getNColunas()*Universo[0]->getNLinhas()-Universo[0]->getNumPessoas() >= op1){
							Universo[0]->acrescentaNJovens(op1);
							//return true;
							continue;
						}else{
							//cout << "\nNumero de jovens que pretende criar nao cabe no mundo\n\n";
						break;
						}		
						
					}else{
						//cout << "\nNao existe nenhum mundo onde colocar os Jovens\n\n";
						break;
					}

			case 14: if(divcmd.size()!=3){
						//cout << "\nPor favor insira um comando valido\n>hospital linha coluna\n\n";
						break;
					}
					if(Universo.size()>0){
						op1=atoi(divcmd[1].c_str());
						op2=atoi(divcmd[2].c_str());
						if(!verificaLimites(op1, op2)){
							//cout << "\nImpossivel criar hospital fora dos limites do mundo\n Linhas(0-" << Universo[0]->getNLinhas()-1 <<"d) Colunas(0-" << Universo[0]->getNColunas()-1 << ")\n";
							break;
						}
						if(!verificaTerreno(op1,op2)){
							//cout << "\nImpossivel criar hospital nestas coordenadas\n";
							break;
						}
					
						Universo[0]->acrescentaHospital(op1,op2);
						//return true;
						continue;
					}else{
						//cout << "\nNao existe nenhum mundo onde colocar o Hospital\n\n";
						break;
					}
					
			case 15: if(divcmd.size()!=3){
						//cout << "\nPor favor insira um comando valido\n>Pantano linha coluna\n\n";
						break;
					}
					if(Universo.size()>0){
						op1=atoi(divcmd[1].c_str());
						op2=atoi(divcmd[2].c_str());
						if(!verificaLimites(op1, op2)){
							//cout << "\nImpossivel criar hospital fora dos limites do mundo\n Linhas(0-" << Universo[0]->getNLinhas()-1 <<"d) Colunas(0-" << Universo[0]->getNColunas()-1 << ")\n";
							break;
						}
						if(!verificaTerreno(op1,op2)){
							//cout << "\nImpossivel criar hospital nestas coordenadas\n";
							break;
						}
					
						Universo[0]->acrescentaPantano(op1,op2);
						//return true;
						continue;
					}else{
						//cout << "\nNao existe nenhum mundo onde colocar o Pantano\n\n";
						break;
					}
					
			case 16: if(divcmd.size()!=3){
						//cout << "\nPor favor insira um comando valido\n>criacopia novo outro\n\n";
						break;
					}
					 if(Universo.size()>0){//cria um mundo com o nome novo como cópia do mundo com o nome outro
						para1=divcmd[1].c_str();
						para2=divcmd[2].c_str();

						if(pesquisaMundo(para2) == 1){//se encontrar mundo com esse nome

							acrescentaMundoCopia(para1,pesquisaMundoNome(para2));
							//return true;
							continue;
						}else{
							//cout << "\nNao existe nenhum mundo com esse nome\n\n";
						break;
						}

					 }else{
						//cout << "\nNao existe nenhum mundo para copiar\n\n";
						break;
					}

			case 17:/* if(divcmd.size()!=2){
						//cout << "\nPor favor insira um comando valido\n>simula nome\n\n";
						break;
					}
					  if(Universo.size()>0){
						  para1=divcmd[1].c_str();
						  if(pesquisaMundo(para1) == 1){//se encontrar mundo com esse nome
							  simula(para1);
							  ite=Universo[0]->getTempo();
							  continue;
							  //return true;
							}else{
							cout << "\nNao existe nenhum mundo com esse nome\n\n";
						break;
						}
					  }else{
						cout << "\nNao existe nenhum mundo para simular\n\n";
						break;
					}*/break;//simula

			case 18: if(divcmd.size()!=2){
						//cout << "\nPor favor insira um comando valido\n>apaga nome\n\n";
						break;
					}
					 if(Universo.size()>0){
						  para1=divcmd[1].c_str();
						  if(pesquisaMundo(para1) == 1){//se encontrar mundo com esse nome
							  if(para1 == Universo[0]->getNome()){
									//cout << "\nMundo que pretende apagar e o k esta a ser simulado\n\n";
									break;
								}
							  apagaMundo(para1);
							  continue;
							  //return true;
							}else{
							//cout << "\nNao existe nenhum mundo com esse nome\n\n";
						break;
						}

					}else{
						//cout << "\nNao existe nenhum mundo para apagar\n\n";
						break;
					}

			case 19: if(divcmd.size()!=3){
						//cout << "\nPor favor insira um comando valido\n>atribui destino origem\n\n";
						break;
					}
					 if(Universo.size()>0){
						para1=divcmd[1].c_str();
						para2=divcmd[2].c_str();

						if(pesquisaMundo(para2) == 1){//se encontrar mundo com nome origem
							if(pesquisaMundo(para1) == 1){//se encontrar mundo com nome destino
								atribuiM(pesquisaMundoNome(para1),pesquisaMundoNome(para2), para1);
								//return true;
								continue;
							}else{
							//cout << "\nNao existe nenhum mundo com esse nome(destino)\n\n";
							break;
						}

						}else{
							//cout << "\nNao existe nenhum mundo com esse nome(origem)\n\n";
						break;
						}

					}else{
						//cout << "\nNao existe nenhum mundo para se fazer atribuicao\n\n";
						break;
					}

			case 20: if(divcmd.size()!=2){
						//cout << "\nPor favor insira um comando valido\n>imun numero\n\n";
						break;
					}
					 if(Universo.size()>0){
						op1=atoi(divcmd[1].c_str());
						if(!verificaPositivo(op1)){
							//cout << "\nPor favor insira um valor positivo valido\n\n";
							break;
						}
						Jovem::setTempoDeImunidade(op1);
						//return 1;
						continue;
					}else{
						//cout << "\nNao existe nenhum mundo com jovens\n\n";
						break;
					}

			case 21: if(divcmd.size()!=2){
						//cout << "\nPor favor insira um comando valido\n>infej numero\n\n";
						break;
					}
					 if(Universo.size()>0){
						op1=atoi(divcmd[1].c_str());
						if(!verificaPositivo(op1)){
							//cout << "\nPor favor insira um valor positivo valido\n\n";
							break;
						}
						Jovem::setTempoDeInfecao(op1);
						//return 1;
						continue;
					}else{
						//cout << "\nNao existe nenhum mundo com jovens\n\n";
						break;
					}

			case 22: if(divcmd.size()!=2){
						//cout << "\nPor favor insira um comando valido\n>infei numero\n\n";
						break;
					}
					 if(Universo.size()>0){
						op1=atoi(divcmd[1].c_str());
						if(!verificaPositivo(op1)){
							//cout << "\nPor favor insira um valor positivo valido\n\n";
							break;
						}
						Idoso::setTempoDeInfecao(op1);
						//return 1;
						continue;
					}else{
						//cout << "\nNao existe nenhum mundo com jovens\n\n";
						break;
					}

			case 23: if(divcmd.size()!=1){
						//cout << "\nPor favor insira um comando valido\n>matasv\n\n";
						break;
					}
					 if(Universo.size()>0){
						 Universo[0]->eliminarSerVivos();
						// return 1;
						 continue;
					}else{
						//cout << "\nNao existe nenhum mundo\n\n";
						break;
					}

			/*case -1: cout << "\nComando invalido\n\n";
					 break;
			*/		

					 

			/*case 0: if(divcmd.size()!=2){
						//cout << "\nPor favor insira um comando valido\n>criai numero\n\n";
						break;
					}
					op1=atoi(divcmd[1].c_str());
					if(!verificaCriai(op1)){
						//cout << "\nPor favor insira um valor positivo valido\n\n";
						break;
					}
					if(Universo.size()>0){
						Universo[0]->acrescentaNIdosos(op1);
						//return true;
						continue;
					}else{
						cout << "\nNao existe nenhum mundo onde colocar os idosos\n\n";
						break;
					}
					

			case 1: if(divcmd.size()!=2){
						//cout << "\nPor favor insira um comando valido\n>minimodepessoas numero\n\n";
						break;
					}
					op1=atoi(divcmd[1].c_str());
					if(!verificaPositivo(op1)){
						//cout << "\nPor favor insira um valor positivo valido\n\n";
						
						break;
					}
					if(Universo.size()>0){
						Universo[0]->setNumMinPessoas(op1);
						//return true;
						continue;
					}else{
						//cout << "\nNao existe nenhum mundo onde definir o \nnumero minimo de pessoas\n\n";
						break;
					}

			case 2: if(divcmd.size()!=4){
						//cout << "\nPor favor insira um comando valido\n>mundo nome numerolinhas numerocolunas\n\n";
						break;
					}
					para1 = divcmd[1];
					op1=atoi(divcmd[2].c_str());
					op2=atoi(divcmd[3].c_str());
					if(!verificaMundo(para1, op1, op2)){
						cout << "\nLimites do mundo errados, por favor insira \nvalores para o numero de linhas e colunas \nentre 50 e 100\n\n";
						break;
					}
					if(Universo.size()<1)
						acrescentaMundo( para1, op1, op2);
					break;


			}	*/
		
	//}while (opcao != 0);
			}
		}
		dados.ignore(100, '\n');

	}
	dados.close();
	return true;
}


/*
void Simulador::opCriarMundoInicial()
{
	int linhas, colunas;
	string nome;

	do{
		con.clrscr();
		cout << "\n\tCriar mundo Inicial: >mundo Nome NumLinhas NumColunas \n\n\t( Numero de linhas e colunas entre 50 a 100 )\n\n>";
		cin.ignore(cin.rdbuf()->in_avail());

		getline(cin, nome, ' ');
		cin >> linhas;
		cin >> colunas;
	}while((linhas < 50 || colunas < 50) || (linhas > 100 || colunas > 100));

	acrescentaMundo( nome, linhas, colunas);
}*/