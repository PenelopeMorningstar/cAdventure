#include "renderer/shader.hpp"


void Shader::LoadFragmentSource(std::string filename){
    std::string loaded_src = LoadFileContents(filename);
    const char* src = loaded_src.c_str();
    fragment_shader_ = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader_, 1, &src, nullptr);
    glCompileShader(fragment_shader_);
}

void Shader::LoadVertexSource(std::string filename) {
    std::string loaded_src = LoadFileContents(filename);
    const char* src = loaded_src.c_str();
    vertex_shader_ = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader_, 1, &src, nullptr);
    glCompileShader(vertex_shader_);
}

void Shader::CompileShader(){
    program_index_ = glCreateProgram();
    glAttachShader(program_index_, vertex_shader_);
    glAttachShader(program_index_, fragment_shader_);
    glLinkProgram(program_index_);
    glDeleteShader(vertex_shader_);
    glDeleteShader(fragment_shader_);
}

void Shader::RegisterUniform(std::string identifier, UniformType uniform_type, int position)
{
    //perform opengl stuff
    const char* src = identifier.c_str();
    unsigned int loc = glGetUniformLocation(program_index_, src);
    UniformStruct u = {loc,uniform_type};
    uniforms_[position] = u;

}

void Shader::SetUniformValues(std::any values[])
{
    for(int i = 0; i < uniform_count_; i++){
        switch (uniforms_[i].uniform_type)
        {
        case UNIFORM_1F:{
            float val = std::any_cast<float>(values[i]);
            glUniform1f(uniforms_[i].uniform_loc, val);
            break;
        }
        case UNIFORM_2F:{
            glm::vec2 val = std::any_cast<glm::vec2>(values[i]);
            glUniform2f(uniforms_[i].uniform_loc, val.x, val.y);
            break;
        }
        case UNIFORM_3F:{
            glm::vec3 val = std::any_cast<glm::vec3>(values[i]);
            glUniform3f(uniforms_[i].uniform_loc, val.x, val.y, val.z);
            break;
        }
        case UNIFORM_4F:{
            glm::vec4 val = std::any_cast<glm::vec4>(values[i]);
            glUniform4f(uniforms_[i].uniform_loc, val.x, val.y, val.z, val.w);
            break;
        }
    }

    }
    
}

std::string Shader::LoadFileContents(std::string filename){
    std::ifstream file(filename);
    if(!file.is_open()){
        throw std::runtime_error("Failed to open shader file: " + filename);
    }

    std::ostringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}