//Tres en Raya - Mauricio Colque Morales - CCOMP2-1
//No me funciona adecuadamente la funcion de revisar que este en una posicion valida,
//y la maquina termina sobreescribiendo sobre la que habia marcado el usiario
//Estoy enviando hasta donde termine

#include<iostream>
#include<cmath>
#include<Windows.h>
#include<stdlib.h>
#include<time.h>


char x = '1'; // Para incrementarlo y llenar la matriz


//Función que inicializa la matriz con los 9 valores
void inicializar(char matriz[3][3])
{
	for(int i = 0; i<3; i++)
	{
		for(int j = 0 ; j < 3 ; j++)
		{
			matriz[i][j] = x;
			x++; // Aumentando el char
		}

	}	
}

//Función que recoje la opción de 'x' u 'o'
char escojaX_u_O()
{
	while(true){ //Bucle que funciona hasta que se ingrese las opciones correctas
		char opcion;
		std::cout << "Escoja ser X u O: ";
		std::cin>>opcion;
		if( opcion != 'X' && opcion != 'x' && opcion != 'o' && opcion != 'O')
		{
			std::cout<<"Debe escoger X u O" << std::endl;
		}
		else
		{
			std::cout<<"Usted ha elegido ser " << opcion << "\n";
			return opcion; //Se retorna la opción escogida
		}
	}
	
	return 'a';
}


//Función que crea un tablero impreso en la pantalla
void mostrar_tablero(char matriz[3][3]){
	
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0 ; j < 3; j++)
		{
			if(j != 2)
			{
				std::cout << matriz[i][j] << " | ";
			}
			else{
				std::cout << matriz[i][j];
			}
		}
		
		if(i != 2) //Para que solo imprima los '---' dos veces
		{
			std::cout << "\n-----------\n";
		}
	}
	std::cout<<std::endl;
}


//Función que genera un tablero con la opción en la posición escogida
void colocar(char matriz[3][3], int num, char opcion)
{
	for(int i = 0 ; i < 3; i ++)
	{
		for(int j = 1; j < 4; j++)
		{
			if(i*3 + j  == num)
			{
				matriz[i][j-1] = opcion;
				i = 5;
			}
		}
	}
	
	mostrar_tablero(matriz); //Llama a la función de crear tablero y pasa la matriz modificada
}


//Función que se encarga de verificar la validez de la posición escogida, 
int posicion_valida(char matriz[3][3], int posicion)
{
	if((posicion < 1) || (posicion > 9)) //Verifica que se escoja un número correco
	{
		return 0;
	}
	
	int temporal = 999; //Valor temporal que me servirá para saber si la posición es correcta
	
	for(int i = 0 ; i < 3; i ++)
	{
		for(int j = 0; j < 3; j++)
		{	
			if(i*3 + j + 1 == posicion){
				if(matriz[i][j] == 'x' || matriz[i][j] == 'X' || matriz[i][j] == 'o' || matriz[i][j] == 'O')
				{
					temporal = 0;
					break;
				}
			}
			
		}
	}

	
	if(temporal == 0)
	{
		return 0; //Posición no válida
	}
	return 1; //Posición válida
	
}

//Funcion que se encarga de revisar si el tablero esta lleno
int tablero_lleno(char matriz[3][3])
{
	int temp = 0; 
	
	for(int i = 0 ; i < 3; i ++)
	{
		for(int j = 0; j < 3; j++)
		{
			if(matriz[i][j] == 'x' || matriz[i][j] == 'X' || matriz[i][j] == 'o' || matriz[i][j] == 'O')
			{
				temp++;
			}
		}
	}
	
	
	if(temp == 9){
		return 0; //El tablero está lleno
	}
	return 1; //El tablero no está lleno
}

//Funcion que se encarga de realizar las operaciones para el turno del usuario
void turno_persona(char matriz[3][3], char dibujo)
{
	
	int posicion;
	int pos_valida = 999; //inicializacion aleatoria
	do{
		std:: cout << "Por favor, introduzca una posicion del tablero: ";
		std:: cin>>posicion;
	
		pos_valida = posicion_valida(matriz, posicion);
	} while(pos_valida != 1); // 1 significa que finalmente se escogio una posicion valida
	
	colocar(matriz, posicion, dibujo); //Para que dibuje en el tablero lo que el usuario escogio
	
	
	}

//Funcion que se encarga de revisar si se realizo un tres en raya
int Tres_en_raya(char matriz[3][3])
{
	int temp = 0;
	//Para revisar las filas
	for(int i = 0; i < 3; i++)
	{
		if(matriz[i][0] == matriz[i][1] && matriz[i][0] == matriz[i][2])
		{
			temp = 1;
		}	
	}
	
	
	//Para revisar las columnas
	for(int i = 0; i < 3; i++)
	{
		if(matriz[0][i] == matriz[1][i] && matriz[0][i] == matriz[2][i])
		{
			temp = 1;
		}	
	}
	
	return temp;
}


//Funcion que se encarga de realizar las operaciones para el turno de la maquina
void turno_maquina(char matriz[3][3],  char dibujo)
{
	//Valores para ver si la maquina puede continuar
	int lleno = tablero_lleno(matriz); 
	int	tres_en_raya = Tres_en_raya(matriz); 
	
	if(lleno == 0 || tres_en_raya == 1)
	{
		return;
	}
	
	int pos_valida = 999; //temporal, para reemplazar
	int aleatorio;
	
	//Hasta que la maquina escoja una una posicion valida
	while(pos_valida != 0)
	{
		aleatorio = 1 + rand()%9;
		pos_valida = posicion_valida(matriz, aleatorio);
	}

	//Dibujar en la posicion valida
	colocar(matriz, aleatorio, dibujo);
	
}
	

int main(){
	
	char matriz[3][3];
	inicializar(matriz);
	int posicion;
	
	srand(time(NULL)); //Para que funcione el rand()
	
	
	//Escogiendo los simbolos a d
	char opcion_persona = escojaX_u_O(); //guardando la opción
	char opcion_maquina;
	if(opcion_persona == 'x' || opcion_persona == 'X')
	{
		opcion_maquina = 'o'; //la opcion de la maquina
	}
	else
	{
		opcion_maquina = 'x';
	}
	
	//Valores random para despues reemplazarlos
	int lleno = 999; 
	int tres_en_raya = 999;
	
	//La mecanica del juego
	while(lleno != 0 || tres_en_raya != 1) //Hasta que no haya mas espacios o hasta que haya un tres en raya
	{
		
		turno_persona(matriz, opcion_persona);//Turno de la persona
		//mostrar_tablero(matriz);
		Sleep(1800);
		system("cls");
		
		turno_maquina(matriz, opcion_maquina);//Turno de la máquina
		//mostrar_tablero(matriz);
		
		Sleep(1800);
		system("cls");
		
		std::cout<< std::endl << std::endl;
		
		//Por si se debe terminar el juego
		lleno = tablero_lleno(matriz); 
		tres_en_raya = Tres_en_raya(matriz); 
		
	}
	
	std::cout << "Acabó el juego" << std::endl;
	system("pause");
	
	return 0;
}





