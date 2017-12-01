function [ N ] = effortnormaux( q,geom,connec,nf,prop)
%EFFORTNORMAUX Summary of this function goes here
%   Detailed explanation goes here

nb=size(connec)
N=zeros(6,nb(1))
qj=zeros(6,nb(1))
nq=size(q)

v=zeros(nb(1),6)
for i=1:nb(1)
    
    
    v(i,1)=nf(connec(i,1),1)
    v(i,2)=nf(connec(i,1),2)
    v(i,3)=nf(connec(i,1),3)
    v(i,4)=nf(connec(i,2),1)
    v(i,5)=nf(connec(i,2),2)
    v(i,6)=nf(connec(i,2),3)
end

for i=1:nb(1)
    for j=1:6
       if v(i,j)~=0
           qj(j,i)=q(v(i,j),i)
       end
    end
    
    xy2=geom(connec(i,2),:)
    
    xy1=geom(connec(i,1),:)
    
    L=((xy2(1)-xy1(1))^2+(xy2(2)-xy1(2))^2)^(1/2)
    c=(xy2(1)-xy1(1))/L
    s=(xy2(2)-xy1(2))/L
    B=[-c,-s,c,s]
    
    ke=BeamElementMatrix(xy1,xy2,prop(i,:))
    
    N(:,i)=ke*qj(:,i)
    
end


end
