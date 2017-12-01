function[z]=lignevecteur(V,u)
n=size(V,1);
z=0;
for i=1:n
    if (u==V(i))
        z=i;
    end
end

        
    