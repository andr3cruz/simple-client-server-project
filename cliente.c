#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include <unistd.h>
#include <time.h>

#define FX "users.txt"

typedef struct{
	char nick[15];
	char pass[15];
    char sub1[100];
    int smsub1;
    char sub2[100];
    int smsub2;
    char sub3[100];
    int smsub3;
    int total_mensagem;
	int tipo;
	} user;

typedef struct{
    char username[15];
    char message[140];
    int like;
	} escrever;

typedef struct{
    char titulo[100];
    int mensagem;
    int likes;
    }topico;

topico maxi[400];
user max[400];
escrever mensagem[1000];
int n_users=0;
int n_mensagens=0;
int n_topicos=0;

//menus
void mostrar_login();
void mostrar_menu(int i);
void mostrar_topicos(int i);
void menu_publicar(int i);
void menu_estatistica(int i);
void gerir_subs(int i);
void erro();
//funções
int registo();
int compara_users();
int verificar(char temp[]);
int existe(char temp[]);
int publicar(int i, char topico[]);
void autenticacao();
void subscrever(int i);
void ver_topico(int i);
void fazer_like(int i, char topico[]);
//gestão user
void remover_sub(int i);
void mudar_password(int i);
//carregar ficheiros
int carrega_users();
int carrega_mensagens(char topico[]);
int carrega_topicos();
//estatistica
void total_utilizadores(int i);
void total_topicos(int i);
void total_likes(int i);


int main(){
        system("clear");
        mostrar_login();
}

void mostrar_login(){
                 int input;
                 carrega_users();
		 carrega_topicos();
                 printf("**Menu de registo**\n\n");
                 printf("1) Login / autenticação\n");
                 printf("2) Pedido de registo de novo utilizador\n");
                 printf("3) Sair\n");
		 scanf("%d", &input);
                 while(input){
                       switch(input){
		       case 1:{system("clear");
			       autenticacao();
			       break;}
	               case 2:{system("clear");
			       registo();
			       break;}
		       case 3:{system("clear");
			       exit(1);
			       break;}
	               default:{system("clear");
			        erro();
			        mostrar_login();
		                break;}
		       }
		 }
}

void mostrar_menu(int i){
                 int input;
		 carrega_users();
		 carrega_topicos();
                 printf("**Menu**\n\n");
		 printf("1) Topicos activos\n");
                 printf("2) Tópicos subscritos\n");
                 printf("3) Ver Estatísticas\n");
		 printf("4) Alterar palavra passe\n");
                 printf("5) Logout\n");
		 scanf("%d", &input);
		 while(input){
		       switch(input){
		       case 1:{system("clear");
			       mostrar_topicos(i);
			       break;}
		       case 2:{system("clear");
			       gerir_subs(i);
			       break;}
		       case 3:{system("clear");
			       menu_estatistica(i);
			       break;}
		       case 4:{system("clear");
			       mudar_password(i);
			       break;}
		       case 5:{system("clear");
			       mostrar_login();
			       break;}
		       default:{system("clear");
			        erro();
			        mostrar_menu(i);
				break;}
		       }
		 }
}
                  

void erro(){ 
                 printf("**Comando inválido**\n\n");
}

void autenticacao(){ 
                 char tempnick[15], temppass[15];
		 int i;
		 printf("***Autenticação***\n");
                 printf("\nNome de Utilizador:\n");
                 scanf("%s", tempnick);
                 printf("\nPalavra-Passe:\n");
                 scanf("%s", temppass);
		 for(i=0;i<n_users;i++){
		   if((strcmp(max[i].nick,tempnick)==0) && (strcmp(max[i].pass,temppass)==0) && (max[i].tipo == 2 || max[i].tipo == 3)){
			 system("clear");
			 mostrar_menu(i);
		       }
		 }
	system("clear");
	printf("*****ACESSO NÃO AUTORIZADO*****\n\n");
	mostrar_login();
}

