#include "pch.h"
#include "Renderer.h"

void Renderer::clear(){
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::drawSkyboxColor(float r, float g, float b, float a){
    glClearColor(r, g, b, a);
}

void Renderer::draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const{
    shader.bind();
    va.bind();
    ib.bind();
    glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr);
}