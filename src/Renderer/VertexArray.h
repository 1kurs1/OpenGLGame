#pragma once

#include "Buffer.h"

class VertexArray{
public:
    VertexArray();
    ~VertexArray();

    void addBuffer(const VertexBuffer& vb, const BufferLayout& layout);
   
    void bind() const;
    void unbind() const;

private:
    uint32_t m_rendererID;
};