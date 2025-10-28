#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/ext.hpp>

const char* vertexSrc =
    R"glsl(
    #version 330 core
    layout (location = 0) in vec3 aPos;
    uniform mat4 projection;
    uniform vec3 offset;
    uniform vec3 scale;

    void main()
    {
        gl_Position = projection * vec4((aPos * scale) + offset,1.0);
    }
    )glsl";

const char* fragmentSrc =
    R"glsl(
    #version 330 core
    out vec4 FragColor;

    void main()
    {
        FragColor = vec4(0.2,0.7,0.3,1.0);
    }
    )glsl";

//temporary
unsigned int shaderProgram;
unsigned int vbo, vao, ebo;
unsigned int offsetUniformLoc;
unsigned int scaleUniformLoc;
unsigned int projUniformLoc;

//these header
void loadShaders();
void loadRectangle();

glm::mat4 projection;

int main() {
    if (!glfwInit()) return -1;
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL + MinGW", nullptr, nullptr);
    projection = glm::ortho(0.0,800.0,0.0,600.0,-1.0,1.0);
    if (!window) return -1;
    glfwMakeContextCurrent(window);
    glewInit();
    loadShaders();
    loadRectangle();
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(vao);

        glUniformMatrix4fv(projUniformLoc, 1, GL_FALSE, glm::value_ptr(projection));
        glUniform3f(offsetUniformLoc,250.0,250.0,0.0);
        glUniform3f(scaleUniformLoc,50.0,100.0,1.0);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
}

void loadShaders(){
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, vertexSrc, nullptr);
    glCompileShader(vertexShader);
    
    
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSrc, nullptr);
    glCompileShader(fragmentShader);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    offsetUniformLoc = glGetUniformLocation(shaderProgram, "offset");
    scaleUniformLoc = glGetUniformLocation(shaderProgram, "scale");
    projUniformLoc = glGetUniformLocation(shaderProgram, "projection");
}

void loadRectangle(){
    float vertices[] = {
        0.5, 0.5, 0.0,
        -0.5, 0.5, 0.0,
        -0.5,-0.5, 0.0,
        0.5,-0.5, 0.0
    };

    unsigned int indices[] = {
        0,1,2,
        0,2,3
    };

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}
