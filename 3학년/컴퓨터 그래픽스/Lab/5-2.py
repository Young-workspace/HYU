import glfw
from OpenGL.GL import *
from OpenGL.GLU import *
import numpy as np


def render(M):
    glClear(GL_COLOR_BUFFER_BIT)
    glLoadIdentity()
    
    drawFrame()
    glColor3ub(255, 255, 255)
    drawTriangle()

    
    th = np.radians(30)
    R = np.identity(4)
    R[:3,:3] = [[np.cos(th),-np.sin(th),0.],
               [np.sin(th), np.cos(th), 0.],
               [0., 0., 1.]]
    
    T = np.identity(4)
    T[:3,3] = [0.6, 0., 0.]

    glMultMatrixf((T@R).T)
    drawFrame()
    
    glColor3ub(0,0,255)
    
    
    drawTriangle()
    

def drawFrame():
    glBegin(GL_LINES)
    glColor3ub(255, 0, 0)
    glVertex2fv(np.array([0., 0.]))
    glVertex2fv(np.array([1., 0.]))
    glColor3ub(0, 255, 0)
    glVertex2fv(np.array([0., 0.]))
    glVertex2fv(np.array([0., 1.]))
    glEnd()

def drawTriangle():
    glBegin(GL_TRIANGLES)
    glVertex2fv(np.array([0., .5]))
    glVertex2fv(np.array([0., 0.]))
    glVertex2fv(np.array([.5, 0.]))
    glEnd()

def main():
    if not glfw.init():
        return
    window = glfw.create_window(480,480,"학번-5-2", None,None)
    if not window:
        glfw.terminate()
        return
    glfw.make_context_current(window)
    glfw.swap_interval(1)

    while not glfw.window_should_close(window):
        glfw.poll_events()


        t = glfw.get_time()
        th = t
        T = np.array([[np.cos(th), -np.sin(th),0.],
                      [np.sin(th), np.cos(th),0.],
                      [0.,         0.,        1.]])
        render(T)
        glfw.swap_buffers(window)

    glfw.terminate()

if __name__ == "__main__":
    main()
