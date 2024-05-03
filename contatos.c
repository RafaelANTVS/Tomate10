#include <stdio.h>
#include <string.h>
#include "contatos.h"

R Novocliente(dados usuario[], int *pos) {
    if (*pos >= TOTAL)
        printf("Agenda lotada!");

    printf("Entre com o nome do usuario: ");
    scanf("%10s", usuario[*pos].nome);
    clearBuffer();


    printf("Entre com um número de CPF: ");
    scanf("%11s", usuario[*pos].CPF);
    clearBuffer();

    printf("Entre com o tipo de conta, 1 - comum, 2 - plus: ");
    scanf("%s", usuario[*pos].tipo);
    clearBuffer();

    printf("Entre com o valor inicial: ");
    scanf("%d", &usuario[*pos].valor);
    clearBuffer();

    printf("Entre com a senha da conta: ");
    scanf("%30s", usuario[*pos].senha);
    clearBuffer();


    (*pos)++;

    return OK;
}

R Apagarcliente(dados usuario[], char *CPF, int *pos) {
    int i;
    int encontrado = 0;

    if (*pos <= 0) {
        return SemContato;
    }

    for (i = 0; i < *pos; i++) {;
        if (strcmp(usuario[i].CPF, CPF) == 0) {
            encontrado = 1;

            for (int j = i; j < *pos - 1; j++) {
                strcpy(usuario[j].nome, usuario[j + 1].nome);
                strcpy(usuario[j].CPF, usuario[j + 1].CPF);
                strcpy(usuario[j].tipo, usuario[j + 1].tipo);
                usuario[j].valor, usuario[j + 1].valor;
                usuario[j].senha, usuario[j + 1].senha;

            }
            (*pos)--;
            printf("conta removida com sucesso!\n");
            break;
        }
    }
    for(int i=0; i<*pos; i++){
        printf("Pos: %c\t", i+1);
        printf("Nome: %s\t", usuario[i].nome);
        printf("CPF: %s\t", usuario[i].CPF);
        printf("tipo: %s\n", usuario[i].tipo);
        printf("valor: %d\n", usuario[i].valor);
    if (!encontrado) {
        printf("Contato com o número do CPF %s não encontrado.\n", CPF);
        return NaoEcontrado;
    }

    return OK;
    }
}

R Listarclientes(dados usuario[], int *pos) {
    if (*pos == 0)
        printf("Sem contas para exibir!");

    for (int i = 0; i < *pos; i++) {
        printDados(usuario[i], i + 1);
    }

    return OK;
}

R Debito(dados usuario[], int *pos){
    printf("Debito\n");
}

R Deposito(dados usuario[], int *pos){
        printf("Deposito\n");
}

R Extrato(dados usuario[], int *pos, int tamanho) {
    FILE *f = fopen("extrato.bin", "rb");
    if (f == NULL) {
        printf("Erro ao abrir o arquivo de extrato.bin\n");
        return ABRIR;
    }
    int i;
    for (i = 0; i < tamanho && fread(&usuario[i], sizeof(dados), 1, f) == 1; i++);
    *pos = i;
    if (fclose(f) != 0) {
        printf("Erro ao fechar o arquivo agenda.bin\n");
        return FECHAR;
    }
    printf("Arquivo aberto com sucesso!");
    return OK;
}

R Transferencia(dados usuario[], int *pos){
    printf("Tranferencia\n");
}
void printDados(dados contatos, int pos) {
    printf("\nPosicao: %d\t", pos);
    printf("Nome: %s\tCPF: %s\t", contatos.nome, contatos.CPF);
    printf("tipo de conta: %s\t", contatos.tipo);
    printf("dinheiro depositado: %d\n", contatos.valor);
}


void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

}