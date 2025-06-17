#pragma once

struct BufferElement{
    uint32_t type;
    uint32_t count;
    u_char normalized;

    static uint32_t getSizeOfType(uint32_t type){
        switch(type){
            case GL_FLOAT: return 4;
            case GL_UNSIGNED_INT: return 4;
            case GL_UNSIGNED_BYTE: return 1;
        }
        return 0;
    }
};

class BufferLayout{
public:
    BufferLayout() : m_stride(0) {}

    template<typename T>
    void push(uint32_t count){
        static_assert(false);
    }

    template<>
    void push<float>(uint32_t count){
        m_elements.push_back({ GL_FLOAT, count, GL_FALSE });
        m_stride += count * BufferElement::getSizeOfType(GL_FLOAT);
    }
    
    template<>
    void push<uint32_t>(uint32_t count){
        m_elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
        m_stride += count * BufferElement::getSizeOfType(GL_UNSIGNED_INT);
    }

    template<>
    void push<u_char>(uint32_t count){
        m_elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
        m_stride += count * BufferElement::getSizeOfType(GL_UNSIGNED_BYTE);
    }

    inline const std::vector<BufferElement>& getElements() const { return m_elements; }
    inline uint32_t getStride() const { return m_stride; }

private:
    std::vector<BufferElement> m_elements;
    uint32_t m_stride;
};

class VertexBuffer{
public:
    VertexBuffer(const void* data, uint32_t size);
    ~VertexBuffer();

    void bind() const;
    void unbind() const;

private:
    uint32_t m_rendererID;
};

class IndexBuffer{
public:
    IndexBuffer(const uint32_t* indices, uint32_t count);
    ~IndexBuffer();

    void bind() const;
    void unbind() const;

    inline unsigned int getCount() const { return m_count; } 

private:
    uint32_t m_rendererID;
    uint32_t m_count;
};