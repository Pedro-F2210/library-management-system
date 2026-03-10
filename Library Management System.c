#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    char titulo[100], autor[80];
    int ano, ID;
} livro;

livro criarlivro() {
    livro liv;

    getchar();
    printf("Digite o Titulo: ");
     scanf("%[^\n]", liv.titulo);
    getchar();
    printf("Digite o nome do Autor: ");
     scanf("%[^\n]", liv.autor);
    printf("Digite o ano de publicacao: ");
     scanf("%d", &liv.ano);
	printf("Digite o ID do livro: ");
	 scanf("%d",&liv.ID);
    return liv;
}

void listarlivros(livro biblioteca[], int qt) {
    for (int i = 0; i < qt; i++) {
        printf("\nLivro %d\n", i + 1);
        printf("Titulo: %s\n", biblioteca[i].titulo);
        printf("Autor: %s\n", biblioteca[i].autor);
        printf("Ano: %d\n", biblioteca[i].ano);
        printf("ID: %d\n", biblioteca[i].ID);
    }
}

void buscarlivros(livro biblioteca[], int qt, int busca) {
	int enc;
	printf("Introduza o ID do livro desejado: ");
	 scanf("%d",&busca);
     for (int i = 0; i < qt; i++) {
      	if(busca == biblioteca[i].ID){
      	  printf("\nLivro encontrado: ");
          printf("\nLivro %d\n", i + 1);
          printf("Titulo: %s\n", biblioteca[i].titulo);
          printf("Autor: %s\n", biblioteca[i].autor);
          printf("Ano: %d\n", biblioteca[i].ano);
          printf("ID: %d\n", biblioteca[i].ID);
          enc=1;
          break;
        } 
     }
     if(enc==0) {
     	printf("O Livro nao foi encontrado!\n");
	 } 
}

void atualizarlivro(livro biblioteca[], int qt) {
	int enc, busca, alt, an;
	char nT[100], nA[80];
	printf("Introduza o ID do livro a atualizar: ");
	 scanf("%d",&busca);
     for (int i = 0; i < qt; i++) {
      	if(busca == biblioteca[i].ID){
      	   getchar();
      	  printf("1 - Alterar Titulo\n"); 
      	  printf("2 - Alterar Autor\n"); 
      	  printf("3 - Alterar Ano\n"); 
      	  printf("4 - Alterar Tudo\n"); 
      	  printf("0 - Cancelar\n"); 
      	   scanf("%d",&alt);
      	   getchar();
      	   switch (alt) {
      	   	 case 0:
      	   	 	printf("Cancelando...\n");
      	   	 	break;
      	   	 case 1:
      	   	 	printf("Titulo anterior: %s\n",biblioteca[i].titulo);
      	   	 	printf("Introduza o novo Titulo: ");
      	   	 	 scanf("%[^\n]",nT);
      	   	 	 strcpy(biblioteca[i].titulo,nT);
      	   	 	 break;
      	   	 case 2: 	 
      	   	 	printf("Autor anterior: %s\n",biblioteca[i].autor);
      	   	 	printf("Introduza o novo Autor: ");
      	   	 	 scanf("%[^\n]",nA);
      	   	 	 strcpy(biblioteca[i].autor,nA); 
      	   	 	 break;
      	   	 case 3:	 
      	   	 	printf("Ano Anterior: %d\n",biblioteca[i].ano);
			    printf("Introduza um novo ano: ");
				 scanf("%d",&an);  
				 biblioteca[i].ano=an;
				 break;
			 case 4:
			 	getchar();
			   	printf("Titulo anterior: %s\n",biblioteca[i].titulo);
      	   	 	printf("Introduza o novo Titulo: ");
      	   	 	 scanf("%[^\n]",nT);
      	   	 	 strcpy(biblioteca[i].titulo,nT); 
      	   	 	getchar(); 
      	   	 	printf("\nAutor anterior: %s\n",biblioteca[i].autor);
      	   	 	printf("Introduza o novo Autor: ");
      	   	 	 scanf("%[^\n]",nA);
      	   	 	 strcpy(biblioteca[i].autor,nA);  
      	   	 	printf("\nAno Anterior: %d\n",biblioteca[i].ano);
			    printf("Introduza um novo ano: ");
				 scanf("%d",&an);   
				 biblioteca[i].ano=an;
				 break;
			 default:
			  printf("Opcao Invalida!");
			  break;	  	
			 }
          enc=1;
          }  
     }
	 if(enc==0) {
       	printf("O Livro nao foi encontrado!\n");
 	 }
}

