//
//  main.cpp
//  testOGL
//
//  Created by Ricky Whutever on 11/3/16.
//  Copyright © 2016 Ricky Herrera. All rights reserved.
//

#include <iostream>
#include <GL/glew.h> /* glew  Library */
#include <GLFW/glfw3.h> /*glfw library*/

void render(void){
    /*Initalize the buffer bit in black*/
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    /*Initialize the triangle with corresponding vertices
     at 1,0,0 , 0,1,0, and 0,0,1.  */
    glBegin(GL_TRIANGLES);{
        glColor3f(1.0, 0.0, 0.0);
        glVertex2f(0, 0.5);
        glColor3f(0.0, 1.0, 0.0);
        glVertex2f(-0.5, -0.5);
        glColor3f(0.0, 0.0, 1.0);
        glVertex2f(0.5, -0.5);
    }
    glEnd();
    
}

int main(int argc, const char * argv[]) {
    GLFWwindow *win;
    /*if GLFW not initialize we return an error. */
    if (!glfwInit()){
        return -1;
        
    }
    win = glfwCreateWindow( 640, 480, "whatsupOpenGL", NULL, NULL);
    if (!win){
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    
    if(!glewInit()){
        return -1;
    }
    
    glfwMakeContextCurrent(win);
    while(!glfwWindowShouldClose(win)){
        render();
        glfwSwapBuffers(win);
        glfwPollEvents();
        
    }
    glfwTerminate();
    exit(EXIT_SUCCESS);
    return 0;
}
