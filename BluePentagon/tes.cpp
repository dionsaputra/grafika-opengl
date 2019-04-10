#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 500
#define M_PI = 3.14

int main() {
    
    if (!glfwInit()) {
        return -1;
    }

    GLFWwindow *window;
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Blue Pentagon", NULL, NULL);
    
    if (!window){
        glfwTerminate( );
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    glViewport(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT);
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity( ); 
    glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 1); 
    glMatrixMode(GL_MODELVIEW); 
    glLoadIdentity(); 
    
    float radius, halfLength;
    int slices;
    for(int i=0; i<slices; i++) {
        float theta = ((float)i)*2.0*M_PI;
        float nextTheta = ((float)i+1)*2.0*M_PI;
        glBegin(GL_TRIANGLE_STRIP);
        /*vertex at middle of end */ glVertex3f(0.0, halfLength, 0.0);
        /*vertices at edges of circle*/ glVertex3f(radius*cos(theta), halfLength, radius*sin(theta));
                                                glVertex3f (radius*cos(nextTheta), halfLength, radius*sin(nextTheta));
        /* the same vertices at the bottom of the cylinder*/
        glVertex3f (radius*cos(nextTheta), -halfLength, radius*sin(nextTheta));
        glVertex3f(radius*cos(theta), -halfLength, radius*sin(theta));
        glVertex3f(0.0, -halfLength, 0.0);
        glEnd();
    }



    while ( !glfwWindowShouldClose( window ) )
    {
        glClear( GL_COLOR_BUFFER_BIT );

        glEnableClientState( GL_VERTEX_ARRAY );
        glVertexPointer( 3, GL_FLOAT, 0, polygonVertices );
        glDrawArrays( GL_POLYGON, 0, 5 );
        glDisableClientState( GL_VERTEX_ARRAY );
        
        glfwSwapBuffers( window );
        
        glfwPollEvents( );
    }
    
    glfwTerminate( );
    
    return 0;
}