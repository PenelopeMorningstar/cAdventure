#include "renderer/opengl_renderer.hpp"
#include <stdio.h>
#include <unordered_map>


const float RECT_VERTICES[] = {
    1, 1, 0.0,
    0, 1, 0.0,
    0,0, 0.0,
    1,0, 0.0
};

const unsigned int RECT_INDICES[] = {
    0,1,2,
    0,2,3
};

const char* COLORED_RECT_VERTEX_SHADER =
    R"glsl(
    #version 330 core
    layout (location = 0) in vec3 aPos;
    uniform mat4 projection;
    uniform vec4 ltwh;

    void main()
    {
        float x = ltwh.x + aPos.x * ltwh.z;
        float y = ltwh.y + aPos.y * ltwh.w;

        gl_Position = projection * vec4(x,y,0.0,1.0);
    }
    )glsl";

const char* COLORED_RECT_FRAGMENT_SHADER =
    R"glsl(
    #version 330 core
    out vec4 FragColor;
    uniform vec4 color;

    void main()
    {
        FragColor = vec4(0,1,0,1.0);
    }
    )glsl";

unsigned int colored_rect_program;
unsigned int colored_rect_projection_i;
unsigned int colored_rect_ltwh_i;
unsigned int colored_rect_color_i;
unsigned int vertexShader;
unsigned int fragmentShader;

bool OpenGLRenderer::ConfigureDisplay(){
    // true = success; false = failure

    if (!glfwInit()) return false;
    window_ = glfwCreateWindow(screen_width_, screen_height_, display_title_.c_str(), nullptr, nullptr);
    projection_ = glm::ortho(0.0f, (float)screen_width_, (float)screen_height_, 0.0f, -1.0f, 1.0f);
    if (!window_) return false;
    
    glfwMakeContextCurrent(window_);
    glViewport(0, 0, screen_width_, screen_height_);
    glewInit();

    const GLubyte* v = glGetString(GL_VERSION);
    printf("OpenGL Version: %s\n", v);


    // shaders
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &COLORED_RECT_VERTEX_SHADER, nullptr);
    glCompileShader(vertexShader);

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &COLORED_RECT_FRAGMENT_SHADER, nullptr);
    glCompileShader(fragmentShader);

    colored_rect_program = glCreateProgram();
    glAttachShader(colored_rect_program, vertexShader);
    glAttachShader(colored_rect_program, fragmentShader);
    glLinkProgram(colored_rect_program);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    colored_rect_projection_i = glGetUniformLocation(colored_rect_program, "projection");
    colored_rect_ltwh_i = glGetUniformLocation(colored_rect_program, "ltwh");
    colored_rect_color_i = glGetUniformLocation(colored_rect_program, "color");

        // rectangle initialization
    glGenVertexArrays(1, &rect_vao_);
    glGenBuffers(1, &rect_vbo_);
    glGenBuffers(1, &rect_ebo_);
    glBindVertexArray(rect_vao_);
    glBindBuffer(GL_ARRAY_BUFFER, rect_vbo_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(RECT_VERTICES), RECT_VERTICES, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rect_ebo_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(RECT_INDICES), RECT_INDICES, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    return true;
}

void OpenGLRenderer::Exit(){
    glfwTerminate();
}

bool OpenGLRenderer::CreateDisplay(){
    // true = success; false = failure
    return true;
}

void OpenGLRenderer::DrawRect(int left, int top, int width, int height){
    DrawRect(left,top,width,height,0);
}

void OpenGLRenderer::DrawRect(int left, int top, int width, int height, float rotation){
    glUseProgram(colored_rect_program);
    glBindVertexArray(rect_vao_);

    glUniformMatrix4fv(colored_rect_projection_i, 1, GL_FALSE, glm::value_ptr(projection_));
    glUniform4f(colored_rect_ltwh_i, left, top, width, height);
    glUniform4f(colored_rect_color_i, 1, 1, 1, 1);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void OpenGLRenderer::Update(){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    DrawRect(10,10,100,100);

    glfwSwapBuffers(window_);
    glfwPollEvents();

    if (glfwWindowShouldClose(window_)) {
        g_game_manager->is_running_ = false;
    }
}