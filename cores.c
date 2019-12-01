#include "cores.h"

void corReseta ();
void corVermelha();
void corVerde();
void corAmarela();
void corAzul();
void corRoxa();
void corCiano();
void imprimeCor(char *Texto, int codCor);   //imprimeCor(Variavel , codCor); 31 - Vermelho /32 - Verde/33 - Amarelo/34 - Azul/35 - Roxa/36 - Ciano


void corReseta () 
{
  printf(" \x1b[0m");
}
void corVermelha()
{
  printf("\x1b\031[1;31m ");
}
void corVerde()
{
  printf("\x1b\032[1;32m ");
}
void corAmarela()
{
  printf("\x1b\033[1;33m");
}
void corAzul()
{
  printf("\x1b\034[1;34m");
}
void corRoxa()
{
  printf("\x1b\035[1;35m");
}
void corCiano()
{
  printf("\x1b\036[1;36m");
}
void imprimeCor(char *Texto, int codCor)
{
    //printf("\n");
    switch(codCor)
    {
        case 31:
            corVermelha();
            printf("%s", Texto);
            corReseta();
            break;
        case 32:
            corVerde();
            printf("%s", Texto);
            corReseta();
            break;
        case 33:
            corAmarela();
            printf("%s", Texto);
            corReseta();
            break;
        case 34:
            corAzul();
            printf("%s", Texto);
            corReseta();
            break;
        case 35:
            corRoxa();
            printf("%s", Texto);
            corReseta();
            break;
        case 36:
            corCiano();
            printf("%s", Texto);
            corReseta();
            break;
    }
    //printf("\n");
}