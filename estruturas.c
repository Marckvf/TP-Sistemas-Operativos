




typedef struct cliente_jogo *p_Cliente;

typedef struct info_inicial{
    //jogadores registados -- em memoria ou leitura ao ficheiro quando necessario
    //mapas                -- em memoria ou leitura de ficheiro quando necessario
} 

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
    p_cliente next_cliente;
}Cliente;


//mapa
//inimigo



