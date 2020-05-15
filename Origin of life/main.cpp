#include <iostream>
#include <map>
using namespace std;
struct GLOBALES{
	int F,C,a,b,c;
};
GLOBALES global;
int movs[8][2]={{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1}};

struct GENERACION{
	char celula[6][7];

	bool operator ==(const GENERACION &otro){
		for(int i=1;i<=global.F;i++){
			for(int j=1;j<=global.C;j++)
				if(celula[i][j]!=otro.celula[i][j]) return false;
		}
		return true;
	}

	bool operator <(const GENERACION &otro)const{
		for(int i=1;i<=global.F;i++){
			for(int j=1;j<=global.C;j++)
				if(celula[i][j]!=otro.celula[i][j]) return celula[i][j]<otro.celula[i][j];
		}
		return false;
	}

	bool Viva(int i,int j,GENERACION g){
		return g.celula[i][j]=='*' ? true: false;
	}

	bool Muere(int i,int j,GENERACION g){
		int celulasVivas=0;
		for(int aux=0;aux<8;aux++){
			if(i+movs[aux][0]<1 or i+movs[aux][0]>global.F or j+movs[aux][1]<1 or j+movs[aux][1]>global.C) continue;
			if(g.celula[i+movs[aux][0]][j+movs[aux][1]]=='*') celulasVivas++;
		}
		return (celulasVivas<global.a or celulasVivas>global.b) ? true: false;
	}

	bool Revive(int i,int j,GENERACION g){
		int c=0;
		for(int aux=0;aux<8;aux++){
			if(i+movs[aux][0]<1 or i+movs[aux][0]>global.F or j+movs[aux][1]<1 or j+movs[aux][1]>global.C) continue;
			if(g.celula[i+movs[aux][0]][j+movs[aux][1]]=='*') c++;
		}
		return c>global.c ? true: false;
	}

	void SiguienteGeneracion(GENERACION g){
		for(int i=1;i<=global.F;i++){
			for(int j=1;j<=global.C;j++){
				if(Viva(i,j,g)){
					if(Muere(i,j,g)) celula[i][j]='.';
				}else{
					if(Revive(i,j,g)) celula[i][j]='*';
				}
			}
		}
	}

	void Inizializar(){
		for(int i=1;i<=global.F;i++)
			for(int j=1;j<=global.C;j++) celula[i][j]='.';
	}

	void Mostrar(){
		for(int i=1;i<=global.F;i++){
			for(int j=1;j<=global.C;j++) cout<<celula[i][j];
			cout<<'\n';
		}
		cout<<'\n';
	}
};
map<GENERACION,int>memo;
map<GENERACION,bool>noEden;
GENERACION generacionActual;

void Lectura(){
	cin>>global.F>>global.C>>global.a>>global.b>>global.c;
	for(int i=1;i<=global.F;i++){
		for(int j=1;j<=global.C;j++){
			cin>>generacionActual.celula[i][j];
		}
	}
}

int DP(GENERACION generacion){
	//generacion.Mostrar();
	if(generacion==generacionActual) return 0;
	if(memo.find(generacion)==memo.end()){
		memo[generacion]=-1;
		GENERACION sig=generacion;
		sig.SiguienteGeneracion(sig);
		memo[generacion]=DP(sig);
		if(memo[generacion]!=-1) memo[generacion]++;
	}
	//cout<<"RETORNO"<<memo[generacion]<<endl;
	return memo[generacion];
}

void GenerarTodasConfiguaraciones(int i,int j,GENERACION generacion){
	DP(generacion);
	while(i<=global.F){
		while(j<=global.C){
			generacion.celula[i][j]='*';
			GenerarTodasConfiguaraciones(i,j+1,generacion);
			generacion.celula[i][j]='.';
			j++;
		}
		j=1;
		i++;
	}
}

void BuscarEden(int i,int j,GENERACION generacion){
	while(i<=global.F){
		while(j<=global.C){
			generacion.celula[i][j]='*';
			GENERACION sig=generacion;
			sig.SiguienteGeneracion(sig);
			noEden[sig]=true;
			BuscarEden(i,j+1,generacion);
			generacion.celula[i][j]='.';
			j++;
		}
		j=1;
		i++;
	}
}

int DistanciaGeneraciones(){
	int minPasos=1048578;
	for(map<GENERACION,int>::iterator it=memo.begin();it!=memo.end();it++)
		if(it->second!=-1 and noEden.find(it->first)==noEden.end()) minPasos=min(minPasos,it->second);
	if(minPasos!=1048578) return minPasos;
	else return -1;
}


int main(){
	Lectura();
	memo[generacionActual]=0;
	GENERACION basica;
	basica.Inizializar();
	GenerarTodasConfiguaraciones(1,1,basica);
	BuscarEden(1,1,basica);
	cout<<DistanciaGeneraciones()<<'\n';

	return 0;
}
///xD
/**
4 5 2 3 2
**.**
..*.*
....*
*****
**/