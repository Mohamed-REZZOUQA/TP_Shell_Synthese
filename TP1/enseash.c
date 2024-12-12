#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>  // Pour clock_gettime
#include "constantes.h"

#define BUFSIZE 128

// Déclaration du buffer pour la lecture de la commande
char buffer[BUFSIZE];

void exe_commande(char *buffer);
void commande_complexe(char *commande);  

int main() {
    // message dans le vrai terminal
    write(STDOUT_FILENO, welcomeMessage, strlen(welcomeMessage));
    write(STDOUT_FILENO, exitMessage, strlen(exitMessage));

    while (1) {
        // Affichage du prompt, dans le nouveau terminal enseash
        write(STDOUT_FILENO, prompt, strlen(prompt));

        // Lecture de l'entrée utilisateur
        ssize_t bytesRead = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
        
        // Gestion d'erreur de lecture
        if (bytesRead <= 0) {
            if (bytesRead == 0) {
                break; // EOF, sortir de la boucle
            }
            perror("Erreur de lecture");
            break; // Si erreur de lecture, sortir de la boucle
        }
        
        buffer[bytesRead - 1] = '\0';  // Suppression du retour à la ligne

        // Comparaison avec la commande 'exit'
        if (strcmp(buffer, exitCommand) == 0) {
            break;
        }
        
        // Appel à la fonction qui gère l'exécution du programme
        exe_commande(buffer);
    }

    // message de fin avant de quitter le terminal enseash
    write(STDOUT_FILENO, "Bye!\n", 5);
    return 0;
}

void exe_commande(char *buffer) {
    int status;
    struct timespec start, end;
    
    // Mesure du temps avant l'exécution de la commande dans le père
    clock_gettime(CLOCK_MONOTONIC, &start);

    pid_t pid = fork(); 

    if (pid == 0) {  // Si on est dans le processus fils
        //printf("%d\n",getpid()); à décommenter pour bien tester le KILL du signal "Question 4"
        //sleep(100);              à décommenter pour bien tester le KILL du signal "Question 4"
        // Vérification si la commande contient un espace (pour les commandes avec arguments)
        if (strchr(buffer, ' ') != NULL) {
            commande_complexe(buffer);
        } else {
            execlp(buffer, buffer, NULL);  // Exécution de la commande simple
        }

        // Si execlp échoue, on affiche une erreur
        perror("commande inconnue");
        exit(EXIT_FAILURE);
    }
    else if (pid > 0) {  // Si on est dans le processus père
        wait(&status);  // Attendre la fin du processus fils et récupérer son statut

        // Mesure du temps après l'exécution de la commande
        clock_gettime(CLOCK_MONOTONIC, &end);

        if (WIFEXITED(status)) { // Si le fils s'est terminé correctement
            int exit = WEXITSTATUS(status);

            // Calcul du temps d'exécution en millisecondes
            long elapsedTime = (end.tv_sec - start.tv_sec) * 1000 + (end.tv_nsec - start.tv_nsec) / 1000000;

            printf("enseash [exit:%d|%ldms]%%\n", exit, elapsedTime);
        }
        else if (WIFSIGNALED(status)) { // Si le fils a été tué par un signal
            int sign = WTERMSIG(status);

            // Calcul du temps d'exécution en millisecondes
            long elapsedTime = (end.tv_sec - start.tv_sec) * 1000 + (end.tv_nsec - start.tv_nsec) / 1000000;

            printf("enseash [sign:%d|%ldms]%%\n", sign, elapsedTime);
        }
    }
}

void commande_complexe(char *commande) {
    char *args[BUFSIZE / 2];  // Tableau pour les arguments de la commande
    char *token;
    int i = 0;

    // On sépare la commande en arguments
    token = strtok(commande, " ");
    while (token != NULL) {
        args[i] = token;
        i++;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;  // Terminaison du tableau d'arguments

    // Exécution de la commande avec ses arguments
    execvp(args[0], args);

    // Si execvp échoue
    perror("commande inconnue");
    exit(EXIT_FAILURE);
}