void removerlivro(livro biblioteca[], int *qt) {
    int id, i, pos = -1;
    printf("Introduza o ID do livro que deseja remover: ");
    scanf("%d", &id);
    for(i = 0; i < *qt; i++) {  
        if(biblioteca[i].ID == id) {
            pos = i;
            break;
        }
    }
    if(pos == -1) {
        printf("Livro nao encontrado.\n");
        return;
    }
    for(i = pos; i < *qt - 1; i++) {
        biblioteca[i] = biblioteca[i + 1]; 
    }
    (*qt)--;// 4️⃣ Diminuir quantidade
    printf("Livro removido com sucesso!\n");
}

void guardarLivros(livro biblioteca[], int qt) {
    FILE *f = fopen("biblioteca.dat", "wb"); 
    if (f == NULL) {
        printf("Erro ao criar o ficheiro!\n");
        return;
    }

    fwrite(&qt, sizeof(int), 1, f);                 
    fwrite(biblioteca, sizeof(livro), qt, f);     

    fclose(f);
}

void carregarLivros(livro biblioteca[], int *qt) {
    FILE *f = fopen("biblioteca.dat", "rb");  

    if (f == NULL) {
        *qt = 0;  
        return;
    }

    fread(qt, sizeof(int), 1, f);                    
    fread(biblioteca, sizeof(livro), *qt, f);        

    fclose(f);
}

int main() {
    system("color f0");
    livro biblioteca[MAX];   
    int qt = 0, alt, an, enc=0, nID;
    int esc, esc2, busca, x, aux, i=0, id, pos;
    char nT[100], nA[80];
    carregarLivros(biblioteca, &qt);
    do {
        printf("\n==== SISTEMA DE BIBLIOTECA ====\n");
        printf("\n1 - Gerenciar Livros\n");
        printf("0 - Sair\n");
        scanf("%d", &esc);

        switch (esc) {

        case 1:
        	system("cls");
        	printf("\n==== GERENCIAR LIVROS ====\n");
            printf("\n1 - Cadastrar Livro\n");
            printf("2 - Listar Livros\n");
            printf("3 - Buscar Livro\n");
            printf("4 - Atualizar Livro\n");
            printf("5 - Remover Livro\n");
            printf("0 - Voltar\n");
            scanf("%d", &esc2);
			
            switch (esc2) {

            case 1:
            	if(qt < MAX){
       			    biblioteca[qt] = criarlivro(); 
				    int IDexiste;
					do {
    					IDexiste = 0;
    					for (int j = 0; j < qt; j++) {
        					if (biblioteca[qt].ID == biblioteca[j].ID) {
           						 IDexiste = 1;
								 printf("ID ja existe! Digite outro: ");
            					 scanf("%d", &biblioteca[qt].ID);
            					 break;
        					}
    					}
				} while (IDexiste);
       			 qt++;        
			    } else {
        			printf("Biblioteca cheia!\n");
    			}
    			system("cls");
    			break;

            case 2:
            	printf("\n==== LISTA DE LIVROS ====\n");
                listarlivros(biblioteca, qt);  
                break;
                       
            case 3:
            	printf("\n==== BUSCA DE LIVROS ====\n");
            	buscarlivros(biblioteca, qt, busca);
            	break;
            	
            case 4: 																																																																																																																																																																																																																																																																																																																																																																																																																																																																									
            	printf("\n==== ATUALIZACAO DE LIVROS ====\n");
        		atualizarlivro(biblioteca, qt);
        	    break;
        	    
        	case 5:
        		removerlivro(biblioteca, &qt);
			    break;
				    
        	default:
			    printf("Opcao Invalida!");    
        	    break;	
        	}
        	break;
        } 
    } while (esc != 0);
    guardarLivros(biblioteca, qt);
    printf("Encerrando o Programa...");
    return 0;

}
