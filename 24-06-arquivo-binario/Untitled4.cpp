#include<string.h>
#include<stdio.h>
#include<conio.h>
#include<iostream>

//TRABALHO PARA 08/JULHO

struct conta{
 int num_conta;
 char tipo_conta;
 char nome[30];
 float limite;
 float saldo;
};

//===============================================================
conta leCliente() { // leitura de um único cliente
 conta Cliente;
 printf("\nEntre com numero da conta:");
 scanf("%d",&Cliente.num_conta);
 printf("\nEntre com tipo da conta (E/C):");
 Cliente.tipo_conta=toupper(getche());
 printf("\nEntre com nome:");
 gets(Cliente.nome);gets(Cliente.nome);
 printf("\nEntre com limite:");
 scanf("%f",&Cliente.limite);
 printf("\nEntre com saldo:");
 scanf("%f",&Cliente.saldo);
 return (Cliente);
}

void exibe(conta Cliente) { // exibe um único cliente
 printf("\n---------------------\n");
 printf("Conta: %d\n",Cliente.num_conta);
 if (Cliente.tipo_conta=='E')
 printf("Tipo: Especial \n");
 else printf("Tipo: Comum \n");
 printf("Nome: %s \n",Cliente.nome);
 printf("Limite: %.2f\n",Cliente.limite);
 printf("Saldo: %.2f\n",Cliente.saldo);
 printf("-----------------------\n");
}

void lerSalvar() {
	conta Cliente;
	char opcao='S';//deseja continuar
	FILE *arqNovo; // ponteiro para a estrutura predefinida FILE
	 arqNovo = fopen("Clientes.bin","wb");//arquivo novo p/gravação apenas
	 while (opcao=='S')
	 {
		 Cliente = leCliente();
		 fwrite(&Cliente,sizeof(conta),1,arqNovo);
		 strset(Cliente.nome,' ');
		
		 printf("deseja continuar (s/n)?");
		 opcao=toupper(getche());
	 }
	 fclose(arqNovo);
}

void exibeCadastrados(conta Cliente) {
	FILE *arqNovo;
	arqNovo = fopen("Clientes.bin","rb"); // leitura dos clientes cadastrados
	 fread(&Cliente, sizeof(conta), 1, arqNovo);
	 // feof retorna diferente de zero se fim
	 // feof retorna zero se não for detectado fim
	 while (!feof(arqNovo))
	 {
	 //exibe o registro lido
	 exibe(Cliente);
	 fread(&Cliente, sizeof(conta), 1, arqNovo);
	 }
	 fclose (arqNovo); 
}

void buscarCliente() {
	conta Cliente;
	 FILE *arqNovo; // ponteiro para a estrutura predefinida FILE
	 arqNovo = fopen("Clientes.bin","r+b");//abre ja existente leitura/gravaçao
	 if (arqNovo!= NULL) { // verifica se o arquivo existe e foi localizado
	 // exibe todos os registros do arquivo
	 fread(&Cliente, sizeof(conta), 1, arqNovo);
	 while (!feof(arqNovo)) {
	 	//exibe o registro lido
		 exibe(Cliente);
		 fread(&Cliente, sizeof(conta), 1, arqNovo);
	 }
	 //.....consulta uma conta
	 int num;
	 printf("\nEntre com o numero da conta a ser procurada: ");
	 scanf("%d",&num);
	
	 fseek(arqNovo,0,SEEK_SET); //posiciona o cursor no inicio do arquivo
	 fread(&Cliente, sizeof(conta),1,arqNovo);
	 int posicao = 0;
	
	 while ((!feof(arqNovo))&&(num != Cliente.num_conta)) {
		 fread(&Cliente, sizeof(conta), 1, arqNovo);
		 posicao++;
	 }
	 if (num == Cliente.num_conta) {
		 printf("encontrou na posicao: %d",posicao);
		 fseek(arqNovo, posicao*sizeof(conta),SEEK_SET);
		 fread(&Cliente, sizeof(conta),1,arqNovo);
		 exibe(Cliente);
	 } else printf("\n Conta inexistente");
	 	fclose(arqNovo);
	 }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// faz leitura de cliente (C comum ou E Especial) e gravva num novo arquivo Clientes.bin
// faz a leitura dos clientes cadastrados e exibe na tela
main(){
 conta Cliente;
 
 int op = 0;
 do {
 	printf("\n=== FAÇA UM MENU NO PROGRAMA PRINCIPAL CONTENDO:  ===");
 	printf("\n1 - Ler um cliente e grava-lo no arquivo");
 	printf("\n2 - Exibir os clientes cadastrados");
 	printf("\n3 - Buscar cliente ao fornecer o numero da conta");
 	printf("\n4 - Exibir os clientes com conta comum");
 	printf("\n5 - Exibir os clientes com conta especial");
 	printf("\n6 - Fazer retirada para um determinado cliente ao fornecer o número da conta");
 	printf("\n7 – Fazer depósito para um determinado cliente ao fornecer o número da conta ");
 	printf("\n8 - Totalizar todos os saldos das contas exibindo para cada cliente o nro.conta, o nome cliente e o saldo");
 	printf("\n9 - Sair");
 	printf("\nOpcao desejada: ");
 	scanf("%d", &op);

 	switch (op) {
 		case 1:
 			lerSalvar();
 			break;
 		case 2:
 			exibeCadastrados(Cliente);
 			break;
 		case 3:
 			buscarCliente();
 			break;
 		default:
 			printf("\nOpcao invalido...\n");
 			break;
	 }
 } while (op != 9);
 
 
 system("PAUSE");
} 

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////










