#include "structs.h"


void menu();

int main(){
  char pipe_name[11]; // 10 elementos para ter PIPE32768 no max
  int pid = getpid();
  int fd_server = open(PIPE_DO_SERVIDOR, O_WRONLY);
  if(fd_server == -1){
    perror("Erro a abrir pipe do servidor / sem servidor. A Aplicação vai encerrar.");
    return 0;
  }
  //     ##################################################           acabar aqui!!!!!!!      #########################################################################
  if(mkfifo("fifo_cliente",0777) == -1){
    perror("Impossivel criar Fifo do Cliente.");
    close(fd_server);
    exit(1);
  }

  printf("%d\n",pid);
  if(write(fd_server,&pid,sizeof(pid)) == -1){
    perror("erro na Inicialização inicial, o programa vai encerrar.\n (Erro ao escrever PID no Pipe do servidor)");
    close(fd_server);
    return 0;
  }



  unlink("fifo_cliente");

  setbuf(stdout,NULL);
  //menu();

  return 0;
}

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
