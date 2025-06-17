#include "pch.h"

#include "Core/Window.h"

#include "TestSkyboxColor.h"
#include "TestTexture2D.h"

int main(){
    std::cout << "OpenGLGame: v" << GAME_VERSION << ' ' << VERSION_CODE_NAME << '\n';

    Window mainWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGLGame");

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Renderer renderer;      // todo: maybe use singleton (?)

    test::Test* currentTest = nullptr;
    test::TestMenu* testMenu = new test::TestMenu(currentTest);
    currentTest = testMenu;

    testMenu->RegisterTest<test::TestSkyboxColor>("Skybox Color");
    testMenu->RegisterTest<test::TestTexture2D>("Texture2D");

    while(!mainWindow.isClosed()){
        // write entry point
        
        renderer.drawSkyboxColor(0.5f, 0.7f, 0.9f, 1.0f);
        renderer.clear();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        
        if(currentTest){
            currentTest->OnUpdate(0.0f);
            currentTest->OnRender();
            ImGui::Begin("Test");
            if(currentTest != testMenu && ImGui::Button("X")){
                delete currentTest;
                currentTest = testMenu;
            }
            currentTest->OnImGuiRender();
            ImGui::End();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        
        mainWindow.swapBuffers();
        mainWindow.pollEvents();
    }

    delete currentTest;
    if(currentTest != testMenu)
        delete testMenu;

    ImGui_ImplGlfw_Shutdown();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();

    return EXIT_SUCCESS;
}