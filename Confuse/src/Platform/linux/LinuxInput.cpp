#include "CEpch.h"
#include "LinuxInput.h"

#include <GLFW/glfw3.h>

#include "Confuse/Application.h"

namespace Confuse{
    Input* Input::s_instance = new LinuxInput();

    bool LinuxInput::isKeyPressedImpl(int keycode){
        auto window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
        auto state = glfwGetKey(window, keycode);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool LinuxInput::isMouseButtonPressedImpl(int button){
        auto window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
        auto state = glfwGetMouseButton(window, button);
        return state == GLFW_PRESS;
    }

    std::pair<float, float> LinuxInput::getMousePositionImpl(){
        auto window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        return {(float)xpos, (float)ypos};
    }

    float LinuxInput::getMouseXImpl(){
        auto [x, y] = getMousePositionImpl();
        return x;
    }

    float LinuxInput::getMouseYImpl(){
        auto [x, y] = getMousePositionImpl();
        return y;
    }
}