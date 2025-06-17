#include "TestSkyboxColor.h"


namespace test{
    TestSkyboxColor::TestSkyboxColor() : m_skyboxColor {0.1f, 0.8f, 0.5f, 1.0f} {

    }

    TestSkyboxColor::~TestSkyboxColor(){

    }

    void TestSkyboxColor::OnUpdate(float deltaTime) {

    }

    void TestSkyboxColor::OnRender() {
        glClearColor(m_skyboxColor[0],m_skyboxColor[1], m_skyboxColor[2], m_skyboxColor[3]);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void TestSkyboxColor::OnImGuiRender() {
        ImGui::ColorEdit4("Skybox Color", m_skyboxColor);
    }
}