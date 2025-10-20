// desafio basico - incluindo bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// definindo numero máximo de territorios
#define max_territorio 5
#define max_string 15

struct Territorio {
    char nome[max_string];
    char cor[max_string];
    int numero;
};

// definindo funcao para limpar buffer (desconsiderar \n)
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// definindo como sera o mapa considerando as pre definiçoes estabelecidas
int main() {
    struct Territorio territoriosmapa[max_territorio];
    int totalterritorio = 0;
    int opcao;

    do {
        printf("--------------------------\n");
        printf("1 - Cadastrar novo territorio\n");
        printf("2 - Listar todos territorios\n");
        printf("0 - Sair\n");  
        printf("--------------------------\n");
        printf("Digite opcao desejada: ");

        scanf("%d", &opcao);
        limparBufferEntrada();

        switch (opcao) {
            case 1: 
                printf("------ Cadastro de novo território ------\n");

                if (totalterritorio < max_territorio) {
                    printf("Digite o nome do território: "); 
                    fgets(territoriosmapa[totalterritorio].nome, max_string, stdin);
                    territoriosmapa[totalterritorio].nome[strcspn(territoriosmapa[totalterritorio].nome, "\n")] = '\0';

                    printf("Digite a cor do exercito: ");
                    fgets(territoriosmapa[totalterritorio].cor, max_string, stdin);
                    territoriosmapa[totalterritorio].cor[strcspn(territoriosmapa[totalterritorio].cor, "\n")] = '\0';

                    printf("Digite o numero de tropas: ");
                    scanf("%d", &territoriosmapa[totalterritorio].numero);
                    limparBufferEntrada();

                    totalterritorio++;

                    printf("\n-----Territorio cadastrado com sucesso!-----\n");
                } else {
                    printf("\n-----O numero maximo de territorios e 5!-----\n");
                }
                break;

            case 2:
                printf("----- Lista de territorios -----\n\n");

                if (totalterritorio == 0) {
                    printf("----- Nenhum territorio cadastrado -----\n");
                } else {
                    for (int i = 0; i < totalterritorio; i++) {
                        printf("-------------------------------\n");
                        printf("Territorio %d\n", i + 1);
                        printf("Nome: %s\n", territoriosmapa[i].nome);
                        printf("Cor: %s\n", territoriosmapa[i].cor);
                        printf("Numero de tropas: %d\n", territoriosmapa[i].numero);
                    }
                    printf("-------------------------------\n");
                }
                break;

            case 0:
                printf("\n----- SAINDO DO SISTEMA -----\n");
                break;

            default:
                printf("\n----- OPCAO INVALIDA, TENTE NOVAMENTE -----\n");
                break;
        }

    } while (opcao != 0);

    return 0;
}
