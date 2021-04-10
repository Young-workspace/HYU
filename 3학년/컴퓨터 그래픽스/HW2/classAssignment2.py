import glfw
from OpenGL.GL import *
from OpenGL.GLU import *
import numpy as np

gCamAng = 0.
gCamHeight = 0.

#for class assignment 1
xRotate = 0.
yRotate = 0.
zRotate = 0.
xTrans = 0.
yTrans = 0.
zoom = 45
xStart = 0.
yStart = 0.
dragging = 0

#for class assignment 2
dropped = 0
vertices = None
normals = None
faces = None
gVertexArraySeparate = np.zeros((3,3))
zflag = 0
sflag = 0
# draw a cube of side 1, centered at the origin.
def drawUnitCube():
    glBegin(GL_QUADS)
    glVertex3f( 1.0, 1.0,-1.0)
    glVertex3f(-1.0, 1.0,-1.0)
    glVertex3f(-1.0, 1.0, 1.0)
    glVertex3f( 1.0, 1.0, 1.0) 
                             
    glVertex3f( 1.0,-1.0, 1.0)
    glVertex3f(-1.0,-1.0, 1.0)
    glVertex3f(-1.0,-1.0,-1.0)
    glVertex3f( 1.0,-1.0,-1.0) 
                             
    glVertex3f( 1.0, 1.0, 1.0)
    glVertex3f(-1.0, 1.0, 1.0)
    glVertex3f(-1.0,-1.0, 1.0)
    glVertex3f( 1.0,-1.0, 1.0)
                             
    glVertex3f( 1.0,-1.0,-1.0)
    glVertex3f(-1.0,-1.0,-1.0)
    glVertex3f(-1.0, 1.0,-1.0)
    glVertex3f( 1.0, 1.0,-1.0)
 
    glVertex3f(-1.0, 1.0, 1.0) 
    glVertex3f(-1.0, 1.0,-1.0)
    glVertex3f(-1.0,-1.0,-1.0) 
    glVertex3f(-1.0,-1.0, 1.0) 
                             
    glVertex3f( 1.0, 1.0,-1.0) 
    glVertex3f( 1.0, 1.0, 1.0)
    glVertex3f( 1.0,-1.0, 1.0)
    glVertex3f( 1.0,-1.0,-1.0)
    glEnd()

#class Assignment given code
def drawCube():
    glBegin(GL_QUADS)
    glVertex3f( 1., 1.0,-1.0)
    glVertex3f(-1.0, 1.0, -1.0)
    glVertex3f(-1.0, 1.0, 1.0)
    glVertex3f( 1.0, 1.0, 1.0) 
                             
    glVertex3f( 1.0,-1.0, 1.0)
    glVertex3f(-1.0,-1.0, 1.0)
    glVertex3f(-1.0,-1.0,-1.0)
    glVertex3f( 1.0,-1.0,-1.0) 
                             
    glVertex3f( 1.0, 1.0, 1.0)
    glVertex3f(-1.0, 1.0, 1.0)
    glVertex3f(-1.0,-1.0, 1.0)
    glVertex3f( 1.0,-1.0, 1.0)
                             
    glVertex3f( 1.0,-1.0,-1.0)
    glVertex3f(-1.0,-1.0,-1.0)
    glVertex3f(-1.0, 1.0,-1.0)
    glVertex3f( 1.0, 1.0,-1.0)
 
    glVertex3f(-1.0, 1.0, 1.0) 
    glVertex3f(-1.0, 1.0,-1.0)
    glVertex3f(-1.0,-1.0,-1.0) 
    glVertex3f(-1.0,-1.0, 1.0) 
                             
    glVertex3f( 1.0, 1.0,-1.0) 
    glVertex3f( 1.0, 1.0, 1.0)
    glVertex3f( 1.0,-1.0, 1.0)
    glVertex3f( 1.0,-1.0,-1.0)
    glEnd()

def drawCubeArray():
    for i in range(5):
        for j in range(5):
            for k in range(5):
                glPushMatrix()
                glTranslatef(i,j,-k-1)
                glScalef(.5,.5,.5)
                drawUnitCube()
                glPopMatrix()

