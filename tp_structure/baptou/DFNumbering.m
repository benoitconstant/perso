function[nf]=DFNumbering(ActiveDoF)
%f u n c t i o n [ n f ] = DFNumbering ( Ac tiveDoF )
%R e t u r n s a n um be ri ng f o r t h e a c t i v e DoF
%E n t r i e s :
% Ac tiveDoF : A "Nn x d" m a t r i x w i t h 1 i n d i c a t i n g an a c t i v e do f
%Output :
% n f : A n um be ri ng f o r t h e a c t i v e DoF
d=size(ActiveDoF,2);
Nn=size(ActiveDoF,1);
nf=zeros(Nn,d);
num=0;
for i =1:Nn
for k=1:d
if(ActiveDoF(i,k)~=0)
num=num+1;
nf(i,k)=num;
end
end
end