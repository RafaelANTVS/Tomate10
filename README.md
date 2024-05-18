# Tomate10
Projeto poupa tem
# projeto4 - Vespertino (CC2632)

# **Banco de Dados**

## Objetivo

O Banco de Dados possibilita o usuário criar uma conta para gerenciar seu dinheiro, nesse código será inserindo seu Nome, CPF, Senha, Tipo de conta sendo Normal ou Plus e Valor Inicial da conta 

Cada registro enumera uma prioridade ao contato, sendo o limite de contatos 1000.


## Compilação


Será utilizado um programa que leia arquivos em formato C e por meio do seu terminal o usuário digita "gcc *.c && ./a.out" fazendo o código funcionar.

## Utilização


Um menu aparecerá na tela dando 8 opções ao usuário, cada opção servindo a uma ação para serem digitadas, precisando ser um dos seguintes números:

- 1- Cria uma conta na ordem do nome, CPF, tipo de Conta sendo pedido 1 para ser Comum e 2 para a Plus, o Valor Inicial da conta e senha. será dada uma posição na memória desse contato. 
- 2- Pede a senha e CPF para deletar a conta, se for encontrado a conta com o respectivo número será apagado.
- 3- Lista todas as contas com os dados na memória.
- 4- Retira da conta do usuário um valor que ele inserir, será pedido  o CPF e senha para poder ser realizado o débito. Será necessário seguir as limitações dos dois tipos de conta com valores negativos, comum até -1000, Plus -5000, caso antes e após o valor da conta do usuário tiver valores menores que os limites, essa opção não será realizada.
- 5- Deposita valor na conta do usuário. Sendo pedido seu CPF e senha.
- 6- Gera um arquivo.txt de todas as transações do usuário, sendo pedido seu CPF e senha.
- 7- Transfere um valor de uma conta para outra, necessita do CPF, senha de origem e o de destino.
- 0- digitando "0" ele sairá do programa.
