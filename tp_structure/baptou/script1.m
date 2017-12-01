geom=[0,0;4,0;2,3];
connec=[1,2;1,3;2,3];
ActiveDoF=[0,0;1,0;1,1];
prop=[230000E6,23;230000E6,23;230000E6,23];

AllKe=AllBarElementsMatrix(geom, connec, prop);
nf=DFNumbering(ActiveDoF);
K=BarElementsAssemblage(AllKe, nf,connec)

Kinv=inv(K);

F=[0;12000;0];

q=Kinv*F