# Commandes

* make : compiler les fichiers sources du compilateur en produisant un executable "myml"

* ./myml : lancer l'interpréteur

  	 SYNTAX :
	 $- a = 1;  (affectation d'un entier positif ou négatif)
	 $- b = 1.0;  (affectation d'un float positif ou négatif)
	 $- c = a+b; (affectation d'une somme)
	 $- c = if (a == 2) then 3 else 6;  (utiliser des conditions)
	 $- c = let x = 3 in (1+x);  (utiliser des local bindings)
	 
* ./myml tst/exemple[1-4]  :  lancer ./myml sur les commandes de l'un des fichiers du répertoire tst/


* make clean : nettoyer le dossier courant


* ./compil tst/exemple1 : compiler les sources du compilateur et lancer l'executable myml sur le fichier exemple1 et produire le code trois adresses compilé
  	   		  Un exécutable "test" est créer



# Description des dossiers 

* src : contient les fichiers sources du compilateur

* tst : contient les fichiers d'exemples des 4 jalons (exemple1-4)

