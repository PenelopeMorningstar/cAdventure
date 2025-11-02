#include "renderer/opengl_renderer.hpp"


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
    layout (location = 1) in vec2 aTexCoord;
    
    out vec2 TexCoord;
    
    uniform mat4 projection;
    uniform vec4 ltwh;
    uniform float rotation;



    void main()
    {
        vec2 pos = ltwh.xy + aPos.xy * ltwh.zw;
        vec2 center = ltwh.xy + ltwh.zw * 0.5;

        mat2 rot = mat2(cos(rotation), -sin(rotation),
                        sin(rotation), cos(rotation));
        pos = center + rot * (pos - center);
        gl_Position = projection * vec4(pos, 0.0, 1.0);
        TexCoord = aPos.xy;
    }
    )glsl";

const char* COLORED_RECT_FRAGMENT_SHADER =
    R"glsl(
    #version 330 core

    in vec2 TexCoord;
    
    out vec4 FragColor;
    
    uniform sampler2D tex;
    uniform vec4 color;
    

    void main()
    {
        FragColor = texture(tex, TexCoord) * color;
    }
    )glsl";


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

    unsigned int vertex_shader;
    unsigned int fragment_shader;

    // shaders

    // colored rect program
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &COLORED_RECT_VERTEX_SHADER, nullptr);
    glCompileShader(vertex_shader);
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &COLORED_RECT_FRAGMENT_SHADER, nullptr);
    glCompileShader(fragment_shader);
    colored_rect_program = glCreateProgram();
    glAttachShader(colored_rect_program, vertex_shader);
    glAttachShader(colored_rect_program, fragment_shader);
    glLinkProgram(colored_rect_program);
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    colored_rect_projection_i = glGetUniformLocation(colored_rect_program, "projection");
    colored_rect_ltwh_i = glGetUniformLocation(colored_rect_program, "ltwh");
    colored_rect_color_i = glGetUniformLocation(colored_rect_program, "color");
    colored_rect_rotation_i = glGetUniformLocation(colored_rect_program, "rotation");

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

void OpenGLRenderer::DrawRect(RectTransform& transform, Color& color){
    
    DrawRect(transform, color, nullptr, 0);
}

void OpenGLRenderer::DrawRect(RectTransform& transform, Color& color, float rotation){

    DrawRect(transform, color, nullptr, rotation);
}

void OpenGLRenderer::DrawRect(RectTransform& transform, Color& color, Texture* texture){
    DrawRect(transform, color, texture, 0);
}

void OpenGLRenderer::DrawRect(RectTransform& transform, Color& color, Texture* texture, float rotation){
    colored_rects.push_back({transform, color, texture, rotation});
}

void OpenGLRenderer::Update(){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(colored_rect_program);
    glBindVertexArray(rect_vao_);
    glUniformMatrix4fv(colored_rect_projection_i, 1, GL_FALSE, glm::value_ptr(projection_));
    while(!colored_rects.empty()){
        ColoredRectCall c = colored_rects.back();
        colored_rects.pop_back();
        glUniform4f(colored_rect_ltwh_i, c.transform.l, c.transform.t, c.transform.w, c.transform.h);
        glUniform4f(colored_rect_color_i, c.color.r, c.color.g, c.color.b, c.color.a);
        glUniform1f(colored_rect_rotation_i, c.rotation);

            glBindTexture(GL_TEXTURE_2D, c.texture->texture_id);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            GLenum format = (c.texture->n_channels == 4) ? GL_RGBA : GL_RGB;
            glTexImage2D(GL_TEXTURE_2D, 0, format, c.texture->width, c.texture->height, 0, format, GL_UNSIGNED_BYTE, c.texture->data);
            glGenerateMipmap(GL_TEXTURE_2D);
        //set textures
        
        
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }

    glfwSwapBuffers(window_);
    glfwPollEvents();

    if (glfwWindowShouldClose(window_)) {
        g_game_manager->is_running_ = false;
    }
}

void OpenGLRenderer::InitTexture(Texture* texture){

    glGenTextures(1,&texture->texture_id);
    glBindTexture(GL_TEXTURE_2D, texture->texture_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    GLenum format = (texture->n_channels == 4) ? GL_RGBA : GL_RGB;
    glTexImage2D(GL_TEXTURE_2D, 0, format, texture->width, texture->height, 0, format, GL_UNSIGNED_BYTE, texture->data);
    glGenerateMipmap(GL_TEXTURE_2D);

}

