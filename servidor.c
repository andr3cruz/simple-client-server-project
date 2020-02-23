#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<unistd.h>
#include"colors.h" //biblioteca implementada a parte (direitos do autor no ficheiro colors.h)

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
    char titulo[100];
    int mensagem;
    int likes;
    }topico;

topico maxi[400];
user max[400];
int n_mensagem=0;
int n_users=0;
char enter = 0;
int alerta=0;

void mostra_login();
void erro(int tecla);
void alert();
void login();
void mostra_menu();
int carrega_user();
int carrega_topicos();
// topico
int criar_topico();
void gerir_topicos();
void mostra_topicos();
void mostra_menu_topicos();
void voltar_menu();
int remover_topicos();
// gerir utilizadores
void mostrar_utilizadores();
void mostrar_menu_utilizadores();
void gerir_utilizadores();
int mudar_tipo();
void mostra_aceitar_users();
void menu_aceitar_users();
void aceitar_users();
int aceitar_users_aceite();
int aceitar_users_remove();
int apagar_user();
// estatistica
void menu_estatistica();
void mostrar_menu_estatistica();
void quantidade_topicos();
void quantidade_topicos_mais_topicos();
void menu_quantidade_topicos();
void menu_quantidade_topicos_mais_topicos();
void switch_analisar_utilizador();
void analisar_utilizador();
void menu_analisar_utilizador();
void quantidade_mensagens();
void analisar_topico();
void menu_quantidade_mensagens();
void menu_topicos_mais_utilizados();
void topicos_mais_utilizados();
void mostra_topicos_mais_utlizados();
int ordenar_funcoes();
// bonitinho
void prints();


