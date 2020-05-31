/* Data de submissao: 31/05/2020
 * Nome: Luiz Guilherme Silva Moreira
 * RA: 202391
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

/* Variaveis globais */
pthread_mutex_t trava;
int contador = 0;

/* Funcao que verifica dado um parametro se o numero n e primo */
int primo(int n){
	int aux = 2;
	int verificacao = 1;
	
	if (n <= 1){
		verificacao = 0;
	}
	
    	while (verificacao == 1 && aux <= n / 2) {
		if (n % aux  == 0){
			verificacao = 0;
		}
		aux = aux + 1;
    	}
	
	return verificacao;
}

/* Funcao worker que verifica todos os numeros */
void* worker(void *arg) {
	int *a = (int*)(arg);
    	int b = (*a);
	int aux = 0;
	
    	pthread_mutex_lock(&trava);
	
		aux = primo(b);
		if(aux){
			contador++;
		}
		
    	pthread_mutex_unlock(&trava);
        
 			
	return NULL;
}
	
int main() {
	/* Thread principal */
	pthread_t threads[4];

	/* Variaveis de auxilio geral */
	int entrada[100];
	int qtd = 0, i = 0, j = 0, k = 0, saida = 0, inteiro;
	char caracter;

	/* Tratamento da entrada */	
	while (saida != -1){
		/* Variavel caracter serve para ler espacos */
		scanf("%d%c", &inteiro, &caracter);
		if(caracter == '\n'){
			entrada[i] = inteiro;
			saida = -1;
			qtd++;
		}else{
			entrada[i] = inteiro;
			i++;
			qtd++;
		} 
	}
   	
	/* Inicio da verificacao de primos */  
	while(j < qtd){

		/* Numero maximo de threads ao mesmo tempo */
		for(k = 0; k < 4; k++){
			if(j < qtd){
				pthread_create(&(threads[k]), NULL, worker, (&entrada[j]));
				j++;
			}
		}

		/* Esperando threads terminarem */
		for (int i = 0; i < 4; i++) {
			pthread_join(threads[i], NULL);
		}
		
	}

	/* Verifica se as threads acabaram */
    for (int i = 0; i < 4; i++) {
		pthread_join(threads[i], NULL);
	}
	
	/* Saida */	
	printf ("%d\n", contador); 
	
	return 0;
	
}
