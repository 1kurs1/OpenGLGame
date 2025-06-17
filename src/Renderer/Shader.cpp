#include "pch.h"
#include "Shader.h"


Shader::Shader(const std::string& path) : m_filePath(path){
    ShaderProgramSource src = parseShader(path);
    m_rendererID = createShader(src.vertexSource, src.fragmentSource);
}

Shader::~Shader(){
    glDeleteShader(m_rendererID);
}

ShaderProgramSource Shader::parseShader(const std::string& path){
    std::ifstream stream(path);

    enum class ShaderType{
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while(getline(stream, line)){
        if(line.find("#shader") != std::string::npos){
            if(line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if(line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else ss[(int)type] << line << '\n';
    }

    return { ss[0].str(), ss[1].str() };
}

uint32_t Shader::compileShader(uint32_t type, const std::string& source){
    uint32_t id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if(result == GL_FALSE){
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "failed to compile shader " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader:\n";
        std::cout << message << '\n';
        glDeleteShader(id);
        return 0;
    }

    return id;
}

uint32_t Shader::createShader(const std::string& vertexSource, const std::string& fragmentSource){
    uint32_t program = glCreateProgram();
    uint32_t vs = compileShader(GL_VERTEX_SHADER, vertexSource);
    uint32_t fs = compileShader(GL_FRAGMENT_SHADER, fragmentSource);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

void Shader::bind() const {
    glUseProgram(m_rendererID);
}

void Shader::unbind() const {
    glUseProgram(0);
}

// integer:
void Shader::setUniform1i(const std::string& loc, int v){
    glUniform1i(getUniformLocation(loc), v);
}

void Shader::setUniform2i(const std::string& loc, int v0, int v1){
    glUniform2i(getUniformLocation(loc), v0, v1);
}

void Shader::setUniform3i(const std::string& loc, int v0, int v1, int v2){
    glUniform3i(getUniformLocation(loc), v0, v1, v2);
}

void Shader::setUniform4i(const std::string& loc, int v0, int v1, int v2, int v3){
    glUniform4i(getUniformLocation(loc), v0, v1, v2, v3);
}

// floats:
void Shader::setUniform1f(const std::string& loc, float v){
    glUniform1f(getUniformLocation(loc), v);
}

void Shader::setUniform2f(const std::string& loc, float v0, float v1){
    glUniform2f(getUniformLocation(loc), v0, v1);
}

void Shader::setUniform3f(const std::string& loc, float v0, float v1, float v2){
    glUniform3f(getUniformLocation(loc), v0, v1, v2);
}

void Shader::setUniform4f(const std::string& loc, float v0, float v1, float v2, float v3){
    glUniform4f(getUniformLocation(loc), v0, v1, v2, v3);
}

// matricies:
void Shader::setUniformMat3f(const std::string& loc, const glm::mat3& m){
    glUniformMatrix3fv(getUniformLocation(loc), 1, GL_FALSE, &m[0][0]);
}

void Shader::setUniformMat4f(const std::string& loc, const glm::mat4& m){
    glUniformMatrix4fv(getUniformLocation(loc), 1, GL_FALSE, &m[0][0]);
}

GLint Shader::getUniformLocation(const std::string& name) const {
    if(m_uniformLocationCache.find(name) != m_uniformLocationCache.end())
        return m_uniformLocationCache[name];
        
    GLint loc = glGetUniformLocation(m_rendererID, name.c_str());
    if(loc == -1) 
        std::cout << "warning: uniform '" << name << "' doesn't exists!\n";
    m_uniformLocationCache[name] = loc;

    return loc;
}