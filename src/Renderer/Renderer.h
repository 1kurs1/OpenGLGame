#pragma once

#include "VertexArray.h"
#include "Shader.h"

class Renderer{
public:
    void clear();
    void drawSkyboxColor(float r, float g, float b, float a = 1.0f);
    void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};