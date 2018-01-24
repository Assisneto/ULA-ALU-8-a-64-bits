#include <stdio.h>
#include <string.h>

#define PALAVRA 4;
#define VPALAVRA 5;


void add(int *a, int *b){
	int i;
	int carryin = 0;
	int r[4];

	for(i=0;i<4;i++){
		r[i] = carryin + a[i] + b[i];
		switch(r[i]){
			case 0:
				carryin = 0;
				break;
			case 1:
				carryin = 0;
				break;
			case 2:
				carryin = 1;
				r[i] = 0;
				break;
			case 3:
				carryin = 1;
				r[i] = 1;
				break;
		}
	}

	for(i=0;i<4;i++){
		printf("%i", r[i]);
	}
}
	

void main(void)
{

	int ea[4],eb[4],i;
	char fun[4],a[5],b[5];
	FILE *arq;
	
	arq = fopen("entrada.txt", "r");
	if(arq == NULL)
			printf("Erro, nao foi possivel abrir o arquivo\n");
	else
		while( (fscanf(arq,"%s %s %s\n", fun,a,b))!=EOF ){
			printf("%s %s %s\n", fun, a,b);
			for(i=4;i>0;i--){
				ea[i] = (int)a[i-1] - 48;
			}
			for(i=4;i>0;i--){
				eb[i] = (int)b[i-1] - 48;
			}
			add(ea,eb);
		}
	
	fclose(arq);
	
}