    function[nf] =DFNumbering(ActiveDoF)
%f u n c t i o n  [ nf ] = DFNumbering ( ActiveDoF )
%Returns  a  numbering  f o r  the  a c t i v e  DoF
%E n t r i e s :
%  ActiveDoF : A "Nn x d"  matrix  with  1  i n d i c a t i n g  an  a c t i v e  dof
%Output :
%  nf : A numbering  f o r  the  a c t i v e  DoF
d=size(ActiveDoF, 2 ) ;
Nn=size(ActiveDoF, 1 ) ;
nf=zeros(Nn,d) ;
num=0;
for i=1:Nn
    for k=1:d
        if (ActiveDoF(i,k)~=0)
            num =num +1;
            nf(i,k)= num;
        end
    end
end