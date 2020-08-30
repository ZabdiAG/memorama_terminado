#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <conio.h>
#include <conio.c>
#define count 100

int arrayauxopened[count], arrayopened[count];

char jug1[count]={}, jug2[count]={}, ingreso[count];
int columnas, filas, primcarta=100, segcarta=100, posxPrimCarta=100, posyPrimCarta=100,numero,  
	posySegCarta=100, posxSegCarta=100, ptsjug1=0, ptsjug2=0, boleanjug=1, abrirarchivo;
bool guardadoarchivos=FALSE, openfiles=TRUE, entrar;
int *pointeraux;int *pointer;

static BOOL WINAPI TrataEvento(DWORD event);
static BOOL salida=FALSE;

void imprimirMatriz();

int main(){

	if(!SetConsoleCtrlHandler(TrataEvento,TRUE)){
        printf("No se puede establecer el handler\n");
        return 1;
    }

	int limjug1,limjug2,bolean,totaljug1=0,totaljug2=0,i,j,
		solonumeros;
	char x[count]={}, y[count]={};
	srand(time(0));
	system("color 74");
				///abrir el archivo guardado
	FILE *opendata;
	if ((opendata=fopen("data.txt","rt"))==NULL){
		printf("MEMORAMA \n\n\n\n\t\t\telaborado por : Luis Aguilera.\n\n");
		system("pause");system("cls");
	}
	else{
		do{
			entrar=false;system("cls");
			printf("MEMORAMA \n\n\n\n\t\t\telaborado por : Luis Aguilera.\n");
			printf("Existe una partida guardada. ¿Desea abrirla?\n 0=no abrirlo\t\t1=abrirlo\n");
			scanf(" %[^\n]",ingreso);
			for (int i = 0;ingreso[i]; ++i){
				if (ingreso[i]>'1' || ingreso[i]<'0' ){
					entrar=true;
				}
			}
		numero=atoi(ingreso);
		}while(entrar);
		if (numero){
			fscanf(opendata,"%d",&filas);
			fscanf(opendata,"%d",&columnas);
			fscanf(opendata,"%d\n",&ptsjug1);
			fscanf(opendata,"%d\n",&ptsjug2);
			for (int i = 0; i < filas; ++i){
					for (int j = 0; j < columnas; ++j){
						fscanf(opendata, "%3d",&arrayopened[i*columnas+j] );				}
					fscanf(opendata,"\n");
			}
			fscanf(opendata, "%s\n%s\n", jug1,jug2);
			for (int i = 0; i < filas*columnas; ++i)
				fscanf(opendata, "%3d",&arrayauxopened[i] );
			openfiles=FALSE;
			fclose(opendata);
			printf("Partida cargada..\n"); system("pause");
		}
		else{
			fclose(opendata);
			system("DEL data.txt");
		}
	}
			///termina el abrir el archivo guardado   
			//variables arrayauxopened, arrayopened , openfiles=false

  	if (openfiles)
  	{
		do{
			bolean=0;
			system("cls");
			printf("Memorama :3 \n   Ingresa nombre jugador 1:\n");
			scanf(" %[^\n]",jug1);
			printf("   Ingresa nombre jugador 2:\n");
			scanf(" %[^\n]",jug2);
			for ( limjug1=0, limjug2=0 ;jug1[limjug1]||jug2[limjug2];){
				if (jug1[limjug1]){
					totaljug1+=tolower(jug1[limjug1]);
					limjug1++;
				}
				if (jug2[limjug2]){
					totaljug2+=tolower(jug2[limjug2]);
					limjug2++;
				}
			}
			if (totaljug2==totaljug1){
				bolean=1;
				printf("Los nombres deben ser diferentes\n\n");
				system("pause");
			} 							
		}while(bolean);
		do{
			solonumeros=0;
			if (x)
				system("cls");
			printf("Memorama :3 \n   Escribe el ancho del memorama \n   especifica un numero entre 2 y 9:\n");
			scanf(" %[^\n]",x);
			for ( i = 0; x[i]; ++i){
				if (x[i]<48||x[i]>57){
					solonumeros=1;
					break;
				}
			}
			columnas=atoi(x);
		}while( solonumeros||columnas<2||columnas>9 );
		do{
			solonumeros=0;
			if (y)
				system("cls");
			printf("Memorama :3 \n   Escribe el alto del memorama \n   especifica un numero entre 2 y 8 que sea par:\n");
			scanf(" %[^\n]",y);
			for ( i = 0; y[i] ; ++i){
				if (y[i]<48||y[i]>57){
					solonumeros=1;
					break;
				}
			}
			filas=atoi(y);
			if (filas%2)
				solonumeros=1;										
		}while(solonumeros||filas<2||filas>8  );	
  	}
						 /*empieza el llenado del array*/
	int valores=filas*columnas/2,limnum=1,s1[valores*2];
	int array[filas][columnas];
	pointeraux=&s1[0];
	pointer=&array[0][0];
	if (!openfiles){
		for (int i = 0; i < filas; ++i){
			for (int j = 0; j < columnas; ++j){
				array[i][j]=arrayopened[i*columnas+j];
			}
		}
		for (int i = 0; i < valores*2; ++i){
			s1[i]=arrayauxopened[i];
			//printf("%3d",s1[i] );
		}
		//system("pause");
	}
	else{
		for ( i = 0; i < valores*2; ++i)	//se llena el array auxiliar de ceros
				s1[i]=0;
		for ( i = 0; i < filas; ++i){		//bucle para llenar memorama
			for ( j = 0; j < columnas;){
				int numrandom=rand()%valores+1;
				bolean=1;
				for (int k = 0; k < limnum;){
					if ( numrandom==s1[k] ){
						if (s1[k+1]==1){
							bolean=0;
							break;
						}
						else{
							s1[k+1]=1;
							array[i][j]=numrandom;
							j++;
						}
					}
					else{
						k+=2;
					}
				}
				if (bolean){
					array[i][j]=numrandom;
					s1[limnum-1]=numrandom;
					limnum+=2;
					j++;
				}
			}
		}
	}
	guardadoarchivos=1;
				/*empieza el juego por turnos*/	
	if (openfiles){
		for (int i = 0; i < valores*2; ++i)
			s1[i]=0;
	}
	i=0;
	do{			
		bolean=1;
		do{
			imprimirMatriz();
			solonumeros=0;
			printf("elige la primera carta :\n");
			scanf(" %[^\n]",x);
			for (int i = 0;x[i]; ++i){
				if (x[i]>'9' || x[i]<'0'){
					solonumeros++;
					break;
				}
			}
			primcarta=atoi(x);
			if ( ((primcarta/10)<filas) && ((primcarta%10)<columnas) ){
				posyPrimCarta=primcarta/10;
				posxPrimCarta=primcarta%10;
				if (s1[array[posyPrimCarta][posxPrimCarta]-1]){
					printf("Esta carta ya la utilizaste, elige otra\n");
					system("pause");solonumeros++;
				}
			}
			else
				solonumeros++;
		}while(solonumeros);
		do{
			imprimirMatriz();
			solonumeros=0;
			printf("elige la segunda carta:\n");
			scanf(" %[^\n]",y);
			for (int i = 0;y[i]; ++i){
				if (y[i]<'0'|| y[i]>'9'){
					solonumeros++;
					break;
				}
			}
			segcarta=atoi(y);
			if (((segcarta/10)<filas) && (segcarta%10<columnas) ){
				posxSegCarta=segcarta%10;
				posySegCarta=segcarta/10;
				if (s1[array[posySegCarta][posxSegCarta]-1]){
					printf("Esta carta ya la utilizaste, elige otra\n");
					system("pause");solonumeros++;
				}
			}
			else
				solonumeros++;
		}while(solonumeros);
		if (primcarta==segcarta){
			printf("No puedes elegir la misma carta\n");
			system("pause");
		}
		else{
			imprimirMatriz();
			if ((array[posyPrimCarta][posxPrimCarta]) == (array[posySegCarta][posxSegCarta]) ){
				s1[array[posyPrimCarta][posxPrimCarta]-1]=array[posyPrimCarta][posxPrimCarta];
				system("pause");
				if (boleanjug)     //boleanjug=1 --->jug1
					ptsjug1++;			
				else
					ptsjug2++;
			}
			else{
				imprimirMatriz();
				boleanjug = !boleanjug;
				posxPrimCarta=100;posyPrimCarta=100;posySegCarta=100;posxSegCarta=100;
				system("pause");
			}
		}
		if (ptsjug1+ptsjug2==valores-1)
			bolean=0;
	}while(bolean);
	if (boleanjug)
		ptsjug1++;
	else
		ptsjug2++;
	for (int i = 0; i < valores; ++i)
		pointeraux[i]=1;
	imprimirMatriz();
	if (ptsjug1==ptsjug2)
		printf("Juego terminado, empate.\n");
	else{
		printf("Juego terminado, ganador : ");
		if (ptsjug1<ptsjug2)
			printf("jug2 %s con %d puntos\n", jug2,ptsjug2);
		else
			printf("jug1: %s con %d puntos\n",jug1,ptsjug1 );
	}
	system("pause");
	system("DEL data.txt");
	return 0;
}

