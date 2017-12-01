function[Ke] =BarElementMatrix(xy1,xy2,E,A)
% f u n c t i o n  [ Ke ] = BarElementMatrix ( xy1 , xy2 , E ,A)
% Creates  the  element  matrix  f o r  bar  element
% E n t r i e s :
%  xy1=[x1 , y1 ]  p o s i t i o n  of  f i r s t  e xt r e m i t y
%  xy2=[x2 , y2 ]  p o s i t i o n  of  second  e x t r em i t y
%  E Young module  of  the  bar  element
%  A Section  area  of  the  bar  element
% Output :
%   Ke=Element  Matrix  of  t h i s  bar  element
L=((xy2(1)-xy1(1))^2+(xy2(2)-xy1(2))^2)^(1/2)
c=(xy2(1)-xy1(1))/L
s=(xy2(2)-xy1(2))/L
Ke=[c^2,c*s,-c^2,-c*s;c*s,s^2,-c*s,-s^2;-c^2,-c*s,-c^2,c*s;-c*s,-s^2,c*s,s^2]
Ke=(E*A/L)*Ke








        
    
    
