/*
    Para compilar no terminal use:
    gcc server.c -lpthread -o server
    Servidor para Thread
*/
#include "bibliotecas.h"
#include "bibliotecas.c"


//Declaração função que usara thread
void        *jogoBatalha                                    (void *);

int main(int argc, char *argv[])
{
    int socket_desc , client_sock , aux;
    struct sockaddr_in server , client;
     
    //Criar o socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Não foi possível criar o soquete");
    }
    imprimeROXO("\nSocket criado");
    printf("\nPORTA USADA: \x1b\031[1;31m %s \x1b[0m\n", argv[1]);
    
    //Preparar o sockaddr_in em uma estrutura
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(atoi(argv[1]));

    //Conectar com servidor
    if(bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("Error: Conexão falhou");
        return 1;
    }
    puts("Conexão com sucesso");
     
    //Aguarda conexão
    listen(socket_desc , USERMAX);                                                                  //Numero maximo de conexões    
    puts("Esperando por entradas das conexões");
    aux = sizeof(struct sockaddr_in);
    listaSocket jogosIniciados[USERMAX/2];
	pthread_t thread_id;
	int cont;
    
    while((jogosIniciados[0].listSock[0]  = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&aux)))
    {
        imprimeVERDE("\nConexão foi aceita!!");
        jogosIniciados[0].listSock[1] = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&aux);
        imprimeVERDE("\nConexão foi aceita!!");
        if(pthread_create(&thread_id, NULL,  jogoBatalha, (void*)&jogosIniciados) < 0)
        {
            perror("Não foi possível criar a thread");
            return 1;
        }
    }
	if (socket_desc < 0)
    {
        perror("Falhou em se conectar!!");
        return 1;
    }
     
    return 0;
}

void *jogoBatalha(void *socket_desc)
{
    listaSocket *jogoIniciado    = (struct listaSocket *)socket_desc;
    declaraMapa *mapaJodadorUm   = alocaMatriz();
    declaraMapa *mapaJodadorDois = alocaMatriz();
    pthread_mutex_t mutex;

    int checkOk1, checkOk2;
    char auxiliarNome[2][TAMSG], *mensagem  = malloc(sizeof(char)*TAMSG);
    
    
    strcpy(auxiliarNome[0], "Aguardando Nome");
    strcpy(mensagem, auxiliarNome[0]);

	send(jogoIniciado[0].listSock[0], mensagem, TAMSG, 0);                          //ENVIA SUA VEZ 
    checkOk1 = recv(jogoIniciado[0].listSock[0], mensagem, TAMSG, 0);                          //RECEBE NOME DE USUARIO   
    strcpy(auxiliarNome[1], mensagem);
    printf("\n Mensagem 1 = %s", mensagem);

	send(jogoIniciado[0].listSock[1], mensagem, TAMSG, 0);                          //ENVIA SUA VEZ
    checkOk2 = recv(jogoIniciado[0].listSock[1], mensagem, TAMSG, 0);                          //RECEBE NOME DE USUARIO                           
    strcpy(auxiliarNome[0], mensagem);
    printf("\n Mensagem 2 = %s", mensagem);
    strcpy(mensagem, "OK");

    //ENVIA OK E RECEBE O MAPA DO JOGADOR 1
	send(jogoIniciado[0].listSock[0], mensagem, TAMSG, 0);                          //  ENVIA OK JOGADOR 1                        
    
    
    checkOk1 = recv(jogoIniciado[0].listSock[0], mapaJodadorUm, sizeof(mapaJodadorUm), 0); //  RECEBE MATRIZ MAPA JOGADOR 1     
    printf("\nJOGADOR 1\n");    
    mostraMapa(mapaJodadorUm);                                                      //  IMPRIME MAPA JOGADOR 1
    

    //ENVIA OK E RECEBE O MAPA DO JOGADOR 2
	send(jogoIniciado[0].listSock[1], mensagem, TAMSG, 0);                          //  ENVIA OK JOGADOR 2
    checkOk2 = recv(jogoIniciado[0].listSock[1], mapaJodadorDois, sizeof(mapaJodadorDois), 0); //  RECEBE MATRIZ MAPA JOGADOR 2
    printf("\nJOGADOR 2\n");   
    mostraMapa(mapaJodadorDois);                                                    //  IMPRIME MAPA JOGADOR 2
 

    strcpy(mensagem, "OK");                                                         //  ENVIA OK JOGADOR 1
    send(jogoIniciado[0].listSock[1], mensagem, TAMSG, 0); 
    int aux = 0, aux2 = 1; 
    while(1)
    {  
        recv(jogoIniciado[0].listSock[aux], mensagem, TAMSG, 0);                       //  ENVIA OK JOGADOR 1
        send(jogoIniciado[0].listSock[aux2], mensagem, TAMSG, 0); 
        printf("\nRECEBEU A COORDENADA: %s", mensagem);
        
        if(aux == 0)
        {
            aux = 1; 
            aux2 = 0;
        }
        else
        {
            aux2 = 1;
            aux = 0; 
        }
    }

    if((checkOk1 == 0) || (checkOk2 == 0))
    {
        puts("\nCliente foi desconectado");
        fflush(stdout);
        pthread_exit(NULL);
    }
    else if((checkOk1 == -1) || (checkOk2 == -1))
    {
        perror("\nReceber do Cliente Falhou");
    }
    return 0;
}