#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 500

int main( void ) {
    
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
    
    glColor3f(0,0,1);
    GLfloat polygonVertices[] = {
        200,200,0,
        300,200,0,
        330,295,0,
        250,355,0,
        170,295,0
    };
    
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

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