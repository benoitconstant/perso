function [ AllKe ] = AllBeamElementsMatrices( geom,connec,prop )
% Computes the global stiffness matrix
% Entries :
% geom: Nn x NDarray with the positions of N nodes i n R^ND space
% connec :Ne x Nne array of elements listing the
% nodes extremities of each beam element
% prop :Ne xNP array of elements listing the properties of the elements (Y)


Ne=size(connec)
AllKe=zeros(6,6,Ne(1))

for i=1:Ne(1)
    AllKe(:,:,i)=BeamElementMatrix(geom(connec(i,1),:),geom(connec(i,2),:),prop(i,:))

end