void imprimirMatriz(){
	system("cls");
	for (int i = 0; i < filas; ++i){
		for (int j = 0; j < columnas; ++j){
			if (pointeraux[pointer[i*columnas+j]-1])
				printf("%6d  ",pointer[i*columnas+j] );
			else{
				if ( (i==posyPrimCarta)&&(j==posxPrimCarta) )
					printf("%6d  ",pointer[i*columnas+j] );
				else{
					if ( (i==posySegCarta)&&(j==posxSegCarta) )
						printf("%6d  ",pointer[i*columnas+j] );
					else
						printf("%6d @", i*10+j );
				}
			}
		}
		printf("\n\n");
	}
	if (boleanjug)
		printf("Turno jugador :> %s \n",jug1 );
	else
		printf("tuno jugador :> %s \n",jug2 );
	printf(" jug 2: %s \t\t\tpts: %d\n",jug2,ptsjug2);
	printf(" jug 1: %s \t\t\tpts: %d\n",jug1,ptsjug1);
}


BOOL WINAPI TrataEvento(DWORD event){
    switch(event){
         case CTRL_C_EVENT:
               printf("\n Recibido Ctrl-C, el programa terminara en 4 segundos.\n");
               break;
         case CTRL_CLOSE_EVENT:
               printf("\n Recibido evento de cierre de ventana Terminando en 4 segundos.\n");
               break;
         default:
               printf("\n Recibido el evento numero %d. Quedan 4 segundos\n",event);
    }
    /*Duerme cuatro segundos*/
    if (guardadoarchivos){
	    FILE *savedata;
		if ((savedata = fopen("data.txt", "w+b"))==NULL){
			printf("Error\n");
		}
		else{
			fprintf(savedata, "%d\n", filas);
			fprintf(savedata, "%d\n",columnas );
			fprintf(savedata, "%d\n", ptsjug1);fprintf(savedata, "%d\n", ptsjug2);
			for (int i = 0; i < filas; ++i){
				for (int j = 0; j < columnas; ++j){
					fprintf(savedata, "%3d",pointer[i*columnas+j] );
				}
				fprintf(savedata, "\n");
			}
			fprintf(savedata, "%s\n%s\n", jug1,jug2);
			for (int i = 0; i < filas*columnas; ++i)
				fprintf(savedata, "%3d",pointeraux[i] );
			fclose(savedata);
			printf("guardando partida....\n");
		}
    }
    Sleep(4000);
    /*Se saldra del bucle principal*/
    salida=TRUE;
    /*El handler ha procesado la señal*/
    return TRUE;
}
