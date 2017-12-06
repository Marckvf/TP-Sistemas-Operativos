/*
 * File:   main.c
 * Author: MARCO FERREIRA
 *
 * Created on 10 de Novembro de 2017, 1:39
 */
#include "structs.h"


void pedido_registo(){

    int i, err_escrita=0, guardar=0, erro = 0,tam_pw, tam_id;
    char id[MAX], pw[MAX], id_f[MAX], pw_f[MAX];

   // Fich com Nome e Pass dos Utilizadores
   FILE *fd = fopen("registo.txt", "a+");
	if(fd == NULL){
            printf("ERRO: Acesso Negado!\n");
            exit(0);
	}

    // Validação dados
    do{
        erro=0;
        __fpurge(stdin);                                                 // previne leituras do resto do stdout do ciclo anterior
        printf("\nNome de Utilizador: ");
  	    scanf(" %s", id);
        tam_id = strlen(id);

        if(strcmp(id,"0")==0){                                          // para sair do loop e voltar ao menu
          fclose(fd);
          return;
        }
        __fpurge(stdin);                                                  // garante que guardar a pass e nao o resto do username
  	    printf("Password: ");
  	    scanf(" %s", pw);
        tam_pw = strlen(pw);

        fseek(fd,0,SEEK_SET);

        while(fscanf(fd, "%s %s", id_f, pw_f)!=EOF){			//Este ciclo guarda em id_t e pw_t o id e pass do jogador nessa linha
            if(strcmp(id, id_f) == 0){				//Se id e id_t forem iguais
                erro = 1;
                printf("\nERRO: Este Nome de Utilizador ja Existe!\n");
                break;
            }
        }
        if (tam_id > MAX_LEN_USER || tam_id < MIN_LEN_USER){
            printf("ERRO: Nome de Utilizador Demasiado Grande/Pequeno!\n");
            erro = 1;
        }

        if (tam_pw > MAX_LEN_PASS || tam_pw < MIN_LEN_PASS){
            printf("ERRO: Password demasiado Grande/Pequena!\n");
            erro = 1;
        }
        else  if (strcmp(id, pw) == 0){
            printf("O Nome de Utilizador e Password devem ser Diferentes!\n");
            erro = 1;
        }
        if(erro==0)
            guardar=1;
    }while(erro);

    // Guardar Nome e Pass
    err_escrita = fprintf(fd, "%s\t%s\n", id, pw);

    if(err_escrita<0){                                                 // erro na escrita para ficheiro
        printf("\nErro de Sistema!   Problema com escrita para ficheiro");
        fclose(fd);
        return;
    }

    // Se nao houverem erros de input e se tiver sido guardado no fich entao:
    printf("\nRegisto bem Sucedido. Bem Vindo ao Bomberman !!!\n");
    fclose(fd);
}

void pedido_login(){

    char id_f[MAX_LEN_USER], pw_f[MAX_LEN_PASS], id[MAX_LEN_USER], pw[MAX_LEN_PASS];
    int match=0, err, nuser;
    FILE *fd=fopen("registo.txt", "r");
    if(fd == NULL){
		printf("ERRO: Acesso Negado ao Ficheiro de utilizadores.\n");
		return;
    }

    printf("Introduza Nome de Utilizador: ");
    scanf(" %s", id);
    printf("Introduza Password: ");
    scanf(" %s", pw);

    while(fscanf(fd," %s %s", id_f, pw_f)!=EOF){
        if(strcmp(id, id_f) == 0 && strcmp(pw, pw_f) == 0)
            match=1;
    }
    if(match){
        printf("\nO Login foi efetuado com sucesso!   Divirta-se!");
        return;
    }
    else{
        printf("\nUser/Password Invalidos\n");
        return;
    }
}

void menu(){				 // fazer função para verificação de erros e proteger o input

    int op;

    while(1){
        op=0;
        __fpurge(stdin);
        printf("\n1- Registar\n2- Login\n3- Sair\nOpcao: ");
        scanf("%d", &op);

        if(op == 1)
            pedido_registo();

        if(op == 2)
            pedido_login();

        if(op == 3)
            exit(0);
    }
}

int main(void){
//  keywords comment -> testar, falta
  int PID = getpid();
  int fd_server = open(PIPE_DO_SERVIDOR,O_WRONLY);
  if(fd_server == -1){
    printf("erro a abrir fifo");
  }

  MTS2 mts_login = {'l',PID,"user","pass"};


  if(write(fd_server,&mts_login,sizeof(mts_login))== -1)
    printf("erro a escrever no pipe");



	//menu();

	exit(0);
}
