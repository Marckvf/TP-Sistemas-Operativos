#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_LEN_USER 30
#define MIN_LEN_USER 3
#define MAX_LEN_PASS 30
#define MIN_LEN_PASS 3

int registo(char *id, char *pw);
int main(){
    setbuf(stdout,NULL);
    char admin[]={'\n','s','e','r','v','e','r','/','a','d','m','i','n','>','>','>'};
    char c;
    char cmd[100];
    char user[MAX_LEN_USER];
    char msg_registo[]={'R','e','g','i','s','t','o',' ','e','f','e','t','u','a','d','o',' ','c','o','m',' ','s','u','c','e','s','s','o','!','\n'};
    char msg_registo_err[]={'R','e','g','i','s','t','o',' ','f','a','l','h','o','u','!',' ','t','e','n','t','e',' ','n','o','v','a','m','e','n','t','e','\n'};
    char pass[MAX_LEN_USER];
    int i, pos_espaco, pos_final, valido=1,v, resultado=0, count_space=0;

    while(1){

        write(STDOUT_FILENO, admin, sizeof(admin)); // é provavel que nao funcione pq tem de ser um buffer diferente. ver pag 3 das FAQ's(sprintf p/ buffer, write)

        i=0;
        while(read(STDIN_FILENO,&c,1)>0){
          cmd[i]=c;
          if(cmd[i]=='\n' || i>98)
            break;
          i++;
        }


        cmd[i]='\0';                          // em caso do utilizador tern escrito muitos carateres sem ter carregado em enter.
                    //a func read nao coloca \0
        pos_final=i;
        if(cmd[0]=='a'){
            if(cmd[1]=='d' && cmd[2]=='d' && cmd[3]==' ')
            printf("registado!");
               for(i=4;valido && i<99 && cmd[i]!='\0';i++){
                             printf("\n avancei 1 carater");
                    if( (cmd[i]<64 || cmd[i]>91) && (cmd[i]<96 || cmd[i]>123) ){        // se ler algo que nao seja letra
                        printf("\n verificar letras");
                        valido=0;     // serve para indicar a todos os if's encadeados que houve um erro no input e que se tmos de voltar ao while principal.
                    }
                    else if (cmd[i]==' '){
                        printf("\n espaco!");
                        count_space++;
                        pos_espaco=i;   //guarda o intervalo entre o user e a pass, no buffer.
                        if(count_space>1 || count_space==0){
                            valido = 0;
                            break;
                        }
                    }
               }
               //após já sabemos que so temos carateres validos e 1 espaço, bem como a sua posição. entao vefiricamos o tamanho do user e da pass.
                if(valido && (pos_espaco-4)<MAX_LEN_USER && (pos_espaco-4)>MIN_LEN_USER && (pos_final-pos_espaco)>MIN_LEN_PASS && (pos_final-pos_espaco)<MAX_LEN_PASS){
                    for(v=0,i=4;i<pos_espaco;v++,i++){              //passa o nome user para o array user
                        user[v]=cmd[i];
                    }user[v]='\0';
                    for(v=0,i=pos_espaco+1;i<pos_final;v++,i++){    //passa a password para o array pass
                        pass[v]=cmd[i];
                    }pass[v]='\0';


                    if(registo(user,pass))
                        write(1, msg_registo, sizeof(msg_registo));
                    else
                        write(1, msg_registo_err, sizeof(msg_registo));
                }
        }

        else if(cmd[0]=='g'){
            if(cmd[1]=='a' && cmd[2]=='m' && cmd[3]=='e')
                printf("game");//chama a função
        }
        else if(cmd[0]=='k'){
            if(cmd[1]=='i' && cmd[2]=='c' && cmd[3]=='k')
                printf("kick");//chama a função
        }
        else if(cmd[0]=='m'){
            if(cmd[1]=='a' && cmd[2]=='p')
                printf("map");//chama a função
        }
        else if(cmd[0]=='u'){
            if(cmd[1]=='s' && cmd[2]=='e' && cmd[3]=='r'&& cmd[4]=='s')
                printf("users");//chama a função
        }
        else if(cmd[0]=='s'){
            if(cmd[1]=='h' && cmd[2]=='u' && cmd[3]=='t'&& cmd[4]=='d' && cmd[5]=='o' && cmd[6]=='w' && cmd[7]=='n')
                printf("shutdown");//chama a função
        }
        else if(cmd[0]=='e'){
            if(cmd[1]=='x' && cmd[2]=='i' && cmd[3]=='t')
                return 0;
        }
    }
}

int registo(char *id, char *pw){

  FILE *f = fopen("registo.txt", "a+");
  int erro = 0, tam_id, tam_pw, err_escrita = 0;
  char id_f[MAX_LEN_USER], pw_f[MAX_LEN_PASS];
  char msg_file[] = { "Acesso Negado!\n" };
  char msg_idpw[] = { "ERRO: Nome de Utilizador e Password sao Iguais\n" };
  char msg_err_esc[] = { "ERRO: Problemas ao Escrever no Ficheiro!\n" };
  char msg_err_id[] = { "ERRO: Nome de Utilizador Demasiado Grande/Pequeno!\n" };
  char msg_err_pw[] = { "ERRO: Password Demasiado Grande/Pequena!\n" };
  char msg_sucesso[] = { "Registo Bem Sucedido! Bem Vindo ao Bomberman!\n" };
  char msg_id_existente[] = { "Este Nome de Utilizador Ja Foi Escolhido!\n" };

  if(f == NULL){
    read(1, &msg_file, sizeof(msg_file));
    return 0;
  }

  tam_id = strlen(id);
  tam_pw = strlen(pw);

  while(fscanf(f, "%s %s", id_f, pw_f)!=EOF){			//Este ciclo guarda em id_t e pw_t o id e pass do jogador nessa linha
      if(strcmp(id, id_f) == 0){				//Se id e id_t forem iguais
          erro = 1;
          read(0, &msg_id_existente, sizeof(msg_id_existente));
          return 0;
      }
  }

  if (tam_id > MAX_LEN_USER || tam_id < MIN_LEN_USER){
      read(0, &msg_err_id, sizeof(msg_err_id));
      erro = 1;
      return 0;
  }

  if (tam_pw > MAX_LEN_PASS || tam_pw < MIN_LEN_PASS){
      read(0, &msg_err_pw, sizeof(msg_err_pw));
      erro = 1;
      return 0;
  }
  else  if (strcmp(id, pw) == 0){
      read(0, &msg_idpw, sizeof(msg_idpw));
      erro = 1;
      return 0;
  }

  if(err_escrita<0){                                                 // erro na escrita para ficheiro
      read(0, &msg_err_esc, sizeof(msg_err_esc));
      fclose(f);
      return 0;
  }

  err_escrita = fprintf(f, "%s\t%s\n", id, pw);

  // Se nao houverem erros de input e se tiver sido guardado no fich entao:
  read(0, "\nRegisto bem Sucedido. Bem Vindo ao Bomberman !!!\n", 0);
  fclose(f);

  return 1;
}
