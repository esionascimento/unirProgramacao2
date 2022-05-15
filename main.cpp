#include <stdbool.h> // para usar variaveis booleanas
#include <time.h>    // calcular a diferença do tempo inicial e final
#include <stdlib.h>  // pra usar a funcao RAND()
#include <stdio.h>
#include <string.h>
#define TF 50000 // tamanho do vetor
#define MAX 9999 // maximo elemento gerado randomicamente dentro do vetor

struct funcionario
{
  char nome[10];
  float salario;
  int idade;
};

void carrega(struct funcionario vetor[20], int &tl)
{
  FILE *fp = fopen("empresa.txt", "r");
  if (fp == NULL)
  {
    printf("\n nao encontrou o arquivo empresas.txt");
    exit(0);
  }
  else
  {
    char nome[10];
    float salario;
    int idade;
    tl = 0;
    while (!feof(fp))
    {
      fscanf(fp, "%s %f %d\n", nome, &salario, &idade);
      strcpy(vetor[tl].nome, nome);
      vetor[tl].salario = salario;
      vetor[tl].idade = idade;
      tl++;
    }
    fclose(fp);
  }
}

void exibe(struct funcionario vetor[20], int tl)
{
  int i;
  for (i = 0; i < tl; i++)
  {
    printf("\n Nome:%s  Salario:%5.2f   Idade:%d", vetor[i].nome,
           vetor[i].salario,
           vetor[i].idade);
  }
}

void buscar(struct funcionario vetor[20], int tl, char nome[10])
{
  int i = 0;
  while ((i < tl) && (strcmp(vetor[i].nome, nome) != 0))
    i++;
  //
  if (i < tl)
  { // encontrou o nome na posicao i
    printf("\nEncontrou o nome %s com salario=%5.2f  e idade=%d", nome,
           vetor[i].salario,
           vetor[i].idade);
  }
  else
    printf("\n nao encontrou o nome fornecido");
}

void cria(int vetor[TF])
{
  for (int i = 0; i < TF; i++)
  {
    /* vetor[i] = rand() % MAX; */
    vetor[i] = i;
  }
}
void exibe(int vetor[TF])
{
  int i;
  for (i = 0; i < TF; i++)
    printf("\n vetor[%2d]=%3d", i, vetor[i]);
  getchar();
}

int buscaExaustiva(int vetor[], int tl, int elem)
{
  int i = 0;
  while ((vetor[i] != elem) && (i < tl))
  {
    i = i + 1;
  }
  if ((i < tl) && (vetor[i] == elem))
  {
    return i; // achou na posição i
  }
  else
  {
    return -1; // não achou
  }
}

int buscaSequencial(int vetor[], int elem)
{
  int i = 0;
  while ((elem > vetor[i]) && (i < TF))
  {
    i++;
  }
  if ((i < TF) && (elem == vetor[i]))
  {
    return i; // achou na posição i
  }
  else
  {
    return -i; // não achou
  }
}

int buscaBinaria(int vetor[], int tl, int elem)
{
  int inicio, meio, fim;
  inicio = 0;
  fim = tl - 1;
  meio = (inicio - fim) / 2;
  while ((elem != vetor[meio]) && inicio < fim)
  {
    if (elem > vetor[meio])
      inicio = meio + 1;
    else
      fim = meio;
    meio = (inicio + fim) / 2;
  }
  if (elem > vetor[meio])
  {
    return (meio + 1);
  }
  else
  {
    return (meio);
  }
}

int main()
{
  int tl = 0;
  int vetor[TF];
  bool ordenado = false;
  int opcao = 0, posicao = -1, elem;
  time_t tempoi, tempof;
  float diferenca;
  while (opcao != 8)
  {
    printf("\n1 - Cria o vetor de %d elementos", TF);
    printf("\n2 - Exibe o vetor gerado");
    printf("\n3 - Ordena o vetor");
    printf("\n4 - Busca Exaustiva de um elemento no vetor desordenado");
    printf("\n5 - Busca Sequencial num vetor Ordenado");
    printf("\n6 - Busca Binaria num vetor Ordenado");
    printf("\n7 - Busca Binaria Recursiva num vetor Ordenado");
    printf("\n8 - Sair");
    printf("\nEntre com a opcao: ");
    scanf("%d", &opcao);
    switch (opcao)
    {
    case 1:
      srand(time(NULL));
      cria(vetor);
      ordenado = false;
      printf("\n vetor gerado com %d elementos \n\n", TF);
      break;
    case 2:
      exibe(vetor);
      break;
    case 3:
      tempoi = time(NULL); // obtem o tempo inicial para cronometrar
      /* ordena(vetor); */
      tempof = time(NULL);
      diferenca = difftime(tempof, tempoi);
      printf("\n ordenou vetor e demorou %f num vetor de %d elementos", diferenca, TF);
      ordenado = true;
      break;
    case 4:
      printf("\n Exaustiva. Entre com o valor a ser procurado: ");
      scanf("%d", &elem);
      tempoi = time(NULL);
      posicao = buscaExaustiva(vetor, TF, elem);
      tempof = time(NULL);
      // calcular a diferenca
      diferenca = difftime(tempof, tempoi);
      if (posicao == -1)
        printf("\n NAO encontrou e demorou %f num vetor de %d elementos", diferenca, TF);
      else
        printf("\n Demorou %f no vetor de %d elementos e encontrou na posicao vetor[%d]=%d", diferenca, TF, posicao, vetor[posicao]);
      break;
    case 5:
      printf("\n SEQUENCIAL exige vetor ORDENADO!!! \n Entre com o valor a ser procurado: ");
      scanf("%d", &elem);
      if (ordenado)
      {
        tempoi = time(NULL);
        posicao = buscaSequencial(vetor, elem);
        tempof = time(NULL);
        // calcular a diferenca do tempo gasto
        diferenca = difftime(tempof, tempoi);
        if (posicao != -1)
          printf("\n Encontrou no vetor na posicao vetor[%d]=%d", posicao, vetor[posicao]);
        else
          printf("\n NAO encontrou e demorou %f num vetor de %d elementos", diferenca, TF);
      }
      else
        printf("Vetor NAO esta ordenado \n\n");
      break;
    case 6:
      printf("\n BINARIA exige vetor ORDENADO!!! \n Entre com o valor a sere procurado: ");
      scanf("%d", &elem);
      if (ordenado)
      {
        tempoi = time(NULL);
        posicao = buscaBinaria(vetor, tl, elem);
        tempof = time(NULL);
        // calcular a diferenca
        diferenca = difftime(tempof, tempoi);
        if (vetor[posicao] != elem)
          printf("\n NAO encontrou - posicao ideal para inserir %d ", posicao);
        else
          printf("\n Encontrou no vetor na posicao vetor[%d]=%d", posicao, vetor[posicao]);
      }
      else
        printf("Vetor NAO esta ordenado \n\n");
      break;
    case 7:
      printf("\n BINARIA RECURSIVA exige vetor ORDENADO");
      scanf("%d", &elem);
      if (ordenado)
      {
        // tempo inicial
        // posicao = binariaRecursiva(vetor,elem,0,TF-1);
        //  tempo final
        //  calcular a diferenca do tempo gasto
        if (vetor[posicao] != elem)
          printf("\n NAO encontrou - posicao ideal para inserir %d ", posicao);
        else
          printf("\n Encontrou no vetor na posicao vetor[%d]=%d", posicao, vetor[posicao]);
      }
      else
        printf("Vetor NAO esta ordenado \n\n");
      break;
    } // switch
  }   // while
} // main