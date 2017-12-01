function [K] = BarElementAssemblage(AllKe,connec, nf)
n=size(nf,1);
d=max(nf);
for l=1:n
    t1=connec(l,1);
    t2=connec(l,2);
    for p=1: d
        dof(l,p) = Nf(t1,p);
    end

    for p=(d+1): 2*d
        dof(l,p) = Nf(t2,p);
    end
end    

for l=1:n
    
 t=Dof(l,:);
 
 for i=1:size(Allke,1)
     for j=1:size(Allke,1)
         k(t(i),t(-j))= k(t(i),t(-j)) + Allke(l,i,j);
     end
 end
end

         