int main(){
	system("clear");
    prints();
	int tecla;
	carrega_user();
    carrega_topicos();
	mostra_login();
	scanf("%d",&tecla);
	while(tecla){
		switch(tecla){
			case 1:{login();break;}
			case 2:exit(1);
			default:{erro(tecla);}
		}
        mostra_login();
        scanf("%d",&tecla);
	}
	return 0;
}
void mostra_login(){ //1ºmenu
    foreground(CYAN);
	printf("Server\n**Menu de registo***\n\n");
    foreground(NORMAL_COLOR);
	printf("1) Autenticação/ Login\n");
	printf("2) Sair/ Exit\n");
}
void erro(int tecla){ //erro
    foreground(RED);
    system("clear");
	printf("\n***Comando %d inválido***\n\n\a",tecla);
    printf("Prima enter para continuar\n");
    while(enter != '\r' && enter != '\n'){
        enter = getchar();
        scanf("%*c");
    }
        enter=0;
        system("clear");
        foreground(NORMAL_COLOR);
}
// login
void login(){ //login
	char nick1[15],pass1[15];
	int i;
    system("clear");
    foreground(CYAN);
	printf("Server\n***login***\n\n");
    foreground(NORMAL_COLOR);
	printf("user:\n");
	scanf("%s", nick1);
	printf("pass:\n");
	scanf("%s", pass1);
	for(i=0;i<n_users;i++){
		if(strcmp(max[i].nick,nick1)==0){
            if(strcmp(max[i].pass,pass1)==0){
                if(max[i].tipo == 3){
                    alert();
                    if(alerta > 0){
                        system("clear");
                        foreground(CYAN);
                        printf("Server\n***Alerta***\n\n");
                        foreground(NORMAL_COLOR);
                        printf("Tem pedidos para aceitar\n\n\a");
                        foreground(RED);
                        printf("Prima enter para continuar\n");
                        foreground(NORMAL_COLOR);
                        while(enter != '\r' && enter != '\n'){
                            enter = getchar();
                            scanf("%*c");
                        }
                        enter=0;
                        system("clear");
                    }
                    voltar_menu();
                }
            }
        }
	}
 	foreground(RED);
 	printf("\n\nacesso nao autorizado\n\n");
    printf("Prima enter para continuar\n");
    while(enter != '\r' && enter != '\n'){
        enter = getchar();
        scanf("%*c");
    }
    enter=0;
    system("clear");
    foreground(NORMAL_COLOR);
}
void alert(){
    for(int i=0;i<n_users;i++){
        if(max[i].tipo == 1){
            alerta++;
        }
    }
}
// menu
void voltar_menu(){
    system("clear");
    int tecla;
    mostra_menu();
    scanf("%d",&tecla);
        while(tecla){
            switch(tecla){
                case 1:{gerir_utilizadores();break;}
                case 2:{gerir_topicos();break;}
                case 3:{mostrar_menu_estatistica();break;}
                case 4:{main();break;}
                case 5:exit(1);
                default:{erro(tecla);}
            }
            mostra_menu();
            scanf("%d",&tecla);
        }
}
void mostra_menu(){
    foreground(CYAN);
	printf("Server\n***Menu***\n\n");
    foreground(NORMAL_COLOR);
	printf("1) Gerir utilizadores\n");
	printf("2) Gerir topicos\n");
	printf("3) Estatísticas\n");
	printf("4) Logout\n");
	printf("5) Sair/ Exit\n");
}
int carrega_user(){ //carrega o ficheiro
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
int carrega_topicos(){
FILE *hue; char s[120],i;
	n_mensagem=0;
	hue=fopen("topicos.txt","r");
	while(fgets(s,120,hue)){
		for(i=0;s[i]!=';';i++) maxi[n_mensagem].titulo[i]=s[i];
		maxi[n_mensagem].titulo[i]='\0';
		i++;
        maxi[n_mensagem].mensagem=atoi(&s[i]);
        i=i+2;
        maxi[n_mensagem].likes=atoi(&s[i]);
		n_mensagem++;
	}
	fclose(hue);
}
// topico
int criar_topico(){
    system("clear");
    chdir("topicos");
    char titulo[100];
    foreground(CYAN);
    printf("***Menu***\n");
    printf(" ***Gerir Topicos***\n");
    printf("  ***Criar Topico***\n\n");
    foreground(NORMAL_COLOR);
    printf("Titulo para o Topico\n\n");
    scanf("%s", titulo);
    FILE *verificar_fi;
    verificar_fi=fopen(titulo,"r");
    if(verificar_fi==NULL){
        FILE *file;
        file = fopen(titulo,"w");
        fclose(file);
        chdir("..");
        FILE *topico;
        topico = fopen("topicos.txt","a");
        fprintf(topico,"%s;0;0\n",titulo);
        fclose(topico);
    }
    else{
        printf("\nnome de topico já existente\n");
        chdir("..");
        foreground(RED);
        printf("Prima enter para continuar\n");
    while(enter != '\r' && enter != '\n'){
        enter = getchar();
        scanf("%*c");
    }
    enter=0;
    system("clear");
    }
    carrega_topicos();
    foreground(NORMAL_COLOR);
}
void gerir_topicos(){
    int tecla;
    system("clear");
    mostra_menu_topicos();
    mostra_topicos();
    scanf("%d",&tecla);
    while(tecla){
        switch(tecla){
            case 1:{remover_topicos();break;}
            case 2:{criar_topico();break;}
            case 3:{voltar_menu();break;}
            default:{erro(tecla);}
        }
        system("clear");
        mostra_menu_topicos();
        mostra_topicos();
        scanf("%d",&tecla);
    }
}
int remover_topicos(){
    system("clear");
    foreground(CYAN);
    printf("***Menu***\n");
    printf(" ***Gerir Topicos***\n");
    printf("  ***Eliminar Topico***\n\n");
    foreground(NORMAL_COLOR);
    printf("Topicos:\n");
    mostra_topicos();
    chdir("topicos");
    char titulo[100];
    printf("\nQual é o topico que deseja apagar?\n\n");
    scanf("%s", titulo);
    remove(titulo);
    chdir("..");
    for(int i=0;i<n_users;i++){
        if(strcmp(max[i].sub1,titulo)==0){
            strcpy(max[i].sub1, "");
            max[i].smsub1=0;
        }
        else if(strcmp(max[i].sub2,titulo)==0){
            strcpy(max[i].sub2, "");
            max[i].smsub2=0;
        }
        else if(strcmp(max[i].sub3,titulo)==0){
            strcpy(max[i].sub3, "");
            max[i].smsub3=0;
        }
        FILE *fx;
        fx=fopen(FX,"w");
        for(int j=0;j<n_users;j++){
            fprintf(fx,"%s;%s;%s;%d;%s;%d;%s;%d;%d;%d\n", max[j].nick,max[j].pass,max[j].sub1,max[j].smsub1,max[j].sub2,max[j].smsub2,max[j].sub3,max[j].smsub3,max[j].total_mensagem,max[j].tipo);
        }
        fclose(fx);
    }
    FILE *hue;
    hue=fopen("topicos.txt","w");
    for(int i=0;i<n_mensagem;i++){
        if(strcmp(maxi[i].titulo,titulo)!=0){
            fprintf(hue,"%s;%d;%d\n",maxi[i].titulo,maxi[i].mensagem,maxi[i].likes);
        }
    }
    fclose(hue);
    carrega_topicos();
}
void mostra_topicos(){
    printf("\n");
    foreground(NORMAL_COLOR);
    printf("||==================||\n");
    for(int i=0;i<n_mensagem;i++){
        foreground(NORMAL_COLOR);
        printf("||");
        foreground(YELLOW);
        printf("%18s",maxi[i].titulo);
        foreground(NORMAL_COLOR);
        printf("||\n");
    }
    printf("||==================||\n");
}
void mostra_menu_topicos(){
    foreground(CYAN);
    printf("Server\n***Menu***\n");
    printf(" ***Gerir Topicos***\n\n");
    foreground(NORMAL_COLOR);
	printf("1) Eliminar Topico\n");
	printf("2) Criar Topico\n");
	printf("3) Voltar ao menu\n\n");
	printf("Topicos:\n");
}
// gerir utilizadores
void mostrar_utilizadores(){
    int i;
    foreground(NORMAL_COLOR);
    printf("||==================||===||\n");
    printf("||");
    foreground(YELLOW);
    printf(" ******NAME****** ");
    foreground(NORMAL_COLOR);
    printf("||");
    foreground(YELLOW);
    printf(" T ");
    foreground(NORMAL_COLOR);
    printf("||\n");
    printf("||==================||===||\n");
    for(i=0;i<n_users;i++){
        if(max[i].tipo != 1){
            foreground(NORMAL_COLOR);
            printf("||");
            foreground(YELLOW);
            printf(" %16s ",max[i].nick);
            foreground(NORMAL_COLOR);
            printf("||");
            foreground(YELLOW);
            printf(" %1d ",max[i].tipo);
            foreground(NORMAL_COLOR);
            printf("||\n");
        }
    }
    printf("||==================||===||\n");
}
void mostrar_menu_utilizadores(){
    foreground(CYAN);
    printf("Server\n***Menu***\n");
    printf(" ***Gerir Utilizadores***\n\n");
    foreground(NORMAL_COLOR);
	printf("1) Alterar tipo\n");
	printf("2) Aceitar pedidos\n");
	printf("3) Apagar user\n");
	printf("4) voltar ao menu\n\n");
}
void gerir_utilizadores(){
    int tecla;
    system("clear");
    mostrar_menu_utilizadores();
    mostrar_utilizadores();
    scanf("%d",&tecla);
    while(tecla){
        switch(tecla){
            case 1:{mudar_tipo();break;}
            case 2:{aceitar_users();break;}
            case 3:{apagar_user();break;}
            case 4:{voltar_menu();break;}
            default:{erro(tecla);}
        }
        system("clear");
        mostrar_menu_utilizadores();
        mostrar_utilizadores();
        scanf("%d",&tecla);
    }

}
int apagar_user(){
    char nick1[15];
    int i;
    printf("Qual é o user que deseja remover?\n");
    scanf("%s", nick1);
    FILE *fx;
    fx=fopen(FX,"w");
    for(i=0;i<n_users;i++){
        if(strcmp(max[i].nick,nick1)!=0){
            fprintf(fx,"%s;%s;%s;%d;%s;%d;%s;%d;%d;%d\n", max[i].nick,max[i].pass,max[i].sub1,max[i].smsub1,max[i].sub2,max[i].smsub2,max[i].sub3,max[i].smsub3,max[i].total_mensagem,max[i].tipo);
        }
    }
    fclose(fx);
    carrega_user();
}
int mudar_tipo(){
    char nick1[15];
    int i;
    int t;
    printf("Qual é o user que deseja alterar?\n");
    scanf("%s", nick1);
    for(i=0;i<n_users;i++){
        if(strcmp(max[i].nick,nick1)==0){
            printf("Qual é o tipo que deseja meter?\n");
            scanf("%d", &t);
            max[i].tipo = t;
            FILE *fx;
            fx=fopen(FX,"w");
            for(i=0;i<n_users;i++){
                 fprintf(fx,"%s;%s;%s;%d;%s;%d;%s;%d;%d;%d\n", max[i].nick,max[i].pass,max[i].sub1,max[i].smsub1,max[i].sub2,max[i].smsub2,max[i].sub3,max[i].smsub3,max[i].total_mensagem,max[i].tipo);
            }
            fclose(fx);
        }
    }
    carrega_user(max);
}
void mostra_aceitar_users(){
    int i;
    foreground(NORMAL_COLOR);
    printf("||==================||\n");
    printf("||");
    foreground(YELLOW);
    printf(" ******NAME****** ");
    foreground(NORMAL_COLOR);
    printf("||\n");
    for(i=0;i<n_users;i++){
        if(max[i].tipo == 1){
            foreground(NORMAL_COLOR);
            printf("||");
            foreground(YELLOW);
            printf(" %16s ",max[i].nick);
            foreground(NORMAL_COLOR);
            printf("||\n");
        }
    }
    printf("||==================||\n");
}
void menu_aceitar_users(){
    foreground(CYAN);
    printf("Server\n***Menu***\n");
    printf(" ***Gerir Utilizadores***\n");
    printf("  ***Aceitar Users***\n\n");
    foreground(NORMAL_COLOR);
    printf("1)Aceitar\n");
    printf("2)Recusar\n");
    printf("3)Voltar\n");
}
void aceitar_users(){
    int tecla;
    system("clear");
    menu_aceitar_users();
    mostra_aceitar_users();
    scanf("%d",&tecla);
    while(tecla){
        switch(tecla){
            case 1:{aceitar_users_aceite();break;}
            case 2:{aceitar_users_remove();break;}
            case 3:{gerir_utilizadores();break;}
            default:{erro(tecla);}
        }
        system("clear");
        menu_aceitar_users();
        mostra_aceitar_users();
        scanf("%d",&tecla);
    }
}
int aceitar_users_aceite(){
    char nick1[15];
    int i;
    printf("Qual é o user que deseja aceitar?\n");
    scanf("%s", nick1);
    for(i=0;i<n_users;i++){
        if(strcmp(max[i].nick,nick1)==0){
            max[i].tipo = 2;
            FILE *fx;
            fx=fopen(FX,"w");
            for(i=0;i<n_users;i++){
                 fprintf(fx,"%s;%s;%s;%d;%s;%d;%s;%d;%d;%d\n", max[i].nick,max[i].pass,max[i].sub1,max[i].smsub1,max[i].sub2,max[i].smsub2,max[i].sub3,max[i].smsub3,max[i].total_mensagem,max[i].tipo);
            }
            fclose(fx);
        }
    }
    carrega_user();
}
int aceitar_users_remove(){
    char nick1[15];
    int i;
    int t;
    printf("Qual é o user que deseja recusar?\n");
    scanf("%s", nick1);
    FILE *fx;
    fx=fopen(FX,"w");
    for(i=0;i<n_users;i++){
        if(strcmp(max[i].nick,nick1)!=0){
            fprintf(fx,"%s;%s;%s;%d;%s;%d;%s;%d;%d;%d\n", max[i].nick,max[i].pass,max[i].sub1,max[i].smsub1,max[i].sub2,max[i].smsub2,max[i].sub3,max[i].smsub3,max[i].total_mensagem,max[i].tipo);
        }
    }
    fclose(fx);
    carrega_user();
}
// estatísticas
void menu_estatistica(){
    foreground(CYAN);
    printf("Server\n***Menu***\n");
    printf(" ***Estatistica***\n\n");
    foreground(NORMAL_COLOR);
    printf("1)Quantidade de topicos ativos;\n"); //feito
    printf("2)Topicos mais utilizados;\n");
    printf("3)Quantidade de mensagens de um determinado topico;\n");
    printf("4)Analisar os topicos subscritos por um determinado utilizador;\n"); //feito
    printf("5)voltar ao menu;\n"); //feito
}
void mostrar_menu_estatistica(){
    int tecla;
    system("clear");
    menu_estatistica();
    scanf("%d", &tecla);
    while(tecla){
        switch(tecla){
            case 1:{quantidade_topicos();break;}
            case 2:{topicos_mais_utilizados();break;}
            case 3:{quantidade_mensagens();break;}
            case 4:{switch_analisar_utilizador();break;}
            case 5:{voltar_menu();break;}
            default:{erro(tecla);}
        }
        menu_estatistica();
        scanf("%d", &tecla);
    }
}
void quantidade_topicos(){
    carrega_topicos();
    FILE *topicos;
    topicos=fopen("topicos.txt","r");
    char top[1000],t=0,i;
    while(fgets(top,1000,topicos)){
        for(i=0;top[i]!='\0';i++)
            if(top[i]=='\n'){
                t++;
            }
    }
    system("clear");
    menu_quantidade_topicos();
    printf("Existem %d topicos\n\n",t);
    int tecla;
    scanf("%d",&tecla);
    while(tecla){
        switch(tecla){
            case 1:{quantidade_topicos_mais_topicos();break;}
            case 2:{mostrar_menu_estatistica();break;}
            default:{erro(tecla);}
        }      
        system("clear");
        menu_quantidade_topicos();
        printf("Existem %d topicos\n",t);
        scanf("%d",&tecla);
    }
}
void quantidade_topicos_mais_topicos(){
    carrega_topicos();
    FILE *topicos;
    topicos=fopen("topicos.txt","r");
    char top[1000],t=0,i;
    while(fgets(top,1000,topicos)){
        for(i=0;top[i]!='\0';i++)
            if(top[i]=='\n'){
                t++;
            }
    }
    system("clear");
    menu_quantidade_topicos_mais_topicos();
    printf("Existem %d topicos\n",t);
    mostra_topicos();
    int tecla;
    scanf("%d",&tecla);
    while(tecla){
        switch(tecla){
            case 1:{mostrar_menu_estatistica();break;}
            default:{erro(tecla);}
        }      
        system("clear");
        menu_quantidade_topicos_mais_topicos();
        printf("Existem %d topicos\n",t);
        mostra_topicos();
        scanf("%d",&tecla);
    }
}
void menu_quantidade_topicos(){
    foreground(CYAN);
    printf("Server\n***Menu***\n");
    printf(" ***Estatistica***\n");
    printf("  ***Quantidade de topicos ativos***\n\n");
    foreground(NORMAL_COLOR);
    printf("1)Ver topicos\n");
    printf("2)Voltar\n\n");
}
void menu_quantidade_topicos_mais_topicos(){
    foreground(CYAN);
    printf("Server\n***Menu***\n");
    printf(" ***Estatistica***\n");
    printf("  ***Quantidade de topicos ativos***\n\n");
    foreground(NORMAL_COLOR);
    printf("1)Voltar\n\n");
}
void switch_analisar_utilizador(){
    int tecla;
    system("clear");
    menu_analisar_utilizador();
    scanf("%d",&tecla);
    while(tecla){
        switch(tecla){
            case 1:{analisar_utilizador();break;}
            case 2:{mostrar_menu_estatistica();break;}
            default:{erro(tecla);break;}
        }
        system("clear");
        menu_analisar_utilizador();
        scanf("%d",&tecla);
    }
}
void analisar_utilizador(){
    carrega_user();
    int i;char name[15];
    int true=0;
     while(true!=1){
        mostrar_utilizadores();
        printf("que utilizador pertende analisar?\n");
        scanf("%s",name);
        for(i=0;i<n_users;i++){
            if(strcmp(max[i].nick,name)==0){
            true=1;
            system("clear");
            break;
            }
            else {
            true=2;
            }
        }
        if(true==2){
            system("clear");
            foreground(CYAN);
            printf("Server\n***Menu***\n");
            printf(" ***Estatistica***\n");
            printf("  ***Analisar os topicos subscritos por um determinado utilizador***\n\n");
            foreground(NORMAL_COLOR);
            printf("utilizador nao existe!\n\n");
        }
    }
    foreground(CYAN);
    printf("Server\n***Menu***\n");
    printf(" ***Estatistica***\n");
    printf("  ***Analisar os topicos subscritos por um determinado utilizador***\n\n");
    foreground(NORMAL_COLOR);
     if((strlen(max[i].sub1) != 0)||(strlen(max[i].sub2) != 0)||(strlen(max[i].sub3) != 0)){
        printf("O utilizador %s está subescrito nos topicos:\n\n",max[i].nick);
        if(strlen(max[i].sub1) != 0){
            foreground(YELLOW);
            printf(" %s\n",max[i].sub1);
        }
        if(strlen(max[i].sub2) != 0){
            foreground(YELLOW);
            printf(" %s\n",max[i].sub2);
        }
        if(strlen(max[i].sub3) != 0){
            foreground(YELLOW);
            printf(" %s\n\n",max[i].sub3);
        }
        foreground(NORMAL_COLOR);
        printf("Numero de mensagens enviadas por topico:\n\n");
        if(strlen(max[i].sub1) != 0){
            foreground(YELLOW);
            printf(" %s",max[i].sub1);
            foreground(NORMAL_COLOR);
            printf(" → ");
            foreground(YELLOW);
            printf("%d\n",max[i].smsub1);
        }
        if(strlen(max[i].sub2) != 0){
            foreground(YELLOW);
            printf(" %s",max[i].sub2);
            foreground(NORMAL_COLOR);
            printf(" → ");
            foreground(YELLOW);
            printf("%d\n",max[i].smsub2);
        }
        if(strlen(max[i].sub3) != 0){
            foreground(YELLOW);
            printf(" %s",max[i].sub3);
            foreground(NORMAL_COLOR);
            printf(" → ");
            foreground(YELLOW);
            printf("%d\n\n",max[i].smsub3);
        }
     }
    else{
        printf("O utilizador %s não tem subescrições\n",max[i].nick);
    }
    foreground(RED);
    printf("Prima enter para continuar\n\n\a");
    while(enter != '\r' && enter != '\n'){
        enter = getchar();
        scanf("%*c");
    }
    enter=0;
}
void menu_analisar_utilizador(){
    foreground(CYAN);
    printf("Server\n***Menu***\n");
    printf(" ***Estatistica***\n");
    printf("  ***Analisar os topicos subscritos por um determinado utilizador***\n\n");
    foreground(NORMAL_COLOR);
    printf("1)Analisar um utilizador\n");
    printf("2)Voltar\n");
}
void quantidade_mensagens(){
	int tecla;
    system("clear");
	menu_quantidade_mensagens();
	scanf("%d",&tecla);
	while(tecla){
		switch(tecla){
			case 1:{analisar_topico();break;}
			case 2:{mostrar_menu_estatistica();break;}
			default:{erro(tecla);}
		}
        system("clear");
		menu_quantidade_mensagens();
		scanf("%d",&tecla);
	}
}
void analisar_topico(){
    carrega_topicos();
    system("clear");
    foreground(CYAN);
    printf("Server\n***Menu***\n");
    printf(" ***Estatistica***\n");
    printf("  ***Quantidade de mensagens de um determinado topico***\n\n");
    foreground(NORMAL_COLOR);
    mostra_topicos();
	chdir("topicos");
	char analise[100];
    printf("\nQue topico deseja analisar?\n");
	scanf("%s",analise);
    FILE *analise2;
	analise2=fopen(analise,"r");
    if(analise2==NULL){
        printf("O topico %s não existe\n\n", analise);
        chdir("..");
        foreground(RED);
        printf("Prima enter para continuar\n");
        foreground(NORMAL_COLOR);
        while(enter != '\r' && enter != '\n'){
            enter = getchar();
            scanf("%*c");
        }
        enter=0;
        system("clear");
    }
    else{
	char top[1000],t=0,i;
	while(fgets(top,1000,analise2)){
			for(i=0;top[i]!='\0';i++)
					if(top[i]=='\n'){
							t++;
					}
	}
	printf("existem %d mensagens no topico %s\n\n",t,analise);
	chdir("..");
    foreground(RED);
    printf("Prima enter para continuar\n");
    foreground(NORMAL_COLOR);
    while(enter != '\r' && enter != '\n'){
        enter = getchar();
        scanf("%*c");
    }
        enter=0;
        system("clear");
    }
}
void menu_quantidade_mensagens(){
    foreground(CYAN);
    printf("Server\n***Menu***\n");
    printf(" ***Estatistica***\n");
    printf("  ***Quantidade de mensagens de um determinado topico***\n\n");
    foreground(NORMAL_COLOR);
	printf("1)analisar um topico\n");
	printf("2)voltar\n");
}
void menu_topicos_mais_utilizados(){
    foreground(CYAN);
    printf("Server\n***Menu***\n");
    printf(" ***Estatistica***\n");
    printf("  ***Topicos mais utilizados***\n\n");
    foreground(NORMAL_COLOR);
    printf("1)Voltar\n\n");
}
void topicos_mais_utilizados(){
    int tecla;
    system("clear");
    menu_topicos_mais_utilizados();
    mostra_topicos_mais_utlizados();
    scanf("%d",&tecla);
    while(tecla){
        switch(tecla){
            case 1:{mostrar_menu_estatistica();break;}
            default:{erro(tecla);}
        }
        system("clear");
        menu_topicos_mais_utilizados();
        mostra_topicos_mais_utlizados();
        scanf("%d",&tecla);
    }
}
void mostra_topicos_mais_utlizados(){
    printf("Tabela de topicos mais utilizados:\n\n");
    ordenar_funcoes();
}
int ordenar_funcoes(){
    carrega_topicos();
    int aux,i,j;
    char copia[100];
    for(j=n_mensagem;j>=0;j--){
        for(i=0;i<j;i++){
            if((maxi[i].mensagem) < (maxi[i+1].mensagem)){
                strcpy(copia, maxi[i].titulo);
                aux = maxi[i].mensagem;
                strcpy(maxi[i].titulo,maxi[i+1].titulo);
                maxi[i].mensagem = maxi[i+1].mensagem;
                maxi[i+1].mensagem = aux;
                strcpy(maxi[i+1].titulo,copia);
            }
        }
    }
    foreground(NORMAL_COLOR);
    printf("||==================||\n");
    for(int i=0;i<n_mensagem;i++){
        foreground(NORMAL_COLOR);
        printf("||");
        foreground(YELLOW);
        printf("%18s",maxi[i].titulo);
        foreground(NORMAL_COLOR);
        printf("||\n");
    }
    printf("||==================||\n");
    carrega_topicos();
}
// bonitinho
void prints(){
    foreground(CYAN);
    printf(" #######  ####### ######  ##      ## ####### ######\n");
    printf("##        ##      #     #  ##    ##  ##      #     #\n");
    printf(" #######  #####   ######    ##  ##   #####   ######\n");
    printf("       ## ##      #   #      ####    ##      #   #\n");
    printf(" #######  ####### #     #     ##     ####### #     #\n");
    foreground(RED);
    printf("\n\nPrima enter para continuar\n");
    while(enter != '\r' && enter != '\n'){
        enter = getchar();
    }
        enter=0;
        system("clear");
        foreground(NORMAL_COLOR);
}
