#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
using namespace std;



int nombre_existe_en_archivo(string usuNombre){
	ifstream Iarchivo;
	Iarchivo.open("datos.txt", fstream::in);
	bool encontrado = false;
	int tempLinea = -1;
	int numeroLinea = -1;
	if (Iarchivo.is_open() && Iarchivo){
		string nombre;

		while ( getline(Iarchivo,nombre,';') ){
			if(strcmp(usuNombre.c_str(),nombre.c_str()) == 0){
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
		Oarchivo << ";" << usuNombre << ";0;" << endl;
		Oarchivo.close();
		encontrado = true;
	}

	numeroLinea = numeroLinea - 1;

	return numeroLinea;
}

bool actualizar_puntaje(string usuNombre, int numeroLinea, int puntaje){
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

		
		Oarchivo << ";" << usuNombre << ";" << puntaje <<";"<<endl;
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

int obtener_puntaje(string usuNombre){
	ifstream Iarchivo;

	Iarchivo.open("datos.txt", fstream::in);
	if (Iarchivo.is_open() && Iarchivo){
		string temp;

		while ( getline(Iarchivo,temp,';') ){
			if(strcmp(usuNombre.c_str(),temp.c_str()) == 0){
				if(getline(Iarchivo,temp,';')){
					Iarchivo.close();
					return stoi(temp);
				}else{
					Iarchivo.close();
					return -1;
				}
			}
		}
	}

	return -1;
}




void preparacion(string usuNombre, int numeroLinea){
	int puntaje = obtener_puntaje(usuNombre);
	int respuesta = 0;
	int mapaX = 0;
	int mapaY = 0;
	string nombreMapa = "";

	cout << "Hola " << usuNombre << endl;
	cout << "Tus victorias: " << puntaje << endl;
	cout << "Elija tablero: " << endl;
	cout << " (1) 8x8 " << endl;	
	cout << " (2) 8x6 " << endl;
	cin >> respuesta;

        switch(respuesta){
	     	case 1:
                        mapaX = 8;
                        mapaY = 8;
			nombreMapa = "mapa8x8.txt";
                        break;
                case 2:
                        mapaX = 8;
                        mapaY = 6;
			nombreMapa = "mapa8x6.txt";
                        break;
                default:
                        mapaX = 8;
                        mapaY = 8;
			nombreMapa = "mapa8x8.txt";
                        break;

        }
	respuesta = 0;
	int tablero[mapaX][mapaY] = {}; // tablero que procesa donde hay minas y caminos
	char usuTablero[mapaX][mapaY] = {}; // tablero que ve el usuario
	
	// el usuario ve el tablero del usuario como representacion
	/*
	 * lo que ve el usuario --> |________________|
	 *                 "abajito"
	 * lo que representa el     __________________
	 * programa
	 *
	 * son identicos, pero uno es una matriz de chars y otro de ints!
	 * */

	// inicia tablero del usuario
	for (int i = 0; i < mapaX; i ++){
		for (int j = 0; j < mapaY; j ++){
			usuTablero[i][j] = '-';
		}
	}

	fstream Iarchivo;
        Iarchivo.open(nombreMapa, fstream::in);

        int y = 0;
        int x = 0;
        string data = "";

        while(getline(Iarchivo,data,';')){
                if(y == mapaY){
                        x = x + 1;
                        y = 0;
                }

                tablero[x][y] = stoi(data);
                y = y + 1;
        }
        Iarchivo.close();


	if( puntaje > -1){ // inicia juego, si no se encontro puntaje quiere decir que puntaje = -1
		
		bool seguir = true;
		int resultadoJuego = 0;
			
		int coordX = 0;
		int coordY = 0;	

		while(seguir){

			// inicio imprime tablero usuario	
			cout << "  ";
			for (int i = 0; i< mapaX; i++){
				cout << " "<<i;
			}
			cout << endl;
			for (int i = 0; i < mapaX; i ++){
				cout << i << " ";
				for (int j = 0; j < mapaY; j ++){
					cout <<" " << usuTablero[i][j];
				}
				cout << endl;
			}
			// fin impresion tablero usuario
			
			if(seguir){
				/*
				 *
				 * Aqui el juego da la opcion de marcar el tablero
				 * M para minas
				 * C para camino
				 * X se muestra cuando el usuario ha abierto una casilla con mina,
				 * 	pero se muestra mas arriba del tablero original asi que toca
				 * 	subir un tanto en la consola para verla
				 * */
				cout << "Que accion quiere hacer?" << endl;
				cout << "1. Abrir casilla " <<endl;
				cout << "2. marcar / desmarcar como mina " <<endl;
				cout << "3. marcar / desmarcar como camino " <<endl;
				cout << "4. comprobar camino" <<endl;
				cin >> respuesta;

				if ( respuesta != 4 && respuesta >=1 || respuesta <= 3){
					cout << "dijite fila: ";
					cin >> coordX;
					cout << "dijite columna: ";
					cin >> coordY;
					if((coordX > -1 && coordX < mapaX) && (coordY) > -1 && coordY < mapaY){
						switch(respuesta){
							case 1:
								if (tablero[coordX][coordY] == 9){
									seguir = false;
									resultadoJuego = 1;
									usuTablero[coordX][coordY] = 'X';
								}else{
									usuTablero[coordX][coordY] = '0' + tablero[coordX][coordY]; // esto de 0 + n es para asignar el numeros en caracteres
								}
								break;	
							case 2:
								if (usuTablero[coordX][coordY] == 'M'){ // si ya esta marcada, desmarquela
									usuTablero[coordX][coordY] = '-';
								}else{ // sino, marquela
									usuTablero[coordX][coordY] = 'M';
								}
								break;
							case 3:
								if (usuTablero[coordX][coordY] == 'C'){
									usuTablero[coordX][coordY] = '-';
								}else{
									usuTablero[coordX][coordY] = 'C';
								}
								break;
						}
					}else{
						cout << " datos no validos"<<endl;
				
					}

				}else if (respuesta == 4){
					resultadoJuego = 2;
					seguir = false;
					for (int i = 0; i < mapaX; i ++){
						for (int j = 0; j < mapaY; j ++){
							if (usuTablero[i][j] == 'C' && tablero[i][j] == 9){ // si el usuario asigno un camino a una mina, pierde
								resultadoJuego = 1;
							}
						}
					}

				}else{
					cout << "Dato no valido " << endl;
				}
			}


		}
		
		// imprime tablero del usuario
		cout << "TABLERO USUARIO " << endl;
		cout << "  ";
		for (int i = 0; i< mapaX; i++){
			cout << " "<<i;
		}
		cout << endl;
		for (int i = 0; i < mapaX; i ++){
			cout << i << " ";
			for (int j = 0; j < mapaY; j ++){
				cout <<" " << usuTablero[i][j];
			}
			cout << endl;
		}
		// fin impresion tablero usuario
		cout << "TABLERO ORIGINAL" << endl;
	 	// imprime tablero que procesa el juego (de int)	
		cout << "  ";
		for (int i = 0; i< mapaX; i++){
			cout << " "<<i;
		}
		cout << endl;
		for (int i = 0; i < mapaX; i ++){
			cout << i << " ";
			for (int j = 0; j < mapaY; j ++){
				cout <<" " << tablero[i][j];
			}
			cout << endl;
		}
		// fin impresion tablero que procesa el juego

		 if (resultadoJuego == 2){
        	        puntaje = puntaje + 1;

                	cout << "Has ganado!" << endl;

	                if (actualizar_puntaje(usuNombre, numeroLinea, puntaje)){
        	                cout << "Se registro tu victoria!" << endl;
	                }else{
        	                cout << "ERROR: archivo victoria" << endl;
	                }
	        }else{
        	        cout<<"Has perdido!"<<endl;
	        }

	}else{
		cout << "ERROR: puntaje no recuperado " << endl;
	}
}

int main(){
	bool seguir = true;
	int respuesta = 0;
	string usuNombre = "";
	while(seguir){
		cout << "Digite su nombre" << endl;
		cin >> usuNombre;
		int numeroLinea = -1;
		numeroLinea = nombre_existe_en_archivo(usuNombre);
	
		if (numeroLinea >= 0){
			preparacion(usuNombre, numeroLinea);
		}else{
			cout << "ERROR: archivo" << endl;
		}

		cout << "continuar con el programa? (0) si (1) no" <<endl;
		cin >> respuesta;
		if (respuesta == 1){
			seguir = false;
		}
	}
	return 0;
}
