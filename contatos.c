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
    int Senha, i, j, valor, resultado;
    int comum = -1000;
    int plus = -5000;
    int conta_comum = 0;
    int conta_plus = 0;

    if (*pos <= 0) {
        printf("Não existem contatos na memoria\n");
    }
    printf("Digite seu CPF: \n");
    scanf("%s", cpf);
    printf("Digite sua Senha: \n");
    scanf("%d", &Senha);

    for (i = 0; i < *pos; i++) {
        if (strcmp(usuario[i].CPF, cpf) == 0 && usuario[i].senha == Senha) {
            if (usuario[i].tipo == 1 && usuario[i].valor > comum) {
                for (j = i; j < *pos; j++) {
                    printf("Digite o valor a ser descontado: \n");
                    scanf("%d", &valor);
                    resultado = usuario[j].valor - valor;
                    if (resultado > comum) {
                        usuario[j].valor2 = usuario[j].valor;
                        usuario[j].debito = valor;
                        usuario[j].valor = usuario[j].valor - valor;
                        printf("O valor na conta é: %d\n", usuario[j].valor);
                        break;
                    } else {
                        printf("Operação cancelada pois o usuário terá seu saldo acima do limite negativo.\n");
                    }
                }
            } else if (usuario[i].tipo == 2 && usuario[i].valor > plus) {
                for (j = i; j < *pos; j++) {
                    printf("Digite o valor a ser descontado: \n");
                    scanf("%d", &valor);
                    resultado = usuario[j].valor - valor;
                    if (resultado > plus) {
                        usuario[j].valor2 = usuario[j].valor;
                        usuario[j].debito = valor;
                        usuario[j].valor = usuario[j].valor - valor;
                        printf("O valor na conta é: %d\n", usuario[j].valor);
                        break;
                    } else {
                        printf("Operação cancelada pois o usuário terá seu saldo acima do limite negativo.\n");
                    }
                }
            }
            break;
        }
    }

    if (i == *pos) {
        printf("CPF ou Senha incorretos! \n");
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
    int criado, Senha, i;
    char cpf[11];
    if (*pos <= 0) {
        printf("Não existem contatos na memoria\n");
    }


    printf("Digite seu CPF: \n");
    scanf("%s", cpf);
    printf("Digite sua Senha: \n");
    scanf("%d", &Senha);

    for (i = 0; i < *pos; i++) {
            if (strcmp(usuario[i].CPF, cpf) == 0 && usuario[i].senha == Senha) {
                printf("Extratos dos clientes: \n");
                printf("nome %s\n", usuario[i].nome);
                printf("Valor Inicial: %d\n", usuario[i].valor2);
                printf("Valor do débito: %d\n", usuario[i].debito);
                printf("Valor na conta após o débito: %d\n", usuario[i].valor);
                // printf("Transferencia de: %d, para: %s", usuario[i].inserir, usuario[i].inserir);
                printf("\n");
        }else {
        printf("CPF ou Senha incorretos! \n");
    }
    }
    FILE *cliente;
    cliente = fopen("Extratos.txt", "a");
    if (cliente == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    fprintf(cliente, "Extratos dos clientes\n");
    fprintf(cliente, "Nome: %s\n", usuario[i].nome);
    fprintf(cliente, "Valor Inicial: %d\n", usuario[i].valor2);
    fprintf(cliente, "Valor do débito: %d\n", usuario[i].debito);
    fprintf(cliente, "Valor na conta após o débito: %d\n", usuario[i].valor);
    fprintf(cliente, "------------------------------------\n");

    fclose(cliente);
}

R Transferencia(dados usuario[], int *pos) {
    char CPF[12]; // Variável para armazenar o CPF da conta do remetente
    char CPF_alvo[12]; // Variável para armazenar o CPF da conta do destinatário
    int senha; // Variável para armazenar a senha da conta do remetente
    int valor; // Variável para armazenar o valor a ser transferido
    int encontrou_conta_remetente = 0;
    int encontrou_conta_alvo = 0;

    // Solicita o CPF da conta do remetente para autenticação
    printf("Entre com o seu CPF: ");
    scanf("%11s", CPF);
    clearBuffer();

    // Solicita a senha da conta do remetente para autenticação
    printf("Entre com a sua senha: ");
    scanf("%d", &senha);
    clearBuffer();

    // Verifica se a conta do remetente e a senha correspondem a alguma conta existente
    int i;
    for (i = 0; i < *pos; i++) {
        printf("Debug: Comparando CPF %s com %s\n", usuario[i].CPF, CPF);
        printf("Debug: Comparando senha %d com %d\n", usuario[i].senha, senha);

        if (strcmp(usuario[i].CPF, CPF) == 0 && usuario[i].senha == senha) {
            encontrou_conta_remetente = 1;
            break; // Sai do loop se encontrar a conta e senha correspondentes
        }
    }

    if (encontrou_conta_remetente == 1) {
        // Solicita o CPF da conta destinatária
        printf("Entre com o CPF do destinatário: ");
        scanf("%11s", CPF_alvo);
        clearBuffer();

        // Solicita o valor a ser transferido
        printf("Entre com o valor da transferência: ");
        scanf("%d", &valor);
        clearBuffer();

        // Verifica se a conta destinatária existe
        int j;
        for (j = 0; j < *pos; j++) {
            printf("Debug: Comparando CPF %s com %s\n", usuario[j].CPF, CPF_alvo);

            if (strcmp(usuario[j].CPF, CPF_alvo) == 0) {
                encontrou_conta_alvo = 1;
                break; // Sai do loop se encontrar a conta destinatária
            }
        }

        if (encontrou_conta_alvo == 1) {
            // Verifica se o remetente tem saldo suficiente para a transferência
            if (usuario[i].valor >= valor) {
                usuario[i].valor -= valor;
                usuario[j].valor += valor;
                printf("Transferência realizada com sucesso!\n");
                printf("Novo saldo do remetente (%s): %d\n", usuario[i].nome, usuario[i].valor);
                printf("Novo saldo do destinatário (%s): %d\n", usuario[j].nome, usuario[j].valor);
                return OK;
            } else {
                printf("Saldo insuficiente para a transferência.\n");
                return NaoEcontrado;
            }
        } else {
            printf("Conta destinatária com CPF %s não encontrada.\n", CPF_alvo);
            return NaoEcontrado;
        }
    } else {
        printf("CPF ou senha incorretos!\n");
        return NaoEcontrado;
    }

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