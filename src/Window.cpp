#include "pch.h"
#include "Window.h"

Window::Window() : m_width(1600), m_height(900), m_title("No Name Window"){init();}
Window::Window(uint32_t w, uint32_t h, std::string t) : m_width(w), m_height(h), m_title(t){
    init();
}

void Window::init(){
    if(!glfwInit()){
        std::cout << "error: glfw doesn`t initialized!\n";
        //assert this
    }

    p_glfwWindow = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(p_glfwWindow);

    if(!p_glfwWindow){
        //assert
        glfwTerminate();
    }

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "error: couldn`d load glad!\n";
        glfwTerminate();
    }
}