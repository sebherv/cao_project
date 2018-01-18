Pour faire tourner l'interpolation de bout en bout, il suffit d'executer sous matlab le script "perform_hct.m" situé dans le sous-répertoire "matlab".

Les fichiers générés (dont le ficher HCT.RES) sont situés dans le répertoire "output"

Pour modifier la liste des points, il suffit de remplacer les données du fichiers hct.pts dans le répertoire "input". ATTENTION: il faut cependant laisser le nom du fichier inchangé.

Le code c++ de l'application hctexe se trouve dans le répertoire "c++".
Pour recompiler le code, taper la ligne suivante dans un terminal sous ce sous répertoire "c++":

g++ -std=c++11 -o hctexe *.cpp