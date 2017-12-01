function[AllKe] =AllBarElementsMatrices(geom,connec,prop)
% f u n c t i o n  [ AllKe ] = AllBarElementsMatrices (geom ,  connec ,  prop )
% Computes  a l l  element  matrices  f o r  a l l  bar  elements
% E n t r i e s :
%  geom :  a Nn x 2  a r ra y  with  the  p o s i t i o n s  of N nodes  in R^21
%  connec :  a Ne x 2  a r r ay  of  elements  l i s t i n g  the
%two  e x t r e m i t i e s  of  each  bar  element
%
%  prop :  a Ne x 2  ar r a y  of  elements  l i s t i n g  Young
%Module E and  area A f o r  each  element
% Output :
%  AllKe :  a Ne x 4 x 4  elements  ar r a y  that  s t o r e s
%a l l  Ne 4x4  element  matrix
Ne=size(connec)
AllKe=zeros(4,4,Ne(1))

for i=1:Ne(1)

AllKe(:,:,i)=BarElementMatrix(geom(connec(i,1),:),geom(connec(i,2),:),prop(i,1),prop(i,2))

end