
Mz = csvread('Paded.csv',0,0);
bz=Mz(:);
Bz = bz' ;
Bz = Bz';
Mx = csvread('Paded_move.csv',0,0);
bx=Mx(:);          %%%%%%%%%%%%%1:1281
% bx = bx(:);
Bx = bx' ;
Bx = Bx';
My = csvread('PadedY.csv',0,0);
by=My(:);
By = by' ;
By = By';

plot3(Bx,By,Bz,'r');
hold on;
xlabel('x'),ylabel('y'),zlabel('z');
[Bx,By,Bz] = peaks;
surf(Bx,By,Bz,gradient(Bz))
colormap cool;
colorbar













