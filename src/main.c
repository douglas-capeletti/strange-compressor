#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

int main()
{
	int freqs[256];
	for(int i=0; i<256; i++){
		freqs[i]=0;
	}

	// FILE *arq = fopen(argv[1], "r");
	FILE *arq = fopen("exemplos.data", "r");

	if (arq == NULL)
	{
		printf("Erro! Arquivo não encontrado!\n");
		exit(EXIT_FAILURE);
	}
	
	char c;
	while ((c = fgetc(arq)) != EOF)
		freqs[c]++;
	printf("char: %c\n", c);

	for (int i=0; i<256; i++){
		printf("%c %d", i, freqs[i]);
	}

   rewind(arq); // volta ao início do arquivo

    char aux[200];
    while(fgets(aux, 200, arq) != NULL)
        printf("str: [%s]\n", aux);

    rewind(arq); // volta ao início do arquivo

    while(fscanf(arq, "%s", aux) != EOF)
        printf("palavra: %s\n", aux);

    rewind(arq); // volta ao início do arquivo

    int num;
    fscanf(arq, "%d", &num); // tenta ler o no.
    printf("Número: %d\n", num);

    fgets(aux, 200, arq); // pula o \n do 42
    fgets(aux, 200, arq); // 2a. linha
    printf("linha 1: %s", aux);
    fgets(aux, 200, arq); // 3a. linha
    printf("linha 2: %s", aux);



    fclose(arq);
    return 0;
}
