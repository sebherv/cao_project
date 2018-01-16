clear all; 
close all;
clc;

%% Génération de la triangulation 

% Charger le fichier d'entree
HCT=load('../input/hct.pts');

% Enlever la premiere ligne
points=HCT(2:23,:);

% Trier dans l'ordre des index d'entree
sortedPoints=sortrows(points);

% Generer la triangulation
TRI=delaunay(sortedPoints(:,2:3));

% Afficher le resultat
triplot(TRI,sortedPoints(:,2), sortedPoints(:,3));

V=(1:size(TRI))';
gen_TRI=[V TRI]; %ajout du vecteur V des index des triangles k à gauche de TRI 

dlmwrite('HCT.RES',gen_TRI, ' ');

%% Affichage des données

p=11;
q=11;
T=load('D:\Projet_CAO\c++\cmake-build-debug\fpointlist.txt');
TX=reshape(T(:,1),p,q)';
TY=reshape(T(:,2),p,q)';
TZ=reshape(T(:,3),p,q)';

figure
surf(TX,TY,TZ);
xlabel('TX');
ylabel('TY');
zlabel('TZ');
title('Interpolation des points');

P=load('D:\Projet_CAO\c++\cmake-build-debug\ferrorlist.txt');
PX=reshape(P(:,1),p,q)';
PY=reshape(P(:,2),p,q)';
PZ=reshape(P(:,3),p,q)';

figure
hP=surf(PX,PY,PZ);
xlabel('PX');
ylabel('PY');
zlabel('PZ');
title('Erreur interpolation');

[PX, PY]=meshgrid(0:2,0:1);

PZ=1-(1-PX).^2;
PX=PX';
PY=PY';
PZ=PZ';

val=[PX(:) PY(:) PZ(:)];

save ferrorlist.txt val -ascii









