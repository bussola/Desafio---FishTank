#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cont = 0;
int contPersonagem = 0; //Contador de cada Personagem
int totalFichas = 10;
int qntTotalPers = 6;

struct Ficha{ //For�a, Percep��o, Resist�ncia, Carisma, Intelig�ncia, Agilidade e Sorte
    char nome[20];
    char descricao[20];
    int forca;
    int percep;
    int resist;
    int caris;
    int intel;
    int agil;
    int sorte;
    int id;
};

void populaFichas(char *buffer, int size, struct Ficha Fichas[totalFichas]){

    int i;

    char primeiraLetra;
    char *linha = (char *)malloc(size);
    char *descricao;
    strcpy ( linha, buffer) ;
    descricao = strrchr(linha, ',');
    primeiraLetra = linha[0];

    //printf("%s", nome);
    //printf("%c", primeiraLetra);
    //if(primeiraLetra != '#' && primeiraLetra != '\n' && primeiraLetra != NULL ){
    if(primeiraLetra == '3' || primeiraLetra == '4' || primeiraLetra == '8' ){
        //Fichas[cont].nome = ;
        //Fichas[cont].descricao = ;
        Fichas[cont].id = cont;

        char *desmembra;
        char *teste;
        char teste1[40];
        int tamanho;
        desmembra = strtok (linha,",");
        int contCaracteristica = 0; //Contador para cada caracteristica do personagem
        while (desmembra != NULL){
            switch(contCaracteristica){
                case 0:
                    Fichas[contPersonagem].forca = atoi(desmembra);
                    //printf(">%s<", desmembra);
                    //printf(">%d<", Fichas[contPersonagem].forca);
                break;
                case 1:
                    Fichas[contPersonagem].percep = atoi(desmembra);
                break;
                case 2:
                    Fichas[contPersonagem].resist = atoi(desmembra);
                break;
                case 3:
                    Fichas[contPersonagem].caris = atoi(desmembra);
                break;
                case 4:
                    Fichas[contPersonagem].intel = atoi(desmembra);
                break;
                case 5:
                    Fichas[contPersonagem].agil = atoi(desmembra);
                break;
                case 6:
                    Fichas[contPersonagem].sorte = atoi(desmembra);
                break;
                case 7:
                     strcpy(Fichas[contPersonagem].nome , desmembra);
                break;
                case 8:
                    //tamanho = strlen(desmembra);
                    //strncpy(teste1, desmembra, tamanho-1);
                    strcpy(Fichas[contPersonagem].descricao , desmembra);
                    //printf (">%s<",desmembra);
                    //printf (">%s<",teste1);
                    //printf (">%i<",tamanho);
                break;
            }
            //printf (">%s<",desmembra);
            //printf(" *%d* ", contCaracteristica);
            //printf(" *%d*\n", contPersonagem);
            desmembra = strtok (NULL, ",");
            contCaracteristica++;
        }

        //printf("%d", Fichas[0].forca);
        //printf("%s *** ", desmembra);
        cont++;
        contPersonagem++;
    }
}

void pegaDados(struct Ficha Fichas[totalFichas]){ //Pega os dados do txt
    int size = 1024, pos;
    int c;
    char *buffer = (char *)malloc(size);

    FILE *f = fopen("fichas.txt", "r");
    if(f) {
        do { // Roda enquanto o arquivo nao terminou
            pos = 0; //Variavel que guarda a posicao de cada caracter
            do{ // Roda enquanto o arquivo nao terminou e nao esta no fim da linha
                c = fgetc(f); //c recebe o primeiro caracter da linha
                if(c != EOF) { //Se nao esta no fim do arquivo
                    buffer[pos++] = (char)c; //Guarda o caracter do txt na variavel buffer. Utiliza a variavel pos e ja a aumenta em 1
                }
                if(pos >= size - 1) { // increase buffer length - leave room for 0
                    size *=2;
                    buffer = (char*)realloc(buffer, size);
                }
            }while(c != EOF && c != '\n');
            buffer[pos] = 0;
            // line is now in buffer
            populaFichas(buffer, size, Fichas);
        } while(c != EOF);
        fclose(f);
    }
    else{
        printf("Arquivo nao encontrado.");
    }
    free(buffer);

}

int main(int argc, char *argv[]) {
    struct Ficha Fichas[totalFichas];
    pegaDados(Fichas);

    int num;
    printf("Bem vindo ao jogo!\n");
    printf("Escolha uma classe para ver sua ficha:\n");
    int i;
    for(i=0;i<qntTotalPers;i++){
        printf("(%i) -- %s", i,Fichas[i].descricao);
        //printf("%d", i);
    }
    printf("\nDigite o numero da classe:");
    scanf("%i", &num);
    while(num < 6){
        printf("\nNome: %s", Fichas[num].nome);
        printf("\nDescricao: %s", Fichas[num].descricao);
        printf("\nForca: %d", Fichas[num].forca);
        printf("\nPercepcao: %d", Fichas[num].percep);
        printf("\nResistencia: %d", Fichas[num].resist);
        printf("\nCarisma: %d", Fichas[num].caris);
        printf("\nInteligencia: %d", Fichas[num].intel);
        printf("\nAgilidade: %d", Fichas[num].agil);
        printf("\nSorte: %d", Fichas[num].sorte);
        printf("\nDigite um numero maior que %i para sair:", qntTotalPers-1);
        scanf("%i", &num);
    }
    printf("Ate logo");
    return 0;
}
