#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

void leituraIndexada(char *arquivo, int *freqs);
void imprimeDados(int *freqs);

int main(int argc, char **argv)
{
    int dados[256];
    leituraIndexada(argv[1], dados);

    for (int i = 0; i < 256; i++)
    {
        printf("Char: %c %d \n", i, dados[i]);
    }

    return 0;
}

void leituraIndexada(char *arquivo, int *freqs)
{
    //leitura
    FILE *arq = fopen(arquivo, "r");
    if (arq == NULL)
    {
        printf("Erro! Arquivo não encontrado!\n");
        exit(EXIT_FAILURE);
    }

    //zera os valores nas posicoes
    for (int i = 0; i < 256; i++)
    {
        freqs[i] = 0;
    }

    //leitura de caracter armazenando na posicao relativa da tabela ascii
    char c;
    while ((c = fgetc(arq)) != EOF)
    {
        freqs[c]++;
    }
    fclose(arq);
    return freqs;
}

void imprimeDados(int *freqs)
{
    for (int i = 0; i < 256; i++)
    {
        printf("Char: %c %d \n", i, freqs[i]);
    }
}