#class Assignment given code
def drawSphere(numLats=12, numLongs=12):
    for i in range(0, numLats + 1):
        lat0 = np.pi *(-0.5 + float(float(i-1)/float(numLats)))
        z0 = np.sin(lat0)
        zr0 = np.cos(lat0)

        lat1 = np.pi * (-0.5 + float(float(i)/float(numLats)))
        z1 = np.sin(lat1)
        zr1 = np.cos(lat1)

        glBegin(GL_QUAD_STRIP)

        for j in range(0, numLongs + 1):
            lng = 2 * np.pi * float(float(j-1)/float(numLongs))
            x = np.cos(lng)
            y = np.sin(lng)
            glVertex3f(x * zr0, y * zr0, z0)
            glVertex3f(x * zr1, y* zr1, z1)

        glEnd()

def drawFrame():
    glBegin(GL_LINES)
    glColor3ub(255, 0, 0)
    glVertex3fv(np.array([0.,0.,0.]))
    glVertex3fv(np.array([10.,0.,0.]))
    glColor3ub(0, 255, 0)
    glVertex3fv(np.array([0.,0.,0.]))
    glVertex3fv(np.array([0.,10.,0.]))
    glColor3ub(0, 0, 255)
    glVertex3fv(np.array([0.,0.,0]))
    glVertex3fv(np.array([0.,0.,10.]))
    glEnd()

def drawGrid():
    #i = 0
    #j = 0
    glColor3ub(0, 255, 255)
    for i in range(-10, 10):
        glBegin(GL_LINE_LOOP)
        glVertex3f(i, 0, -10)
        glVertex3f(i, 0, 10)
        glEnd()

    for j in range(-10, 10):
        glBegin(GL_LINE_LOOP)
        glVertex3f(-10, 0, j)
        glVertex3f(10, 0, j)
        glEnd()

def scenemodel():
    global dropped, zflag, sflag
    #glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT)
    #glEnable(GL_DEPTH_TEST)
    if zflag == 0:
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE )
    else:
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL)
    
    if sflag == 0:
        glShadeModel(GL_FLAT)
    else:
        glShadeModel(GL_SMOOTH)
    drawGrid()
    drawFrame()
    #draw 
   
    #glBegin(GL_TRIANGLES)
    #----------------------------------------------
    # 여기에 구현
    # Class Assignment 2
    #----------------------------------------------
    
    
    #glLoadIdentity()
    # light source
    glEnable(GL_LIGHTING)
    glEnable(GL_LIGHT0)
    glEnable(GL_LIGHT1)
    glEnable(GL_LIGHT2)

    #light position
    glPushMatrix()
    lightPos0 = (1., 2., .3, 1.)
    lightPos1 = (3., 2., 1., 1.)
    lightPos2 = (1., 3., 2., 1.)
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0)
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos1)
    glLightfv(GL_LIGHT2, GL_POSITION, lightPos2)
    glPopMatrix()

    # light intensity for each channel
    # light 0
    lightColor = (1., 1., 1., 1.)
    ambientLightColor = (.1, .1, .1, 1.)
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor)
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightColor)
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLightColor)
    # light 1
    lightColor = (.5, 1., .5, .5)
    ambientLightColor = (.05, .05, .05, 1.)
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor)
    glLightfv(GL_LIGHT1, GL_SPECULAR, lightColor)
    glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLightColor)
    # light2 
    lightColor = (0., 0.5, 1, 0.5)
    ambientLightColor = (.025, .025, .025, 1.)
    glLightfv(GL_LIGHT2, GL_DIFFUSE, lightColor)
    glLightfv(GL_LIGHT2, GL_SPECULAR, lightColor)
    glLightfv(GL_LIGHT2, GL_AMBIENT, ambientLightColor)

    # material reflectance for each color channel
    objectColor = (.5, .5, .5, 1.)
    #specularObjectColor = (1., 0., 1., 1.)
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, objectColor)
    #glMaterialfv(GL_FRONT, GL_SPECULAR, specularObjectColor)

    glPushMatrix()

    if dropped == 1:
        draw_glDrawArray()
        
    glPopMatrix()
    glDisable(GL_LIGHTING)
    
    
