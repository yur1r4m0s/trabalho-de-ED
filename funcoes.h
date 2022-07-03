#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define VERMELHO "\x1b[31m"
#define VERDE "\x1b[32m"
#define RESET "\x1b[0m"

typedef struct Vertice{
    int id;
    char nome_aluno[100];
    int matricula;
    char descricao[200];

    struct Vertice * esq;
    struct Vertice * dir;
}VERTICE;

typedef struct fila{
    int id;
    char * nome_aluno;
    int matricula;
    char * descricao;

    char campus_origem[50];
    char campus_destino[50];
    int responsavel;
    int prioridade;

    struct fila * prox;
    struct fila * ant;
}fila;

typedef struct funcionario{
    char * nome_fun;
    int cpf_fun;
    int senha_fun;
    int cargo; //1 - transportador / 2 - secretario / 3 - gerente

    struct funcionario * prox;
}funcionario;

VERTICE * raiz = NULL;

fila * inicio_fila = NULL;
fila * fim_fila = NULL;
int tam_fila = 0;

funcionario * inicio_fun = NULL;
funcionario * fim_fun = NULL;
int tam_fun = 0;

VERTICE * buscar(int id, VERTICE * aux){
    if(aux == NULL){
        return NULL; 
    }else if(id == aux->id){
        return aux; 
    }else if(id < aux->id){ //buscar no lado esquerdo
        if(aux->esq != NULL){
            return buscar(id, aux->esq);
        }else{// esquerda ta vazia
            return aux;
        }
    }else{//buscar pelo lado direito
        if(aux->dir != NULL){
            return buscar(id, aux->dir);
        }else{//direita ta vazia
            return aux;
        }
    }
}

char * buscar_resp(int cpf_resp){
    funcionario * resp = inicio_fun;
    for(int i=0; i < tam_fun; i++){
        if(resp->cpf_fun == cpf_resp){
            return resp->nome_fun;
        }else{
            resp = resp->prox;
        }
    }
    return "0";
}

int cadastrar_encomenda(int id){
    VERTICE * busca = buscar(id, raiz);
    if(busca == NULL || busca->id != id){// vazia OU a adição é permitida porquê o busca->ID é diferente do X    
        VERTICE * novo = malloc (sizeof(VERTICE));
        novo->id = id;

        printf("----CADASTRAR----\n\nId da encomenda %d\n", id);
        printf("Aluno: ");
        scanf(" %[^\n]s",novo->nome_aluno);
        printf("Matricula: ");
        scanf("%d", &novo->matricula);
        printf("Descrição: ");
        scanf(" %[^\n]s",novo->descricao);
        printf("\n");

        novo->esq = NULL;
        novo->dir = NULL;

        if(busca == NULL){ //add na raiz
            raiz = novo;
        }else{
            if(id < busca->id){
                busca->esq = novo;
            }else{
                busca->dir = novo;
            }
        }
        system("clear");
        printf(VERDE"Encomenda de %s cadastrada"RESET"\n", novo->nome_aluno);
    }else{
        printf("ID ""%d"" DUPLICADO!! A adição não foi realizada pois já existe um ID ""%d"". \n", id, id);
        return 0;
    }
}
