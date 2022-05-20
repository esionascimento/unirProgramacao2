#define TF 500000 // tamanho do vetor
#define MAX 9999  // maximo elemento gerado randomicamente dentro do vetor

#include <stdbool.h> // para usar variaveis booleanas
#include <time.h>    // calcular a diferença do tempo inicial e final
#include <stdlib.h>  // pra usar a funcao RAND()
#include <stdio.h>
void cria(int vetor[TF])
{
  for (int i = 0; i < TF; i++)
  {
    vetor[i] = rand() % MAX;
  }
}
void exibe(int vetor[TF])
{
  int i;
  for (i = 0; i < TF; i++)
    printf("\n vetor[%2d]=%3d", i, vetor[i]);
  getchar();
}
// ORDENACAO
void Bolha(int vetor[TF])
{
  int i;
  int tam;
  tam = TF - 1;
  while (tam > 1)
  {
    for (i = 0; i < tam; i++)
    {
      if (vetor[i] > vetor[i + 1])
      {
        int aux = vetor[i];
        vetor[i] = vetor[i + 1];
        vetor[i + 1] = aux;
      }
    }
    tam = tam - 1;
  }
}
void ordenaSelecao(int vetor[TF]) {
  int i, j, menor, posmenor;
    for(i=0;i<TF -1;i++) {
    menor=vetor[i];
    posmenor=i;
    for(j=i+1;j<TF;j++)
    if(vetor[j]<menor)
    {
      menor=vetor[j];
      posmenor=j;
    }
      vetor[posmenor]=vetor[i];
      vetor[i]=menor;
    }
}
void descrecente(int vetor[TF]) {
  int i, j, menor, posmenor;
    for(i=0;i<TF -1;i++) {
    menor=vetor[i];
    posmenor=i;
    for(j=i+1;j<TF;j++)
    if(vetor[j]>menor)
    {
      menor=vetor[j];
      posmenor=j;
    }
      vetor[posmenor]=vetor[i];
      vetor[i]=menor;
    }
}
// INSERCAO
void InsercaoDireta(int vetor[TF]){
  int aux, i, j, n, posi;
  if (vetor[0]>vetor[1])  {
    aux=vetor[0];
    vetor[0]=vetor[1];
    vetor[1]=aux;
  }
  for (n=2;n<TF;n++)  {
    aux=vetor[n];
    //aux é o elemento a ser reinserido de forma ordenada
    // n-1 é o tamanho do vetor que já está ordenado
    posi=buscaSequencial(vetor,n,aux);
    for(j=n ;j>posi ;j--)
      vetor[j]=vetor[j-1];
    vetor[posi]=aux;
  }  
}
void InsercaoBinaria(int vetor[TF]){
int aux, i, j, n, posi;
  if (vetor[0]>vetor[1])  {
    aux=vetor[0];
    vetor[0]=vetor[1];
    vetor[1]=aux;
  }
  for (n=2;n<TF;n++)  {
    aux=vetor[n];
    //aux é o elemento a ser reinserido de forma ordenada
    // n-1 é o tamanho do vetor que já está ordenado
    posi=buscaBinaria(vetor,n,aux);
    for(j=n ;j>posi ;j--)
      vetor[j]=vetor[j-1];
    vetor[posi]=aux;
  }  	
}

// BUSCAS

int buscaSequencial(int vetor[TF], int tl, int elem)   { // obrigatorio o vetor estar ORDENADO
  int i=0;
  while ((elem > vetor[i])&&(i<tl))
    i=i+1;
  
  return i; // achou na posição i OU encontrou a posicao ideal para inserir
}
int buscaBinaria(int vetor[TF],int tl, int elem)    { // obrigatorio o vetor estar ORDENADO
  int inicio, meio, fim;
  inicio=0;
  fim=tl-1;
  meio=(inicio+fim)/2;
  while((elem!=vetor[meio])&&(inicio<fim)) {
    if(elem>vetor[meio])
      inicio=meio+1;
    else
      fim=meio;
    meio=(inicio+fim)/2;
  }
  if (elem>vetor[meio])
    return(meio+1);
  else
    return(meio);
}

int buscaExaustiva (int vetor[TF], int elem)   { // vetor DESORdenado
  int i=0;
  while ((vetor[i] != elem)&&(i<TF))
    i=i+1;
  if ((i < TF) && (vetor[i] == elem)) 
    return i;           // achou na posição i 
  else return  -1; // não achou
}

