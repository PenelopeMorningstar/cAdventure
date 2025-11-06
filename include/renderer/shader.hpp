#pragma once
#include "common.hpp"

enum UniformType {
    UNIFORM_1F,
    UNIFORM_2F,
    UNIFORM_3F,
    UNIFORM_4F,
    UNIFORM_MATRIX_4
};

struct UniformStruct{
    unsigned int uniform_loc;
    UniformType uniform_type;
};

class Shader{
    public:
        void LoadFragmentSource(std::string source);
        void LoadVertexSource(std::string source);
        void RegisterUniform(std::string identifier, UniformType uniform, int position);
        void SetUniformValues(std::any values[]);
        void CompileShader();
        unsigned int program_index_;
    private:
        int uniform_count_;
        UniformStruct uniforms_[16];
        unsigned int fragment_shader_;
        unsigned int vertex_shader_;
        std::string LoadFileContents(std::string filename);
};



//Creating a shader:
//  Shader* lit_rect = new Shader(4);
    // lit_rect->SetFragmentSource("PathToSrc.glsl");
    // lit_rect->SetVertexSource("PathToSrc.glsl");
    // lit_rect->RegisterUniform("projection",UNIFORM_MATRIX_4,-1);
    // lit_rect->RegisterUniform("ltwh",UNIFORM_4F,0);
    // lit_rect->RegisterUniform("color",UNIFORM_4F,1);
    // lit_rect->RegisterUniform("rotation",UNIFORM_1F,2);
    // RectTransform t = {10,10,100,100};
    // Color c = {1.0,1.0,1.0,1.0};
    // RectTransform r2 = {110,10,200,100};
    // std::any value[] = {t,c,r2};


    // lit_rect->SetUniformValues(value*);
    