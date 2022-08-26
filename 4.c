#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct automotor{
	int tipoVehivulo;
	char marca[15];
	char modelo[15];
	int anio;
	char dominio[10];
	char color[15];
};

struct automotor leerAutos(FILE *entrada){
	struct automotor salida;
	fscanf(entrada,"%d",&salida.tipoVehivulo);
	fscanf(entrada," %[^\n]",salida.marca);
	fscanf(entrada," %[^\n]",salida.modelo);
	fscanf(entrada,"%d",&salida.anio);
	fscanf(entrada," %[^\n]",salida.dominio);
	fscanf(entrada," %[^\n]",salida.color);
	return salida;
}

void mostrarAutos(struct automotor *datos,int N){
	int i;
	printf("********************************************************************\n");
	printf("|tp  |marca          |modelo    |anio   |dominio   |color          |\n");
	printf("|------------------------------------------------------------------|\n");
	for (i = 0; i < N; i++){
		printf("|%d   ",datos[i].tipoVehivulo);
		printf("|%-15s",datos[i].marca);
		printf("|%-10s",datos[i].modelo);
		printf("|%d   ",datos[i].anio);
		printf("|%-10s",datos[i].dominio);
		printf("|%-15s|\n",datos[i].color);
	}
	printf("********************************************************************\n");
	printf("\n");
}

int ordenarPorModelo(void const *p1,void const *p2){
	struct automotor v1;
	struct automotor v2;
	v1 = *(struct automotor *)p1;
	v2 = *(struct automotor *)p2;
	if (strcmp(v1.modelo,v2.modelo)>0){//cambiado
	return -1;
	}
	if (strcmp(v1.modelo,v2.modelo)==0){
	return 0;
	}
	return 1;
}

int ordenarPorMarca(void const *p1,void const *p2){
	struct automotor v1;
	struct automotor v2;
	v1 = *(struct automotor *)p1;
	v2 = *(struct automotor *)p2;
	if (strcmp(v1.marca,v2.marca)<0){//al reves
	return -1;
	}
	if (strcmp(v1.marca,v2.marca)==0){
	return 0;
	}
	return 1;
}

int ordenarPorDominio(void const *p1,void const *p2){
	struct automotor v1;
	struct automotor v2;
	v1 = *(struct automotor *)p1;
	v2 = *(struct automotor *)p2;
	if (strcmp(v1.dominio,v2.dominio)>0){
	return -1;
	}
	if (strcmp(v1.dominio,v2.dominio)==0){
	return 0;
	}
	return 1;
}
int ordenarPorColor(void const *p1,void const *p2){
	struct automotor v1;
	struct automotor v2;
	v1 = *(struct automotor *)p1;
	v2 = *(struct automotor *)p2;
	if (strcmp(v1.color,v2.color)<0){
	return -1;
	}
	if (strcmp(v1.color,v2.color)==0){
	return 0;
	}
	return 1;
}
void cargaArchivo(struct automotor *datos,int N, FILE *salida){
	int i;
	fprintf(salida,"tp  ;marca          ;modelo    ;anio   ;dominio   ;color          ;\n");
	for (i = 0; i < N; i++){
		fprintf(salida,"%d;",datos[i].tipoVehivulo);
		fprintf(salida,"%-15s;",datos[i].marca);
		fprintf(salida,"%-10s;",datos[i].modelo);
		fprintf(salida,"%d;",datos[i].anio);
		fprintf(salida,"%-10s;",datos[i].dominio);
		fprintf(salida,"%-10s\n",datos[i].color);
	}
}
void estadisticaEnArchivo(struct automotor *datos,int N){
	int i,k=0,tp;
	int men[3],may[3],tipos[3],meng[3],mayg[3];
	FILE *salida;
	
	salida = fopen("estadisticas.csv","w");
	
	for (i = 0; i < 3; i++){
		men[i]=0;
		may[i]=9999;
		tipos[i]=0;
		meng[i]=0;
		mayg[i]=0;
	}
	
	for (i = 0; i < N; i++){
		tp=datos[i].tipoVehivulo;
		switch (tp){
			case (1):{
				tipos[k]++;
				break;
				}
			case (2):{
				tipos[k+1]++;
				break;
				}
			case (3):{
				tipos[k+2]++;
				break;
				}	
		}
		
		if (datos[i].anio > men[k]){
			men[k]=datos[i].anio;
			meng[k]=i;
		}
		else{
				if (datos[i].anio > men[k+1]){
					men[k+1]=datos[i].anio;
					meng[k+1]=i;
				}
			else{
				if (datos[i].anio > men[k+2]){
					men[k+2]=datos[i].anio;
					meng[k+2]=i;
				}
				
			}
		}
	}
	for (i = 0; i < N; i++){
		
		if (datos[i].anio < may[k]){
			may[k]=datos[i].anio;
			mayg[k]=i;
		}
		else{
				if (datos[i].anio < may[k+1]){
					may[k+1]=datos[i].anio;
					mayg[k+1]=i;
					}
			else{
				if (datos[i].anio < may[k+2]){
					may[k+2]=datos[i].anio;
					mayg[k+2]=i;
				}
			}
		}
	}
	fprintf(salida,"tipo  ;marca          ;modelo    ;anio   ;dominio   ;color          ;\n");
	for (i = 0; i < 3 ; i++){
		printf("%d = %d ",i+1,men[i]); // imprimi los autos mas nuevos 
		fprintf(salida,"%d;",datos[meng[i]].tipoVehivulo);
		fprintf(salida,"%-15s;",datos[meng[i]].marca);
		fprintf(salida,"%-10s;",datos[meng[i]].modelo);
		fprintf(salida,"%d;",datos[meng[i]].anio);
		fprintf(salida,"%-10s;",datos[meng[i]].dominio);
		fprintf(salida,"%-10s\n",datos[meng[i]].color);
	}	
	printf("\n");
	fprintf(salida,"tp  ;marca          ;modelo    ;anio   ;dominio   ;color          ;\n");
	for (i = 0; i < 3 ; i++){
		printf("%d = %d ",i+1,may[i]); // imprime los autos mas viejos
		fprintf(salida,"%d;",datos[mayg[i]].tipoVehivulo);
		fprintf(salida,"%-15s;",datos[mayg[i]].marca);
		fprintf(salida,"%-10s;",datos[mayg[i]].modelo);
		fprintf(salida,"%d;",datos[mayg[i]].anio);
		fprintf(salida,"%-10s;",datos[mayg[i]].dominio);
		fprintf(salida,"%-10s\n",datos[mayg[i]].color);
	}	
	printf("\n");
	for (i = 0; i < 3 ; i++){
		printf("%d = %d ",i+1,tipos[i]); // imprimi cuantos vehiculos de cada tipo hay
	}	
	fprintf(salida,"\n");
	fprintf(salida,"procentajes\n");
	fprintf(salida,"motos; %0.2f \n",tipos[1]*100/45.0);
	fprintf(salida,"autos; %0.2f \n",tipos[2]*100/45.0);
	fprintf(salida,"camiones; %0.2f \n",100-(tipos[1]*100/45.0 + tipos[2]*100/45.0));

}	

