    function[ke] = BarElementMatrix(xy1,xy2,E,A)
    % Creates the element matrix for barelement
% Entries :
% xy1=[x1, y1] position of first extremity
% xy2=[x2 , y2 ] position of second extremity
% E Young module of the beam element
% A cross-section of the barelement
% Output :
% Ke=Element Matrix of barelement

D=E*A
L=((xy2(1)-xy1(1))^2+(xy2(2)-xy1(2))^2)^(1/2)
detj=L/2
B=1/L*[-1,0,1,0]

ke=transpose(B)*D*B*2*detj
    





