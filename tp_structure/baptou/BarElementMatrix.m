function[Ke]=BarElementMatrix(xy1,xy2,E,A)
teta=atan((xy2(2)-xy1(2))/(xy2(1)-xy1(1)));
c=cos(teta);
s=sin(teta);
L=sqrt((xy2(1,1)-xy1(1,1))^2+(xy2(1,2)-xy1(1,2))^2);
Ke=(E*A/L)*[c^2,c*s,-c^2,-c*s;c*s,s^2,-c*s, -s^2;-c^2, -c*s, c^2, c*s; -c*s, -s^2, c*s, s^2];
%E=module d'young
%A=section



