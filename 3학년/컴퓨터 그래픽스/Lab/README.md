# 실습

## Assignment 3
1. python program to draw a __rotating__ triangle
    > using render() function   
    > t rad rotated when t seconds have elapsed since the program was executed
2. python program to draw a __transformed__ triangle
    > using render() function of above  
    > traingle transformed by pressing keys 
    > > W: scale by 0.9 times in x direction  
    > > E: scale by 1.1 times in x direction  
    > > S: rotate by 10 degrees counterclockwise  
    > > D: Rotate by 10 degrees clockwise  
    > > X: Shear by a factor of -0.1 in x direction  
    > > C: Shear by a factor of 0.1 in x direction  
    > > R: Reflection across x axis  
    > > 1: Reset the traingle with identity matrix  
    >  
    > transform should be **accumulated** 
    > 


## Assignment 4
1. python program to draw a __transformed traingle in a 2D space__
    > using render() function    
    > triangle transformed by pressing keys  
    > >Q: translate by -0.1 in x direction w.r.t global coordinate  
    > >E: translate by 0.1 in x direction w.r.t global coordinate
    > >A: rotate by 10 degrees counterclockwise w.r.t local coordinate  
    > >D: rotate by 10 degrees clockwise w.r.t local coordinate  
    > >1: reset the triangle with identity matrix
    >  
    > transfomr should be **accumulated**
2. python program to draw a __transformed triangle in a 3D space__
    > use code given  
    > triangle transformed by pressing keys
    >  > Q: translate by -0.1 in x direction w.r.t. global coordinate  
    >  > E: translate by 0.1 in x direction w.r.t. global coordinate  
    >  > A: rotate about y axis by -10 degrees w.r.t local coordinate  
    >  > D: rotate about y axis by +10 degrees w.r.t. local coordinate  
    >  > W: rotate about x axis by -10 degrees w.r.t. local coordinate  
    >  > S: rotate about x axis by +10 degrees w.r.t. local coordinate  
    >  > 1: rotate camera -10 degree  
    >  > 3: rotate camera 10 degree
    >   
    > transfomr should be **accumulated**
    > 


## Assignment 5
1. python program to draw __rotating point__ p=(0.5, 0) and vector v=(0.5, 0) in a __2D space__
    > p and v should be t rad rotated when t seconds have elapsed since the program was executer
2. python program to draw __transformed triangle__ and its __local frame in 3D space__
    > use drawFrame() and drawTriangle() function  
    >   Steps
    >   1. draw an untransformed white traingle and a globla frame  
    >   2. draw transformed blue triangle and its local frame
    >   3. rotate triangle by 30degrees then translated by (0.6, 0, 0) w.r.t. the global frame
    >   


## Assignment 6
1. write myLookAt() and myOrtho() function that behaves same as gluLookAt() and gluOrtho()
    > skeleton code is given  
2. replace __gluLookAt() with two glRotatef() and one glTranslatef()__



## Assignment 7
1. python program to draw __hierarchical model of boxed__  
    > skeleton code is given  
    > add green arm at the end of the red arm, and rotate the green arm about its local z axis    
    > render local frames of the blue base, red arm, green arm using drawFrame()  
2. python program to draw __triangular pyramid__
    > using indexed triangles representation and glDrawElements()  
    > camera manipulation shortcuts:  
    > > '1','3','2','w'  


## Assignment 8
1. draws __color-changing cube__
    > Draw flat-shaded cube  
    > camera manipulation shortcuts:    
    > > '1','3','2','w'
    >  
    > key to diffuse & specular color of the light and the ambient & diffuse color of the object:
    > > A: change the light color to red  
    > > S: change the light color to green  
    > > D: change the light color to blue  
    > > F: change the light color to white  
    > > Z: change the object color to red  
    > > X: change the object color to green  
    > > C: change the object color to blue  
    > > V: change the object color to white
2. draws __smooth-shaded cube__
    > use glDrawElements()
    > use given normal vector data
    > > ![image](https://user-images.githubusercontent.com/82203285/114271497-9ac92e80-9a4c-11eb-9a0b-1c96807d41f9.png)



## Assignment 9
1. visualize __ZXZ Euler angles__
    > how ZXZ Euler angles work
    > > Rotate along Z-axis by alpha  
    > > Rotate along X0Axis of the new frame by beta  
    > > Rotate along Z-axis of the new frame by gamma  
    >  
    > keys to change alpha, beta, gamma  
    > > A: increase alpha by 10 degree   
    > > Z: decrease alpha by 10 degree  
    > > S: increase beta by 10 degree  
    > > X: decrease beta by 10 degree  
    > > D: increase gamma by 10 degree  
    > > C: decrease gamma by 10 degree  
    > > V: initialize orientation  
    > > 


## Assignment 10
1. __compare 4 orientation interpolation methods__
    > Steps
    1. implement functions
      > exp(rv), log(R)
    2. Interpolation functions
      > slerp(R1, R2, t) - R1&R2:L rotation matrices  
      > interpolateRotVec(rv1, rv2, t) - rv1, rv2: rotation vectors  
      > interolateZYXEulerAngles(euler1, euler2, t) - euler1&euler2: tuples of ZYX Euler angles  
      > interpolateRotMat(R1, R2,t)
    >  
    > skeleton code is given
    > shortkeys
    > > A: toggle slerp() result  
    > > S: toggle interpolateRotVec() result  
    > > D: toggle interpolateZYXEuler() result  
    > > F: toggle interpolateRotMat() result  
    > > Z: Hide all results  
    > > X: Show all results 


## Assignment 11
1. __visualize Bezier curve__
    > skeleton code is given
    > > draws a line segment between two end points  
    > > can drag the end points
    >  
    > control points p0, p1, p2, p3 are draggable and rendered in green  

