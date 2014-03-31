#include <stdio.h>
#include <stdlib.h>
#include "user.c" 

int main (int argc, char *argv[]) {
    User *pUser;
    demanderNom();
    direNom();
    pUser = getUser();

    printf("Adresse memoire du pUser->nom (main.c) : %p\n", pUser->nom);

    return 0;
}