def draw_glDrawArray():
    global gVertexArraySeparate
    varr = gVertexArraySeparate
    glEnableClientState(GL_VERTEX_ARRAY)
    glEnableClientState(GL_NORMAL_ARRAY)
    glNormalPointer(GL_FLOAT, 6*varr.itemsize, varr)
    glVertexPointer(3, GL_FLOAT, 6*varr.itemsize, ctypes.c_void_p(varr.ctypes.data + 3*varr.itemsize))
    glDrawArrays(GL_TRIANGLES, 0, int(varr.size/6))

def polarView():
    global yTrans, xTrans, zRotate, xRotate, yRotate
    glTranslatef(yTrans/100., .0, .0)
    glTranslatef(.0, -xTrans/100., .0)
    glRotatef(-zRotate, .0, .0, 1.)
    glRotatef(-xRotate, 1., .0, .0)
    glRotatef(-yRotate, .0, 1., .0)

def render():
    global zoom, gCamAng, gCamHeight, dropped
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT)
    glEnable(GL_DEPTH_TEST)
    
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    
    gluPerspective(zoom, 1, 1, 10)
    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()
    gluLookAt(5*np.sin(gCamAng), gCamHeight, 5*np.cos(gCamAng), 0, 0, 0, 0, 1, 0)   
    
    
    polarView()
    #drawCube()
    scenemodel()
    
    
#mouse button callback
def button_callback(window, button, action, mod):
    global dragging
    if button == glfw.MOUSE_BUTTON_LEFT:                                # click mouse left
        if action == glfw.PRESS:
            dragging = 1
            glfw.set_cursor_pos_callback(window, cursor_callback)
            
        elif action == glfw.RELEASE:
            dragging = 0
            

    elif button == glfw.MOUSE_BUTTON_RIGHT:                             # click mouse right
        if action == glfw.PRESS:
            dragging = 2
            glfw.set_cursor_pos_callback(window, cursor_callback)

        elif action == glfw.RELEASE:
            dragging = 0


#mouse wheel callback
def scroll_callback(window, xoffset, yoffset):
    global  zoom, yStart, xStart
    if yoffset < 0:
        zoom -= yoffset
    elif yoffset > 0:
        zoom -= yoffset
    
    xStart = xoffset
    yStart = yoffset
    

#drag call back
def cursor_callback(window, xpos, ypos):
    global zoom, xStart, yStart, xRotate, yRotate, zRotate, xTrans, yTrans
    if dragging == 1:
        yRotate -= xpos - xStart
        xRotate += ypos - yStart
    elif dragging == 2:
        yTrans += xpos - xStart
        xTrans += ypos - yStart

    xStart = xpos
    yStart = ypos


#key call back
def key_callback(window, key, scanfcode, action, mods):
    global zflag, sflag
    if action == glfw.PRESS or action ==glfw.REPEAT:
        if key == glfw.KEY_Z:
            if zflag == 0:
                zflag = 1
            else:
                zflag = 0

        elif key == glfw.KEY_S:
            if sflag == 0:
                #glShadeModel(GL_SMOOTH)
                sflag = 1
            else:
                #glShadeModel(GL_FLAT)
                sflag = 0
