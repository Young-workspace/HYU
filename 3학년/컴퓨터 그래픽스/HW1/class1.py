import glfw
from OpenGL.GL import *
from OpenGL.GLU import *
import numpy as np

viewDis = 9.
width = 600
height = 600

nearPlane = 1.
farPlane = 1000.

xRotate = 0.
yRotate = 0.
zRotate = 0.
xTrans = 0.
yTrans = 0.
zoom = 30
xStart = 0.
yStart = 0.
dragging = 0

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
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT)
    glEnable(GL_DEPTH_TEST)
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE )
    drawGrid()

    #draw 
    glColor3ub(255, 255, 255)
    t = glfw.get_time()
    
    # head
    glPushMatrix()
    glScalef(.5, .5, .5)
    glTranslate(3, 0, 0)
    glTranslate(-t/3*np.sin(60), 0, 0)
    drawSphere()
    
    #glPopMatrix()

    #body
    glPushMatrix()
    glScalef(1.7, .3, .5)
    #glTranslate(-0.35, -.5, -.127)
    glTranslate(-1.5, -.5, -.127)
    drawCube()
    glPopMatrix()
    
    #right arm
    glPushMatrix()
    glTranslate(-1.5, -.1, .6)
    glRotatef(t*(-180/np.pi), 0, 0, 1)
    glTranslate(-1.5, 0, 0)
    glScalef(-1.5, 0.15, .1)
    drawCube()
    glPopMatrix()

    #left arm
    glPushMatrix()
    glTranslate(-1.5, -.1, -.7)
    glRotatef((t+60)*(-180/np.pi), 0, 0, 1)
    glTranslate(-1.5, 0, 0)
    glScalef(-1.5, 0.15, .1)
    drawCube()
    glPopMatrix()
    
    #right leg
    glPushMatrix()
    glTranslate(-6.3, -.1, .3) 
    glScalef(2., 0.15, .15)
    
    drawCube()
    glPopMatrix()

    #left leg
    glPushMatrix()
    glTranslate(-6.3, -.1, -.3) 
    glScalef(2., 0.15, .15)
    
    drawCube()
    glPopMatrix()
    glPopMatrix()
    

    

def polarView():
    global yTrans, xTrans, zRotate, xRotate, yRotate
    glTranslatef(yTrans/100., .0, .0)
    glTranslatef(.0, -xTrans/100., .0)
    glRotatef(-zRotate, .0, .0, 1.)
    glRotatef(-xRotate, 1., .0, .0)
    glRotatef(-yRotate, .0, 1., .0)

def render():
    global zoom, viewDis, width, height, nearPlane, farPlane
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT)
    glEnable(GL_DEPTH_TEST)
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE )
    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()

    
    gluLookAt(0, 5, -viewDis, 0, 0, 0, 0, 1, 0)
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    gluPerspective(zoom, float(width)/float(height), nearPlane, farPlane)
    glMatrixMode(GL_MODELVIEW)
    
   
    polarView()
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

        
    
    
def main():
    if not glfw.init():
        return
    window = glfw.create_window(1028,1028,'2017030155-class1', None,None)
    if not window:
        glfw.terminate()
        return
    glfw.make_context_current(window)
    #glfw.set_key_callback(window, key_callback)
    glfw.set_mouse_button_callback(window, button_callback)
    glfw.set_scroll_callback(window, scroll_callback)
    while not glfw.window_should_close(window):
        glfw.poll_events()
        render()
        glfw.swap_buffers(window)

    glfw.terminate()

if __name__ == "__main__":
    main()