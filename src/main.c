/* Data de submissao: 31/05/2020
 * Nome: Luiz Guilherme Silva Moreira
 * RA: 202391
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

typedef struct {
	int dado_entrada;
	int id_thread;
} thread_dados;

/* Variaveis globais */
pthread_mutex_t trava;
int contador = 0;
int libera[4];
int k = 0;

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
	
	thread_dados *infos_worker = (thread_dados *)arg; 
	int aux = 0;
	
    pthread_mutex_lock(&trava);
	
	aux = primo(infos_worker->dado_entrada);
	if(aux){
		contador++;
	}
	libera[infos_worker->id_thread] = 0;	
    pthread_mutex_unlock(&trava);
        
 			
	return NULL;
}
	
int main() {
	/* Thread principal */
	pthread_t threads[4];

	/* Variaveis de auxilio geral */
	int entrada[100];
	int qtd = 0, i = 0, j = 0, saida = 0, inteiro;
	char caracter;
	thread_dados *infos;

	/* Preenchendo o vetor liberador de zeros */
	/* Legenda: 0 - thread livre 1 - thread ocupada */
	for(i = 0; i < 4; i++){
		libera[i] = 0;
	}

	i = 0;

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
			if(libera[k]== 0){
				libera[k] = 1;
				infos = (thread_dados*)malloc(sizeof(thread_dados));
				infos ->dado_entrada = entrada[j];
				infos ->id_thread = k;
				pthread_create(&(threads[k]), NULL, worker, (void*) infos);
				j++;
				break;
			}
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