int registo(){ 
            FILE *fx;
            char tempnick[15], temppass[15];
	    int i;
            printf("Escolha um nome de utilizador:\n(Limite 15 caracteres e apenas dígitos ou letras)\n");
            scanf("%s", tempnick);
	    if(verificar(tempnick) == 0){
	      system("clear");
	      printf("***NOME DE UTILIZADOR INVÁLIDO***\n\n");
	      mostrar_login();
	      return n_users;
	    }
            printf("\nEscolha uma palavra-passe:\n(Limite 15 caracteres e apenas dígitos ou letras)\n");
            scanf("%s", temppass);
	    if(verificar(temppass) == 0){
	      system("clear");
	      printf("***PALAVRA-PASSE INVÁLIDA***\n\n");
	      mostrar_login();
	      return n_users;
	    }
	    for(i=0;i<n_users;i++){
		     if(strcmp(max[i].nick,tempnick)==0){
		       system("clear");
		       printf("***USUÁRIO JÁ EXISTENTE***\n\n");
		       mostrar_login();
		       return n_users;
		     }
	    }
	      fx = fopen(FX,"a");
	      fprintf(fx,"%s;%s;;0;;0;;0;0;1\n",tempnick,temppass);
	      fclose(fx);
	      system("clear");
	      printf("***PEDIDO REGISTADO, AGUARDE APROVAÇÃO***\n\n");
	      mostrar_login();
	      return n_users;
}

int carrega_users(){ //carrega o ficheiro
	FILE *fx; char s[350],i,j;
	n_users=0;
	fx=fopen(FX,"r");
	while(fgets(s,350,fx)){
		for(i=0;s[i]!=';';i++) max[n_users].nick[i]=s[i];
		max[n_users].nick[i]='\0';
		i++;
		j=0;
		for(;s[i]!=';';i++) max[n_users].pass[j++]=s[i];
		max[n_users].pass[j]='\0';
		i++;
		j=0;
        for(;s[i]!=';';i++) max[n_users].sub1[j++]=s[i]; //carrega sub1
        max[n_users].sub1[j]='\0';
        i++;
        j=0;
        max[n_users].smsub1=atoi(&s[i]);
        i=i+2;
        for(;s[i]!=';';i++) max[n_users].sub2[j++]=s[i]; //carrega sub2
        max[n_users].sub2[j]='\0';
        i++;
        j=0;
        max[n_users].smsub2=atoi(&s[i]);
        i=i+2;
        for(;s[i]!=';';i++) max[n_users].sub3[j++]=s[i]; //carrega sub3
        max[n_users].sub3[j]='\0';
        i++;
        j=0;
        max[n_users].smsub3=atoi(&s[i]);
        i=i+2;
        max[n_users].total_mensagem=atoi(&s[i]);
        i=i+2;
		max[n_users].tipo=atoi(&s[i]);
		n_users++;
	}
	fclose(fx);
}

int carrega_mensagens(char topico[]){
    char tamanho[160];
    int j,k;
    n_mensagens = 0;
    chdir("topicos");
    FILE *verificar_fi;
    verificar_fi=fopen(topico,"r");
    while(fgets(tamanho,160,verificar_fi)){
		for(j=0;tamanho[j]!=';';j++) mensagem[n_mensagens].username[j]=tamanho[j];
		mensagem[n_mensagens].username[j]='\0';
		j++;
		k=0;
		for(;tamanho[j]!=';';j++) mensagem[n_mensagens].message[k++]=tamanho[j];
		mensagem[n_mensagens].message[k]='\0';
		j++;
		k=0;
		mensagem[n_mensagens].like=atoi(&tamanho[j]);
		n_mensagens++;
	}
	fclose(verificar_fi);
	chdir("..");
}

int carrega_topicos(){
FILE *hue; char s[120],i;
	n_topicos=0;
	hue=fopen("topicos.txt","r");
	while(fgets(s,120,hue)){
		for(i=0;s[i]!=';';i++) maxi[n_topicos].titulo[i]=s[i];
		maxi[n_topicos].titulo[i]='\0';
		i++;
        maxi[n_topicos].mensagem=atoi(&s[i]);
        i=i+2;
        maxi[n_topicos].likes=atoi(&s[i]);
		n_topicos++;
	}
	fclose(hue);
}

void mudar_password(int i){
                    char newpass[15];
                    int j;
                    printf("Nova Palavra-Passe:\n");
                    scanf("%s", newpass);
                    if(verificar(newpass)){
	               strcpy(max[i].pass,newpass);
		       FILE *fx;
		       fx=fopen(FX,"w");
                       for(j=0;j<n_users;j++){
		       fprintf(fx,"%s;%s;%s;%d;%s;%d;%s;%d;%d;%d\n",max[j].nick, max[j].pass, max[j].sub1, max[j].smsub1, max[j].sub2, max[j].smsub2, max[j].sub3, max[j].smsub3, max[j].total_mensagem, max[j].tipo);
		       }
		       fclose(fx);
		       system("clear");
		       printf("***Palavra-Passe alterada com sucesso***\n\n");
		       mostrar_menu(i);
		    }
		    system("clear");
		    printf("***Palavra-Passe inválida!***\n\n");
		    mostrar_menu(i);
}
				  
