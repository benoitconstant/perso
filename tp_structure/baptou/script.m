geom=[0,0;4,0;4,6];
connec=[1,2;1,3;2,3];
ActiveDoF=[0,0;1,0;1,1];
prop=[230000E6,0.0023;230000E6,0.0023;230000E6,0.0023]

AllKe=AllBarElementsMatrix(geom, connec, prop);
nf=DFNumbering(ActiveDoF);
K=BarElementsAssemblage(AllKe, nf,connec,geom)

Kinv=inv(K);

F=[0;12000;0]

q=Kinv*F

N=effort(geom,q,nf,AllKe,connec)