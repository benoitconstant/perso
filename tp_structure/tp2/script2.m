clear all
close all
clc

geom=[0,0;4,0;9,0;16,0]
connec=[1,2;2,3;3,4]
prop=[200*10^9,0.028845,120*10^6*10^(-12);200*10^9,0.028845,120*10^6*10^(-12);200*10^9,0.028845,120*10^6*10^(-12)] %E,A,I
ActiveDof=[0,0,0;1,0,1;1,0,1;0,0,0]
p=20*10^6
w=4*10^6
load=[0,p/2,p*4/8;0,p/2+w*2/2,-p*4/8+w*4/12;0,w*2/2,-w*4/12;0,0,0]
displ=[0,0,0;0,0,0;0,0,0]

nf=DFNumbering(ActiveDof)
AllKe=AllBeamElementsMatrices(geom,connec,prop)
K=BeamAssemblage(AllKe,nf,connec)
q=inv(K)*load

N=effortnormaux( q,geom,connec,nf,prop)

%le programme marche mais ne comprend pas pk il y a que des zeros et erreur
%sur le load, je ne prends pas en compte le mfz