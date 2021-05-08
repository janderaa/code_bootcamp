#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
using namespace std;

string globalNombre = "";
int puntaje = 0; // numero de victorias
int numeroLinea = 0; // numero de linea donde se encuentra el usuario
int tablero[8][8] = {}; // tablero del juego
int mapaX = 0; // dimension X del tablero
int mapaY = 0; // dimension Y del tablero


void hacer_tablero(string nombreMapa){
	fstream Iarchivo;
	Iarchivo.open(nombreMapa, fstream::in);

	int y = 0;
	int x = 0;
	string data = "";
	
	while(getline(Iarchivo,data,';')){
		if(x == 8){
			y = y + 1;
			x = 0;
		}

		tablero[y][x] = stoi(data);
		x = x + 1;
	}
	Iarchivo.close();

}


bool nombre_existe_en_archivo(){
	ifstream Iarchivo;
	Iarchivo.open("datos.txt", fstream::in);
	bool encontrado = false;
	int tempLinea = -1;
	if (Iarchivo.is_open() && Iarchivo){
		string nombre;

		while ( getline(Iarchivo,nombre,';') ){
			if(strcmp(globalNombre.c_str(),nombre.c_str()) == 0){
				numeroLinea = ( tempLinea/3 ) + 1;
				encontrado = true;
			}
			tempLinea = tempLinea+1;
		}	
		Iarchivo.close();
	}

	if(!encontrado){
		numeroLinea= (tempLinea/3) + 1;
		ofstream Oarchivo;
		Oarchivo.open("datos.txt",fstream::app);
		Oarchivo << ";" << globalNombre << ";0;" << endl;
		Oarchivo.close();
		encontrado = true;
	}

	numeroLinea = numeroLinea - 1;

	return encontrado;
}

bool actualizar_puntaje(){
	ifstream Iarchivo;
	ofstream Oarchivo;

	Iarchivo.open("datos.txt", fstream::in);
	Oarchivo.open("datos2.txt", fstream::app);

	int tempLinea = 0;

	if (Iarchivo.is_open() && Iarchivo){
		string linea;

		while ( getline(Iarchivo,linea) ){

		    if(tempLinea != numeroLinea){
		    	Oarchivo << linea << endl;
		    }

		    tempLinea = tempLinea + 1;
		}

		
		Oarchivo << ";" << globalNombre << ";" << puntaje <<";"<<endl;
		Oarchivo.close();
		Iarchivo.close();

	}

	if ( remove("datos.txt") == 0){
		if ( rename("datos2.txt","datos.txt") == 0 ){
			return true;
		}
	}


	return false;
}

int obtener_puntaje(){
	ifstream Iarchivo;

	Iarchivo.open("datos.txt", fstream::in);
	if (Iarchivo.is_open() && Iarchivo){
		string nombre;

		while ( getline(Iarchivo,nombre,';') ){
			if(strcmp(globalNombre.c_str(),nombre.c_str()) == 0){
				if(getline(Iarchivo,nombre,';')){
					Iarchivo.close();
					return stoi(nombre);
				}else{
					Iarchivo.close();
					return -1;
				}
			}
		}
	}

	return -1;
}


void juego(int posX, int posY){
	bool seguir = true;
	int resultadoJuego = 0;
	int movimiento = -1;
	int x = posX;
	int y = posY;
	int tempX = posX;
	int tempY = posY;
	while(seguir){
		tempX = x;
		tempY = y;

		switch(movimiento){
			
			case 1:
				x = x-1;	
				break;
			case 2:
				y = y-1;
				break;
			case 3:
				x = x+1;
				break;
			case 4:
				y = y+1;
				break;
	
		}

		if( x >= mapaX ){
			x = mapaX-1;
		}else if( x < 0 ){
			x = 0;
		}

		if( y >= mapaY ){
			y = mapaY-1;
		}else if( y < 0 ){
			y = 0;
		}
		
		switch( tablero[x][y] ){
			case 1:
				tablero[x][y] = 3;
				tablero[tempX][tempY] = 2;		
				seguir = false;
				resultadoJuego = 1;
				break;
			case 2:
				tablero[x][y] = 3;
				tablero[tempX][tempY] = 2;		
				break;
			case 4:
				tablero[x][y] = 3;
				tablero[tempX][tempY] = 2;		
				resultadoJuego = 2;
				seguir = false;
				break;
			default:
				resultadoJuego = 0;
				break;
		}

		for(int i = 0; i < mapaX; i++){
			for(int j = 0; j < mapaY; j++){
				cout << tablero[i][j];
			}
			cout << endl;
		}
		
		if(seguir){
			cout << "Controles: " << endl;
			cout << "1 ARRIBA" << endl;
			cout << "2 IZQUIERDA" << endl;
			cout << "3 ABAJO" << endl;
			cout << "4 DERECHA" << endl;
			cout << "MAPA: 1 son minas, 2 es el camino" << endl;
			cin>> movimiento;
		}

	}


	cout << "Fin del juego!" << endl;
	
	if (resultadoJuego == 2){
		puntaje = puntaje + 1;
		
		cout << "Has ganado!" << endl;

		if (actualizar_puntaje()){
			cout << "Se registro tu victoria!" << endl;
		}else{
			cout << "ERROR: archivo victoria" << endl;
		}

	}else{
		cout<<"Has perdido!"<<endl;
	}

}


void preparacion(){
	puntaje = obtener_puntaje();
	string temp = "";
	int respuesta = 0;
	int x = 0;
	int y = 0;
	int inicioX = 0;
	int inicioY = 0;
	cout << "Hola " << globalNombre << "!" << endl;
	cout << "Tus victorias son: " << puntaje << endl; 
	cout << "Elija que tablero quieres usar: " << endl;
	cout << " (1) 8x8 " << endl;
	cout << " (2) 8x6 " << endl;
	cin >> respuesta;
	
	switch(respuesta){
		case 1:
			mapaX = 8;
			mapaY = 8;
			hacer_tablero("mapa8x8.txt");
			inicioX = 7;
			inicioY = 0;
			break;
		case 2:
			mapaX = 6;
			mapaY = 8;
			inicioX = 5;
			inicioY = 7;
			hacer_tablero("mapa8x6.txt");
			break;
		default:
			mapaX = 8;
			mapaY = 8;
			inicioX = 7;
			inicioY = 0;
			hacer_tablero("mapa8x8.txt");
			break;
	
	}
	
	if( puntaje > -1){
		juego(inicioX, inicioY);
		//cout << "Gaming" << endl;
		//cout << "Usuario#"<<numeroLinea<<endl;
		//cout << "Puntaje :"<<puntaje<<endl;
		cin >> temp;
	}else{
		cout << "ERROR: puntaje no recuperado " << endl;
	}
}

int main(){
	cout << "Digite su nombre" << endl;
	cin >> globalNombre;
	if (nombre_existe_en_archivo()){
		preparacion();
	}else{
		cout << "ERROR: archivo" << endl;
	}
	return 0;
}
