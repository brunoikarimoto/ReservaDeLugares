#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define LIN 10
#define COL 10

typedef struct dataNasc{
    int dia;
    int mes;
    int ano;
}DataNasc;

typedef struct poltrona{
    int x;
    int y;
}Poltrona;

typedef struct cliente{
    DataNasc data;
    char nome[50];
    char cpf[11];
    long int telefone;
    char sexo;
    int codigo;
    Poltrona p;
}Cliente;

void mostraLugares(char matriz[LIN][COL]);
void inicializaLugares(char matriz[LIN][COL]);
void menu();
Cliente cadastro(char matriz[LIN][COL], int pos);
int validarCPF(char *cpf);
int validarTelefone(long int tel);
int validarNasc(int dia, int mes, int ano);
int pegaLinha();
int pegaColuna();
void pesquisar(Cliente clientes[LIN*COL]);
void imprimeClientes(Cliente cliente);
int cancelar(Cliente clientes[LIN*COL]);
void inicializaClientes(Cliente clientes[LIN*COL]);
void alterar(Cliente clientes[LIN*COL], char matriz[LIN][COL]);
void mostraTodosClientes(Cliente clientes[LIN*COL]);