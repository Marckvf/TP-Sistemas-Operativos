#include "structs.h"


//void menu();
int pedido_login( char * pipe_cliente, int fd_server);


int main(){
  int i=1;
  char pipe_name[TAM_ARRAY_PIPE_CLI]; // 11 elementos para ter PIPE_32768 no max
  int pid = getpid();
  int fd;
  int fd_server;
  char feedback = '0';

  setbuf(stdout,NULL);

  sprintf(pipe_name,"PIPE_%d",pid);

  fd_server = open(PIPE_DO_SERVIDOR, O_WRONLY);
  if(fd_server == -1){
    perror("Erro a abrir pipe do servidor / sem servidor. A Aplicação vai encerrar.");
    return 0;
  }
  if(mkfifo(pipe_name,0777) == -1){
    perror("Impossivel criar Fifo do Cliente.");
    close(fd_server);
    return -1;
  }

  fd = open(pipe_name, O_RDWR);
  if (fd == -1){
    perror("Impossivel iniciar pipe do cliente em modo leitura.");
    close(fd_server);
    unlink(pipe_name);
    return -1;
  }

  printf("\nBem Vindo. É um jogador registado?\nVerifique os seus dados.");
  while(i){
    if(pedido_login(pipe_name,fd_server) == 0){
      puts("falta me ler no meu pipe o FEEDBACK");
      if(read(fd,&feedback,sizeof(feedback)) == -1){
        perror("Impossivel ler Feedback.");
        // #########################################
        // Acabar apartir daqui
        // #########################################
      }
      printf("%c\n",feedback );
      if(feedback == 'l'){
        puts("\nVamos Jogar");
      }
      //#########################################
      // receber e tratar signal
      /*
      a minha sugestão é usar o read para o caso de sucesso. e o signal para insucesso. ver servidor
      */
      //#########################################

      i=0;
    }
    else
      printf("\nTentar Novamente? Prima 1. Sair? Prima 0.\t");
      scanf("%1d[^]0-1]",&i);
  }

  //Sair:
  close(fd_server);
  close(fd);
  unlink(pipe_name);
  return 0;
}

int pedido_login( char * pipe_cliente, int fd_server){

  char id[MAX_LEN_USER], pw[MAX_LEN_PASS];
  int tam;
  MTS_login msg;

  printf("Introduza Nome de Utilizador: ");
  scanf(" %s", id);
  printf("Introduza Password: ");
  scanf(" %s", pw);

  tam = strlen(id);
  if (tam >= MAX_LEN_USER || tam <= MIN_LEN_USER){
      printf("ERRO: Nome de Utilizador Demasiado Grande/Pequeno!\n");
      return -1;
  }
  tam=strlen(pw);
  if (tam >= MAX_LEN_PASS || tam <= MIN_LEN_PASS){
      printf("ERRO: Password demasiado Grande/Pequena!\n");
      return -1;
  }
  else  if (strcmp(id, pw) == 0){
      printf("O Nome de Utilizador e Password devem ser Diferentes!\n");
      return -1;
  }
  msg.tipo = 'l';

  // é garantido pelo DEFINE que tem o mesmo tamanho.
  strcpy(msg.pipe_name, pipe_cliente);
  strcpy(msg.user, id);
  strcpy(msg.pass, pw);

  if(write(fd_server,&msg,sizeof(msg)) == -1){
  perror("Mensagem de login nao enviada. Erro na funcao write.");
    return -1;
  }
  return 0;


}
/*
void menu(){

    int op;

    while(1){
        op=0;
        __fpurge(stdin);                  //ver necessidade, alternativas e outros erros de input nesta func que possam existir.
        printf("\n1- Login\n2- Registar\n3- Sair\nOpcao: ");
        scanf("%d", &op);

        if(op == 1)
            //pedido_login();
        if(op == 2)
            //pedido_registo();
        if(op == 3)
            exit(0);
    }
}
*/


/*
no server:

gravar pid de clientes ligados  ->  salvaguardar que nenhum outro programa escreve para a pipe.
          explicaçao: os clientes enviao primeiro que tudo o pid e o server faz o save.
          só e validado o passo de login se o pid já existir

ver melhor a diferença entre o close e unlink.

*/

/*
questions:
confirmar a mascara dos mkfifo cli e serv
Só o server regista, certo?
qual o valor minimo para o pid?


----------------

ver variavel de ambiente NMAXPLAY 20


*/