int verificar(char temp[]){
               int j, soma = 0;
               if(strlen(temp) > 15){
		   return 0;
		}
	       //conta todas as ocorrências em que o caracter é digito ou letra
		for(j=0; j<strlen(temp);j++){
		  if(isdigit(temp[j]) || isupper(temp[j]) || islower(temp[j])){
		    soma++;
		  }
		}
		return(soma == strlen(temp));
}

void mostrar_topicos(int i){
                    int input;
		    carrega_users();
		    carrega_topicos();
                    printf("***TÓPICOS***\n\n");
                    system("ls topicos");
                    printf("\n1) Subscrever tópico\n");
		    printf("2) Voltar ao menu\n");
                    scanf("%d", &input);
                    while(input){
                          switch(input){
			  case 1:{if((strlen(max[i].sub1) != 0) && (strlen(max[i].sub2) != 0) && (strlen(max[i].sub3) != 0))
			           {
				     system("clear");
		                     printf("Subscrições máximas atingidas\n\n");
		                     mostrar_topicos(i);
				     break;
		                   }
			          system("clear");
			          subscrever(i);
			          break;}
                          case 2:{system("clear");
			          mostrar_menu(i);
	                          break;}
			  default:{system("clear");
	                           erro();
		                   mostrar_topicos(i);
	                           break;}
			  }
		    }
}

void subscrever(int i){
                  char temp[100];
		  int j,msgs = 0;
		  carrega_users();
		  carrega_topicos();
		  printf("***TÓPICOS***\n\n");
		  system("ls topicos");
		  printf("\nIntroduza o nome do tópico que pretende subscrever\n");
		  scanf("%s", temp);
		  if(existe(temp)){
		    if((strcmp(max[i].sub1, temp) == 0) || (strcmp(max[i].sub2, temp) == 0) || (strcmp(max[i].sub3, temp) == 0)){
		      system("clear");
		      printf("Tópico já subscrito!\n\n");
		      mostrar_topicos(i);
		    }
		  carrega_mensagens(temp);
		  FILE *fx;
		  chdir("topicos");
		  fx=fopen(temp,"r");
		  for(j=0;j<n_mensagens;j++){
		    if((strcmp(mensagem[j].username, max[i].nick) == 0)) msgs++;
		  }
		  fclose(fx);
		  chdir("..");
		  if(strlen(max[i].sub1) == 0){
		    strcpy(max[i].sub1, temp);
		    max[i].smsub1 = msgs;
		  }
		    else if(strlen(max[i].sub2) == 0){
		      strcpy(max[i].sub2, temp);
		      max[i].smsub2 = msgs;
		    }
		      else if(strlen(max[i].sub3) == 0){
			strcpy(max[i].sub3, temp);
			max[i].smsub3 = msgs;
		      }
		  fx=fopen(FX,"w");
                  for(j=0;j<n_users;j++){
		      fprintf(fx,"%s;%s;%s;%d;%s;%d;%s;%d;%d;%d\n",max[j].nick, max[j].pass, max[j].sub1, max[j].smsub1, max[j].sub2, max[j].smsub2, max[j].sub3, max[j].smsub3, max[j].total_mensagem, max[j].tipo);
		  }
		  fclose(fx);
		  system("clear");
		  printf("Tópico subscrito com sucesso!\n\n");
		  mostrar_topicos(i);
		  }
		  system("clear");
		  printf("Tópico não existente!\n\n");
		  mostrar_topicos(i);
		       
}

int existe(char temp[]){
           chdir("topicos");
           FILE *verificar_fi;
           verificar_fi = fopen(temp, "r");
           if(verificar_fi == NULL){
	      chdir("..");
              return 0;
           }
	   chdir("..");
           return 1;
}


