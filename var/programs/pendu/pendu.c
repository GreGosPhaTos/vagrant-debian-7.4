#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAILLE_WORD 40
#define NB_TRY 20

#define REALLOC(_p,_t,_n) do{ \
(_t) * temp; \
temp = realloc ( (_p) , (_n) * sizeof( (_t) ) ); \
if( temp == NULL ) \
{ \
    fprintf(stderr,"Allocation impossible dans le fichier :%s ligne : %s",__FILE__,__LINE__);\
    free( (_p) ); \
    exit(EXIT_FAILURE); \
} \
else \
{ \
    (_p) = temp; \
} \
}while(0)

typedef struct { 
    char motSecret[TAILLE_WORD];
    char motSaisi[TAILLE_WORD];
    char motIndice[TAILLE_WORD];
    int coupsRestants;
} Pendu;

void initPendu(Pendu* pendu);
void demanderMot(Pendu* pendu);
int compareString(Pendu* pendu);

int main (int argc, char *argv[]) {
    Pendu *pendu;
    FILE* fichierConfig = NULL;
    char current;
    int cpt = 0, track = 0; 

    fichierConfig = fopen("words.txt", "r");
    if (fichierConfig != NULL) {
        do {
            initPendu(pendu);
            do {
                current = fgetc(fichierConfig);
                if (current == EOF) {
                    return EXIT_SUCCESS;
                }

                if ('#' != current) {
                    if (track == 0) {
                        pendu->motSecret[cpt] = current;
                    } else {
                        pendu->motIndice[cpt] = current;
                    }
                    cpt++;
                } else {                
                    cpt = 0;
                    track = 1;
                }
            } while (current != 10);
         
            pendu->motSecret[cpt] = '\0';
            pendu->motIndice[cpt] = '\0';
            char *p = &(pendu->motSecret);
            *p = realloc(*p, cpt * sizeof(char));
            pendu->motIndice = realloc(pendu->motIndice, cpt * sizeof(char));
            do {

                if (pendu->coupsRestants == 0) {
                    printf("Vous avez perdu !!");
                    return EXIT_SUCCESS;
                } 
            
                printf("Il vous reste %d chances \n", pendu->coupsRestants);
                demanderMot(pendu);
                pendu->coupsRestants--;
            } while (compareString(pendu) == 1);
        } while (current != EOF);
        
        fclose(fichierConfig);
    } else {
        printf("Il y a un probleme avec le chargement du fichier;\n");
    	return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

void initPendu(Pendu* pendu) {
//   pendu->motSaisi = NULL;
  // pendu->motIndice = {};
   //pendu->motSecret = {};
   pendu->coupsRestants = NB_TRY;
}

void demanderMot(Pendu* pendu) {
    printf("Trouvez le mot secret : %s\n", pendu->motIndice);
    scanf("%s", pendu->motSaisi);
}

int compareString (Pendu* pendu) {
    int lenthMotIndice, i;
    lenthMotIndice = strlen(pendu->motIndice);
    for (i = 0; i <= lenthMotIndice; i++) {
        if (pendu->motSaisi[i] == pendu->motSecret[i]) {
            pendu->motIndice[i] = pendu->motSecret[i];
        } else {
            return 1;
        }
    }
   
    printf("Bravo !! Vous avez trouvé le mot secret !! \n Il s'agissait du mot \"%s\"\n\n", pendu->motSecret);
    return 0;
}

