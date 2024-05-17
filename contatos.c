#include <stdio.h>
#include <string.h>
#include "contatos.h"

R Novocliente(dados usuario[], int *pos) {
    if (*pos >= TOTAL) {
        printf("Agenda lotada!\n");
        return SemContato;
    }

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

    for (i = 0; i < *pos; i++) {
        if (strcmp(usuario[i].CPF, CPF) == 0) {
            encontrado = 1;

            for (int j = i; j < *pos - 1; j++) {
                strcpy(usuario[j].nome, usuario[j + 1].nome);
                strcpy(usuario[j].CPF, usuario[j + 1].CPF);
            }
            (*pos)--;
            printf("Conta removida com sucesso!\n");
            break;
        }
    }

    if (!encontrado) {
        printf("Contato com o número do CPF %s não encontrado.\n", CPF);
        return NaoEcontrado;
    }

    for (int i = 0; i < *pos; i++) {
        printf("Pos: %d\t", i + 1);
        printf("Nome: %s\t", usuario[i].nome);
        printf("CPF: %s\t", usuario[i].CPF);
        printf("tipo: %d\n", usuario[i].tipo);
        printf("valor: %d\n", usuario[i].valor);
    }

    return OK;
}

R Listarclientes(dados usuario[], int *pos) {
    if (*pos == 0) {
        printf("Sem contas para exibir!\n");
        return SemContato;
    }

    for (int i = 0; i < *pos; i++) {
        printDados(usuario[i], i + 1);
    }

    return OK;
}

R Debito(dados usuario[], int *pos){
    char cpf[11];
    int Senha;
    int i;
    int valor;
    int comum = -1000;
    int plus = -5000;
    int resultado;
    if (*pos <= 0) {
        printf("Não existem contatos na memoria\n");
    }

    for (i = 0; i < *pos; i++) {
        printf("Digite seu CPF: \n");
        scanf("%s", cpf);
        printf("Digite sua Senha: \n");
        scanf("%d", &Senha);
        if (strcmp(usuario[i].CPF, cpf) == 0 && usuario[i].senha == Senha) {
            if (usuario[i].tipo == 1 && usuario[i].valor > comum) {
                for (int j = i; j < *pos; j++) {
                    printf("Digite o valor a ser descontado: \n");
                    scanf("%d", &valor);
                    resultado = usuario[j].valor - valor;
                    if (resultado > comum){
                        usuario[j].valor = usuario[j].valor - valor;
                        printf ("o valor na conta é: %d\n", usuario[j].valor);
                    } else  {
                        printf("Operação cancelada pois o usuario terá seu saldo acima do limite negativo.");
                    }
                } break;
            } else if (usuario[i].tipo == 2 && usuario[i].valor > plus){
                for (int j = i; j < *pos; j++) {
                    printf("Digite o valor a ser descontado: \n");
                    scanf("%d", &valor);
                    resultado = usuario[j].valor - valor;
                    if (resultado > plus){
                        usuario[j].valor = usuario[j].valor - valor;
                        printf ("o valor na conta é: %d\n", usuario[j].valor);
                    } else {
                        printf("Operação cancelada pois o usuario terá seu saldo acima do limite negativo.");
                    }
                }       
            } break;
        } else {
            printf("CPF ou Senha incorretos! \n");
        }
    }
}
R Deposito(dados usuario[], int *pos) {
    char CPF[12]; // Variável para armazenar o CPF da conta
    char senha[31]; // Variável para armazenar a senha da conta
    int valor; // Variável para armazenar o valor a ser depositado
    int encontrou_conta = 0;
    int Senha;

    // Solicita o CPF da conta para autenticação
    printf("Entre com o seu CPF: ");
    scanf("%11s", CPF);
    clearBuffer();

    // Solicita a senha da conta para autenticação
    printf("Entre com a sua senha: ");
    scanf("%30d", &Senha);
    clearBuffer();

    // Verifica se a conta e a senha correspondem a alguma conta existente
    int i;
    for (i = 0; i < *pos; i++) {
        printf("Debug: Comparando CPF %s com %s\n", usuario[i].CPF, CPF);
        printf("Debug: Comparando senha %ls com %d\n", &usuario[i].senha, Senha);

        if (strcmp(usuario[i].CPF, CPF) == 0 && usuario[i].senha == Senha) {
            encontrou_conta = 1;
            break; // Sai do loop se encontrar a conta e senha correspondentes
        }
    }

    // Se a conta e senha forem válidas, continua com o processo de depósito
    if (encontrou_conta == 1) {
        // Solicita o valor a ser depositado
        printf("Entre com o valor a ser depositado: ");
        scanf("%d", &valor);
        clearBuffer();

        // Adiciona o valor ao saldo da conta
        usuario[i].valor += valor;

        printf("Depósito realizado com sucesso!\n");
        printf("Novo saldo para a conta de %s: %d\n", usuario[i].nome, usuario[i].valor);

        return OK; // Retorna OK indicando sucesso no depósito
    } else {
        // Se o CPF ou a senha fornecidos para a conta estiverem incorretos, exibe uma mensagem de erro
        printf("CPF ou senha incorretos!\n");
        return NaoEcontrado; // Retorna um código de erro indicando que a conta não foi encontrada
    }
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