void gerir_subs(int i){
                int input;
		carrega_users();
		carrega_topicos();
		if((strlen(max[i].sub1) == 0) && (strlen(max[i].sub2) == 0) && (strlen(max[i].sub3) == 0)){
		   system("clear");
		   printf("Não existe nenhuma subscrição activa\n\n");
		   mostrar_menu(i);
		}
                printf("***Tópicos subscritos***\n\n");
                if(strlen(max[i].sub1) != 0) printf("%s\n", max[i].sub1);
                if(strlen(max[i].sub2) != 0) printf("%s\n", max[i].sub2);
                if(strlen(max[i].sub3) != 0) printf("%s\n", max[i].sub3);
                printf("\n1) Remover subscrição\n");
		printf("2) Ver tópico\n");
		printf("3) Publicar num tópico\n");
                printf("4) Voltar ao menu\n");
                scanf("%d", &input);
                while(input){
                      switch(input){
	              case 1:{system("clear");
		              remover_sub(i);
		              break;}
		      case 2:{system("clear");
			      ver_topico(i);
			      break;}
		      case 3:{system("clear");
			       menu_publicar(i);
			       break;}
                      case 4:{system("clear");
		              mostrar_menu(i);
	                      break;}
		      default:{system("clear");
	                       erro();
		               gerir_subs(i);
	                       break;}
		      }
		}
}

void remover_sub(int i){
                 int j;
                 char temp[100];
		 carrega_users();
		 carrega_topicos();
		 if((strlen(max[i].sub1) == 0) && (strlen(max[i].sub2) == 0) && (strlen(max[i].sub3) == 0)){
		   system("clear");
		   printf("Não existe nenhuma subscrição activa\n\n");
		   gerir_subs(i);
		 }
                 printf("***Tópicos subscritos***\n\n");
                 if(strlen(max[i].sub1) != 0) printf("%s\n", max[i].sub1);
                 if(strlen(max[i].sub2) != 0) printf("%s\n", max[i].sub2);
                 if(strlen(max[i].sub3) != 0) printf("%s\n", max[i].sub3);
                 printf("\nQue tópico pretende remover subscrição?\n");
                 scanf("%s", temp);
		 if((strcmp(max[i].sub1, temp) != 0) && (strcmp(max[i].sub2, temp) != 0) && (strcmp(max[i].sub3, temp) != 0)){
		   system("clear");
		   printf("Tópico não existente!\n\n");
		   gerir_subs(i);
		 }
                 if(strcmp(max[i].sub1, temp) == 0){
		   strcpy(max[i].sub1, "");
		   max[i].smsub1 = 0;
		 }
		   if(strcmp(max[i].sub2, temp) == 0){
		     strcpy(max[i].sub2, "");
		     max[i].smsub2 = 0;
		   }
		     if(strcmp(max[i].sub3, temp) == 0){
		       strcpy(max[i].sub3, "");
		       max[i].smsub3 = 0;
		     }
                 FILE *fx;
                 fx=fopen(FX,"w");
                 for(j=0;j<n_users;j++){
		     fprintf(fx,"%s;%s;%s;%d;%s;%d;%s;%d;%d;%d\n",max[j].nick, max[j].pass, max[j].sub1, max[j].smsub1, max[j].sub2, max[j].smsub2, max[j].sub3, max[j].smsub3, max[j].total_mensagem, max[j].tipo);
		 }
                 fclose(fx);
                 system("clear");
                 gerir_subs(i);
}

void menu_publicar(int i) {
                   char topico[100];
		   carrega_users();
		   carrega_topicos();
		   if((strlen(max[i].sub1) == 0) && (strlen(max[i].sub2) == 0) && (strlen(max[i].sub3) == 0)){
		   system("clear");
		   printf("Não existe nenhuma subscrição activa\n\n");
		   gerir_subs(i);
		   }
	           printf("***Tópicos subscritos***\n\n");
                   if(strlen(max[i].sub1) != 0){
		     printf("%s\n", max[i].sub1);
		   }
                   if(strlen(max[i].sub2) != 0){
		     printf("%s\n", max[i].sub2);
		   }
                   if(strlen(max[i].sub3) != 0){
		     printf("%s\n", max[i].sub3);
		   }
                   printf("\nEm que tópico pretende publicar\n");
	           scanf("%s", topico);
		   setbuf(stdin, NULL);
		   if(existe(topico) == 0){
		   system("clear");
		   printf("Tópico não existente!\n\n");
		   gerir_subs(i);
		   }
		   if((strcmp(max[i].sub1, topico) != 0) && (strcmp(max[i].sub2, topico) != 0) && (strcmp(max[i].sub3, topico) != 0)){
		     system("clear");
		     printf("Tópico não subscrito!\n\n");
		     gerir_subs(i);
		   }
		   publicar(i,topico);
}

