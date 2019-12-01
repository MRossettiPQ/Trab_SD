#include "bibliotecas.h"
#include "cores.h"
#include "cores.c"

//FUNÇÕES UTILIZADAS NO TRABALHO
    //FUNÇÃO DE BEM-VINDO
    void        bemVindo            ();
    //FUNÇÕES DO MAPA
    int         confereMapa         (declaraMapa *mapaDeclarado);
    void        mostraBarcos        (declaraMapa *mapaDeclarado);
    int         mostraMapa          (declaraMapa *mapaDeclarado);
    declaraMapa *criaMapa           ();
    declaraMapa *alocaMatriz        ();
    //FUNÇÕES DOS BARCOS
    int         atacaBarco          (declaraMapa *mapaAtacado, int cordX, int cordY);
    int         insereBarco         (declaraMapa *mapaDeclarado, int Barco, int cordX, int cordY, int orientacao);
    int         verificaBarcoUsado  (declaraMapa *mapaDeclarado);


void bemVindo                       ()
{
    system("clear");
    imprimeAMARELO("/////////////////////////////////////////////////////////\n")
    imprimeAMARELO("//                    BATALHA NAVAL                    //\n");
    imprimeAMARELO("//                        EQUIPE                       //\n");
    imprimeAMARELO("//                     ANDREI SAVI                     //\n");
    imprimeAMARELO("//                    BRUNO PAULINO                    //\n");
    imprimeAMARELO("//                  MATHEUS ROSSETTI                   //\n");
    imprimeAMARELO("//                    RIAN TURIBIO                     //\n");
    imprimeAMARELO("/////////////////////////////////////////////////////////\n")
    printf("\nAguarde\n");
}
int atacaBarco                      (declaraMapa *mapaAtacado, int cordX, int cordY)
{
    //Verifica se o ataque foi dentro do mapa designado
    if (cordX > mapaAtacado->Largura || cordX < 0 || cordY > mapaAtacado->Largura || cordY < 0)
    {
        return -1;
    }

    //Verifica se o ataque foi em um navio ou no mar
    if (mapaAtacado->Mapa[cordY][cordX] == NAVIO || mapaAtacado->Mapa[cordY][cordX] == ACERTOU)
    {
        mapaAtacado->Mapa[cordY][cordX] = ACERTOU;
        return 1;
    }
    else {
        mapaAtacado->Mapa[cordY][cordX] = ERROU;
        return 0;
    }
}
int insereBarco                     (declaraMapa *mapaDeclarado, int Barco, int cordX, int cordY, int orientacao)
{
    int aux, Tamanho;

    switch(Barco)
    {
        case PORTAVIAO:
            Tamanho = tamanhoPORTAVIAO;
            break;
        case ENCOURACADO:
            Tamanho = tamanhoENCOURACADO;
            break;
        case SUBMARINO:
            Tamanho = tamanhoSUBMARINO;
            break;
        case PATRULHA:
            Tamanho = tamanhoPATRULHA;
            break;
    }

    if (orientacao == VERTICAL)
    {
        if (cordX >= mapaDeclarado->Altura || cordY + Tamanho - 1 >= mapaDeclarado->Largura)
        {
            return -1;
        }
    }

    if (orientacao == HORIZONTAL)
    {
        if (cordY >= mapaDeclarado->Largura || cordX + Tamanho - 1 >= mapaDeclarado->Altura)
        {
            return -1;
        }
    }

    if (orientacao == VERTICAL)
    {
        for (aux = cordY; aux < cordY + Tamanho; aux++)
        {
            if (mapaDeclarado->Mapa[aux][cordX] != 0)
            {
                return -1;
            }
        }

        for (aux = cordY; aux < cordY + Tamanho; aux++)
        {
                mapaDeclarado->Mapa[aux][cordX] = NAVIO;
        }
    }

    if (orientacao == HORIZONTAL)
    {
        
        for (aux = cordX; aux < cordX + Tamanho; aux++)
        {
            
            if (mapaDeclarado->Mapa[cordY][aux] != 0)
            {
                return -1;
            }
        }
        for (aux = cordX; aux < cordX + Tamanho; aux++)
        {
            mapaDeclarado->Mapa[cordY][aux] = NAVIO;
        }
    }
    mapaDeclarado->navioUsado[Barco]--;
    return 0;
}
int verificaBarcoUsado              (declaraMapa *mapaDeclarado)
{
    int aux, procura = 0;

    for (aux = 0; aux < sizeof(mapaDeclarado->navioUsado)/sizeof(int); aux++)
    {
        if (mapaDeclarado->navioUsado[aux] > 0)
        {
            procura += mapaDeclarado->navioUsado[aux];
        }
    }
    return procura;
}
void mostraBarcos                   (declaraMapa *mapaDeclarado)
{
    int cordX;

    printf("Size:\t\t\t\t");
    for(cordX = 0; cordX < tamanhoMAIORNAVIO; cordX++)
    {
        printf("  %i", cordX + 1);
    }
    printf("\n");
    
    printf("0) Porta avião (%i)\t\t", mapaDeclarado->navioUsado[0]);
    for(cordX = 0; cordX < tamanhoPORTAVIAO; cordX++) 
    {
        imprimeVERDE("  O");
    }

    printf("\n1) Encouraçado (%i)\t\t", mapaDeclarado->navioUsado[1]);
    for(cordX = 0; cordX < tamanhoENCOURACADO; cordX++) 
    {
        imprimeVERDE("  O");
    }
    for(cordX = 0; cordX < (tamanhoMAIORNAVIO - tamanhoENCOURACADO); cordX++) 
    {
        imprimeAZUL("  ~");
    }

    printf("\n2) Submarino (%i)\t\t", mapaDeclarado->navioUsado[2]);
    for(cordX = 0; cordX < tamanhoSUBMARINO; cordX++) 
    {
        imprimeVERDE("  O");
    }
    for(cordX = 0; cordX < (tamanhoMAIORNAVIO - tamanhoSUBMARINO); cordX++) 
    {
        imprimeAZUL("  ~");
    }

    printf("\n3) Patrulha oceanica (%i)\t", mapaDeclarado->navioUsado[3]);
    for(cordX = 0; cordX < tamanhoPATRULHA; cordX++) 
    {
        imprimeVERDE("  O");
    }
    for(cordX = 0; cordX < (tamanhoMAIORNAVIO - tamanhoPATRULHA); cordX++) 
    {
        imprimeAZUL("  ~");
    }
    printf("\n\n");

    /*
        PARA CADA NOVO TIPO DE EMBARACAÇÃO ADICIONADA DEVERA SERA ADICIONADO UMA DUPLA DE REPETIÇÃO (IGUAL AS DE CIMA) PARA IMPRIMIR A TELA COM SEU TAMANHO
    */
}
int confereMapa                     (declaraMapa *mapaDeclarado)
{
    int cordY, cordX;

    for(cordY = 0; cordY < mapaDeclarado->Largura; cordY++)
    {
        for(cordX = 0; cordX < mapaDeclarado->Altura; cordX++)
        {
            if (mapaDeclarado->Mapa[cordY][cordX] == NAVIO)
            {    
                return 1;
            }
        }
    }
    return 0;
}
int mostraMapa                      (declaraMapa *mapaDeclarado)
{
    int cordY, cordX;

    //IMPRIME A PRIMEIRA LINHA DO MAPA: AS POSIÇÕES
    printf("\t y\\x ");
    for (cordX = 0; cordX < larguraMAX; cordX++)
    {
        if (cordX < larguraMAX)
        {        
            printf("%i  ", cordX);
        }    
        else
        {    
            printf("%i ", cordX);
        }
    }
    //IMPRIME O MAPA: SE É MAR OU NAVIO
    for (cordY = 0; cordY < alturaMAX; cordY++)
    {
        printf("\n\t");
        // IMPRIME A COLUNA DAS COORDENADAS
        if (cordY < alturaMAX)
        {
            printf("  %i", cordY);
        }
        else
        {
            printf(" %i", cordY);
        }

        for (cordX = 0; cordX < larguraMAX; cordX++)
        {
            switch(mapaDeclarado->Mapa[cordY][cordX])
            {
                case AGUA:
                    imprimeAZUL("  ~");
                    break;
                case ERROU:
                    imprimeVERMELHO("  ~");
                    break;
                case NAVIO:
                    imprimeVERDE("  O");
                    break;
                case ACERTOU:
                    imprimeVERMELHO("  X");
                    break;
                default:
                    printf("  ?");
                    break;
            }
        }
    }
    printf("\n");
}
declaraMapa *alocaMatriz            ()
{
    declaraMapa *mapaIniciado = malloc(sizeof(declaraMapa));
    int cordX, cordY;

    mapaIniciado->Largura = larguraMAX;
    mapaIniciado->Altura = alturaMAX;

    mapaIniciado->Mapa = malloc(larguraMAX * sizeof(int *));

    for(cordX=0; cordX < mapaIniciado->Largura; cordX++)
    {
        mapaIniciado->Mapa[cordX] = malloc(alturaMAX * sizeof(int));
        for(cordY=0; cordY < mapaIniciado->Altura; cordY++)
        {
            mapaIniciado->Mapa[cordX][cordY] = 0;
        }
    }

    mapaIniciado->navioUsado[0] = qtdPORTAVIAO;
    mapaIniciado->navioUsado[1] = qtdENCOURACADO;
    mapaIniciado->navioUsado[2] = qtdSUBMARINO;
    mapaIniciado->navioUsado[3] = qtdPATRULHA;

    return mapaIniciado;
}
declaraMapa *criaMapa               ()
{
    declaraMapa *mapaJogo = alocaMatriz();
    int aux, Barquinho, orientacao, cordX, cordY;
    while((aux = verificaBarcoUsado(mapaJogo)) > 0)
    {
        // Mostra barco e mapa
        mostraMapa(mapaJogo);
        mostraBarcos(mapaJogo);

        printf("Você tem %i navios(s) para organizar\n", aux);
        printf("Escolha um modelo para adicionar ao mapa: ");
        scanf("%i", &Barquinho);
        while(Barquinho > 3 || Barquinho < 0 || mapaJogo->navioUsado[Barquinho] == 0)
        {
            printf("Modelo invalido\n");
            printf("Escolha outro modelo: ");
                scanf("%i", &Barquinho);
        }

        printf("Orientação da embarcação (1-vert/2-hori): ");
        scanf("%i", &orientacao);
        while(orientacao != 1 && orientacao != 2)
        {
            printf("Orientação invalida\n");
            printf("Escolha outra orientação: ");
            scanf("%i", &orientacao);
        }

        printf("Posição da ponta do navio\n");
        printf("CordX: ");
        scanf("%i", &cordX);
        while(cordX > mapaJogo->Largura || cordX < 0)
        {
            imprimeVERMELHO("Coordenada invalida\n");
                printf("Escolha outra Coordenada X: ");
                scanf("%i", &cordX);
        }

        printf("CordY: ");
        scanf("%i", &cordY);
        while(cordY > mapaJogo->Altura || cordY < 0)
        {
            imprimeVERMELHO("Coordenada invalida\n");
                printf("Escolha outra Coordenada Y: ");
                scanf("%i", &cordY);
        }
        
        //system("clear");
        if (insereBarco(mapaJogo, Barquinho, cordX, cordY, orientacao) == -1)
        {
            imprimeVERMELHO("\nJá existe navio nessa posição!\nTente em outra...\n\n");
        }
    }

    imprimeAMARELO("\nNavios ao Mar, prepare-se para a batalha!\n");
    return mapaJogo;
}