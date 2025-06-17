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

    void setUniform1i(const std::string& loc, int v);
    void setUniform2i(const std::string& loc, int v0, int v1);
    void setUniform3i(const std::string& loc, int v0, int v1, int v2);
    void setUniform4i(const std::string& loc, int v0, int v1, int v2, int v3);

    void setUniform1f(const std::string& loc, float v);
    void setUniform2f(const std::string& loc, float v0, float v1);
    void setUniform3f(const std::string& loc, float v0, float v1, float v2);
    void setUniform4f(const std::string& loc, float v0, float v1, float v2, float v3);

    void setUniformMat3f(const std::string& loc, const glm::mat3& m);
    void setUniformMat4f(const std::string& loc, const glm::mat4& m);

private:
    uint32_t compileShader(uint32_t type, const std::string& source);
    uint32_t createShader(const std::string& vertexSource, const std::string& fragmentSource);
    GLint getUniformLocation(const std::string& name) const;
    static ShaderProgramSource parseShader(const std::string& path);

private:
    uint32_t m_rendererID;
    std::string m_filePath;
    mutable std::unordered_map<std::string, GLint> m_uniformLocationCache; 
};