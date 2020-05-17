#include <iostream>
#include <vector>
using namespace std;
int N;
vector<int>pos,orden;
vector<int>::iterator it;

void Inicializar(){
	orden.push_back(0); orden.push_back(1); orden.push_back(2);
	pos.push_back(0); pos.push_back(1); pos.push_back(2);
}

void Ordenar(){
	int ini,fin;
	for(int i=3;i<=N;i++){
		ini=1; fin=i;
		for(int j=i-2;j>=1;j-=2){
			if(pos[j]<pos[(j+i)/2]) fin=min(fin,pos[(j+i)/2]);
			else ini=max(ini,pos[j]);
		}
		it=orden.begin();
		orden.insert(it+fin,i);
		pos.push_back(1);
		for(int i=1;i<orden.size();i++) pos[orden[i]]=i;
	}
}

void Mostrar(){
	for(int i=1;i<=N;i++) cout<<orden[i]<<endl;
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(NULL);
	cin>>N;
	Inicializar();
	Ordenar();
	Mostrar();

	return 0;
}
///xD
/**
**/