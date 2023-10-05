#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//criando a struct para variável de tipo produto 
struct produto{
  char nome[30], codigo[15], preco[10], quant[5], marca[30];
};

struct produto *dados; //criando o ponteiro
char maisum = 's';
int cont = 0, opcao; 

int mostrar_menu(void){
  printf("   ---------------------------------------------------------------------\n\n");
  printf("MENU\n\n");
  printf("1 - Incluir\n2 - Consultar\n3 - Alterar\n4 - Imprimir\n5 - Excluir\n\n");
  printf("Selecione o número correspondente a opção.\n");
  scanf("%d", &opcao);
  while(opcao < 1 || opcao > 5){
    printf("NÚMERO INVÁLIDO. Tente novamento digitando os números correspondentes às opções do menu. (1 a 5).\n");
    scanf("%d", &opcao);
    break; //caso o user digite algo diferente de um número, sem o brek tava dando um loop infinito
  }
  return opcao;
}

char continuar_operando(void){
  printf("\nDeseja fazer mais alguma operação?(s/n)\n");
  getchar(); //consome o caractere de quebra de linha pendente
  scanf(" %c", &maisum); //sem o getchar a funçao scanf anterior deixou um caractere de quebra de linha pendente no buffer de entrada
  system("clear"); 
  return maisum;
}

void imprimir(void){
  if(cont > 0){ 
    printf("\nA lista dos produtos registrados no estoque da padaria L.P. 1 foram:\n\n");
    printf("----------------------------------------------------------------------------------\n");
    printf("| %-4s | %-15s | %-13s | %-8s | %-8s | %-4s |\n", "  ", "Nome", "Marca", "Código", "Preço", "Quantidade");
    printf("----------------------------------------------------------------------------------\n");
  
    for(int ind = 0; ind < cont; ind++){
      //se o item for apagado, a impressão (estética) muda, só para ficar diferente no arquivo gerado e na interface de interação
      //no arquivo, cada item do produto deve apresentar a string: "item excluído pelo usuário"
      //na interface, por ser em modelo de tabela, só o primeiro item (nome) apresenta a string e o resto tem um e spaço em branco
      
      if((strcmp(dados[ind].nome, "Item excluído pelo usuário.") == 0)){ 
        printf("| %-4d | %-15s |\n", ind + 1, dados[ind].nome); 
      }
        
      else{
        printf("| %-4d | %-15s | %-13s | %-8s | %-8s | %-4s |\n", ind + 1, dados[ind].nome, dados[ind].marca, dados[ind].codigo, dados[ind].preco, dados[ind].quant); 
      }  
      printf("--------------------------------------------------------------------------------\n");
    }
    printf("----------------------------------------------------------------------------------\n");
    
    //% -Xs: especificadores de formato p definir uma largura fixa de X caracteres 
  }
    
  else{
   printf("\nNenhum produto foi registrado ainda. Para registrar o primeiro, volte ao menu e selecione a opção incluir, de número 1.\n");
  }
} 

void incluir(void){
   printf("\nApós checar os produtos já registrados na padaria na tabela abaixo, insira: o nome, a marca, o código, o preço e a quantidade do produto.\n\n");
   if(cont > 1){ 
     printf("Segue a lista:\n");
  imprimir();//imprimindo antes o que já tem para evitar repetição
   }
   printf("\nLembrete: você não precisa digitar acentos gráficos como: ` ou ´ ou ~ ou ^ ou ç.\n\n");
   while(maisum == 's' || maisum == 'S'){
    printf("Nome: ");
    scanf(" %[^\n]", dados[cont].nome); 
    
    for(int m = 0; m < strlen(dados[cont].nome); m++){ 
      dados[cont].nome[m] = toupper(dados[cont].nome[m]); 
    }
     
    printf("Marca: ");
    scanf(" %[^\n]", dados[cont].marca); 
    for(int n = 0; n < strlen(dados[cont].marca); n++){ 
      dados[cont].marca[n] = toupper(dados[cont].marca[n]); 
    }
      
    printf("Código: ");
    scanf("%s", dados[cont].codigo); 
      
    printf("Preço: ");
    scanf("%s", dados[cont].preco); 
      
    printf("Quantidade: ");
    scanf("%s", dados[cont].quant); 
      
    cont++; 
    
    
    break;
  }   
} 

