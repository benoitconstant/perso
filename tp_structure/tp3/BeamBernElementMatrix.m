function [ KeB ] = BeamBernEl ementMatrix ( xy1 , xy2 , E , A , I)


L=((xy2(1)-xy1(1))^2+(xy2(2)-xy1(2))^2)^(1/2)
l1=-1/2
l2=1/2

h1=3/2*1/
h2=L/8(-2+6e)
h3=1/4*(-6e)
h4=L/8(2+6e)

detj=L/2

D=(E*A,0;0,E*I)

B=(l1/detj,0,0,l2/detj,0,0;0,h1/detj^3,h2/detj^3,0,h3/detj^3,h4/detj^3)
 KeB=E*A/detj*transpose(B(0,:))*B(0,:)
 KeB=KeB+1/detj^3*