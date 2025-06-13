#include "pch.h"

#include "Window.h"
#include "Texture.h"

#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900

int main(){
    std::cout << "OpenGLGame: v" << GAME_VERSION << '\n';

    Window mainWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGLGame");

    float sc = ((float)mainWindow.getHeight()/(float)mainWindow.getWidth());

    float vertices[] = {
        -0.5f * sc, -0.5f, 0.0f, 0.0f,
        0.5f * sc, -0.5f, 1.0f, 0.0f,
        0.5f * sc, 0.5f, 1.0f, 1.0f,
        -0.5f * sc, 0.5f, 0.0f, 1.0f
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
    
    // // debug:
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    float r = 0.1f;
    float i = 0.005f;
    while(!mainWindow.isClosed()){
        // write entry point
        
        renderer.clear();
        renderer.drawSkyboxColor(0.3, 0.3, 0.85, 1);
        
        shader.bind();
        
        renderer.draw(va, ib, shader);
        
        glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr);
        
        if(r >= 1.0f) i = -0.005f;
        else if(r < 0.01f) i = 0.005f;
        r += i;
        
        mainWindow.swapBuffers();
        mainWindow.pollEvents();
    }

    glfwTerminate();

    return EXIT_SUCCESS;
}