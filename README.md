# TP_Shell_Synthese
---------------------Description du TP

Ce projet consistait à créer un micro shell appelé enseash, un programme capable d'exécuter des commandes système et d'afficher des informations comme le temps d'exécution ou les codes de retour des commandes.

---------------------Ce que j'ai appris

Ce TP m’a permis de mieux comprendre certaines notions clés, comme :

fork() : Comment un processus père peut créer un processus fils pour exécuter une commande.

execvp : L’exécution d’une commande avec des arguments.

La gestion des signaux et des codes de retour : J’ai appris à détecter si une commande s’arrête normalement ou si elle est tuée par un signal.

La mesure du temps d’exécution : Avec clock_gettime(), j’ai pu calculer la durée d’exécution d’une commande et afficher cette information dans le prompt.

---------------------Problèmes rencontrés

Au début de la deuxième séance, j’ai eu des problèmes avec mon code, car j’avais séparé mes fonctions dans plusieurs fichiers pour rendre le code plus clair. Cependant, cela a causé des erreurs de compilation difficiles à gérer sur le moment. Pour avancer, j’ai tout regroupé dans un seul fichier main. Même si ce n’est pas optimal, cela m’a permis de comprendre mon code plus facilement et de corriger les erreurs.

---------------------Conclusion

Ce TP m’a été très utile pour comprendre comment fonctionne la création et la gestion des processus en C. J’ai aussi réalisé que même si une bonne organisation du code est importante, il faut parfois simplifier les choses pour mieux comprendre ce qu’on fait. Ce TP m’a clairement fait progresser dans la programmation système.
