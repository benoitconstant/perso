function [ KeB ] = BeamElementMatrix(xy1,xy2,prop)
% Creates the element matrix for Bernoulli’s beam element
% Entries :
% xy1=[x1, y1 ] position of first extremity
% xy2=[x2 , y2 ] position of second extremity
% E Young module of the beam element
% I second moment of inertia of the beam element
% Output :
% KeB=Element Matrix of beam element



L=((xy2(1)-xy1(1))^2+(xy2(2)-xy1(2))^2)^(1/2)
E=prop(1)
A=prop(2)
I=prop(3)
a=E*A/L
b=12*E*I/L^3
c=6*E*I/L^2
d=4*E*I/L
e=E*I/L
k=[a,0,0,-a,0,0;0,b,c,0,-b,c;0,c,d,0,-c,e;-a,0,0,a,0,0;0,-b,-c,0,b,-c;0,c,e,0,-c,d;]

%changement de repere

c=(xy2(1)-xy1(1))/L
s=(xy2(2)-xy1(2))/L

R=[c,s,0,0,0,0;...
    -s,c,0,0,0,0;...
    0,0,1,0,0,0;...
    0,0,0,c,s,0;...
    0,0,0,-s,c,0;...
    0,0,0,0,0,1]
R2=transpose(R)

KeB=R2*k*R


end