#drop call back
def drop_callback(window, paths):
    global vertices, normals, faces, dropped, gVertexArraySeparate, zflag, sflag
    numV3 = 0       # number of faces with 3 vertices
    numV4 = 0       # number of faces with 4 vertices
    numV_more = 0   # number of faces with more than 4 vertices
    dropped = 1
    
    #fileName
    fileName = paths[0].split('\\')[-1]
    
    # check it is .obj file or not
    if(fileName.split('.')[1] != "obj"):
       print("Not .obj file")
       return
    
    # open file
    with open(paths[0]) as f:
        lines = f.readlines()    # read each line from file
        
        # Check vertices
        # strip('~'): delete something inside ( ) left side and right side
        # startswith(' '): check string start with ( )
        vStrings = [x.strip('v') for x in lines if x.startswith('v ')]
        vertices = convert(vStrings)
        if np.amax(vertices) <= 1.2:    # amax: return max value in array
            vertices /= np.amax(vertices)
        else:
            vertices /= np.amax(vertices)/2
        
        # Check normals
        vnStrings = [x.strip('vn') for x in lines if x.startswith('vn')]
        # no normal vectors in file
        if not vnStrings:  
            # len(): size of ( )
            normals = NormalArray(len(vStrings))
        else:
            normals = convert(vnStrings)
        
        # Check faces
        faces = [x.strip('f') for x in lines if x.startswith('f')]
    
    # Increase face count
    for face in faces:
        if len(face.split()) == 3:
            numV3 += 1
        elif len(face.split()) == 4:
            numV4 += 1
        else:
            numV_more +=1

    # Print info
    print("File name: ", fileName)
    print("\nTotal number of faces: ", len(faces))
    print("\nNumber of faces with 3 vertices: ", numV3)
    print("\nNumber of faces with 4 vertices: ", numV4)
    print("\nNumber of faces with more than 4 vertices: ", numV_more)
    print("\n")

    if(numV4 >0 or numV_more >0):
        faces = triangulate()
    
    gVertexArraySeparate = createVertexArraySeparate()

    zflag = 0
    sflag = 0

def NormalArray(numVertices):
    normals = np.zeros((numVertices, 3))
    i = 0
    for vertice in vertices:
        normals[i] = 1/np.sqrt(np.dot(vertice, vertice)) * np.array(vertice)
        #normals[i] = normalized(vertice)
        i += 1
    return normals

def normalized(v):
    l = np.sqrt(np.dot(v,v))
    return 1/l * np.array(v)

def convert(verticeString):
    v = np.zeros((len(verticeString), 3))
    i = 0
    for vertice in verticeString:
        j = 0
        for t in vertice.split():
            try:
                v[i][j] = (float(t))
            except ValueError:
                pass
            j+=1
        i+=1
    return v

def triangulate():
    facelist = []
    nPolygons = []
    for face in faces:
        if(len(face.split()) >= 4):
            nPolygons.append(face)    # append: add () to list
        else:
            facelist.append(face)
    for face in nPolygons:
        for i in range(1, len(face.split())-1):
            seq = [str(face.split()[0]), str(face.split()[i]), str(face.split()[i+1])]
            string = ' '.join(seq)  #join( ): change ( ) to string
            facelist.append(string)
    return facelist

def createVertexArraySeparate():
    varr = np.zeros((len(faces)*6, 3), 'float32')
    i = 0
    normalIndex = 0
    verticeIndex = 0
    for face in faces:
        for f in face.split():
            if '//' in f:
                verticeIndex = int(f.split('//')[0])-1
                normalIndex = int(f.split('//')[1])-1
            elif '/' in f:
                if len(f.split('/')) == 2:
                    verticeIndex = int(f.split('/')[0])-1
                    normalIndex = int(f.split('/')[0])-1
                else:
                    verticeIndex = int(f.split('/')[0])-1
                    normalIndex = int(f.split()[2])-1
            else:
                verticeIndex = int(f.split()[0])-1
                normalIndex = int(f.split()[0])-1
            varr[i] = normals[normalIndex]
            varr[i+1] = vertices[verticeIndex]
            i += 2
    return varr

def main():
    global gVertexArraySeparate
    if not glfw.init():
        return
    window = glfw.create_window(1028,800,'2017030155-class2', None,None)
    if not window:
        glfw.terminate()
        return
    glfw.make_context_current(window)
    glfw.set_key_callback(window, key_callback)
    glfw.set_mouse_button_callback(window, button_callback)
    glfw.set_scroll_callback(window, scroll_callback)
    glfw.set_drop_callback(window, drop_callback)
    while not glfw.window_should_close(window):
        glfw.poll_events()
        render()
        glfw.swap_buffers(window)

    glfw.terminate()

if __name__ == "__main__":
    main()