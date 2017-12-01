% prop=zeros(3,2)
% for i=1:3
%     prop(i,1)=230000*10^6
%     prop(i,2)=0.0023
% end
% 
% connec=[1,2;2,3;3,1]
% n=[0,0;1,0;1,1]
% geom=[0,0;4,0;4,6]

prop=zeros(15,2)

for i=1:15
    prop(i,1)=30*10^9
    if i<8
         prop(i,2)=0.045
    else
        prop(i,2)=0.02
    end
end

connec=[1,3;3,5;5,7;7,9;2,4;4,6;6,8;1,2;2,3;3,4;4,5;5,6;6,7;7,8;8,9]
    
for i=1:9
    if mod(i,2)==0 %nombre pair
        geom(i,1)=(i-1)*0.5
        geom(i,2)=2
    else 
        geom(i,1)=(i-1)*0.5,
        geom(i,2)=0
end
    
end

n=[0,0;1,1;1,1;1,1;1,1;1,1;1,1;1,1;1,0]

AllKe=AllBarElementsMatrices(geom,connec,prop)
nf=DFNumbering(n)


K=BarElementAssemblage(AllKe,nf,connec)
%B=[0;12*10^3;0]
B=[15*10^3;0;0;5*10^3;0;7*10^3;0;0;0;0;0;10*10^3;0;0;0]
q=inv(K)*B

N=effortnormaux( q,geom,connec,nf,prop)