#include <stdio.h>
#include <string.h>
#include "contatos.h"

int main (){

    int opcao;
    int pos = 0;
    dados usuario[TOTAL];

    do {
        printf("\nMenu principal\n");
        printf("1 - Novo cliente\n");
        printf("2 - Apaga cliente\n");
        printf("3 - Listar clientes\n");
        printf("4 - Débito\n");
        printf("5 - Depósito\n");
        printf("6 - Extrato\n");
        printf("7 - Transferência Entre Contas\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcão: ");
        scanf("%d", &opcao);
        printf("Opção escolhida: %d\n", opcao);

        switch (opcao) {
            case 1:
                Novocliente(usuario, &pos);
                break;
            case 2: {
                char cliente_a_remover[11];
                printf("Digite o número do CPF do cliente que deseja remover: ");
                scanf("%19s", cliente_a_remover);
                Apagarcliente(usuario, cliente_a_remover, &pos);
                break;
}
            case 3:
                Listarclientes(usuario, &pos);
                break;
            case 4:
                Debito(usuario, &pos);
                break;
            case 5:
                Deposito(usuario, &pos);
                break;
            case 6:
                Extrato(usuario, &pos, TOTAL);
                break;
            case 7:
                Transferencia(usuario, &pos);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida\n");
        }
    } while (opcao != 0);

    return 0;
}