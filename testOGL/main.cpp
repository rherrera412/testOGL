/* Attempt to learn OpenGL basics, using glew and glfw
 https://github.com/SonarSystems/Modern-OpenGL-Tutorials/
 */

#include <iostream>
#include <GL/glew.h> /* glew  Library */
#include <GLFW/glfw3.h> /*glfw library*/

/* Window dimensions */
const GLuint WIDTH = 800, HEIGHT = 600;

// Shaders
const GLchar* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"void main(){\n"
"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
"}\0";

/* Color of the triangle. #ed2d4a */
const GLchar* fragmentShaderSource = "#version 330 core\n"
"out vec4 color;\n"
"void main(){\n"
"color = vec4(.929f, .176f, .29f, 1.0f);\n"
"}\n\0";

int main(){
    glfwInit( );
    
    /* Set all the required options for GLFW */
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
    
    glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );
    
    /* Create a GLFWwindow object that we can use for GLFW's functions */
    GLFWwindow *window = glfwCreateWindow( WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr );
    
    int screenWidth, screenHeight;
    glfwGetFramebufferSize( window, &screenWidth, &screenHeight );
    
    if ( nullptr == window ) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate( );
        return EXIT_FAILURE;
    }
    
    glfwMakeContextCurrent( window );
    
    /* Set this to true so GLEW knows to use a modern
       approach to retrieving function pointers and extensions */
    glewExperimental = GL_TRUE;
    
    /* Initialize GLEW to setup the OpenGL Function pointers */
    if ( GLEW_OK != glewInit( ) ) {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }
    
    /* Define the viewport dimensions */
    glViewport( 0, 0, screenWidth, screenHeight );
    
    
    /* Build and compile our shader program
       Vertex shader */
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER );
    glShaderSource(vertexShader, 1,&vertexShaderSource,NULL );
    glCompileShader(vertexShader );
    
    /* Check for compile time errors */
    GLint success;
    GLchar infoLog[512];
    
    /* Error message for an unsuccessful attempt. */
    glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&success);
    if (!success) {
        glGetShaderInfoLog( vertexShader, 512, NULL, infoLog );
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    /* Fragment shader followed by a 
       check for compile time errors */
    GLuint fragmentShader = glCreateShader( GL_FRAGMENT_SHADER );
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL );
    glCompileShader( fragmentShader );
    
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog( fragmentShader, 512, NULL, infoLog );
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    /* Link shaders followed by a 
       check for errors.  Delete the vertexShader
       and fragmentShader in case of error. */
    GLuint shaderProgram = glCreateProgram( );
    glAttachShader( shaderProgram, vertexShader );
    glAttachShader( shaderProgram, fragmentShader );
    glLinkProgram( shaderProgram );
    
    glGetProgramiv( shaderProgram, GL_LINK_STATUS, &success );
    if ( !success ) {
        glGetProgramInfoLog( shaderProgram, 512, NULL, infoLog );
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader( vertexShader );
    glDeleteShader( fragmentShader );
    
    
    /* Set up vertex data (and buffer(s)) and attribute pointers */
    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f, // Left
        0.5f, -0.5f, 0.0f,  // Right
        0.0f,  0.5f, 0.0f   // Top
    };
    
    GLuint VBO, VAO;
    glGenVertexArrays( 1, &VAO );
    glGenBuffers( 1, &VBO );
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray( VAO );
    
    glBindBuffer( GL_ARRAY_BUFFER, VBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW );
    
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*) 0 );
    glEnableVertexAttribArray( 0 );
    
    glBindBuffer( GL_ARRAY_BUFFER, 0 ); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind
    
    glBindVertexArray( 0 ); // Unbind VAO
    
    /* Game loop - Check if any events have been activiated and calls 
       corresponding response functions. Render and clear the color 
       buffer. First triangle is drawn out. Swap the screen buffers. */
    while ( !glfwWindowShouldClose( window ) ) {
        glfwPollEvents( );
        
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
        glClear( GL_COLOR_BUFFER_BIT );
        
        glUseProgram( shaderProgram );
        glBindVertexArray( VAO );
        glDrawArrays( GL_TRIANGLES, 0, 3 );
        glBindVertexArray( 0 );
        
        glfwSwapBuffers( window );
    }
    
    /* Properly de-allocate all resources once they've outlived their purpose */
    glDeleteVertexArrays( 1, &VAO );
    glDeleteBuffers( 1, &VBO );
    
    /* Terminate GLFW, clearing any resources allocated by GLFW. */
    glfwTerminate( );
    
    return EXIT_SUCCESS;
}

void render(void){
    /* Initalize the buffer bit in black*/
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    /* Initialize the triangle with corresponding RGB */
    glBegin(GL_TRIANGLES);{
        glColor3f(.929, .439, .176);
        glVertex2f(0, 0.5);
        glColor3f(.929, .816, .176);
        glVertex2f(-0.5, -0.5);
        glColor3f(.929, .176, .29);
        glVertex2f(0.5, -0.5);
    }
    glEnd();
}


int boop(int argc, const char * argv[]) {
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
