#define TOTAL 1000

typedef struct {
    char nome[20];
    char CPF[11];
    char tipo[2];
    int valor;
    char senha;
}dados;

typedef enum {OK,ContatoMax,SemContato,NaoEcontrado, FECHAR, ABRIR, ERROR} R;


R Novocliente(dados usuario[], int *pos);
R Apagarcliente(dados usuario[], char *CPF, int *pos);
R Listarclientes(dados usuario[], int *pos);
R Debito(dados usuario[], int *pos);
R Deposito(dados usuario[], int *pos);
R Extrato(dados usuario[], int *pos, int tamanho);
R Transferencia(dados usuario[], int *pos);

void printDados(dados usuario, int pos);
void clearBuffer();
