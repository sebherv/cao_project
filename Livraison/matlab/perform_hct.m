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

dlmwrite('Triangle.RES',gen_TRI, ' ');

%% Invocation hctexe
%!../c++/hctexe

%% Affichage des données de la fonction F

p=51;
q=51;
T=load('../output/fpointlist.txt');
TX=reshape(T(:,1),p,q)';
TY=reshape(T(:,2),p,q)';
TZ=reshape(T(:,3),p,q)';

figure
surf(TX,TY,TZ);
xlabel('TX');
ylabel('TY');
zlabel('TZ');
title('Interpolation des points de la fonction f');

P=load('../output/ferrorlist.txt');
PX=reshape(P(:,1),p,q)';
PY=reshape(P(:,2),p,q)';
PZ=reshape(P(:,3),p,q)';

figure
surf(PX,PY,PZ);
xlabel('PX');
ylabel('PY');
zlabel('PZ');
title('Erreur interpolation de la focntion f');

[PX, PY]=meshgrid(0:2,0:1);

PZ=1-(1-PX).^2;
PX=PX';
PY=PY';
PZ=PZ';

val=[PX(:) PY(:) PZ(:)];


%% Affichage des données de la fonction G

T=load('../output/gpointlist.txt');
TX=reshape(T(:,1),p,q)';
TY=reshape(T(:,2),p,q)';
TZ=reshape(T(:,3),p,q)';

figure
surf(TX,TY,TZ);
xlabel('TX');
ylabel('TY');
zlabel('TZ');
title('Interpolation des points de la fonction g');

P=load('../output/gerrorlist.txt');
PX=reshape(P(:,1),p,q)';
PY=reshape(P(:,2),p,q)';
PZ=reshape(P(:,3),p,q)';

figure
hP=surf(PX,PY,PZ);
xlabel('PX');
ylabel('PY');
zlabel('PZ');
title('Erreur interpolation de la fonction g');

[PX, PY]=meshgrid(0:2,0:1);

PZ=1-(1-PX).^2;
PX=PX';
PY=PY';
PZ=PZ';

val=[PX(:) PY(:) PZ(:)];








