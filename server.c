/*
    Para compilar no terminal use:
    gcc server.c -lpthread -o server
    ./server 31000
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
        pthread_join(thread_id, NULL);
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
    int checkOk1, checkOk2, cont;
    char auxiliarNome[2][TAMSG], mensagem[TAMSG];
    char cordX[TAMSG], cordY[TAMSG];
    
    //RECEBE NOME DO JOGADOR 1 E ENVIA PARA O JOGADOR 2
    strcpy(auxiliarNome[1], "Aguardando Nome");
	send(jogoIniciado[0].listSock[0], auxiliarNome[1], TAMSG, 0);                   //ENVIA SUA VEZ 
    verificaUsuario(recv(jogoIniciado[0].listSock[0], auxiliarNome[0], TAMSG, 0));  //RECEBE NOME DE USUARIO   
	
    send(jogoIniciado[0].listSock[1], auxiliarNome[0], TAMSG, 0);  
    printf("\n Mensagem 1 = %s", auxiliarNome[0]);
    //RECEBE O NOME DO JOGADOR 2 E ENVIA PARA O JOGADOR 1
    verificaUsuario(recv(jogoIniciado[0].listSock[1], auxiliarNome[1], TAMSG, 0));  //RECEBE NOME DE USUARIO                           
	send(jogoIniciado[0].listSock[0], auxiliarNome[1], TAMSG, 0);     
    printf("\n Mensagem 2 = %s", auxiliarNome[1]);

    
    //ENVIA OK E RECEBE O MAPA DO JOGADOR 1
    strcpy(mensagem, "OK MAPA");
	write(jogoIniciado[0].listSock[0], mensagem, TAMSG);                          //  ENVIA OK JOGADOR 1                            
    for(cont = 0; cont < larguraMAX; cont++)
    {
        read(jogoIniciado[0].listSock[0], (declaraMapa*)&mapaJodadorUm->Mapa[cont], sizeof(mapaJodadorUm->Mapa[cont])); //  RECEBE MATRIZ MAPA JOGADOR 1         
    }
    read(jogoIniciado[0].listSock[0], (declaraMapa*)&mapaJodadorUm->navioUsado, sizeof(mapaJodadorUm->navioUsado));
    read(jogoIniciado[0].listSock[0], (declaraMapa*)&mapaJodadorUm->Total, sizeof(mapaJodadorUm->Total));
    printf("\nJOGADOR 1\n");    
    mostraMapa(mapaJodadorUm);                                                      //  IMPRIME MAPA JOGADOR 1
    
    //ENVIA OK E RECEBE O MAPA DO JOGADOR 2
    strcpy(mensagem, "OK MAPA");
	send(jogoIniciado[0].listSock[1], mensagem, TAMSG, 0);                          //  ENVIA OK JOGADOR 1                            
    for(cont = 0; cont < larguraMAX; cont++)
    {
        read(jogoIniciado[0].listSock[1], (declaraMapa*)&mapaJodadorDois->Mapa[cont], sizeof(mapaJodadorDois->Mapa[cont])); //  RECEBE MATRIZ MAPA JOGADOR 1         
    }
    read(jogoIniciado[0].listSock[1], (declaraMapa*)&mapaJodadorDois->navioUsado, sizeof(mapaJodadorDois->navioUsado));
    read(jogoIniciado[0].listSock[1], (declaraMapa*)&mapaJodadorDois->Total, sizeof(mapaJodadorDois->Total));
    printf("\nJOGADOR 2\n");    
    mostraMapa(mapaJodadorDois);       
    
    declaraAtaque recebeAtaque;
    int aux = 0, aux2 = 1, checkOk; 
    while(1)
    {
        strcpy(mensagem, "SUA VEZ");  
        write(jogoIniciado[0].listSock[aux], mensagem, TAMSG);
        verificaUsuario(recv(jogoIniciado[0].listSock[aux], (declaraAtaque*)&recebeAtaque, sizeof(declaraAtaque), 0));
        if(aux == 0)
        {
            checkOk = atacaBarco(mapaJodadorDois, recebeAtaque.cordX, recebeAtaque.cordY);
            recebeAtaque.Celula = mapaJodadorDois->Mapa[recebeAtaque.cordY][recebeAtaque.cordX];
            
            write(jogoIniciado[0].listSock[aux], (declaraAtaque*)&recebeAtaque, sizeof(recebeAtaque));
            verificaUsuario(recv(jogoIniciado[0].listSock[aux], cordX, TAMSG, 0));
            
            strcpy(mensagem, "VEZ OUTRO"); 
            send(jogoIniciado[0].listSock[aux2], mensagem, sizeof(mensagem), 0);    
            write(jogoIniciado[0].listSock[aux2], (declaraAtaque*)&recebeAtaque, sizeof(recebeAtaque));
            
            verificaUsuario(recv(jogoIniciado[0].listSock[aux2], cordX, TAMSG, 0));
        }
        else
        {
            checkOk = atacaBarco(mapaJodadorUm, recebeAtaque.cordX, recebeAtaque.cordY);
            recebeAtaque.Celula = mapaJodadorUm->Mapa[recebeAtaque.cordY][recebeAtaque.cordX];
            
            write(jogoIniciado[0].listSock[aux], (declaraAtaque*)&recebeAtaque, sizeof(recebeAtaque));
            verificaUsuario(recv(jogoIniciado[0].listSock[aux], cordX, TAMSG, 0));
            
            strcpy(mensagem, "VEZ OUTRO"); 
            send(jogoIniciado[0].listSock[aux2], mensagem, sizeof(mensagem), 0);    
            write(jogoIniciado[0].listSock[aux2], (declaraAtaque*)&recebeAtaque, sizeof(recebeAtaque));
            
            verificaUsuario(recv(jogoIniciado[0].listSock[aux2], cordX, TAMSG, 0));
        }
        printf("\nJOGADOR 1\n");    
        mostraMapa(mapaJodadorUm); 
        printf("\nJOGADOR 2\n");    
        mostraMapa(mapaJodadorDois);
        if(aux == 0)
        {
            aux = 1;
            aux2 = 0;
        }
        else
        {
            aux = 0;
            aux2 = 1;
        }
		if(confereMapa(mapaJodadorUm) == 0)
		{
			imprimeVERMELHO("\nJOGADOR 2 VENCEU\n\n");
            strcpy(mensagem, "VOCE VENCEU"); 
			write(jogoIniciado[0].listSock[1], mensagem, sizeof(mensagem));
            strcpy(mensagem, "VOCE PERDEU"); 
			write(jogoIniciado[0].listSock[0], mensagem, sizeof(mensagem));
            return 0;
		}
		else if(confereMapa(mapaJodadorDois) == 0)
		{
			imprimeVERMELHO("\nJOGADOR 1 VENCEU\n\n"); 
            strcpy(mensagem, "VOCE VENCEU"); 
			write(jogoIniciado[0].listSock[0], mensagem, sizeof(mensagem));
            strcpy(mensagem, "VOCE PERDEU"); 
			write(jogoIniciado[0].listSock[1], mensagem, sizeof(mensagem));
            return 0;
		}
        else
        {
            strcpy(mensagem, "AINDA N"); 
            write(jogoIniciado[0].listSock[0], mensagem, TAMSG);
            write(jogoIniciado[0].listSock[1], mensagem, TAMSG);
        }
        //if()
    }
    return 0;
}