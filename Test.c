#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int Principlemain(int argc, char *argv[]);

int main() {
    char name[1000];
    char filename[1000];
    char *p;
    char check [2];
    char check2 [2];
    char *bouton1;
    char *bouton2;


    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char buffer[20];

    sprintf(buffer, "%04d-%02d-%02d_%02d-%02d-%02d", 
        tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
        tm.tm_hour, tm.tm_min, tm.tm_sec);
    
    printf("Entrez le nom du fichier : ");
    scanf("%s", name);

    int close = 1;
    while (close = 1 ) {
        char Question[2];
        strcpy(filename, name);
        char *extension = strrchr(filename, '.');
        if (extension) {
            *extension = '\0';
        }

        filename[strcspn(filename, "\n")] = '\0';

        printf("Voulez-vous utiliser cette adresse ? (Y/N) : ");
        scanf ("%s", Question);

        if  (strcmp(Question, "Y") == 0 || strcmp(Question, "y") == 0) {
            break;
        } else {
            printf("Entrez le nouveau nom du fichier : ");
            fgets(name, 1000, stdin);
            name[strcspn(name, "\n")] = '\0';
        }
    }


    printf("Voulez-vous avoir tous les événements (ALL events) ou seulement les événements en coïncidence (COINCIDENCE) ? (A/C) : ");
    scanf ("%s", check);
    getchar();

    if (strcmp(check, "A") == 0 || strcmp(check, "a") == 0) {
        printf("Vous avez choisi d'avoir tous les événements, souhaitez-vous changer ? (Y/N) :\n");

        scanf ("%s", check2);
        getchar();
        if (strcmp(check2, "N") == 0 || strcmp(check2, "n") == 0) {
            bouton1="ALL-EVENTS";
        } else {
            bouton1="COINCIDENCE";
        }
    } else if (strcmp(check, "C") == 0 || strcmp(check, "c") == 0) {
        printf("Vous avez choisi de traiter seulement les événements en coïncidence souhaitez-vous changer ? (Y/N) :\n");
        scanf ("%s", check2);
        getchar();
        if (strcmp(check2, "N") == 0 || strcmp(check2, "n") == 0) {
            bouton1="COINCIDENCE";
        } else {
            bouton1="ALL-EVENTS";
        }
    } else {
        printf("Choix invalide.\n");
        getchar(); 
        return 0;
    }

    printf("Voulez-vous utiliser les données d'ENERGY ou de TIME pour ADC0 ? (E/T) : ");
    char choix2[2];
    fgets(choix2, 2, stdin);
    getchar();

    if (choix2[0] == 'E' || choix2[0] == 'e') {
        printf("Vous avez choisi sélectionné ADC0 sur ENERGY et donc ADC1 sur TIME, souhaitez-vous changer ? (Y/N) :\n");
        char choix[2];
        fgets(choix, 2, stdin);
        getchar();
        if (choix[0] == 'N' || choix[0] == 'n') {
            bouton2 = "ENERGY";
        } else {
            bouton2 = "TIME";
        }
    } else if (choix2[0] == 'T' || choix2[0] == 't') {
        printf("Vous avez choisi d'avoir ADC0 sur TIME et ADC1 sur ENERGY, souhaitez-vous changer ? (Y/N)\n");
        char choix[2];
        fgets(choix, 2, stdin);
        getchar();        
        if (choix[0] == 'N' || choix[0] == 'n') {
            bouton2 = "TIME";
        } else {
            bouton2 = "ENERGY";
        }
    } else {
        printf("Choix invalide.\n");
        return 0;
    }
    sprintf(filename + strlen(filename), "_%s.txt", buffer);

    printf("Le nom du fichier est : %s\n", filename);
    printf("Appuyer sur entrée pour lancer le programme\n");
    getchar();
    char* args[] = {name, filename, bouton1, bouton2};
    int num_args = sizeof(args) / sizeof(args[0]);
    Principlemain(num_args, args);
    printf("Fin du programme\n");
    getchar();
    return 0;
}

int Principlemain(int argc, char *argv[]) {
    char *name = argv[0];
    printf("argv[0] = %s\n", argv[0]);
    printf("argv[1] = %s\n", argv[1]);
    printf("argv[2] = %s\n", argv[2]);
    printf("argv[3] = %s\n", argv[3]);
    argc=argc-2;
    printf("argc: %d\n", argc);
    FILE *fp = fopen(name, "r");
    int count = 0;
    char c;
    if (fp == NULL) {
        perror("Erreur lors de l'ouverture du fichier.\n");
        printf("Erreur lors de l'ouverture du fichier.\n");
        return 1;
    }
    while ((c = fgetc(fp)) != EOF) {
        if (c == '\n') {
            count++;
        }
    }
    fclose(fp);
}