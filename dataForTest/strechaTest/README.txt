In this folder, there are some data for testing the strecha solver.
In fact here we use P3P solver to find out the camera position and orientation.

It takes the following data as Input:
Matrix K,
coordinate 3D for each control point.
coordinate 2D on each image which are projections of control points.

And the output is:
the camera center for each image.
the camera orientation, which is presented by Matrix R, a rotation matrix

more info, see http://ksimek.github.io/2012/08/14/decompose/ 

-------------------------------------------------------------------

the data is generated from 2 matlab file.
StrechaTestData.m
rotation.m

coordinate 3D are:

         0         0   -1.0000
    1.0000         0         0
   -1.0000         0         0
         0    1.0000         0
    1.0000    1.0000    0.5000
   -1.0000    1.0000    0.5000

centers of camera are:

C1=[0 -10 0]
C2=[5 -7 2]
C3=[-4 -5 -1]

orientations are:

R1 =

    1.0000         0         0
         0    0.0000   -1.0000
         0    1.0000    0.0000


R2 =

    0.8660    0.5000         0
   -0.0000    0.0000   -1.0000
   -0.5000    0.8660    0.0000


R3 =

    0.8660   -0.5000         0
    0.0000    0.0000   -1.0000
    0.5000    0.8660    0.0000

----------------------------------------

To test the solver:
- Launch the program.
- Click "Point2D-3D" Tab
- load 3 photo arbitraily
- load Point2D from 2d.txt
- load Point3D from 3d.txt
- load KMatrix from kmatrix.txt
- Click "solve by strecha"
- Click "Camera" Tab, you will see the result
- Save the result in a txt file, and compare.