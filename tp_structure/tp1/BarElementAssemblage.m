function[K] =BarElementAssemblage(AllKe,nf,connec)
%f u n c t i o n  [K] = BarElementAssemblage ( Nodes ,  Elem ,  Prop ,  nf ,  d i s p l )
% E n t r i e s :
%AllKe :  a Ne x 4 x 4  elements  a rr a y  that  s t o r e s
%a l l  Ne 4x4  element  matrix2
%nf : A Nn x 2  a rr a y  numbering  the  a c t i v e  degrees  of  freedom
%A non  a c t i v e  degree  of  freedom  has  number 0 .
%
% Output :
% K:  matrice  de  r i g i d i t e  g l o bal
n=size(nf)
nb=0

n3=size(AllKe)
for i=1:n(1)
    if nf(i,1)~=0
        nb=nb+1
    end
    if nf(i,2)~=0
        nb=nb+1
    end
end

K=zeros(nb,nb)
v=zeros(n3(3),4)

for i=1:n3(3)
    
    
    v(i,1)=nf(connec(i,1),1)
    v(i,2)=nf(connec(i,1),2)
    v(i,3)=nf(connec(i,2),1)
    v(i,4)=nf(connec(i,2),2)
        
  
        for k=1:4
            for l=1:4
                if v(i,k)~=0 
                    if v(i,l)~=0
                        if k==l
                            K(v(i,k),v(i,l))=K(v(i,k),v(i,l))+AllKe(k,l,i)
                        else
                            K(v(i,k),v(i,l))=K(v(i,k),v(i,l))+AllKe(k,l,i)
                            K(v(i,l),v(i,k))=K(v(i,l),v(i,k))+AllKe(l,k,i)
                        end
                    end
                end      
            end
        
        
      
    end
end

                
    
    
    
    
        