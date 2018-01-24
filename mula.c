#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//conf da ula
#define PALAVRA 8

int saida(int *r, int *ea, int *eb, int ov, int zu, char fc[4]){
	FILE *arq;
	int i = 0;
	char a[PALAVRA],b[PALAVRA],rs[PALAVRA];
	arq = fopen("log.txt","a");
	
	//fORMATACAO DA SAIDA 
	if (PALAVRA==4){
	fprintf(arq," EA   EB   RST  LC OV ZULA\n");
	}
	if (PALAVRA==8){
	fprintf(arq,"   EA        EB      RST    LC OV ZULA\n");
	}
	if (PALAVRA==16){
	fprintf(arq,"      EA                 EB              RST        LC OV ZULA\n");
	}
	if (PALAVRA==32){
	fprintf(arq,"           EA                                 EB                                RST                 LC OV ZULA\n");
	}
	if (PALAVRA==64){
	fprintf(arq,"                                      EA                                         EB                                                                RST                                              LC OV ZULA\n");
	}
	
	//impressao do resultado
	for(i = 0;i<PALAVRA;i++){
		rs[i]=r[i]+48;
		fprintf(arq,"%c",rs[i]);
	}
	
	//impressao das entradas
	fprintf(arq," ");
	for(i = 0;i<PALAVRA;i++){
		a[i]=ea[i]+48;
		fprintf(arq,"%c",a[i]);
	}
	
	fprintf(arq," ");
	for(i = 0;i<PALAVRA;i++){
		b[i]=eb[i]+48;
		fprintf(arq,"%c",b[i]);
	}
	
	//impressao da linha de controle
    fprintf(arq," ");
	for(i = 0;i<4;i++){
		fprintf(arq,"%c",fc[i]);
	}
	
	//impressao do overFlow e zero da Lua
	fprintf(arq," %d %d\n", ov, zu);
	
	fclose(arq);
	//Saida na Tela
   printf("\nEntrada A: ");
 	for(i=0;i<PALAVRA;i++){
			printf("%i",ea[i]);
		}
	printf("\nEntrada B: ");
   
   for(i=0;i<PALAVRA;i++){
		     printf("%i",eb[i]);
		}		
     printf("\nLinha de Controle: ");
 	for(i=0;i<4;i++){
			printf("%c",fc[i]);
		}
    
	printf("\nResultado: ");
    for(i=0;i<PALAVRA;i++){
		     printf("%i",r[i]);
		}	
   
    printf("\nOverFlow: %i ", ov);
    printf("\nZero da ULa: %i ", zu);
 
 
}

int inverte(int bi){
	if(bi==0){
		return 1;
	} else {
		return 0;
	}
}

int overFlow(int c1, int c2){
	if(c1!=c2){
		return 1;
	} else {
		return 0;
	}
}

int zeroUla(int *r){
	//calculando o 0 da ula
	int i;
	for( i = 0;i<PALAVRA;i++){
		if(!(r[i]==0)){
			return inverte(1);
		}
	}
	return inverte(0);
}

void and(int *a, int *b,int func){
	int r[PALAVRA];
	int i;
	switch(func){
		case 1:
			//calculo das ulas
			for(i=PALAVRA-1;i>=0;i--){
				if(a[i]&&b[i]){
					r[i] = 1;
				} else {
					r[i] = 0;
				}
			}
			for(i = 0;i<PALAVRA;i++){
				printf("%i",r[i]);
			}
			
			saida(r,a,b, 0,zeroUla(r),"0000");
		break;
		
		case 2:
			//inverte a
			for(i=0;i<PALAVRA;i++){
				a[i] = inverte(a[i]);
			}
			//inverte b
			for(i=0;i<PALAVRA;i++){
				b[i] = inverte(b[i]);
			}
			//calculo das ulas
			for(i=PALAVRA-1;i>=0;i--){
				if(a[i]&&b[i]){
					r[i] = 1;
				} else {
					r[i] = 0;
				}
			}
			for(i = 0;i<PALAVRA;i++){
				printf("%i",r[i]);
			}
			saida(r,a,b, 0,zeroUla(r),"1100");
		break;
	}
}

