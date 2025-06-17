#pragma once

#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900

class Window{
public:
    Window();
    Window(uint32_t w, uint32_t h, std::string t);
    ~Window(){glfwTerminate();}

    uint32_t getWidth() const {return m_width;}
    uint32_t getHeight() const {return m_height;}
    std::string getTitle() const {return m_title;}

    bool isClosed() const {return glfwWindowShouldClose(p_glfwWindow);}

    void pollEvents() const {glfwPollEvents();}
    void swapBuffers() const {glfwSwapBuffers(p_glfwWindow);}

private:
    void init();

private:
    uint32_t m_width;
    uint32_t m_height;
    std::string m_title;

    GLFWwindow* p_glfwWindow;
};