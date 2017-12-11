
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio_ext.h>
#include <fcntl.h>      // para uso dos open, por exemplo

#include <signal.h>
#include <sys/stat.h>
#include <sys/types.h>


// defines server
#define PIPE_DO_SERVIDOR "Server_Pipe"
#define NMAXPLAY 20           // pode ser alterado entre 1 e 20 (enunciado projeto).
// defines cliente
#define TAM_ARRAY_PIPE_CLI 11 // garante funcionamento em sist. unix de 32 bits. (max pid = 32678)
#define MAX 100
#define MIN 100
#define MAX_LEN_USER 40
#define MIN_LEN_USER 3
#define MAX_LEN_PASS 40
#define MIN_LEN_PASS 5
// defines structs
#define MAX_MSG 50


typedef struct cliente_jogo *p_Cliente;

typedef struct info_inicial{
    //jogadores registados -- em memoria ou leitura ao ficheiro quando necessario
    //mapas                -- em memoria ou leitura de ficheiro quando necessario
}info;

typedef struct sessao_jogo{
    int id_sessao;
    // struct ou var mapa
    // p_Cliente           --lista de jogadores (estrutura jogadores)
    // time?
}Sessao;

typedef struct clientes_com_login{
  char pipe_name[TAM_ARRAY_PIPE_CLI];
  int fd;
}cli_online;

typedef struct cliente_jogo{
    int pid_cliente;
    //id_pipe
    int bin_info; // int unico com info de n_bombas, bombinhas, vidas
    int pontuacao;
    char carater_boneco;
    //id_sessao?
    p_Cliente next_cliente;
}Cliente;

// Estruturas de envio e respetivas de recebimento (cliente > servidor)
typedef struct msg_to_server_1{
    char tipo;
    int pid;
    char msg1[MAX_MSG];
}MTS1;
typedef struct msg_fom_cliente_1{
    int pid;
    char msg1[MAX_MSG];
}MFC1;
typedef struct msg_to_server_2{
    char tipo;
    int pid;
    char msg1[MAX_MSG];
    char msg2[MAX_MSG];
}MTS2;
typedef struct msg_from_cliente_2{
    int pid;
    char msg1[MAX_MSG];
    char msg2[MAX_MSG];
}MFC2;
//mapa
//inimigo

// -------  Login ---------
typedef struct msg_to_server_login{
  char tipo;
  char pipe_name[TAM_ARRAY_PIPE_CLI];
  char user[MAX_LEN_USER];
  char pass[MAX_LEN_PASS];
}MTS_login;
typedef struct msg_from_cliente_login{
  char pipe_name[TAM_ARRAY_PIPE_CLI];
  char user[MAX_LEN_USER];
  char pass[MAX_LEN_PASS];
}MFC_login;



/*

Notas para o relatorio:

- falta proteger o scanf no pedido_login do cliente.

- o setbuff é apenas necessario na main ou nas outras func chamadas?

- no ciclo de leitura do servidor. nao sei o motivo. é enviado algo após cada mensagem?

- proteção input, estao defindas constantes, no input é garantido que as string têm TAM_DEFINED - 1.

- how to put pipe files in a temp folder para serem removidos com exit

- No caso de haver leitura nos reads ou writes, nomeadamente no server, eu encerro a app e enviao
  uma mensagem de erro, dado a leitura em ciclo e possiveis erros geradas apartir dai. Está correto
  deste modo ou devo garantir que continua a ler corretamente?

- limitação de pid's até 32768

-ver se os max len dos vetores contam com o \0. ou fazer -1 ou
  aceitar fazer if < MAX_LEN_USER..




*/
