#include <stdbool.h> // para usar variaveis booleanas
#include <time.h>    // calcular a diferença do tempo inicial e final
#include <stdlib.h>  // pra usar a funcao RAND()
#include <stdio.h>
#include <string.h>
#define TF 20    // tamanho do agenda
#define MAX 9999 // maximo elemento gerado randomicamente dentro do agenda

struct agenda
{
  char aux[20];
  char nome[20];
  char celular[20];
};

void carrega(struct agenda agenda[], int &tl)
{
  FILE *fp = fopen("agenda.txt", "r");
  if (fp == NULL)
  {
    printf("\n nao encontrou o arquivo agenda.txt");
    exit(0);
  }
  else
  {
    char nome[20];
    char celular[20];
    tl = 0;
    while (!feof(fp))
    {
      fscanf(fp, "%s %s\n", nome, celular);
      printf("%s %s\n", nome, celular);
      strcpy(agenda[tl].celular, celular);
      strcpy(agenda[tl].nome, nome);
      tl++;
    }
    fclose(fp);
    tl--;
  }
}

void exibe(struct agenda agenda[20], int tl)
{
  printf("\n==== LISTAR ====");
  int i;
  for (i = 0; i < tl; i++)
  {
    printf("\n Posicao=%d Nome: %s Telefone: %s", i, agenda[i].nome,
           agenda[i].celular);
  }
}

void buscar(struct agenda agenda[20], int tl, char nome[10])
{
  printf("BUSCAR\n");
  int i = 0;
  while ((i < tl) && (strcmp(agenda[i].nome, nome) != 0))
    i++;
  //
  if (i < tl)
  { // encontrou o nome na posicao i
    printf("\nEncontrou o nome %s com Telefone=%d", nome,
           agenda[i].celular);
  }
  else
    printf("\n nao encontrou o nome fornecido");
}

void incluir(struct agenda agenda[20], int &tl)
{
  if (tl >= 20)
  {
    printf("\n Agenda cheia.");
    return;
  }
  printf("\n ==== INCLUIR ====");
  char nome[20];
  char telefone[20];
  printf("\nDigite seu nome: ");
  scanf("%s", nome);
  printf("\nDigite seu telefone: ");
  scanf("%s", telefone);
  strcpy(agenda[tl].nome, nome);
  strcpy(agenda[tl].celular, telefone);
  tl++;
  printf("\n Inserido com sucesso.");
}

void regravar(struct agenda agenda[], int tl)
{
  FILE *file = fopen("agenda.txt", "w");
  int i;
  for (i = 0; i < tl - 1; i++)
  {
    fprintf(file, "%s %s\n", agenda[i].nome, agenda[i].celular);
  }
  fprintf(file, "%s %s", agenda[i].nome, agenda[i].celular);
  printf("\nRegravado com sucesso\n");
  fclose(file);
}

int buscaExaustiva(struct agenda agenda[], int tl, char elem[])
{
  int i = 0;
  printf("\nBuscando a %s\n", elem);
  while ((strcmp(agenda[i].nome, elem) != 0) && (i < tl))
  {
    i = i + 1;
  }
  if ((i < tl) && (strcmp(agenda[i].nome, elem) == 0))
  {
    return i; // achou na posição i
  }
  else
  {
    return -1; // não achou
  }
}

void remover(struct agenda agenda[20], int &tl, char nome[])
{
  int i = buscaExaustiva(agenda, tl, nome);
  if (i == -1)
  {
    printf("\nUsuario nao existe\n");
  }
  else
  {
    for (int j = i; j < tl; j++)
    {
      strcpy(agenda[j].nome, agenda[j + 1].nome);
      strcpy(agenda[j].celular, agenda[j + 1].celular);
    }
  }
  tl--;
  printf("\nRemovido com sucesso\n");
}

int main()
{
  int tl = 0;
  struct agenda contato[20];
  char opcao = 'a';
  int posicao = -1;
  char elem[20];
  char nome[20];
  carrega(contato, tl);
  while (strcmp(&opcao, "s") != 0)
  {
    printf("\n\n ====== AGENDA ======");
    printf("\nDigite a opcao desejada");
    printf("\n(I)ncluir");
    printf("\n(E)xcluir");
    printf("\n(B)uscar");
    printf("\n(L)istar");
    printf("\n(R)egravar");
    printf("\n(S)air");
    printf("\nEntre com a opcao: ");
    scanf("%s", &opcao);
    switch (opcao)
    {
    case 'i':
      incluir(contato, tl);
      break;
    case 'e':
      printf("Digite nome a ser removido: ");
      scanf("%s", nome);
      remover(contato, tl, nome);
      break;
    case 'b':
      printf("Digite nome do usuario: ");
      scanf("%s", nome);
      posicao = buscaExaustiva(contato, tl, nome);
      if (posicao == -1)
      {
        printf("Usuario nao existe\n");
      }
      else
      {
        printf("Usuario contem na lista, na posicao: %d", posicao);
      }
      break;
    case 'l':
      exibe(contato, tl);
      break;
    case 'r':
      regravar(contato, tl);
      break;
    default:
      printf("invalido\n");
    } // switch
  }   // while
} // main