void or(int *a, int *b){
	int i;
	int r[PALAVRA];
	for(i=PALAVRA-1;i>=0;i--){
		if(a[i]||b[i]){
			r[i] = 1;
		} else {
			r[i] = 0;
		}
	}
	
	saida(r,a,b, 0,zeroUla(r),"0001");
}

void add(int *a, int *b, int func){
	
	int i;
	int carryin = 0;
	int carry[PALAVRA];
	int r[PALAVRA];

	switch(func){
		case 1:
			//calculo da ula
			for(i=PALAVRA-1;i>=0;i--){
				r[i] = carryin + a[i] + b[i];
				switch(r[i]){
					case 0:
						carryin = 0;
						carry[i] = carryin;
						break;
					case 1:
						carryin = 0;
						carry[i] = carryin;
						break;
					case 2:
						carryin = 1;
						carry[i] = carryin;
						r[i] = 0;
						break;
					case 3:
						carryin = 1;
						carry[i] = carryin;
						r[i] = 1;
						break;
				}
			}
			
		
			saida(r,a,b, overFlow(carry[0],carry[1]),zeroUla(r),"0010");
		
			//printf("%i\n",overFlow(carry[0],carry[1]));	
			//printf("%i\n",zeroUla(r));
		break;

		case 2:
			carryin = 1;
			//inverte o b
			for(i=0;i<PALAVRA;i++){
				b[i] = inverte(b[i]);
			}
			//calcula as ulas
			for(i=PALAVRA-1;i>=0;i--){
				r[i] = carryin + a[i] + b[i];
				switch(r[i]){
					case 0:
						carryin = 0;
						carry[i] = carryin;
						break;
					case 1:
						carryin = 0;
						carry[i] = carryin;
						break;
					case 2:
						carryin = 1;
						carry[i] = carryin;
						r[i] = 0;
						break;
					case 3:
						carryin = 1;
						carry[i] = carryin;
						r[i] = 1;
						break;
				}
			}
			saida(r,a,b, overFlow(carry[0],carry[1]),zeroUla(r),"0110");
		break;

	}
}
	
	

	
void entradas(int *ea, int *eb){
	char a[PALAVRA*4], b[PALAVRA*4];
	int i, j, n=0;

	//PRIMEIRA ENTRADA
	printf("Digite a primeira entrada:\n");	
	scanf("%s", a);
    fflush(stdin);
    int lenA=strlen(a);
    
    //Verificacao de caracteres invalidos
    for(i=0;i<lenA;i++){
		if((a[i]!=48) && (a[i]!=49) ){
			n++;			

		}
	}
	
	if(n != 0){
		
		while( n!=0)
		 {
			  printf("digite um numero com apenas 0 ou 1\nDigite novamente\n");
			  scanf("%s", a);
	          fflush(stdin);    
              lenA=strlen(a);
              n=0;
              
              for(i=0;i<lenA;i++){
                 if((a[i]!=48) && (a[i]!=49) ){
                	n++;		         
		        }
              }
              
      	}
	}
    
    
  	
   //Verefica Se numero digitado eh maior do que palavra e faz a atribuicao de acordo com o tam da palavra  
   if(lenA>PALAVRA){
     	j=lenA-1;
     	 for(i=PALAVRA-1; i>=0 ;i--){
   	     ea[i] = (int)a[j] - 48;
   	     j--;
    }		 
	 }else{	         	 
     //atribuicao para vetor de int da entrada A      
     for(i=0;i<PALAVRA;i++){
   	     ea[i] = (int)a[i] - 48;
        }
   }
   
 
 	//SEGUNDA ENTRADA
	printf("Digite a segunda entrada:\n");
	scanf("%s", b);
	fflush(stdin);
	int lenB=strlen(b);
     n=0;
	
	 //Verificacao de caracteres invalidos
    for(i=0;i<lenB;i++){
		if((b[i]!=48) && (b[i]!=49) ){
			n++;			

		}
	}
	
	if(n != 0){
		
		while( n!=0)
		 {
			  printf("digite um numero com apenas 0 ou 1\nDigite novamente\n");
			  scanf("%s", b);
	          fflush(stdin);    
              lenB=strlen(b);
              n=0;
              
              for(i=0;i<lenB;i++){
                 if((b[i]!=48) && (b[i]!=49) ){
                	n++;		         
		        }
              }
              
      	}
	}
	
	
	
   //Verefica Se numero digitado eh maior do que palavra e faz a atribuicao de acordo com o tam da palavra  
   if(lenB>PALAVRA){
     	j=lenB-1;
     	 for(i=PALAVRA-1; i>=0 ;i--){
   	     eb[i] = (int)b[j] - 48;
   	     j--;
    }		 
	 }else{	         	 
     //atribuicao para vetor de int da entrada B      
     for(i=0;i<PALAVRA;i++){
   	     eb[i] = (int)b[i] - 48;
       }
	 }


    
    //Atribuicao de 0 nos espacos vazios da entrada A
	j=PALAVRA-1;

    if( lenA < PALAVRA){
   	 for(i=0;i<  lenA ;i++){
	 	ea[j]=ea[ lenA -1-i]; 
	 	j--;  
       } 
 
  	 for(i=0;i<PALAVRA - lenA ;i++){
		ea[i]=0;
	
	 } 
	}

    
    //Atribuicao de 0 nos espacos vazios da entrada B        
	j=PALAVRA-1;

    if( lenB < PALAVRA){
	 for(i=0;i<lenB;i++){	
	 	eb[j]=eb[lenB-1-i]; 
	 	j--;  
       } 
  	 for(i=0;i<PALAVRA - lenB;i++){
		eb[i]=0;
	 } 
	}
	 

	
	
}

