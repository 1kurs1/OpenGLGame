#include "pch.h"

#include "Window.h"
#include "Texture.h"

#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900

int main(){
    std::cout << "OpenGLGame: v" << GAME_VERSION << '\n';

    Window mainWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGLGame");

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
    
    VertexArray va;
    VertexBuffer vb(vertices, 4*4*sizeof(float));

    BufferLayout layout;
    layout.push<float>(2);
    layout.push<float>(2);
    va.addBuffer(vb, layout);
    IndexBuffer ib(indices, 6);

    float aspectRatio = ((float)WINDOW_WIDTH)/((float)WINDOW_HEIGHT);
    glm::mat4 projectionMatrix = glm::ortho(-1000.0f * aspectRatio, 1000.0f * aspectRatio, -1000.0f, 1000.0f, -1.0f, 1.0f);

    Shader shader("../shaders/Standart.shader");
    shader.bind();
    
    Texture texture("../assets/images/nicromis_logo.png");
    texture.bind();
    shader.setUniform1i("u_texture", 0);

    va.unbind();
    vb.unbind();
    ib.unbind();
    shader.unbind();

    Renderer renderer;      // todo: maybe use singleton (?)
    

    // Variable parameters:
    glm::vec3 modelTranslation = glm::vec3(100, 100, 0);
    glm::vec3 cameraTranslation = glm::vec3(-500, 0, 0);
    glm::vec3 skyboxColor = glm::vec3(0.3f, 0.3f, 0.85f);

    // // debug:
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while(!mainWindow.isClosed()){
        // write entry point
        
        renderer.clear();
        renderer.drawSkyboxColor(skyboxColor.r, skyboxColor.g, skyboxColor.b, 1.0f);
        
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        glm::mat4 cameraView = glm::translate(glm::mat4(1.0f), cameraTranslation);
        glm::mat4 model = glm::translate(glm::mat4(1.0f), modelTranslation);
        glm::mat4 mvp = projectionMatrix * cameraView * model;

        shader.bind();
        shader.setUniformMat4f("u_ModelViewProjection", mvp);

        renderer.draw(va, ib, shader);

        {
            ImGui::Begin("Inspector");
            ImGui::DragFloat3("Model Position", &modelTranslation.x);
            ImGui::DragFloat3("Camera Position", &cameraTranslation.x);
            ImGui::Spacing();
            ImGui::ColorEdit3("Skybox Color", &skyboxColor.r);
            ImGui::End();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        
        glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr);
        
        mainWindow.swapBuffers();
        mainWindow.pollEvents();
    }

    ImGui_ImplGlfw_Shutdown();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();

    return EXIT_SUCCESS;
}