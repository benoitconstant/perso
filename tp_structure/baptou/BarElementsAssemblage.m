function[K]=BarElementsAssemblage(AllKe, nf,connec,geom)

n=max(max(nf));
K=zeros(n);
 %for l=1:size(geom,1)
 %for l=1:max(max(nf))
 for l=1:size(connec,1)
    colonne=[0;0;0;0]; %a changer par la suite car ici uniquement pour une barre (4 degrés de liberté perso)
    for i=1:n
        for j=1:n
            colonne=[nf(connec(l,1),1);nf(connec(l,1),2);nf(connec(l,2),1);nf(connec(l,2),2)];
            q=lignevecteur(colonne,i);
            s=lignevecteur(colonne,j);
            if (q~=0 & s~=0)
                K(i,j)=K(i,j)+AllKe(q,s,l);
            end
            
        end
                
    end
    
 end

