#include "pch.h"

#include "Shader.h"
#include "Window.h"
#include "VertexArray.h"

#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900

int main(){
    std::cout << "OpenGLGame: v" << GAME_VERSION << '\n';

    Window mainWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGLGame");

    float sc = ((float)mainWindow.getHeight()/(float)mainWindow.getWidth());

    float vertices[] = {
        -0.5f * sc, -0.5f, 0.0f,
        0.5f * sc, -0.5f, 0.0f,
        0.5f * sc, 0.5f, 0.0f,
        -0.5f * sc, 0.5f, 0.0f
    };
    uint32_t indices[] = {
        0, 1, 2,
        2, 3, 0
    };
    
    VertexArray va;
    VertexBuffer vb(vertices, 4*3*sizeof(float));

    BufferLayout layout;
    layout.push<float>(3);
    va.addBuffer(vb, layout);
    IndexBuffer ib(indices, 6);

    Shader shader("../shaders/triangles.shader");
    shader.bind();
    shader.setUniform4f("u_color", 1.0f, 0.5f, 0.2f, 1.0f);
    
    va.unbind();
    vb.unbind();
    ib.unbind();
    shader.unbind();
    
    // // debug:
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    float r = 0.1f;
    float i = 0.005f;
    while(!mainWindow.isClosed()){
        // write entry point
        
        glClearColor(0.3, 0.3, 0.85, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        
        shader.bind();
        shader.setUniform4f("u_color", r, 0.5f, 0.2f, 1.0f);
        
        va.bind();
        ib.bind();
        
        glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr);
        
        if(r >= 1.0f) i = -0.005f;
        else if(r < 0.0f) i = 0.005f;
        r += i;
        
        mainWindow.swapBuffers();
        mainWindow.pollEvents();
    }

    glfwTerminate();

    return EXIT_SUCCESS;
}