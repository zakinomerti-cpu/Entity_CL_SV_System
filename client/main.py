import socket
import struct
import glfw
from OpenGL.GL import *
from OpenGL.GLU import *

# UDP setup
IP = "0.0.0.0"
PORT = 9000
BUFFER_SIZE = 65535
FORMAT = "<32s32sfffffffff"  # name, type, pos(3), rot(3), scl(3)

# Draw simple cube centered at origin
def draw_cube():
    glBegin(GL_QUADS)
    # Front
    glColor3f(1,0,0)
    glVertex3f(-0.5,-0.5,0.5)
    glVertex3f(0.5,-0.5,0.5)
    glVertex3f(0.5,0.5,0.5)
    glVertex3f(-0.5,0.5,0.5)
    # Back
    glColor3f(0,1,0)
    glVertex3f(-0.5,-0.5,-0.5)
    glVertex3f(0.5,-0.5,-0.5)
    glVertex3f(0.5,0.5,-0.5)
    glVertex3f(-0.5,0.5,-0.5)
    # Left
    glColor3f(0,0,1)
    glVertex3f(-0.5,-0.5,-0.5)
    glVertex3f(-0.5,-0.5,0.5)
    glVertex3f(-0.5,0.5,0.5)
    glVertex3f(-0.5,0.5,-0.5)
    # Right
    glColor3f(1,1,0)
    glVertex3f(0.5,-0.5,-0.5)
    glVertex3f(0.5,-0.5,0.5)
    glVertex3f(0.5,0.5,0.5)
    glVertex3f(0.5,0.5,-0.5)
    # Top
    glColor3f(1,0,1)
    glVertex3f(-0.5,0.5,-0.5)
    glVertex3f(0.5,0.5,-0.5)
    glVertex3f(0.5,0.5,0.5)
    glVertex3f(-0.5,0.5,0.5)
    # Bottom
    glColor3f(0,1,1)
    glVertex3f(-0.5,-0.5,-0.5)
    glVertex3f(0.5,-0.5,-0.5)
    glVertex3f(0.5,-0.5,0.5)
    glVertex3f(-0.5,-0.5,0.5)
    glEnd()

# Init GLFW
if not glfw.init():
    raise Exception("GLFW can't initialize")

window = glfw.create_window(800,600,"Entity Visualizer",None,None)
glfw.make_context_current(window)

glEnable(GL_DEPTH_TEST)
glClearColor(0.1,0.1,0.1,1)

# Perspective projection
glMatrixMode(GL_PROJECTION)
glLoadIdentity()
gluPerspective(45, 800/600, 0.1, 100)
glMatrixMode(GL_MODELVIEW)

# UDP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind((IP, PORT))
sock.setblocking(False)

# Initial transform
pos = [0.0,0.0,0.0]
rot = [0.0,0.0,0.0]
scl = [1.0,1.0,1.0]

while not glfw.window_should_close(window):
    glfw.poll_events()

    # Try to get UDP
    try:
        data, addr = sock.recvfrom(BUFFER_SIZE)
        if len(data) >= struct.calcsize(FORMAT):
            unpacked = struct.unpack(FORMAT, data[:struct.calcsize(FORMAT)])
            pos = list(unpacked[2:5])
            rot = list(unpacked[5:8])
            scl = list(unpacked[8:11])
    except BlockingIOError:
        pass

    # Clear
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glLoadIdentity()

    # Camera
    gluLookAt(5,5,5, 0,0,0, 0,1,0)

    # Apply cube transform: scale -> rotate -> translate
    glTranslatef(*pos)
    glRotatef(rot[0],1,0,0)
    glRotatef(rot[1],0,1,0)
    glRotatef(rot[2],0,0,1)
    glScalef(*scl)

    # Draw cube
    draw_cube()

    glfw.swap_buffers(window)

glfw.terminate()
