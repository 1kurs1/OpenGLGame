#pragma once

#include "Test.h"

namespace test{
    class TestSkyboxColor : public Test{
    public:
        TestSkyboxColor();
        ~TestSkyboxColor();

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;

    private:
        float m_skyboxColor[4];
    };
}