void novo_prod(void){ //o produto que a pessoa digitou não foi identificado no banco e a função ver se a pessoa quer adicionar
  char novo;
  printf("\nInfelizmente, esse produto não se encontra no banco de registros da padaria. Deseja inseri-lo no estoque? (s/n)\n");
  getchar(); 
  scanf(" %c", &novo);
  if(novo == 's' || novo == 'S'){ 
    incluir();
  }
  else{
    printf("\nFim da operação.\n");
  }
}

int consultar(){
  char retorno, qual_prod[30] = {};
  int i, index = 0, diferentes = 0;
  if(cont > 0){
    printf("\nQual produto você deseja consultar? Digite seu nome para que os dados do mesmo sejam mostrados.\n");
    printf("Você não precisa digitar acentos gráficos como: ` ou ´ ou ~ ou ^ ou ç.\n");
    scanf(" %[^\n]", qual_prod);
    for(int p = 0; p < strlen(qual_prod); p++){
      qual_prod[p] = toupper(qual_prod[p]); 
    }
    for(i = 0; i < cont; i++){
      if(strcmp(qual_prod, dados[i].nome) == 0){ 
        index = i; 
        retorno = 'v';
        printf("\nOs dados do(a) %s são:\n", qual_prod);
        printf("Nome: %s\n", dados[i].nome);
        printf("Marca: %s\n", dados[i].marca);
        printf("Código: %s\n", dados[i].codigo);
        printf("Preço: %s\n", dados[i].preco);
        printf("Quantidade: %s\n", dados[i].quant);
      }
      else{
        diferentes++;
      }
    }
    if(diferentes == cont){ //todos estão diferentes
       retorno = 'f';
       novo_prod();
    }
  }
  else{
    printf("\nNenhum produto foi registrado ainda. Para registrar o primeiro, volte ao menu e selecione a opção incluir, de número 1.\n");
  }
  switch(retorno){
    case 'v':
      return index; //o índice do registro em questão para que não se perca na função alterar
      break;
    case 'f':
      return -1; //função alterar sabe que o prod n existe 
      break;
    default:
      return 0;
  }
}


void dados_alterados(int p_alteracao, int p_existe){
  printf("Lembrete: você não precisa digitar acentos gráficos como: ` ou ´ ou ~ ou ^ ou ç.\n");
  switch(p_alteracao){
    case 1:
      printf("\n\nInsira o novo nome:\n");
      scanf(" %[^\n]s", dados[p_existe].nome); //existe = índice não é perdido e o nome certo é alterado 
      for(int r = 0; r < strlen(dados[p_existe].nome); r++){
      dados[p_existe].nome[r] = toupper(dados[p_existe].nome[r]); //deixando em letra maiúscula 
      }
      break;
    case 2:
      printf("\nInsira a nova marca:\n");
      scanf(" %[^\n]s", dados[p_existe].marca); //existe = índice não é perdido e a marca certa é alterada 
      for(int s = 0; s < strlen(dados[p_existe].marca); s++){ 
      dados[p_existe].marca[s] = toupper(dados[p_existe].marca[s]); //deixando em letra maiúscula 
      }
      break;
    case 3:
      printf("\nInsira o novo código:\n");
      scanf("%s", dados[p_existe].codigo); 
      break;
    case 4:
      printf("\nInsira o novo preço:\n");
      scanf("%s", dados[p_existe].preco); 
      break;
    case 5:
      printf("\nInsira a nova quantidade:\n");
      scanf("%s", dados[p_existe].quant); 
      break;
  }
}  

void alterar(void){
  int existe = 0, alteracao;
  
  printf("\nPara alterar algum produto do banco de registros da padaria, consulte-o primeiro.\n");
  existe = consultar(); 
  
  if(existe != -1){ //o produto existe, e a variável carrega o índice do registro, que é diferente de -1
    printf("\nQual dado você deseja alterar?\n");
    printf("1 - Nome\n2 - Marca\n3 - Código\n4 - Preço\n5 - Quantidade\n\n");
    printf("Selecione o número correspondente a opção.\n");
    scanf("%d", &alteracao);
    dados_alterados(alteracao, existe); 
  }
} 

