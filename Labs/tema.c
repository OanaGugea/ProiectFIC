#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define NUMAR 10
char cuvinteCheie[NUMAR][10]={"movq", "movl", "cmpl", "subl","imull","addl","jmp","jge","jle","jg"};
int contoare[NUMAR];

/* 
   T = numarul total de instructiuni
   D = numarul de instructiuni de transfer de date
   A = numarul de instructiuni aritmetice
   J = numarul de instructiuni de salt (conditionat sau neconditionat)
   O = alte instructiuni
*/

char operati[][5]={"T", "D", "A", "J", "O"};
int instructiuni[5];

void numara(char *linie){
	int i;
	if((linie[0]=='.')||(linie[1]=='.')||(isalpha(linie[0]))){
		return;
	}
	else{
		for(i=0;i<NUMAR;i++){
			if((strstr(linie,cuvinteCheie[i]))!=NULL){
				contoare[i]++;
				return;
			}
		}
		instructiuni[4]++;
	}
}
void calcul(){
	int i;
	for(i=0;i<NUMAR;i++){
		instructiuni[0]+=contoare[i];
	}
	instructiuni[0]+=instructiuni[4];
	instructiuni[1]+=contoare[0]+contoare[1];
	instructiuni[2]+=contoare[2]+contoare[3]+contoare[4]+contoare[5];
	instructiuni[3]+=contoare[6]+contoare[7]+contoare[8]+contoare[9];

}
void printare(){
	int i;
	for(i=0;i<5;i++){
		printf("%s -> %d\n", operati[i], instructiuni[i]);
	}
}
void afisare(){
	printf("Operatii <movq>  %d\n", contoare[0]);
	printf("Operatii <movl>  %d\n", contoare[1]);
	printf("Operatii <cmpl>  %d\n", contoare[2]);
	printf("Operatii <subl>  %d\n", contoare[3]);
	printf("Operatii <imull> %d\n", contoare[4]);
	printf("Operatii <addl>  %d\n", contoare[5]);
	printf("Operatii <jmp>   %d\n", contoare[6]);
	printf("Operatii <jge>   %d\n", contoare[7]);
	printf("Operatii <jle>   %d\n", contoare[8]);
	printf("Operatii <jg>    %d\n", contoare[9]);
}

int main(int argc, char **argv){
	FILE *f;
	int i;
	char buffer[100];
	int linie=0;
	for(i=0;i<NUMAR;i++){
		contoare[i]=0;
	}
	for(i=0;i<5;i++){
		instructiuni[i]=0;
	}
	if(argc<2){
		printf("Eroare: argumente insuficiente!\n");
		exit(2);
	}
	f=fopen(argv[1],"r");

	while((fgets(buffer, 100, f))!=NULL){
		linie++;
		numara(buffer);
	}
	printf("Am parcurs tot fisierul!\n");
	printf("Fisierul contine %d linii!\n", linie);

	/*
	printf("Vectorul de contoare: ");
	for(i=0;i<NUMAR;i++){
		printf("%d ", contoare[i]);
	}
	printf("\n");
	*/

	calcul();
	printare();
	//afisare();
	return 0;
}
