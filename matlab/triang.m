clear all; close all;
clc;

% Charger le fichier d'entrée
HCT=load('../input/hct.pts');

% Enlever la première ligne
points=HCT(2:23,:);

% Trier dans l'ordre des index d'entrée
sortedPoints=sortrows(points);

% Générer la triangulation
TRI=delaunay(sortedPoints(:,2:3));

% Afficher le résultat
triplot(TRI,sortedPoints(:,2), sortedPoints(:,3));
