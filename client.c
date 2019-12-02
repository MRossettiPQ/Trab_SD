//TESTE DE CLIENTE
/*
    Para compilar no terminal use:
    gcc client.c -lpthread -o client
    ./client 127.0.0.1 31000
	Cliente Simples Para Servidor com Thread
*/
#include "bibliotecas.h"
#include "bibliotecas.c"

int main(int argc, char *argv[])
	{
    	printf("\n IP - %s : %s\n", argv[1], argv[2]);
    	declaraMapa *mapaJodadorUm = alocaMatriz();   //TABULEIRO DO JOGADOR DOIS
		
    	int i, Barcos, cordX, cordY, orientation, checkOk; // Ship insertion
		int fimJogo;

	 	int sock_conn, val, aux, cont, read_size;
		struct sockaddr_in client_addr;
		char mensagem[TAMSG], auxiliarNome[2][TAMSG];

		sock_conn = socket(AF_INET, SOCK_STREAM, 0);

		client_addr.sin_family = AF_INET;
		int addr = atoi(argv[1]), port = atoi(argv[2]);
		client_addr.sin_addr.s_addr = inet_addr(argv[1]); 
		client_addr.sin_port = htons(port);

		if(connect(sock_conn, (struct sockaddr*)&client_addr, sizeof(client_addr)) == 0)
        {
			printf("Conexão estabalecida com o servidor !! \n");
        }
		else
        {
			printf("Falha ao conectar no servidor !\n");
        }      
		

		bemVindo();
		checkOk = recv(sock_conn, mensagem, TAMSG, 0);        
		printf("Conectou: %s\n\n", mensagem);
		printf("Seu nome no jogo: ");
		fgets(mensagem, 30, stdin);
		if (mensagem[strlen(mensagem) - 1] == '\n')
		{
			mensagem[strlen(mensagem) - 1] = '\0';
		}
		strcpy(auxiliarNome[0], mensagem);
		system("clear");
		send(sock_conn, mensagem, TAMSG, 0);                         	//ENVIA SUA VEZ 
    	printf("\nAguarde sua vez!!\n");

		checkOk = recv(sock_conn, mensagem, TAMSG, 0);         			//RECEBE OK
		
		mapaJodadorUm = criaMapa();										//JOGADOR ADICIONA SUAS PEÇAS
		printf("\nMAPA ADICIONADO FOI\n");
		mostraMapa(mapaJodadorUm);
		
		//send(sock_conn, (declaraMapa*)&mapaJodadorUm, sizeof(declaraMapa), 0);
		for(cont = 0; cont < larguraMAX; cont++)
		{
			send(sock_conn, (declaraMapa*)&mapaJodadorUm->Mapa[cont], sizeof(mapaJodadorUm->Mapa[cont]), 0); //  RECEBE MATRIZ MAPA JOGADOR 1     
		}
		send(sock_conn, (declaraMapa*)&mapaJodadorUm->navioUsado, sizeof(mapaJodadorUm->navioUsado), 0);
		send(sock_conn, (declaraMapa*)&mapaJodadorUm->Total, sizeof(mapaJodadorUm->Total), 0);
	while(1)
	{  
		send(sock_conn, mensagem, TAMSG, 0);							//RECEBE OK

		printf("\nAtacado na Cordenada X/Y: %s", mensagem);

		printf("\nDigite a Cordenada X/Y: ");
		fgets(mensagem, 30, stdin);
		if (mensagem[strlen(mensagem) - 1] == '\n')
		{
			mensagem[strlen(mensagem) - 1] = '\0';
		}
		checkOk = recv(sock_conn, mensagem, TAMSG, 0);
	}
	system("clear");		
	return 0;	
}