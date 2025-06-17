#pragma once

#include "Test.h"

#include "src/Core/Window.h"
#include "src/Renderer/Texture2D.h"

namespace test{
    class TestTexture2D : public Test{
    public:
        TestTexture2D(const std::string& texturePath = "../assets/images/nicromis_logo.png");
        ~TestTexture2D();

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;

    private:
        std::string m_texturePath;
        glm::vec3 m_modelTranslationA;
        glm::vec3 m_modelTranslationB;
        glm::vec3 m_cameraTranslation;

        glm::mat4 m_cameraView;
        glm::mat4 m_projectionMatrix;

        std::unique_ptr<VertexArray> m_VAO;
        std::unique_ptr<VertexBuffer> m_VBO;
        std::unique_ptr<IndexBuffer> m_IB;
        std::unique_ptr<Shader> m_shader;
        std::unique_ptr<Texture> m_texture;
    };
}