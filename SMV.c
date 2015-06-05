#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"

struct Page {
	char address[9];
	Page *next;	
};

//Retorna o índice da página menos recentemente usada
int LRU(Page *pages, int numPages){
	return 0;
}

//Retorna o índice da primeira página usada
int FIFO(Page *pages, int numPages){
	return 0;
}

//Retorna o índice de uma página aleatória
int Random(Page *pages, int numPages){
	return 0;
}

bool Find(Page *head, char value[9]){
	Page *tmp = head;
	while(tmp != NULL){
		if(strcmp(tmp->address, value)==0)
			return true;
		tmp = tmp->next;
	}
	return false;
}

void FreeMemory(Page *head){
	Page *tmp = head;
	while(tmp != NULL){
		free(tmp);
		tmp = tmp->next;
	}
}

int main(int argc, char *argv[]){
	char *alg, *filePath, line[20], value[9];
	int pageSize, memSize, numPages, operations=0, reads=0, writes=0, hits=0, misses=0, writebacks=0, usedPages=0;
	float faults=0;
	FILE *file;
	Page *first, *last;
	
	alg = argv[1];
	filePath = argv[2];
	pageSize = atoi(argv[3]);
	memSize = atoi(argv[4]);

	if(pageSize < 2 || pageSize > 64){	
		printf("ERRO: O tamanho de cada pagina deve estar entre 2 e 64.");
		return 0;
	}
		
	if(memSize < 128 || memSize > 16384){
		printf("ERRO: O tamanho da memoria deve estar entre 128 e 16384.");
		return 0;
	}	
	
	if(strcmp(alg, "lru") && strcmp(alg, "fifo") && strcmp(alg,"random")){
		printf("ERRO: O algoritmo deve ser lru, fifo ou random.");
		return 0;	
	}
	
	numPages = memSize/pageSize;
		
	if(strlen(filePath) > 0){
		file = fopen(filePath, "rt");
		while(fgets(line, 20, file) != NULL){
			if(line[9] == 'W' || line[9] == 'w'){
				Page *current = (Page*)malloc(sizeof(Page));
				strncpy(current->address, line, 8);
				current->address[8] = '\0';
				current->next = NULL;
				if(usedPages < numPages){
					if(usedPages==0){
						first = current;
						last = first;
					}
					else {
						last->next = current;
						last = current;
					}			
					usedPages++;
				}
				else{
					faults++;
					//Algoritmo de substituição
				}
				writes++;
			}
			else if(line[9] == 'R' || line[9] == 'r'){
				strncpy(value, line, 8);
				value[8] = '\0';
				if(Find(first, value)){
					hits++;	
				}
				else{
					misses++;
				}
				reads++;
			}
			else{
				printf("ERRO: Os dados do arquivo de entrada estao em formato incorreto.");
				return 0;	
			}	
		}
	}
	else{
		printf("ERRO: Arquivo de entrada inválido.");
		return 0;
	}
	
	Page *tmp = first;
	while(tmp != NULL){
		printf("[%s] -> ", tmp->address);
		tmp = tmp->next;
	}
	
	printf("\nExecutando o simulador...\n");
	printf("Tamanho da memoria: %iKB\n", memSize);
	printf("Tamanho das paginas: %iKB\n", pageSize);
	printf("Tecnica de reposicao: %s\n", alg);
	printf("Numero de paginas: %i\n", numPages);
	printf("Operacoes no arquivo de entrada: %i\n", operations);
	printf("Operacoes de leitura: %i\n", reads);
	printf("Operacoes de escrita: %i\n", writes);
	printf("Page hits: %i\n", hits);
	printf("Page misses: %i\n", misses);
	printf("Numero de writebacks: %i\n", writebacks);
	printf("Taxa de page fault: %f \n", faults/writes*100);
	
	FreeMemory(first);
		
	return 0;
}


//g++ -Wall -o E:\BTI\IOAC\memoriavirtual\virtual.exe e:\BTI\IOAC\memoriavirtual\SMV.c
//E:\BTI\IOAC\memoriavirtual\virtual lru E:\BTI\IOAC\memoriavirtual\arquivo.log 32 128