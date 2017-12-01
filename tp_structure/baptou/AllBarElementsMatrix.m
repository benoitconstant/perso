function[AllKe]=AllBarElementsMatrix(geom, connec, prop)
%n=size(geom,1);
n=size(connec,1)
for i=1:n
    AllKe(:,:,i)=[BarElementMatrix([geom(connec(i,1),1),geom(connec(i,1),2)],[geom(connec(i,2),1),geom(connec(i,2),2)],prop(i,1),prop(i,2))];
  end
