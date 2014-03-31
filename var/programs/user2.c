#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "constants.c"

typedef struct User User;

struct User {
    char nom[MAX_STRING_SIZE], prenom[MAX_STRING_SIZE];
    int age;    
};

static User user;

void demanderNom() {
    printf("Quel est ton nom ?\n");
    scanf("%s", user.nom);
}

void direNom() {
    if (strlen(user.nom)) {
        printf("Bonjour %s\n", user.nom);
    } else {
        printf("Tu ne veux pas me donner ton ? Allez sois sympa ... \n");
        demanderNom();
    }

}

User* getUser() {
    printf("Adresse memoire du user.nom (user.c) : %p\n", user.nom);
    return &user;
}

