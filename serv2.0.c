#include "structs.h"

int registo(char *id, char *pw);
void exit_error(int fd,char *msg_erro);
void server_online();

int main(){
  char pass[MAX_LEN_USER];
  char user[MAX_LEN_USER];

  int i, pos_espaco, pos_final, valido,v, resultado=0, count_space=0;
  char cmd[100];

  char teste_temp1[20], teste_temp2[20];

  setbuf(stdout,NULL);

  while (1) {

    printf("SERV/ADMIN>>>>>> ");
    fgets(cmd, sizeof(cmd), stdin);

    printf("%s\n", cmd );
    if(strcmp(cmd,"ad\n")==0){
        printf("qual o user e pass??");
        scanf("%s %s",teste_temp1,teste_temp2);
        registo(teste_temp1, teste_temp2);
        continue;
    }
    if(strcmp(cmd,"pipe\n")==0){
      //testar a comunicação pipes
      server_online();
    }

    if(cmd[0]=='a'){
        if(cmd[1]=='d' && cmd[2]=='d' && cmd[3]==' ')
          // vamos varrer o cmd e verificar o input, guardando a pos entre user e pass e a pos final.
             for(i=4, valido=1 ; valido && i<99 && cmd[i]!='\n' && cmd[i]!='\0' ;i++){

                if( (cmd[i]>64 && cmd[i]<91) || (cmd[i]>96 && cmd[i]<123) || (cmd[i]>47 && cmd[i]<58) )        // se for letra ou numero
                    continue;

                if (cmd[i]==' ' && count_space == 0){  // se for o 1º espaço, se houver 2 dá erro.
                    count_space++;
                    pos_espaco=i;   // guarda o intervalo entre o user e a pass, no buffer.
                    continue;
                }

                else{
                    printf(" -%c- \n%s\n",cmd[i],"string corrumpida" );
                    valido = 0;
                }

           }pos_final = i;


           //após já sabemos que so temos carateres validos e 1 espaço, bem como a sua posição. entao vefiricamos o tamanho do user e da pass.
           if(valido){
             if ( (pos_espaco-3)<MAX_LEN_USER && (pos_espaco-3)>MIN_LEN_USER && (pos_final-pos_espaco)>MIN_LEN_PASS && (pos_final-pos_espaco)<MAX_LEN_PASS ){

                for(v=0,i=4;i<pos_espaco;v++,i++){              //passa o nome user para o array user
                    user[v]=cmd[i];
                }user[v]='\0';

                for(v=0,i=pos_espaco+1;i<pos_final;v++,i++){    //passa a password para o array pass
                    pass[v]=cmd[i];
                }pass[v]='\0';


                if(registo(user,pass))
                    printf("MAIN: registo efetuado com sucesso");
                else
                    printf("MAIN: registo falhou");
             }
             else{
              perror("Atenção ao tamanho do user e pass.");
              printf("O user deve ter entre %d e %d, e a pass entre %d e %d", MIN_LEN_USER, MAX_LEN_USER, MIN_LEN_PASS, MAX_LEN_PASS );
            }
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
  }while(strcmp(cmd, "exit") != 0);


  return 0;
}



int registo(char *id, char *pw){

  printf("%s\n", "entrei no registo" );

  FILE *f = fopen("registo.txt", "a+");

  int erro = 0, tam_id, tam_pw, err_escrita = 0;
  char id_f[MAX_LEN_USER], pw_f[MAX_LEN_PASS];


  char msg_err_esc[] = { "ERRO: Problemas ao Escrever no Ficheiro!\n" };
  char msg_sucesso[] = { "Registo Bem Sucedido! Bem Vindo ao Bomberman!\n" };
  char msg_id_existente[] = { "Este Nome de Utilizador Ja Foi Escolhido!\n" };

  if(f == NULL){
    perror("Acesso Negado!");
    return 0;
  }

  tam_id = strlen(id);
  tam_pw = strlen(pw);

  //Inicio de verificações de segurança:
  if (strcmp(id, pw) == 0){
     perror("Password e User iguais!");
     fclose(f);
     return 0;
  }
  while(fscanf(f, "%s %s", id_f, pw_f)!=EOF){			//Este ciclo guarda em id_t e pw_t o id e pass de cada linha, até ao fim ficheiro
      if(strcmp(id, id_f) == 0){				          //Se id e id_t forem iguais
          perror("Utilizador já existe!");
          fclose(f);
          return 0;
      }
  }

  if (tam_id > MAX_LEN_USER || tam_id < MIN_LEN_USER){
      perror("Nome de Utilizador Demasiado Grande/Pequeno!");
      fclose(f);
      return 0;
  }

  if (tam_pw > MAX_LEN_PASS || tam_pw < MIN_LEN_PASS){
      perror("Password Demasiado Grande/Pequena!");
      fclose(f);
      return 0;
  }


  //Se tiver passado nas validações, então Guardar:
  err_escrita = fprintf(f, "%s\t%s\n", id, pw);

  if(err_escrita<0){                                                 // erro na escrita para ficheiro
      perror("Problemas ao Escrever no Ficheiro!");
      fclose(f);
      return 0;
  }
  // Se nao houverem erros de input e se tiver sido guardado no fich entao:
  printf("Novo registo bem Sucedido !\n");
  fclose(f);
  return 1;
}



void server_online(){
  //setbuf(stdout,NULL);

      printf("Server_online\n");

      int array_pid_cliente[30], it_apc=0;      // array com os pids de clientes sem login, possiveis jogadores validos
      int fd_server, tipo_mensagem;
      MFC2 mfc_login;                             //estrutura com 2 arrays, para user e pass.

      if( mkfifo(PIPE_DO_SERVIDOR, 0777) == -1){
        perror("Erro na Inicialização. Só pode existir uma instancia do Servidor.");
        return;
       }

      fd_server = open(PIPE_DO_SERVIDOR,O_RDWR);
      if(fd_server == -1){
        perror("Erro a abrir pipe do Servidor.");
        unlink(PIPE_DO_SERVIDOR);
        return;
      }

      while(1){

        tipo_mensagem = 0;

        if(read(fd_server,&tipo_mensagem,sizeof(tipo_mensagem))==-1)
          exit_error(fd_server,"A func read nao consegiui ler");

          printf("%d\n",tipo_mensagem );

        if(tipo_mensagem == 1 ){ //

          printf("Fazer Aqui tratamento para login\n ler resto estrutura, etc\n");

          if(read(fd_server,&mfc_login,sizeof(mfc_login)) == -1)
            exit_error(fd_server,"A func read nao consegiui ler");

          printf("%s", mfc_login.msg1);
          printf("%s", mfc_login.msg2);


        }
        if (tipo_mensagem == 0){
          perror("Atenção: Foram recebidos dados inválidos. \nO servidor vai continuar em funcionamento.\n");
          continue;
        }
        else if(tipo_mensagem > 0){    //deverá ser um PID
          printf("recebi um pid, vou guardar!\n");
          array_pid_cliente[it_apc] = tipo_mensagem;
          continue;
        }
      }
      exit_error(fd_server, "O servidor Terminou Corretamente");
}

void exit_error(int fd,char *msg_erro){
  perror(msg_erro);
  close(fd);
  unlink(PIPE_DO_SERVIDOR);
  exit(1);
}