void main(void)
{

	int ea[PALAVRA],eb[PALAVRA],i,esc;
	char fun[4],a[PALAVRA+1],b[PALAVRA+1];
	FILE *arq;
	
	
	
	
	printf("-----------------------------------\n");
	printf("------------mULA.c-----------------\n");
	printf("-----------------------------------\n");
	printf("1 - Add\n2 - Sub\n3 - Or\n4 - And\n5 - Nor\n6 - Automatico\n");
	scanf("%i",&esc);
	fflush(stdin);
	
	
	switch(esc){
		case 1:
			entradas(ea,eb);
			add(ea,eb,1);
			break;
        case 2:
	        entradas(ea,eb);
			add(ea,eb,2);
        	break;
  	    case 3:
    		entradas(ea,eb);
			or(ea,eb);
  	    	break;
    	case 4:
 			entradas(ea,eb);
			and(ea,eb,1);
    		break;
 		case 5:
            entradas(ea,eb);
            and(ea,eb,2);
 			break;
		
		case 6:
			arq = fopen("entrada.txt", "r");
			if(arq == NULL)
					printf("Erro, nao foi possivel abrir o arquivo\n");
			else
				while( (fscanf(arq,"%s %s %s\n", fun,a,b))!=EOF ){
					for(i=0;i<PALAVRA;i++){
						ea[i] = (int)a[i] - 48;
					}
					for(i=0;i<PALAVRA;i++){
						eb[i] = (int)b[i] - 48;
					}
					//pseudo unidade de controle
					if(!strcmp(fun,"0010")){
						add(ea,eb,1);
					} else if (!strcmp(fun,"0110")){
						add(ea,eb,2);
					} else if (!strcmp(fun,"0000")){
						and(ea,eb,1);
					} else if (!strcmp(fun,"1100")){
						and(ea,eb,2);
					} else if(!strcmp(fun,"0001")){
						or(ea,eb);
					}
				}
			
			fclose(arq);
			break;
	}
}
