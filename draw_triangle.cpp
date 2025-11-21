//video: https://www.youtube.com/watch?v=45MIykWJ-C4 until 30min is what this code is. 

/*
                                                    What does this program do?

                    Draws a triangle by telling OpenGL to use the triangle primitive between three vertices. 0, 1, and 2. 
*/


#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std; 

//openGL does not provide defaults for vertex and fragment shaders, have to write our own. 
//these are the shader scene (WILL HAVE TO LOOK MORE INTO THIS MYSELF AS THE VIDEO I'M WATHCING DOESN'T COVER THIS)

//specifying the coordinates of our vertices. We are working in 2D, so ignore z axis 
//origin is located in the midle of the window. x points right, y points up
//left most part of the window is x = -1 and the right most is x = 1, similar for y. upper y = 1, lower y = -1 
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

int main(){

    glfwInit();// initialize glfw so we can use it's functions (can use it to make windows)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // glfw doesn't know our version of openGL, so we need to tell it!
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); 
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Required on macOS for forward-compatible core profile

    /*
    array of datatype GLfloat
    GLfloat over normal float because the float openGL uses might be different in size than a normal one, so to be safe we just use GLfloat
    more openGL data types: https://wikis.khronos.org/opengl/Data_Type_(GLSL)
    */
    GLfloat vertices[] = //array of vertices 
    {
        //coordinates
        //every three floats represents one coordinate 
        -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // left corner 
        0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // right corner
        0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f // upper corner
        //equilatarol triangle
    };

    // window itself                    width, height, name, fullscreen, "not important apparently"
    GLFWwindow* window = glfwCreateWindow(800, 800, "Draw Triangle", NULL, NULL);
    // error handling if window fails 
    if(window == NULL){
        cout << "Failed to create GLFW window" << endl; 

        return -1; 
    }
    // "glfw isn't the smartest kid on the block, we need to tell it to actually use the window we just created"
    glfwMakeContextCurrent(window); // use window 

    //time to use GLAD (the way it was done in tutorial is old, new way to initialize below)
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 800, 800); // tell openGL the area of our window we want it to render in. from bottom left (0, 0) to (800, 800)



    //SHADERS
    //-----------------------------------------------------------
    /*
    all objects in OpenGL are accessed by references/values.
    GLuint = openGL version of unsigned int (non negative, int x >= 0)
    so below is where we are storing our reference to our vertext shader. 

    use 'glCreateShader' to create shader and get ref value, then specifify the type of shader. 
    */
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER); // vertex shader
    //            ref value, 1 screen, point to source code, 'doesn't matter'  
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); // feeding it the source code from earlier (above main())
    //GPU can't understand source code, so we need to compile it to machine code NOW
    glCompileShader(vertexShader); 

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); // creating ref for fragment shader
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL); // feed it the source code 
    glCompileShader(fragmentShader); //compile it now, GPU can't understand source code. 


    //in order to use these shaders, we need to wrap them in a "shader program"
    GLuint shaderProgram = glCreateProgram(); //don't need to specify anything, one type of shader program

    //attaching shaders to shader program
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader); 

    //after attaching, we need to wrap up the shader program. 
    glLinkProgram(shaderProgram);

    //keep it tidy, delete shaders we created before because they are already in the program itself... ??
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader); 

    //-----------------------------------------------------------
    //BUFFERS

    //BUFFERS for sending things from cpu to gpu
    //sending data too and fro is slow, so sending in big batches is better. known as buffers, this is the way. (NOT ANYTHING TO DO WITH GRAPHICS BUFFERS)
    GLuint VAO, VBO; //vertext buffer object and vertext attribute object 

    //generate VAO
    glGenVertexArrays(1, &VAO); //GENERATE VAO BEFORE VBO
    //only have 1, then point it to the ref
    glGenBuffers(1, &VBO);//generate the VBO, VBO stores raw vertex data (position, color, normals (vectors for lighting calcs), texture coordniates for mapping textures)

    //BINDING
    glBindVertexArray(VAO); //bind VAO so we can work with it
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    //then send the vertex data to the GPU
    //specifiy type of buffer, total size of data in bytes, actual data itself (vertices), specifiy use of data. (bunch of differnt ones like stream, dynamic, static. Then draw, read, copy)
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //nicely packed object now with vertex data!

    //configure VAO so openGL knows how to read the VBO
    glVertexAttribPointer(
        0,                  // attribute location, this matches line 23 from our source 
        3,                  // this is the size/how many components each vertex has (x, y, z), even though we don't use z
        GL_FLOAT,           // this tells openGL what data type the components are, we defined them as GLfloat earlier for our vertices[]
        GL_FALSE,           // should OpenGL normalize the data? floats usually want FALSE.
        3 * sizeof(float),  // stride. How many bytes to skip to get from one vertex to the next? 
        (void*)0            // where does this attribute start in the buffer. 0 means beginning 
    );
    glEnableVertexAttribArray(0);//enable the attribute so GPU uses it, location 0

    //this isn't mandatory, nice to have so we don't accidently change a VBO or VAO later
    //this is like "closing the file" after editing it
    //we unbind them so they can't be messed with
    //ORDER important here. 
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //-----------------------------------------------------------

    // code for frame buffers...
    glClearColor(0.07f, 0.20f, 0.17f, 1.0f); // clear buffer and give another color (BACK BUFFER)
    glClear(GL_COLOR_BUFFER_BIT); // want opengl to execute the command, specifying on color buffer (is this the front buffer? either way the front buffer will still have the default color)
    //need to swap buffers to see color
    glfwSwapBuffers(window); 


    //need while loop to keep open until WE say close 
    while(!glfwWindowShouldClose(window)) // render loop
    {

        glClearColor(0.07f, 0.20f, 0.17f, 1.0f); 
        glClear(GL_COLOR_BUFFER_BIT); 
        glUseProgram(shaderProgram); //activate shader program
        glBindVertexArray(VAO); //bind the vao, telling openGL that we want to use this one
        glDrawArrays(GL_TRIANGLES, 0, 3); //specify type of primitive, starting index of vertices, number of verteces we want to draw 
        glfwSwapBuffers(window); //make sure to swap buffers to the image actually gets drawn

        //tell glfw to process all poll events - window resize, appearing, etc. Window won't respond if you don't do this
        glfwPollEvents(); 
    }

    //keep it clean and delete objects we've created so far. 
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram); 

    glfwDestroyWindow(window); // once done with window, need to delete
    glfwTerminate(); // make sure to close glfw when done
    return 0; 
}