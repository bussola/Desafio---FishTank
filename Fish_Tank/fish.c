#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int contPersonagem = 0; //Contador de cada Personagem
int totalFichas = 10; //numero maximo de fichas
int qntTotalPers = 0; //quantidade total de personagens

//Cria uma struct para a ficha
struct Ficha{
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

//Funcao para popular as Structs com os dados obtidos da funcao pegaDados
void populaFichas(char *buffer, int size, struct Ficha Fichas[totalFichas]){
    int i;
    char primeiraLetra;
    char *linha = (char *)malloc(size); //Ponteiro para guardar as linhas
    char *descricao;
    strcpy ( linha, buffer) ; //copia a string buffer para linha
    primeiraLetra = linha[0];

    //Se a primeira letra for um numero
    if(primeiraLetra == '0' || primeiraLetra == '1' || primeiraLetra == '2'|| primeiraLetra == '3' || primeiraLetra == '4' || primeiraLetra == '5'
       || primeiraLetra == '6'|| primeiraLetra == '7' || primeiraLetra == '8' || primeiraLetra == '9'  ){
        Fichas[contPersonagem].id = contPersonagem;
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
                    strcpy(Fichas[contPersonagem].descricao , desmembra);
                break;
            }
            desmembra = strtok (NULL, ",");
            contCaracteristica++;
        }
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

void adiciona(struct Ficha Fichas[totalFichas]){
    char aux[10];
    int num;
    FILE *f = fopen("fichas.txt", "a");
    if(f){
        fputc ( '\n' , f );
        printf("\nDigite a forca do personagem:");
        scanf("%i", &num);
        fprintf(f, "%d,", num);
        Fichas[qntTotalPers].forca = num;

        printf("\nDigite a percepcao do personagem:");
        scanf("%i", &num);
        fprintf(f, "%d,", num);
        Fichas[qntTotalPers].percep = num;

        printf("\nDigite a resistencia do personagem:");
        scanf("%i", &num);
        fprintf(f, "%d,", num);
        Fichas[qntTotalPers].resist = num;

        printf("\nDigite o carisma do personagem:");
        scanf("%i", &num);
        fprintf(f, "%d,", num);
        Fichas[qntTotalPers].caris = num;

        printf("\nDigite a inteligencia do personagem:");
        scanf("%i", &num);
        fprintf(f, "%d,", num);
        Fichas[qntTotalPers].intel = num;

        printf("\nDigite a agilidade do personagem:");
        scanf("%i", &num);
        fprintf(f, "%d,", num);
        Fichas[qntTotalPers].agil = num;

        printf("\nDigite a sorte do personagem:");
        scanf("%i", &num);
        fprintf(f, "%d,", num);
        Fichas[qntTotalPers].sorte = num;

        printf("\nDigite o nome do personagem:");
        scanf("%s", aux);
        fputs(aux, f);
        fputs(",", f);
        strcpy(Fichas[qntTotalPers].nome , aux);

        printf("\nDigite a descricao do personagem:");
        scanf("%s", aux);
        fputs(aux, f);
        strcpy(Fichas[qntTotalPers].descricao , aux);

        fclose (f);
    }
    else{
        printf("Arquivo nao encontrado.");
    }
    qntTotalPers++;
}

int main(int argc, char *argv[]) {
    struct Ficha Fichas[totalFichas];
    pegaDados(Fichas);
    qntTotalPers = contPersonagem; //recebe o valor da qnt de personagens
    int num = 0;
    while(num != 3){
        printf("Bem vindo ao jogo!\n");
        printf("Escolha uma opcao:");
        printf("\n(1) para adicionar ficha");
        printf("\n(2) para verificar ficha");
        printf("\n(3) para sair\n");
        scanf("%i", &num);

        if(num == 1){
            adiciona(Fichas);
        }
        else if(num == 2){
            printf("Escolha uma classe para ver sua ficha:\n");
            int i;
            for(i=0;i<qntTotalPers;i++){
                printf("\n(%i) -- %s", i,Fichas[i].descricao);
            }
            printf("\nDigite o numero da classe:");
            scanf("%i", &num);
            while(num <= qntTotalPers-1){
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
        }
    }


    printf("Ate logo");
    return 0;
}
