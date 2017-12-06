
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
// defines cliente
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

typedef struct cliente_jogo{
    //pid_cliente
    //id_pipe
    int bin_info; // int unico com info de n_bombas, bombinhas, vidas
    int pontuacao;
    char carater_boneco;
    //id_sessao?
    p_Cliente next_cliente;
}Cliente;

typedef struct msg_to_server_1{
    char tipo;
    int pid;
    char msg1[MAX_MSG];
}MTS1;
typedef struct msg_to_server_2{
    char tipo;
    int pid;
    char msg1[MAX_MSG];
    char msg2[MAX_MSG];
}MTS2;
//mapa
//inimigo
