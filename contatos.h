#define TOTAL 1000

typedef struct {
    char nome[20];
    int CPF;
    int tipo;
    int valor;
    char senha[30];
}dados;

typedef enum {OK,ContatoMax,SemContato,NaoEcontrado} R;


R Novocliente(dados usuario[], int *pos);
R Apagacliente(dados usuario[], int *pos);
R Listarclientes(dados usuario[], int *pos);
R Debito(dados usuario[], int *pos);
R Deposito(dados usuario[], int *pos);
R Extrato(dados usuario[], int *pos, int tamanho);
R Transferencia(dados usuario[], int *pos);

void printDados(dados usuario, int pos);
void clearBuffer();
