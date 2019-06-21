#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    char key;
    unsigned int freq;
    struct Node *pai;
    struct Node *esq;
    struct Node *dir;
} Node;

int readMap(char *arquivo, int *freqs);
Node *genList(int *dados, int size);
Node *genTree(Node *node, int size);

Node *newNode(char key, int freq);
Node *newTreeNode(Node *node, int size);

int compare(const void *a, const void *b);

void printFreq(Node *node, int size);

int main(int argc, char **argv)
{
    //leitura e criacao do mapa de nodos
    int dados[256];
    int size = readMap(argv[1], dados);
    Node *list = genList(dados, size);
    printFreq(list, size);
    Node *tree = genTree(list, size);
    
    //imprime o nodo raiz
    printf("Bingo\n");
    //printf("\n%c - (%d) \n", tree->key, tree->freq);

    return EXIT_SUCCESS;
}

int readMap(char *arquivo, int *freqs)
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
        freqs[i] = 0;

    //leitura de caracter armazenando na posicao relativa da tabela ascii
    char c;
    while ((c = fgetc(arq)) != EOF)
        if (c != 64)
            freqs[c]++;
    fclose(arq);

    int count = 0;
    for(int i = 0; i<256; i++)
        if(freqs[i] > 0)
            count += 1;
    
    return count;
}

Node * genList(int *freqs, int size){
    //popula map com valores contidos no array de frequencias
    int index = 0;
    Node *nodeList = malloc(sizeof(Node *)* size);

    for (int i = 0; i < 256; i++)
        if (freqs[i] > 0)
            nodeList[index++] = *newNode(i, freqs[i]);

    //Ordena os nodos de forma decrescente baseados na frequencia
    qsort(nodeList, index, sizeof(Node), compare);
    return nodeList;
}

Node *genTree(Node *node, int size)
{
    //para somente quando há apenas um nodo raiz
    if (size == 0)
        return &node[0];

    //cria um nodo na penultima posicao com a frequencia dos dois ultimos
    node[size - 2] = *newTreeNode(node, size);

    //ordena a lista já com o nodo novo
    qsort(node, size -1, sizeof(Node), compare);

    //recursivo
    genTree(node, size-1);
}

//cria um nodo nodo para a arvore baseado nos dois ultimos do mapa
Node *newTreeNode(Node *node, int size)
{
    int sum = ((node[size - 1].freq) + (node[size - 2].freq));
    Node *new = newNode('@', sum);
    new->esq = &node[size - 1];
    new->dir = &node[size - 2];
    return new;
}

Node *newNode(char key, int freq)
{
    Node *new = malloc(sizeof(Node));
    new->key = key;
    new->freq = freq;
    new->pai = NULL;
    new->esq = NULL;
    new->dir = NULL;
    return new;
}

int compare(const void *a, const void *b)
{
    return (((Node *)b)->freq - ((Node *)a)->freq);
}

void printFreq(Node *node, int size){
    printf("\n");
    for(int i=0; i<size; i++){
        printf("[%c] - %d\n", node[i].key, node[i].freq);
    }
}
