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
    scanf("%d", &usuario[*pos].tipo);
    clearBuffer();

    printf("Entre com o valor inicial: ");
    scanf("%d", &usuario[*pos].valor);
    clearBuffer();

    printf("Entre com a senha da conta: ");
    scanf("%30d", &usuario[*pos].senha);
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
                usuario[j].tipo, usuario[j + 1].tipo;
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
        printf("tipo: %d\n", usuario[i].tipo);
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
    char cpf[11];
    int i;
    int valor;
    int comum = -1000;
    int plus = -5000;

    if (*pos <= 0) {
        printf("Não existem contatos na memoria\n");
    }


    for (i = 0; i < *pos; i++) {;
        printf("Digite seu CPF: \n");
        scanf("%s", cpf);
        if (strcmp(usuario[i].CPF, cpf) == 0) {
            if (usuario[i].tipo >= comum || usuario[i].tipo >= plus) {
                for (int j = i; j < *pos; j++) {
                    printf("Digite o valor a ser descontado: \n");
                    scanf("%d", &valor);
                    usuario[j].valor = usuario[j].valor - valor;
                    printf ("o valor na conta é: %d\n", usuario[j].valor);
                    break;
            } 
        } else {
                printf("Valor na conta insuficiente!\n");
        }
    } else {
            printf("CPF não econtrado\n");
        }
    }

}
// FILE *f = fopen("agenda.bin", "wb");
//     if (f == NULL)
//         return ABRIR;
//     for (int i = 0; i < *pos; i++) {
//         if (fwrite(&usuario[i], sizeof(Agenda), 1, f) != 1) {
//             fclose(f);
//             return ESCREVER;
//         }
//     }
//     if (fwrite(pos, sizeof(int), 1, f) != 1) {
//         fclose(f);

//     int qtd = fwrite(contatos, sizeof(Agenda), *pos, f);
//     if (qtd != *pos)
//         return ESCREVER;

//     if (fwrite(pos, sizeof(int), 1, f) != 1)
//         return ESCREVER;
//     }
//     if (fclose(f) != 0)
//         return FECHAR;
//         printf("Arquivo salvo com sucesso!");
//     return OK;
// }






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
    printf("tipo de conta: %d\t", contatos.tipo);
    printf("dinheiro depositado: %d\n", contatos.valor);
}


void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

}