int publicar(int i, char topico[]){
                   int j;
                   char mensagem[140];
		   carrega_users();
		   carrega_topicos();
		   system("clear");
		   printf("Mensagem:\n(Limite 140 caracteres)\n");
		   scanf("%[^\n]s", mensagem);
		   max[i].total_mensagem++;
		   if(strcmp(max[i].sub1, topico) == 0) max[i].smsub1++;
		   if(strcmp(max[i].sub2, topico) == 0) max[i].smsub2++;
                   if(strcmp(max[i].sub3, topico) == 0)  max[i].smsub3++;
		   for(j=0;j<n_topicos;j++){
		     if(strcmp(maxi[j].titulo, topico) == 0) maxi[j].mensagem++;
		   }
		   chdir("topicos");
		   FILE *fx;
		   fx=fopen(topico,"a");
		   fprintf(fx,"%s;%s;0\n",max[i].nick, mensagem);
		   fclose(fx);
		   chdir("..");
                   fx=fopen(FX,"w");
                   for(j=0;j<n_users;j++){
		     fprintf(fx,"%s;%s;%s;%d;%s;%d;%s;%d;%d;%d\n",max[j].nick, max[j].pass, max[j].sub1, max[j].smsub1, max[j].sub2, max[j].smsub2, max[j].sub3, max[j].smsub3, max[j].total_mensagem, max[j].tipo);
                   }
                   fclose(fx);
		   fx=fopen("topicos.txt","w");
		   for(j=0;j<n_topicos;j++){
		     fprintf(fx, "%s;%d;%d\n", maxi[j].titulo, maxi[j].mensagem, maxi[j].likes);
		   }
		   fclose(fx);
		   system("clear");
		   printf("Mensagem publicada com sucesso!\n\n");
		   mostrar_menu(i);
		   return 0;
}

void ver_topico( int i){
               char topico[100];
	       int input,j;
	       carrega_users();
	       carrega_topicos();
	       if((strlen(max[i].sub1) == 0) && (strlen(max[i].sub2) == 0) && (strlen(max[i].sub3) == 0)){
		   system("clear");
		   printf("Não existe nenhuma subscrição activa\n\n");
		   gerir_subs(i);
	       }
	       printf("***Tópicos subscritos***\n\n");
               if(strlen(max[i].sub1) != 0) printf("%s\n", max[i].sub1);
               if(strlen(max[i].sub2) != 0) printf("%s\n", max[i].sub2);
               if(strlen(max[i].sub3) != 0) printf("%s\n", max[i].sub3);
	       printf("\nIntroduza o nome do tópico que pretende abrir\n");
	       scanf("%s", topico);
	       if(existe(topico) == 0){
		   system("clear");
		   printf("Tópico não existente!\n\n");
		   gerir_subs(i);
		   }
	       if((strcmp(max[i].sub1, topico) != 0) && (strcmp(max[i].sub2, topico) != 0) && (strcmp(max[i].sub3, topico) != 0)){
		   system("clear");
		   printf("Tópico não subscrito!\n\n");
		   gerir_subs(i);
	       }
	       carrega_mensagens(topico);
	       system("clear");
	       for(j=n_mensagens -1;j>=0;j--) printf("%d - %s: %s\n    likes:%d\n\n",j, mensagem[j].username, mensagem[j].message, mensagem[j].like);
		  printf("\n1) Fazer like\n");
		  printf("2) Voltar atrás\n");
		  scanf("%d", &input);
                  while(input){
                      switch(input){
		      case 1:{system("clear");
			      fazer_like(i, topico);
			      break;}
	              case 2:{system("clear");
		              gerir_subs(i);
		              break;}
		      default:{system("clear");
	                       erro();
			       ver_topico(i);
	                       break;}
		      }
		  }
}

void fazer_like(int i, char topico[]){
                int j, msg,input;
		carrega_users();
		carrega_topicos();
                for(j=n_mensagens -1;j>=0;j--) printf("%d - %s: %s\n    likes:%d\n\n",j, mensagem[j].username, mensagem[j].message, mensagem[j].like);
		printf("Insira o número da mensagem\n");
		scanf("%d", &msg);
		system("clear");
		chdir("topicos");
		FILE *fx;
		fx=fopen(topico,"w");
		mensagem[msg].like++;
	        for(j=0;j <= n_mensagens -1;j++) fprintf(fx,"%s;%s;%d\n",mensagem[j].username, mensagem[j].message, mensagem[j].like);
		fclose(fx);
		chdir("..");
		fx=fopen("topicos.txt","w");
		for(j=0; j<n_topicos; j++){
		  if(strcmp(maxi[j].titulo, topico) == 0) maxi[j].likes++;
		}
		for(j=0;j<n_topicos;j++){
		    fprintf(fx, "%s;%d;%d\n", maxi[j].titulo, maxi[j].mensagem, maxi[j].likes);
		}
	        fclose(fx);
		for(j=n_mensagens -1;j>=0;j--) printf("%d - %s: %s\n    likes:%d\n\n",j, mensagem[j].username, mensagem[j].message, mensagem[j].like);
		printf("\n1) Fazer like\n");
		printf("2) Voltar atrás\n");
		scanf("%d", &input);
                while(input){
                      switch(input){
		      case 1:{system("clear");
			      fazer_like(i, topico);
			      break;}
	              case 2:{system("clear");
		              gerir_subs(i);
		              break;}
		      default:{system("clear");
	                       erro();
		               fazer_like(i, topico);
	                       break;}
		      }
		}
}

