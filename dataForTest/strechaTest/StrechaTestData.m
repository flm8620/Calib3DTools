p3D=[0 0 -1;
     1 0 0;
     -1 0 0;
     0 1 0;
     1 1 0.5;
     -1 1 0.5]';
C1=[0 -10 0]';
C2=[5 -7 2]';
C3=[-4 -5 -1]';
Rc1=rotation(0,0,0)* rotation(-pi/2,0,0);
Rc2=rotation(0,0,pi/6)* rotation(-pi/2,0,0);
Rc3=rotation(0,0,-pi/6)* rotation(-pi/2,0,0);

R1=Rc1',
R2=Rc2',
R3=Rc3',
t1=-R1*C1,
t2=-R2*C2,
t3=-R3*C3,

K=[200  0  100;
    0  200 100;
    0   0   1];

p2D1=K*[R1,t1]*[p3D;[1 1 1 1 1 1]];
for i=1:size(p2D1,2)
    p2D1(1,i)=p2D1(1,i)/p2D1(3,i);
    p2D1(2,i)=p2D1(2,i)/p2D1(3,i);
    p2D1(3,i)=p2D1(3,i)/p2D1(3,i);
end
p2D2=K*[R2,t2]*[p3D;[1 1 1 1 1 1]];
for i=1:size(p2D1,2)
    p2D2(1,i)=p2D2(1,i)/p2D2(3,i);
    p2D2(2,i)=p2D2(2,i)/p2D2(3,i);
    p2D2(3,i)=p2D2(3,i)/p2D2(3,i);
end
p2D3=K*[R3,t3]*[p3D;[1 1 1 1 1 1]];
for i=1:size(p2D1,2)
    p2D3(1,i)=p2D3(1,i)/p2D3(3,i);
    p2D3(2,i)=p2D3(2,i)/p2D3(3,i);
    p2D3(3,i)=p2D3(3,i)/p2D3(3,i);
end
p2D1(1:2,:)',p2D2(1:2,:)',p2D3(1:2,:)'
p3D'


    