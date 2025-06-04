#pragma once

struct ShaderProgramSource{
    std::string vertexSource;
    std::string fragmentSource;
};  

class Shader{
public:
    Shader(const std::string& path);
    ~Shader();

    void bind() const;
    void unbind() const;

    void setUniform4f(const std::string& loc, float v0, float v1, float v2, float v3);

private:
    uint32_t compileShader(uint32_t type, const std::string& source);
    uint32_t createShader(const std::string& vertexSource, const std::string& fragmentSource);
    int32_t getUniformLocation(const std::string& name);
    static ShaderProgramSource parseShader(const std::string& path);

private:
    uint32_t m_rendererID;
    std::string m_filePath;
    std::unordered_map<std::string, int32_t> m_uniformLocationCache; 
};