int binariaRecursiva(int vetor[], int elem, int inicio, int fim) {
int meio;
  if (inicio > fim)
    return -1; //nao achou
  else {
    meio = (inicio+fim) / 2;
    if (elem == vetor[meio])
      return meio;
    else if (elem < vetor[meio])
      binariaRecursiva(vetor,elem,inicio ,meio-1);
    else binariaRecursiva (vetor,elem,meio+1,fim);
  }
}

int binariaRecursiva(int vetor[], int elem, int inicio, int fim)
{
  int meio;
  if (inicio > fim)
    return -1; // nao achou
  else
  {
    meio = (inicio + fim) / 2;
    if (elem == vetor[meio])
      return meio;
    else if (elem < vetor[meio])
      binariaRecursiva(vetor, elem, inicio, meio - 1);
    else
      binariaRecursiva(vetor, elem, meio + 1, fim);
  }
}
main()
{
  int tl = 0;
  int vetor[TF];
  bool ordenado = false;
  int opcao = 0, posicao = -1, elem;
  time_t tempoi, tempof;
  float diferenca;

  while (opcao != 12)
  {
    printf("\n1 - Cria o vetor de %d elementos", TF);
    printf("\n2 - Exibe o vetor gerado");
    printf("\n3 - ORDENA BOLHA - Ordena o vetor");
    printf("\n4 - ORDENA SELECAO - Ordena o vetor");
    printf("\n5 - ");
    printf("\n6 - ");
    printf("\n7 - Busca Exaustiva de um elemento no vetor desordenado");
    printf("\n8 - Busca Sequencial num vetor Ordenado");
    printf("\n9 - Busca Binaria num vetor Ordenado");
    printf("\n10 - Busca Binaria Recursiva num vetor Ordenado");
    printf("\n11 - Decrescente selecao");
    printf("\n12 - Sair");
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
      Bolha(vetor);
      tempof = time(NULL);
      diferenca = difftime(tempof, tempoi);
      printf("\n BOLHA - ordenou vetor e demorou %f num vetor de %d elementos", diferenca, TF);
      ordenado = true;
      break;
    case 4:
      tempoi = time(NULL); // obtem o tempo inicial para cronometrar
      ordenaSelecao(vetor);
      tempof = time(NULL);
      diferenca = difftime(tempof, tempoi);
      printf("\n SELECAO - ordenou vetor e demorou %f num vetor de %d elementos", diferenca, TF);
      ordenado = true;
      break;
    case 5:
      break;
    case 6:
      break;
    case 7:
      printf("\n Exaustiva. Entre com o valor a ser procurado: ");
      scanf("%d", &elem);
      // tempoi
      posicao = buscaExaustiva(vetor, elem);
      // tempof
      // calcular a diferenca
      if (posicao == -1)
        printf("\n NAO encontrou e demorou %f num vetor de %d elementos", diferenca, TF);
      else
        printf("\n Demorou %f no vetor de %d elementos e encontrou na posicao vetor[%d]=%d", diferenca, TF, posicao, vetor[posicao]);
      break;
    case 8:
      printf("\n SEQUENCIAL exige vetor ORDENADO!!! \n Entre com o valor a ser procurado: ");
      scanf("%d", &elem);
      if (ordenado)
      {
        tempoi = time(NULL);
        posicao = buscaSequencial(vetor, elem);
        tempof = time(NULL);
        diferenca = difftime(tempof, tempoi);
        if (posicao != -1)
          printf("\n Encontrou no vetor na posicao vetor[%d]=%d", posicao, vetor[posicao]);
        else
          printf("\n NAO encontrou e demorou %f num vetor de %d elementos", diferenca, TF);
      }
      else
        printf("Vetor NAO esta ordenado \n\n");
      break;
    case 9:
      printf("\n BINARIA exige vetor ORDENADO!!! \n Entre com o valor a sere procurado: ");
      scanf("%d", &elem);
      if (ordenado)
      {
        // obter o tempo inicial
        posicao = buscaBinaria(vetor, elem);
        // obter o tempo final
        // calcular a diferenca
        if (vetor[posicao] != elem)
          printf("\n NAO encontrou - posicao ideal para inserir %d ", posicao);
        else
          printf("\n Encontrou no vetor na posicao vetor[%d]=%d", posicao, vetor[posicao]);
      }
      else
        printf("Vetor NAO esta ordenado \n\n");
      break;
    case 10:
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
    case 11:
      tempoi = time(NULL); // obtem o tempo inicial para cronometrar
      descrecente(vetor);
      tempof = time(NULL);
      diferenca = difftime(tempof, tempoi);
      printf("\n DESCRECENTE SELECAO - ordenou vetor e demorou %f num vetor de %d elementos", diferenca, TF);
      ordenado = true;
      break;
    } // switch
  }   // while
} // main