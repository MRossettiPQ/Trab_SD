#ifndef BIBLIOTECAS_H   // Guardas de cabeçalho, impedem inclusões cíclicas
    //Bibliotecas de apoio para o codigo
    #include <stdio.h>                          //  CABEÇALHO PADRÃO DE ENTRADAS E SAIDAS
    #include <string.h>                         //  FUNÇÕES DE MANIPULAÇÃO DE STRING: strlen(), strcpy(), strcpm()
    #include <stdlib.h>                         //  POSSUI FUNÇÕES PARA MANIPULAR MEMORIA: malloc(), atoi(), system(), exit
    #include <unistd.h>                         //  POSSUI UMA API PARA ACESSO A FUNÇÕES POSIX: read(), write(), close(). ENVIO DE MENSAGEM POR SOCKET
    #include <sys/socket.h>                     //  MACROS USADOS PARA CRIAÇÃO DE UM CANAL DE COMUNICAÇÃO: bind(), connect(), accept()
    #include <arpa/inet.h>                      //  MACRO UTILIZADO PARA DEFINIR O PROTOCOLO DE CONEXÃO, UTILIZADO NO CLIENTE (APENAS CONECTA APOS ESTE PROCURAR A CONEXÃO, NÃO PODE SER ENCONTRADO PELO SERVIDOR)
    #include <netinet/in.h>                     //  MACRO UTILIZADO PARA DEFINIR O PROTOCOLO DE CONEXÃO, UTILIZADO NO SERVIDOR 
    #include <netdb.h>                          //  MACROS PARA REDE DE BANCO DE DADOS: h_addrtype  
    #include <sys/wait.h>	                    //  MACROS PARA FUNÇÕES DE ESPERA: waitpid ()
    #include <pthread.h>                        //  USADO PARA CRIAR THREADS, PROCESSAMENTO MULTITAREFA, LINK PARA <lpthread.h>
    #include <sys/types.h>                      //  OUTROS MACROS USADOS PARA FUNÇÕES POSIX
    #include <sys/uio.h>

    //TABULEIROS E TAMANHO DA PARTIDA
    #define larguraMAX          10              //  DEFINE A LARGURA QUE O TABULEIRO TERÁ
    #define alturaMAX           10              //  DEFINE A ALTURA QUE O TABULEIRO TERÁ
    #define TAMSG               500             //  DEFINE O TAMANHO QUE AS MENSAGENS TROCADAS TERÃO
    #define TAMNOME             50              //  DEFINE O TAMANHO MAXIMO QUE UM USERNAME PODE TERÁ
    #define USERMAX             10              //  DEFINE QUANTIDA MAXIMA DE USUARIO QUE O SERVIDOR PODERÁ RECEBER, USAR MULTIPLO DE MAXUSRJOGO (MAXUSRJOGO * (NUMERO DE PARTIDAS NECESSARIAS)) PARA HAVER POSSIBILIDADES DE DUPLAS
    #define MAXUSRJOGO          2               //  DEFINE A QUANTIDADE DE JOGADORES QUE PODERÃO SE CONECTAR NA PARTIDA
    #define NRMAPA              1

    //CONFIGURAÇÃO DOS BARCOS
    #define TIPOSNAVIO          4               //  QUANTIDADE DE MODELOS DE NAVIO
    #define PORTAVIAO           0               //  MODELO 0
    #define ENCOURACADO         1               //  MODELO 1
    #define SUBMARINO           2               //  MODELO 2
    #define PATRULHA            3               //  MODELO 3

    #define tamanhoMAIORNAVIO   5               //  USAR O TAMANHO DO MAIOR NAVIO
    #define tamanhoPORTAVIAO    5               //  TAMANHO DE CASAS OCUPADAS PELO PORTAVIAO
    #define tamanhoENCOURACADO  4               //  TAMANHO DE CASAS OCUPADAS PELO ENCOURACADO  
    #define tamanhoSUBMARINO    3               //  TAMANHO DE CASAS OCUPADAS PELO SUBMARINO  
    #define tamanhoPATRULHA     2               //  TAMANHO DE CASAS OCUPADAS PELO PATRULHA  


    #define qtdPORTAVIAO        1               //  QUANTIDADE DE PORTAVIAO NO JOGO
    #define qtdENCOURACADO      0               //1  QUANTIDADE DE ENCOURACADO  NO JOGO 
    #define qtdSUBMARINO        0               //2  QUANTIDADE DE SUBMARINO NO JOGO
    #define qtdPATRULHA         0               //2  QUANTIDADE DE PATRULHA NO JOGO


    #define VERTICAL            1               //  ORIENTAÇÃO DA IMPRESSÃO DO MODELO
    #define HORIZONTAL          2               //  ORIENTAÇÃO DA IMPRESSÃO DO MODELO

    //CONFIGURAÇÃO DO MAPA
    // Tipo de pontos no mapa
    #define AGUA                0               //  TIPO 1
    #define ERROU               1               //  TIPO 2
    #define ACERTOU             2               //  TIPO 3
    #define NAVIO               3               //  TIPO 4

    // Simbolos usados no desenho de mapa
    #define simboloAGUA         ~               //  SIMBOLO DA AGUA
    #define simboloERROU        ~               //  SIMBOLO DE ERRAR NAVIO
    #define simboloACERTOU      X               //  SIMBOLO DE ACERTAR O NAVIO
    #define simboloNAVIO        O               //  SIMBOLO DE NAVIO NA TELA DO JOGADOR

    //Conjunto de Sockets (Conexões com Clientes) Participantes de uma Partida
    typedef struct listaSocket
    {
        int listSock[MAXUSRJOGO];               //  SOCKET DE TODOS OS USUARIOS CONECTADOS A MESMA PARTIDA
    } listaSocket;
    //Conjunto de dados presente em um Tabuleiro de mapa
    typedef struct estruturaMapa
    {   
        char Mapa[alturaMAX][larguraMAX];       //  ARMAZENA O MAPA
        int navioUsado[TIPOSNAVIO];             //  TIPO DE NAVIO USADO
        int Total;                              //  QUANTIDADE DE NAVIOS RESTANTES
    } declaraMapa;
    typedef struct estruturaAtaque
    {   
        int cordX;
        int cordY;
        char Celula;
    } declaraAtaque;
#define BIBLIOTECAS_H
#endif