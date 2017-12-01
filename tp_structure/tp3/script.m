clear all
close all
clc

geom=[0,0;525,909.32;1050,0]
connec=[1,2;2,3;3,1]
prop=[210*10^9,20*10^-6;210*10^9,20*10^-6,] %E,A
ActiveDof=[1,1,0;0,0,0;0,1,0]
load=[0,0,0;0,400,0;0,0,0]
displ=[0,0,0;0,0,0;0,0,0]

ke=BarElementMatrix(geom(connec(1,1),:),geom(connec(1,2),:),prop(1,1),prop(1,2))
% nf=DFNumbering(ActiveDof)
% AllKe=AllBeamElementsMatrices(geom,connec,prop)
% K=BeamAssemblage(AllKe,nf,connec)
% q=inv(K)*load
% 
% N=effortnormaux( q,geom,connec,nf,prop)