void excluir(void){
  char exclusao_prod[30];
  int k, nao_ta = 0;
  
  if(cont > 0){
    printf("\nQual dos produtos você deseja excluir?\n");
    printf("Você não precisa digitar acentos gráficos como: ` ou ´ ou ~ ou ^ ou ç.\n");
    scanf(" %[^\n]", exclusao_prod);

    for(int q = 0; q < strlen(exclusao_prod); q++){
      exclusao_prod[q] = toupper(exclusao_prod[q]); //deixando em letra maiúscula
    }
    
    for(k = 0; k < cont; k++){ 
      if(strcmp(exclusao_prod, dados[k].nome) == 0){ //identificou lá no estoque
        strcpy(dados[k].nome, "Item excluído pelo usuário.");
        strcpy(dados[k].marca, "0");
        strcpy(dados[k].codigo, "0");
        strcpy(dados[k].preco, "0");
        strcpy(dados[k].quant, "0");
      }
      else{
        nao_ta++;
      }
    }
    if(nao_ta == cont){ //o produto não foi identificado no banco
      novo_prod();
    }
  }
  else{
    printf("\nNenhum produto foi registrado ainda. Para registrar o primeiro, volte ao menu e selecione a opção incluir, de número 1.\n");
  }
} 

int main(void) {
  dados = (struct produto *)malloc(sizeof(struct produto)); //alocando memoria p a struct

    FILE *arquivo;
    arquivo = fopen("Registros.txt", "r");
  
    if(arquivo != NULL){ 
      fscanf(arquivo, "%d\n", &cont);
      dados = (struct produto *)realloc(dados, (cont + 1) * sizeof(struct produto)); //realocação de espaço na memória p qnd o arquivo for lido, incrementando o valor do contador
      for(int l = 0; l < cont; l++){
        fscanf(arquivo, " %[^,], %[^,], %[^,], %[^,], %[^\n]", dados[l].nome, dados[l].marca, dados[l].codigo, dados[l].preco, dados[l].quant); 
      }  
      fclose(arquivo);
    }
      
   else{
    printf("Não foi possível ler o arquivo.\n");
   }
   
  printf("            ------------------------------------------------\n");
  printf("            ---------Bem-vindo(a) à Padaria L.P. 1!!!!------\n");
  printf("            ------------------------------------------------\n\n");
  printf("Aqui você encontra o menu para registro de novos produtos, navegue pelas opções de incluir, consultar, alterar, imprimir e excluir. Após executar o que deseja, verifique o arquivo ""Registros.txt"", que contém a quantidade de produtos registrados e os dados dos mesmos. O arquivo também poderá ser recarregado quando você voltar nesta página se quiser fazer qualquer tipo de edição nos registros.\n\n");
  
  while(maisum == 's' || maisum == 'S'){
    mostrar_menu(); 
    system("clear"); 
    
    switch(opcao){
      case 1:
        incluir();
        dados = (struct produto *)realloc(dados, (cont + 1) * sizeof(struct produto)); //realocação de espaço na memória p qnd um produto for adicionado, incrementando o valor do contador
        break;
      case 2:
        consultar();
        dados = (struct produto *)realloc(dados, (cont + 1) * sizeof(struct produto)); //chama a função incluir 
        break;
      case 3:
        alterar();
        break;
      case 4:
        imprimir();
        break;
      case 5:
        excluir();
        dados = (struct produto *)realloc(dados, (cont + 1) * sizeof(struct produto)); //chama a função incluir 
        break;
    }
    
  continuar_operando(); 
    if(maisum == 'n' || maisum == 'N'){
      
      arquivo = fopen("Registros.txt", "w");
      //gravando dados no arquivo
      if(arquivo == NULL){
        printf("Erro, nao foi possivel abrir o arquivo.\n");
      }
        
      else{
        fprintf(arquivo, "%d\n", cont); 
        for(int j = 0; j < cont; j++){ 
          fprintf(arquivo, "%s, %s, %s, %s, %s\n", dados[j].nome, dados[j].marca, dados[j].codigo, dados[j].preco, dados[j].quant); 
        }  
      }
      fclose(arquivo);
      printf("\nOk. Fim da operação.\nUm arquivo, chamado de 'Registros.txt', com os registros da padaria foi gerado.");
     
    }
  }
  return 0;
}