void menu_estatistica(int i){
                 int input;
                 carrega_users();
		 carrega_topicos();
                 printf("**Menu de estatistica**\n\n");
		 printf("1) Utilizadores e total mensagens\n");
		 printf("2) Tópicos e total mensagens\n");
		 printf("3) Total de likes por tópico\n");
		 printf("4) Voltar ao menu\n");
		 scanf("%d", &input);
		 while(input){
		   switch(input){
		   case 1:{system("clear");
		           total_utilizadores(i);
		           break;}
		   case 2:{system("clear");
			   total_topicos(i);
			   break;}
		   case 3:{system("clear");
		           total_likes(i);
			   break;}
		   case 4:{system("clear");
		           mostrar_menu(i);
			   break;}
		   default:{system("clear");
	                   erro();
			   menu_estatistica(i);
			   break;}
		   }
		 }
}
         
void total_utilizadores(int i){
    int j,input;
    carrega_users();
    carrega_topicos();
    printf("||==================||===============||\n");
    printf("||");
    printf(" **Utilizadores** || **Mensagens** ");
    printf("||\n");
    printf("||==================||===============||\n");
    for(j=0;j<n_users;j++){
        if(max[j].tipo != 1){
            printf("||");
            printf(" %16s ",max[j].nick);
            printf("||");
	    printf("%15d", max[j].total_mensagem);
	    printf("||\n");
	}
    }
    printf("||==================||===============||\n");
    printf("\n1) Voltar atrás\n");
    scanf("%d", &input);
    while(input){
          switch(input){
	         case 1:{system("clear");
		         menu_estatistica(i);
		         break;}
		 default:{system("clear");
	                  erro();
		          total_utilizadores(i);
	                  break;}
	  }
    }
}

void total_topicos(int i){
    int aux,j,k,input;
    char copia[100];
    carrega_users();
    carrega_topicos();
    for(k=n_topicos;k>=0;k--){
        for(j=0;j<k;j++){
            if((maxi[j].mensagem) < (maxi[j+1].mensagem)){
                strcpy(copia, maxi[j].titulo);
                aux = maxi[j].mensagem;
                strcpy(maxi[j].titulo,maxi[j+1].titulo);
                maxi[j].mensagem = maxi[j+1].mensagem;
                maxi[j+1].mensagem = aux;
                strcpy(maxi[j+1].titulo,copia);
            }
        }
    }
    printf(" ***Topicos e número de mensagens***\n\n");
    printf("||==================||\n");
    for(int i=0;i<n_topicos;i++){
        printf("||");
        printf("%d mensagens    %s",maxi[i].mensagem, maxi[i].titulo);
        printf("||\n");
    }
    printf("||==================||\n");
    printf("\n1)Voltar\n\n");
    scanf("%d",&input);
    while(input){
        switch(input){
	case 1:{system("clear");
	        menu_estatistica(i);
	        break;}
        default:{system("clear");
	         erro();
		 total_topicos(i);
	         break;}
	}
    }
}

void total_likes(int i){
                int input;
                printf(" ***Topicos e número de likes***\n\n");
		printf("||==================||\n");
                for(int i=0;i<n_topicos;i++){
                printf("||");
                printf("%d likes        %s",maxi[i].likes, maxi[i].titulo);
                printf("||\n");
		}
                printf("||==================||\n");
                printf("\n1)Voltar\n\n");
                scanf("%d",&input);
                while(input){
                      switch(input){
	              case 1:{system("clear");
	                      menu_estatistica(i);
	                      break;}
                      default:{system("clear");
	                       erro();
		               total_likes(i);
	                       break;}
		      }
		}
}
		

 
     