void mostrarMenu(){

	printf(" Menu (ingrese -1 para salir): \n");
		printf("op = 1 Mostrar autos de la lista\n");
		printf("op = 2 Ordenear por colores los vehiculos\n");
		printf("op = 3 Ordenear por ...\n");
		printf("op = 4 Ordenear por ...\n");
		printf("op = 5 Ordenear por ...\n");
		printf("op = 6 Ordenear por ...\n");
		printf("op = 7 Ordenear por ...\n");
		
}
int decicion(){
	int letra;
	
	printf("desea continuar 1(si)/2(no)");
	scanf("%d",&letra);
	
	while(letra != 1){
			printf("intente de nuevo");
			scanf("%d",&letra);
	}
	
	
	if(letra == 1){
		system("cls");
		return 1;
	}else{
		return 0;
	}
		
}
int main(){
	int N,i;
	int selectorDeOpciones = 0;
	struct automotor *autito;
	FILE *entrada;
	FILE *modelo,*marca,*dominio,*color;
	
	modelo=fopen("modelo.csv","w");
	marca=fopen("marca.csv","w");
	dominio=fopen("dominio.csv","w");
	color=fopen("color.csv","w");
	
	entrada = fopen("vehiculos.txt","r");
	
	if (entrada == NULL){
		printf("no esta el archivo de lectura");
		return 0;
	}
	
	printf("ingrese la cantidad de autos: ");
	scanf("%d",&N);
	while (N<1 || N>45){
		printf("Error.");
		scanf("%d",&N);
	}
	printf("\n");
	
	autito =(struct automotor *)malloc(sizeof(struct automotor)*N);
	
	for (i = 0; i < N ; i++){
		autito[i] = leerAutos(entrada);
	}
           
           
    while (selectorDeOpciones != -1)
	{
		mostrarMenu();
		scanf("%d",&selectorDeOpciones);
		
		switch (selectorDeOpciones)
		{
			case (1):
				system("cls");
				mostrarAutos(autito,N);
				if(decicion() == 0){selectorDeOpciones=-1;}
				break;
			case (2):
				system("cls");
				qsort(autito,N,sizeof(struct automotor),ordenarPorColor);
				printf("Se ordenaron los autos por color\n");
				if(decicion() == 0){selectorDeOpciones=-1;}
				break;
			default:
				if(selectorDeOpciones==-1){
					system("cls");
				}
		}
		
	}
	//mostrarAutos(autito,N);
	qsort(autito,N,sizeof(struct automotor),ordenarPorModelo);
	cargaArchivo(autito,N,modelo);
	qsort(autito,N,sizeof(struct automotor),ordenarPorMarca);
	cargaArchivo(autito,N,marca);
	qsort(autito,N,sizeof(struct automotor),ordenarPorDominio);
	cargaArchivo(autito,N,dominio);
	qsort(autito,N,sizeof(struct automotor),ordenarPorColor);
	cargaArchivo(autito,N,color);
	//estadisticaEnArchivo(autito,N);
	return 0;
}

