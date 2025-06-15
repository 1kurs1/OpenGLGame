cmake_minimum_required(VERSION 3.30)
project(OpenGLGame VERSION 0.3.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

add_definitions(-DIMGUI_DEFINE_MATH_OPERATORS)

add_library(glad STATIC vendor/glad/glad.c)
target_include_directories(glad PUBLIC vendor/glad)

set(SOURCES 
    src/main.cpp 
    src/pch.cpp
    src/Window.cpp
    src/Buffer.cpp
    src/VertexArray.cpp
    src/Shader.cpp
    src/Renderer.cpp
    vendor/stb_image/stb_image.cpp
    vendor/imgui/imgui.cpp
    vendor/imgui/imgui_demo.cpp
    vendor/imgui/imgui_draw.cpp
    vendor/imgui/imgui_widgets.cpp
    vendor/imgui/imgui_tables.cpp
    vendor/imgui/imgui_impl_glfw.cpp
    vendor/imgui/imgui_impl_opengl3.cpp
    src/Texture.cpp
)

set(HEADERS 
    src/pch.h
    src/Window.h
    src/Buffer.h
    src/VertexArray.h
    src/Shader.h
    src/Renderer.h
    src/Texture.h
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_precompile_headers(${PROJECT_NAME} PRIVATE src/pch.h)

target_compile_definitions(${PROJECT_NAME} PUBLIC GAME_VERSION="${CMAKE_PROJECT_VERSION}")
target_include_directories(${PROJECT_NAME} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    vendor/glfw/include
    vendor/glad
    vendor/spdlog/include
    vendor/glm/glm
    vendor/stb_image
    vendor/imgui
)

target_link_directories(
    ${PROJECT_NAME} PRIVATE
    vendor/glfw/build/src
    vendor/spdlog/build/
    vendor/glm/build/glm
)

target_link_libraries(
    ${PROJECT_NAME}
    glad
    glfw3
    GL 
    X11 
    Xrandr 
    Xi 
    Xxf86vm 
    Xinerama 
    Xcursor
    pthread 
    dl 
    m
    gtk-3
    libspdlog.a
    libglm.a
)