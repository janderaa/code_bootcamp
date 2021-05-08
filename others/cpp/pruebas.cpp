#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
using namespace std;

int main(){
	int matriz[8][8] = {};
	fstream i;
	i.open("mapa8x6.txt",fstream::in);
	int y = 0;
	int x = 0;
	string data = "";
	while(getline(i,data,';')){
		if ( x == 8 ){
			y+=1;
			x=0;
		}
		matriz[y][x] = stoi(data);
		x+=1;
	}
	i.close();
	for(int i = 0; i<6;i++){
		for(int j=0;j<8;j++)
			printf("%d",matriz[i][j]);
		printf("\n");
	}

}
