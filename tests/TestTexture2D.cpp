#include "src/pch.h"

#include "TestTexture2D.h"

namespace test{
    TestTexture2D::TestTexture2D(const std::string& texturePath) : m_texturePath(texturePath){
        float vertices[] = {
            -200.0f, -200.0f, 0.0f, 0.0f,
            200.0f, -200.0f, 1.0f, 0.0f,
            200.0f, 200.0f, 1.0f, 1.0f,
            -200.0f, 200.0f, 0.0f, 1.0f
        };
        uint32_t indices[] = {
            0, 1, 2,
            2, 3, 0
        };

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
        m_VAO = std::make_unique<VertexArray>();
        m_VBO = std::make_unique<VertexBuffer>(vertices, 4*4*sizeof(float));

        BufferLayout layout;
        layout.push<float>(2);
        layout.push<float>(2);
        m_VAO->addBuffer(*m_VBO, layout);
        m_IB = std::make_unique<IndexBuffer>(indices, 6);

        float aspectRatio = ((float)WINDOW_WIDTH)/((float)WINDOW_HEIGHT);
        m_projectionMatrix = glm::ortho(-1000.0f * aspectRatio, 1000.0f * aspectRatio, -1000.0f, 1000.0f, -1.0f, 1.0f);

        m_shader = std::make_unique<Shader>("../shaders/Standart.shader");
        m_shader->bind();
        
        m_texture = std::make_unique<Texture>(m_texturePath.c_str());
        m_shader->setUniform1i("u_texture", 0);

        m_modelTranslationA = glm::vec3(-300, 0, 0);
        m_modelTranslationB = glm::vec3(300, 0, 0);
        m_cameraTranslation = glm::vec3(0, 0, 0);
    }


    TestTexture2D::~TestTexture2D(){}

    void TestTexture2D::OnUpdate(float deltaTime) {

    }

    void TestTexture2D::OnRender() {
        glClearColor(0.5f, 0.7f, 0.9f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        Renderer renderer;

        m_texture->bind();

        m_cameraView = glm::translate(glm::mat4(1.0f), m_cameraTranslation);
        
        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_modelTranslationA);
            glm::mat4 mvp = m_projectionMatrix * m_cameraView * model;
            m_shader->bind();
            m_shader->setUniformMat4f("u_ModelViewProjection", mvp);
            renderer.draw(*m_VAO, *m_IB, *m_shader);
        }
        
        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_modelTranslationB);
            glm::mat4 mvp = m_projectionMatrix * m_cameraView * model;
            m_shader->bind();
            m_shader->setUniformMat4f("u_ModelViewProjection", mvp);
            renderer.draw(*m_VAO, *m_IB, *m_shader);
        }

    }

    void TestTexture2D::OnImGuiRender() {
        ImGui::DragFloat3("Model Position A", &m_modelTranslationA.x);
        ImGui::DragFloat3("Model Position B", &m_modelTranslationB.x);
        ImGui::DragFloat3("Camera Position", &m_cameraTranslation.x);
    }
}