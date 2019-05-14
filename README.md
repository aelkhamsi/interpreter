
######## Description des dossiers #########

* src : contient les fichiers sources du compilateur

* tst : contient les fichiers d'exemples des 4 jalons (exemple1-4)

######## Commandes ########

* make : compiler les fichiers sources du compilateur en produisant un executable "myml"

* make clean : nettoyer le dossier courant

* ./compil tst/exemple1 : compiler les sources du compilateur et lancer l'executable myml sur le fichier exemple1 et produire le code trois adresses compilé
  	   		  Un exécutable "test" est créer      

####### Description du travail réalisé ########

Nous avons réussi à implémenter les 4 premiers jalons du projet. Le problème des let imbriqués qu'on a rencontré dans la dernière séance du projet est résolu.
Notre programme est à la fois un interpréteur et un compilateur. En effet, on a trouvé que le fait d'interpréter le code rend plus facile l'étape de la génération de code, ce qui rend les fonctions d'interprétation et de compilation fortement liées. Par conséquent, on a pas pu supprimer l'étape d'interprétation.

La plupart du code produit est dans le fichier Attribut.c, sauf pour le jalon 2 où on a choisi de modifier le prototype et le code de la fonction set_symbol_value pour qu'elle puisse sauvegarder la valeur d'un symbol avant de l'écraser. La sauvegarde est stocké dans une pile.  
