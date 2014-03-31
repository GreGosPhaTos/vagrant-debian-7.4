#include <stdio.h>
#include <string.h>

char * saisir_chaine(char * lpBuffer, int buf_size);

int main()
{
    char src[FILENAME_MAX]; /* FILENAME_MAX est defini dans stdio.h */
    FILE * fsrc;

    printf("Ce programme permet de copier un fichier.\n");
    printf("source : ");
    saisir_chaine(src, sizeof(src));

    fsrc = fopen(src, "rb");
    if (fsrc == NULL)
        perror(src);
    else
    {
        char dest[FILENAME_MAX];
        FILE * fdest;

        printf("dest : ");
        saisir_chaine(dest, sizeof(dest));

        if (strcmp(src, dest) == 0)
            printf("La source ne peut pas etre en meme temps la destination.\n");
        else
        {
            fdest = fopen(dest, "wb");
            if (fdest == NULL)
                perror(dest);
            else
            {
                int c;

                while ((c = getc(fsrc)) != EOF)
                    putc(c, fdest);

                fclose(fdest);
                printf("Copie terminee.\n");
            }
        }

        fclose(fsrc);
    }

    printf("Merci d'avoir utilise ce programme. A bientot !\n");

    return 0;
}

char * saisir_chaine(char * lpBuffer, int buf_size)
{
    char * ret = fgets(lpBuffer, buf_size, stdin);

    if (ret != NULL)
    {
        char * p = strchr(lpBuffer, '\n');
        if (p != NULL)
            *p = '\0';
        else
        {
            int c;

            do
                c = getchar();
            while (c != EOF && c != '\n');
        }
    }

    return ret;
}
