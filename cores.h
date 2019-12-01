#ifndef CORES_H   // Guardas de cabeçalho, impedem inclusões cíclicas
    //Bibliotecas de apoio para o codigo
    //FUNÇÕES DE IMPRESSÃO COLORIDA
    /*
        COD         CORES
        31         Vermelho
        32         Verde
        33         Amarelo
        34         Azul
        35         Roxa
        36         Ciano
        imprimeCor(Variavel , codCor); 31 - Vermelho /32 - Verde/33 - Amarelo/34 - Azul/35 - Roxa/36 - Ciano
    */

    #define imprimeVERMELHO(string)          printf("\x1b[31m%s\x1b[0m", string);
    #define imprimeVERDE(string)             printf("\x1b[32m%s\x1b[0m", string);
    #define imprimeAMARELO(string)           printf("\x1b[33m%s\x1b[0m", string);
    #define imprimeAZUL(string)              printf("\x1b[34m%s\x1b[0m", string);
    #define imprimeROXO(string)              printf("\x1b[35m%s\x1b[0m", string);
    #define imprimeCIANO(string)             printf("\x1b[36m%s\x1b[0m", string);

    #define tamanhoPORTAVIAO 5
    #define tamanhoENCOURACADO 4
    #define tamanhoSUBMARINO 3
    #define tamanhoPATRULHA 2

#define CORES_H
#endif