#include <stdio.h>
#include <string.h>
#include "contatos.h"

R Novocliente(dados usuario[], int *pos) {
    if (*pos >= TOTAL)
        printf("Clientes maximo atingido!");

    printf("Entre com o nome da conta: ");
    scanf("%99s", usuario[*pos].nome);
    clearBuffer();

    printf("Entre com o CPF: ");
    scanf("%99d", usuario[*pos].CPF);
    clearBuffer();

    printf("Entre com o tipo de conta (comum ou plus?): ");
    scanf("%19s", usuario[*pos].tipo);
    clearBuffer();

    printf("Entre com o valor inicial da conta: ");
    scanf("%d", usuario[*pos].valor);
    clearBuffer();

    printf("Entre com a senha de sua conta: ");
    scanf("%s", usuario[*pos].senha);
    clearBuffer();

    (*pos)++;

    return OK;
}

R Listarclientes(dados usuario[], int *pos) {
    if (*pos == 0)
        printf("Sem contatos para exibir!");

    for (int i = 0; i < *pos; i++) {
        printDados(contatos[i], i + 1);
    }

    return OK;
}

R Apagacliente(dados usuario[], int *pos) {
    int i;
    int encontrado = 0;

    if (*pos <= 0) {
        return SEM_CONTATOS;
    }

    for (i = 0; i < *pos; i++) {
        if (strcmp(contatos[i].telefone, telefone) == 0) {
            encontrado = 1;

            for (int j = i; j < *pos - 1; j++) {
                strcpy(contatos[j].nome, contatos[j + 1].nome);
                strcpy(contatos[j].email, contatos[j + 1].email);
                strcpy(contatos[j].telefone, contatos[j + 1].telefone);
            }
            (*pos)--;
            printf("Contato removido com sucesso!\n");
            break;
        }
    }
    for(int i=0; i<*pos; i++){
        printf("Pos: %c\t", i+1);
        printf("Nome: %s\t", contatos[i].nome);
        printf("email: %s\t", contatos[i].email);
        printf("telefone: %s\n", contatos[i].telefone);
    if (!encontrado) {
        printf("Contato com o número de telefone %s não encontrado.\n", telefone);
        return NAO_ENCONTRADO;
    }

    return OK;
    }
}

R Transferencia(dados usuario[], int *pos) {
    printf("\m");
}


R Extrato(dados usuario[], int *pos) {
    FILE *f = fopen("agenda.bin", "rb");
    if (f == NULL) {
        printf("Erro ao abrir o arquivo agenda.bin\n");
        return ABRIR;
    }
    int i;
    for (i = 0; i < tamanho && fread(&contatos[i], sizeof(Agenda), 1, f) == 1; i++);
    *pos = i;
    if (fclose(f) != 0) {
        printf("Erro ao fechar o arquivo agenda.bin\n");
        return FECHAR;
    }
    printf("Arquivo aberto com sucesso!");
    return OK;
}
void printAgenda(Agenda contatos, int pos) {
    printf("\nPosicao: %d\t", pos);
    printf("Nome: %s\tEmail: %s\t", contatos.nome, contatos.email);
    printf("Telefone: %s\n", contatos.telefone);
}


void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

}