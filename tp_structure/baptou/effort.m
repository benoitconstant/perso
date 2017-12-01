function[N]=effort(geom,q,nf,AllKe,connec)


n=max(max(nf));

%for i=1:size(geom,1)
  for i=1:size(connec,1)
    colonne=[nf(connec(i,1),1);nf(connec(i,1),2);nf(connec(i,2),1);nf(connec(i,2),2)];
    new_q=[0;0;0;0]; %marche uniquement pour des barres
    
    
    for j=1:n
    s=lignevecteur(colonne,j);
    if (s~=0)
        new_q(s)=q(j);
    end 
    N(:,i)=AllKe(:,:,i)*new_q;
    end
end
    
    
