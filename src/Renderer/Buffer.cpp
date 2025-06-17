#include "pch.h"
#include "Buffer.h"

// VertexBuffer: 

VertexBuffer::VertexBuffer(const void* data, uint32_t size){
    glGenBuffers(1, &m_rendererID);
    glBindBuffer(GL_ARRAY_BUFFER, m_rendererID); 
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer(){
    glDeleteBuffers(1, &m_rendererID);
}

void VertexBuffer::bind() const{
    glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
}

void VertexBuffer::unbind() const{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}


// IndexBuffer:

IndexBuffer::IndexBuffer(const uint32_t* indices, uint32_t count) : m_count(count){
    glGenBuffers(1, &m_rendererID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer(){
    glDeleteBuffers(1, &m_rendererID);
}

void IndexBuffer::bind() const{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID);
}

void IndexBuffer::unbind() const{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}