geom=[0,0;0.5,sqrt(3)/2.;1,0];
connec=[1,2;3,2;1,3];
ActiveDoF=[0,0;1,1;1,0];
prop=[1,1;1,1;1,1];

AllKe=AllBarElementsMatrix(geom, connec, prop);
nf=DFNumbering(ActiveDoF);
K=BarElementsAssemblage(AllKe, nf,connec)

Kinv=inv(K);

F=[1;0;0];

q=Kinv*F