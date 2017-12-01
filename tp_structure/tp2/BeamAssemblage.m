function [k]=BeamAssemblage(AllKe,nf,connec)
n=size(nf)
nb=0
n3=size(AllKe)

for i=1:n(1)
    for j=1:n(2)
        if nf(i,j)~=0
            nb=nb+1
           end
    end
end

K=zeros(nb,nb)
v=zeros(n3(3),6)

for i=1:n3(3)
    
    
    v(i,1)=nf(connec(i,1),1)
    v(i,2)=nf(connec(i,1),2)
    v(i,3)=nf(connec(i,1),3)
    v(i,4)=nf(connec(i,2),1)
    v(i,5)=nf(connec(i,2),2)
    v(i,6)=nf(connec(i,2),3)
        
  
        for k=1:6
            for l=1:6
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