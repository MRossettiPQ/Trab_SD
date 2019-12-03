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
    	declaraMapa *mapaJodadorUm = alocaMatriz();   //TABULEIRO DO JOGADOR UM
    	declaraMapa *mapaAdversario = alocaMatriz();   //TABULEIRO DO JOGADOR DOIS
		declaraAtaque envieiAtaque;
    	int checkOk, fimJogo, sock_conn, val, aux, cont;
		char mensagem[TAMSG], auxiliarNome[2][TAMSG];
		char cordX[TAMSG], cordY[TAMSG], celula[TAMSG];;

		struct sockaddr_in client_addr;
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

		verificaUsuario(recv(sock_conn, auxiliarNome[1], TAMSG, 0));
		
		printf("Conectou a \x1b[33m%s\x1b[0m\n\nSeu nome no jogo: ", mensagem);
		fgets(auxiliarNome[0], 30, stdin);
		if (auxiliarNome[0][strlen(auxiliarNome[0]) - 1] == '\n')
		{
			auxiliarNome[0][strlen(auxiliarNome[0]) - 1] = '\0';
		}
		system("clear");
		printf("\nAguarde sua vez!!\n");                        	//ENVIA SUA VEZ 
		send(sock_conn, auxiliarNome[0], TAMSG, 0); 
		//system("clear");

		if(strcmp(auxiliarNome[1], "Aguardando Nome") == 0)
		{
			verificaUsuario(recv(sock_conn, auxiliarNome[1], TAMSG, 0)); 
		}
		//RECEBE OK PARA INICIAR MAPA
		verificaUsuario(recv(sock_conn, mensagem, TAMSG, 0));  
		if(strcmp(mensagem, "OK MAPA") == 0)
		{
			mapaJodadorUm = criaMapa();					
			for(cont = 0; cont < larguraMAX; cont++)
			{
				send(sock_conn, (declaraMapa*)&mapaJodadorUm->Mapa[cont], sizeof(mapaJodadorUm->Mapa[cont]), 0); //  RECEBE MATRIZ MAPA JOGADOR 1     
			}
			send(sock_conn, (declaraMapa*)&mapaJodadorUm->navioUsado, sizeof(mapaJodadorUm->navioUsado), 0);
			send(sock_conn, (declaraMapa*)&mapaJodadorUm->Total, sizeof(mapaJodadorUm->Total), 0);
			system("clear");
		}
		else
		{
			imprimeVERMELHO("\n\nNÃO ESTA OK PARA O MAPA");
		}
		
		imprimeVERDE("\nAguarde sua vez!!"); 
	 	read(sock_conn, mensagem, TAMSG);
		while(1)
		{
			if(confereMapa(mapaJodadorUm) == 0)
			{
				imprimeVERMELHO("\nVOCÊ PERDEU\n\n"); 
				send(sock_conn, mensagem, sizeof(mensagem), 0);
				close(sock_conn);
				exit(1);
			}
			//NOME DOS JOGADORES ENVOLVIDOS
			printf("\n\t\t");
			imprimeCIANO(auxiliarNome[0]);
			printf(" vs ");
			imprimeAMARELO(auxiliarNome[1]);
			//SEU MAPA
			printf("\n\n Seu mapa ");
			imprimeAMARELO(auxiliarNome[0]);
			printf(":\n");
			mostraMapa(mapaJodadorUm);
			//MAPA DO ADVERSARIO CONHECIDO
			printf("\n Seu adversario ");
			imprimeAMARELO(auxiliarNome[1]);
			printf(":\n");
			mostraMapa(mapaAdversario);
			//RECEBE AUTORIZAÇÂO PARA INICIAR O ATAQUE OU RECEBER ATAQUE
			verificaUsuario(read(sock_conn, mensagem, TAMSG));
			printf("\nMENSAGEM RECEBIDA: %s", mensagem);
			if(strcmp(mensagem, "SUA VEZ") == 0)
			{
				//COORDENADA X
				do
				{
					printf("\nAtaque Cord X: ");
					scanf("%s", cordX);
					if (cordX[strlen(cordX) - 1] == '\n')
					{
						cordX[strlen(cordX) - 1] = '\0';
					}
					if((atoi(cordX) > larguraMAX) && (atoi(cordX) < 0))
					{
						printf("\nCordX invalida!! Tente um valor abaixo de %i", larguraMAX);
					} 
					printf("\nAguarde o envio!!\n");                        	//ENVIA SUA VEZ 
					send(sock_conn, cordX, TAMSG, 0);
				} while((atoi(cordX) > larguraMAX) && (atoi(cordX) < 0));
				//COORDENADA Y
				do
				{
					verificaUsuario(read(sock_conn, mensagem, TAMSG));
					printf("\nAtaque Cord Y: ");
					scanf("%s", cordY);
					if (cordY[strlen(cordY) - 1] == '\n')
					{
						cordY[strlen(cordY) - 1] = '\0';
					}
					if((atoi(cordY) > larguraMAX) && (atoi(cordY) < 0))
					{
						printf("\nCordY invalida!! Tente um valor abaixo de %i", larguraMAX);
					} 
					printf("\nAguarde o envio!!\n");   
				} while((atoi(cordY) > larguraMAX) && (atoi(cordY) < 0));
				                     	//ENVIA SUA VEZ 
					send(sock_conn, cordY, TAMSG, 0);
				verificaUsuario(read(sock_conn, mensagem, TAMSG));
				mapaAdversario->Mapa[atoi(cordY)][atoi(cordX)] = mensagem[0];
				//system("clear");
				imprimeVERDE("\nAguarde pelo Ataque!");
				send(sock_conn, cordY, TAMSG, 0);
			}
			else
			{
				imprimeVERDE("\nAguarde pelo Ataque!");

				verificaUsuario(recv(sock_conn, cordX, sizeof(cordX), 0)); //X
				send(sock_conn, cordX, TAMSG, 0);
				verificaUsuario(recv(sock_conn, cordY, sizeof(cordY), 0)); 	//Y
				send(sock_conn, cordY, TAMSG, 0);
				verificaUsuario(recv(sock_conn, celula, sizeof(celula), 0)); //VALOR CELULA
				mapaJodadorUm->Mapa[atoi(cordY)][atoi(cordX)] = celula[0];
				send(sock_conn, cordY, TAMSG, 0);
				printf("\nMENSAGEM RECEBIDA CordX: %s", cordX);
				printf("\nMENSAGEM RECEBIDA CordY: %s", cordY);
				printf("\nMENSAGEM RECEBIDA Celula: %s", celula);
			}
		send(sock_conn, cordY, TAMSG, 0);
    }
	//system("clear");		
	return 0;	
}