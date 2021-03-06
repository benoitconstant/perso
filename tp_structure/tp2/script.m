clear all
close all
clc

geom=[0,0;3,0;7,0]
connec=[1,2;2,3]
prop=[200*10^9,0.024329,120*10^6*10^(-12);200*10^9,0.030652,240*10^6*10^-12] %E,A,I
ActiveDof=[0,0,0;1,0,1;0,0,0]
load=[0,0,0;0,12*10^3,6*16/12*10^3;0,12*10^3,-6*16/12*10^3]
displ=[0,0,0;0,0,0;0,0,0]

nf=DFNumbering(ActiveDof)
AllKe=AllBeamElementsMatrices(geom,connec,prop)
K=BeamAssemblage(AllKe,nf,connec)
q=inv(K)*load

N=effortnormaux( q,geom,connec,nf,prop)

