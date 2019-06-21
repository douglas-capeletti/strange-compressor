#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

typedef struct Node
{
    char key;
    unsigned int freq;
    struct Node *pai;
    struct Node *esq;
    struct Node *dir;
} Node;

typedef struct Map
{
    int length;
    struct Node *node;
} Map;

Map *index(char *arquivo);
Node *genTree(Map *map);

Map *newMap(Node *node, int length);
Node *newNode(char key, int freq);
Node *newTreeNode(Map *map);

int compare(const void *a, const void *b);

int main(int argc, char **argv)
{
    //leitura e criacao do mapa de nodos
    Map *map = index(argv[1]);
    
    //criacao da arvore
    Node *node = genTree(map);
    
    //imprime o nodo raiz
    //printf("\n%c - (%d) \n", node->key, node->freq);

    return EXIT_SUCCESS;
}

Map *index(char *arquivo)
{
    //leitura
    FILE *arq = fopen(arquivo, "r");
    if (arq == NULL)
    {
        printf("Erro! Arquivo não encontrado!\n");
        exit(EXIT_FAILURE);
    }

    //zera os valores nas posicoes
    int freqs[256];
    for (int i = 0; i < 256; i++)
        freqs[i] = 0;

    //leitura de caracter armazenando na posicao relativa da tabela ascii
    char c;
    while ((c = fgetc(arq)) != EOF)
        if (c != 64)
            freqs[c]++;
    fclose(arq);

    //popula map com valores contidos no array de frequencias
    int index = 0;
    Node *nodeList = malloc(sizeof(Node *));
    for (int i = 0; i < 256; i++)
        if (freqs[i] > 0)
            nodeList[index++] = *newNode(i, freqs[i]);

    //Ordena os nodos de forma decrescente baseados na frequencia
    qsort(nodeList, index, sizeof(Node), compare);
    return newMap(nodeList, index);
}

Node *genTree(Map *map)
{
    //para somente quando há apenas um nodo raiz
    if (map->length == 0)
        return &map->node[0];

    //cria um nodo na penultima posicao com a frequencia dos dois ultimos
    map->node[map->length - 2] = *newTreeNode(map);

    //subtrai um no tamanho final da lista
    map->length = map->length - 1;

    //ordena a lista já com o nodo novo
    qsort(map->node, map->length, sizeof(Node), compare);

    //recursivo
    genTree(map);
}

//cria um nodo nodo para a arvore baseado nos dois ultimos do mapa
Node *newTreeNode(Map *map)
{
    int sum = ((map->node[map->length - 1].freq) + (map->node[map->length - 2].freq));
    Node *new = newNode('@', sum);
    new->esq = &map->node[map->length - 1];
    new->dir = &map->node[map->length - 2];
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

Map *newMap(Node *node, int length)
{
    Map *map = malloc(sizeof(Map *));
    map->node = node;
    map->length = length;
}

int compare(const void *a, const void *b)
{
    return (((Node *)b)->freq - ((Node *)a)->freq);
}
