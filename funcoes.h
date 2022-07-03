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
void add_funcionario(char * nome, int cpf, int senha, int cargo){
    funcionario * novo_fun = malloc(sizeof(funcionario));
    novo_fun->nome_fun = nome;
    novo_fun->cpf_fun = cpf;
    novo_fun->senha_fun = senha;
    novo_fun->cargo = cargo;
    novo_fun->prox = NULL;

    if(inicio_fun == NULL){
        inicio_fun = novo_fun;
        fim_fun = novo_fun;
    }else{
        fim_fun->prox = novo_fun;
        fim_fun = novo_fun;
    }
    tam_fun++;
}
void add_fila(int id, char * nome_aluno, int matricula, char * descricao, int cpf_resp){
    fila * novo = malloc(sizeof(fila));
    novo->id = id;
    novo->nome_aluno = nome_aluno;
    novo->matricula = matricula;
    novo->descricao = descricao;
    novo->responsavel = cpf_resp;

    printf("---DADOS---\n"VERMELHO"-------------------------------"RESET"\n");
    printf("Id: %d\nNome: %s\nMatricula: %d\nDescricao: %s\nResponsavel: %s\n", id, nome_aluno, matricula, descricao, buscar_resp(cpf_resp));
    printf(VERMELHO"-------------------------------"RESET"\n");
    printf("Campus onde o livro está: ");
    scanf(" %[^\n]s",novo->campus_origem);
    printf("Campus de destino: ");
    scanf(" %[^\n]s",novo->campus_destino);
    printf("Prioridade [0-100]: ");
    scanf("%d", &novo->prioridade);
    printf("\n");

    novo->prox = NULL;
    novo->ant = NULL;

    if(inicio_fila == NULL){
        inicio_fila = novo;
        fim_fila = novo;
    }else{
        if(novo->prioridade > inicio_fila->prioridade || novo->prioridade == inicio_fila->prioridade){
            novo->prox = inicio_fila;
            inicio_fila->ant = novo;
            inicio_fila = novo;
        }else if(novo->prioridade < fim_fila->prioridade || novo->prioridade == fim_fila->prioridade){
            fim_fila->prox = novo;
            novo->ant = fim_fila;
            fim_fila = novo;
        }else{
            fila * aux = inicio_fila->prox;
            while(novo->prioridade < aux->prioridade || novo->prioridade == aux->prioridade){
                aux = aux->prox;
            }
            aux->ant->prox = novo;
            novo->ant = aux->ant;
            novo->prox = aux;
            aux->ant = novo;
        }
    }
    tam_fila++;
    system("clear");
}
VERTICE * remover(VERTICE * aux, int id, int cpf_resp){
    if(raiz != NULL){
        VERTICE * busca = buscar(id, raiz);
        if(busca != NULL){
            if(aux == NULL){
                printf(VERMELHO"Não encontrado"RESET"\n");
                return NULL;
            }else if(aux->id > id){
                aux->esq = remover(aux->esq, id, cpf_resp);
            }else if(aux->id < id){
                aux->dir = remover(aux->dir, id, cpf_resp);
            }else{
                if(aux->esq == NULL && aux->dir == NULL){
                    add_fila(aux->id, aux->nome_aluno, aux->matricula, aux->descricao, cpf_resp);
                    aux = NULL;
                    printf(VERMELHO"Id: %d Removido"RESET"\n", id);
                    return aux;
                }else if(aux->esq == NULL){
                    add_fila(aux->id, aux->nome_aluno, aux->matricula, aux->descricao, cpf_resp);
                    aux = aux->dir;
                    printf(VERMELHO"Id: %d Removido"RESET"\n", id);
                    return aux;
                }else if(aux->dir == NULL){
                    add_fila(aux->id, aux->nome_aluno, aux->matricula, aux->descricao, cpf_resp);
                    aux = aux->esq;
                    printf(VERMELHO"Id: %d Removido"RESET"\n", id);
                    return aux;
                }else{
                    VERTICE * f = aux->esq;
                    while(f->dir != NULL){
                        f = f->dir;
                    }
                    aux->id = f->id;
                    strcpy(aux->nome_aluno, f->nome_aluno);
                    aux->matricula = f->matricula;
                    strcpy(aux->descricao, f->descricao);
                
                    f->id = id;
                    aux->esq = remover(aux->esq, id, cpf_resp);
                }
            }
            return aux;
            free(aux);
        }
    }else{
        printf(VERMELHO"Inválido nada removido"RESET"\n");
        return 0;
    }
}
