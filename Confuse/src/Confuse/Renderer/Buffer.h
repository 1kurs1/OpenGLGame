#pragma once

#include <cstdint>

namespace Confuse{
    enum class ShaderDataType{
        None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
    };

    static uint32_t shaderDataTypeSize(ShaderDataType type){
        switch(type){
            case ShaderDataType::Float: return 4;
            case ShaderDataType::Float2: return 4 * 2;
            case ShaderDataType::Float3: return 4 * 3;
            case ShaderDataType::Float4: return 4 * 4;
            case ShaderDataType::Mat3: return 4 * 3 * 3;
            case ShaderDataType::Mat4: return 4 * 4 * 4;
            case ShaderDataType::Int: return 4;
            case ShaderDataType::Int2: return 4 * 2;
            case ShaderDataType::Int3: return 4 * 3;
            case ShaderDataType::Int4: return 4 * 4;
            case ShaderDataType::Bool: return 1;
        }

        CE_CORE_ASSERT(false, "unknown shader data type!");
        return 0;
    }

    struct BufferElement{
        std::string name;
        ShaderDataType type;
        uint32_t size;
        uint32_t offset;
        bool normalized;

        BufferElement(){}
        BufferElement(ShaderDataType type, const std::string& name, bool normalized = false) : name(name), type(type), size(shaderDataTypeSize(type)), offset(0), normalized(normalized){}
    
        uint32_t getComponentCount() const{
            switch(type){
                case ShaderDataType::Float: return 1;
                case ShaderDataType::Float2: return 2;
                case ShaderDataType::Float3: return 3;
                case ShaderDataType::Float4: return 4;
                case ShaderDataType::Mat3: return 3 * 3;
                case ShaderDataType::Mat4: return 4 * 4;
                case ShaderDataType::Int: return 1;
                case ShaderDataType::Int2: return 2;
                case ShaderDataType::Int3: return 3;
                case ShaderDataType::Int4: return 4;
                case ShaderDataType::Bool: return 1;
            }

            CE_CORE_ASSERT(false, "unknown ShaderDataType!");
            return 0;
        }
    };
    
    class BufferLayout{
    public:
        BufferLayout(){}
        BufferLayout(const std::initializer_list<BufferElement>& elements) : m_elements(elements){
            CalculateOffsetsAndStride();
        }

        inline uint32_t getStride() const {return m_stride;}
        inline const std::vector<BufferElement>& getElements() const {return m_elements;}

        std::vector<BufferElement>::iterator begin(){return m_elements.begin();}
        std::vector<BufferElement>::iterator end(){return m_elements.end();}
        std::vector<BufferElement>::const_iterator begin() const {return m_elements.begin();}
        std::vector<BufferElement>::const_iterator end() const {return m_elements.end();}

    private:
        void CalculateOffsetsAndStride(){
            uint32_t offset = 0;
            m_stride = 0;
            for(auto& element: m_elements){
                element.offset = offset;
                offset += element.size;
                m_stride += element.size;
            }
        }

    private:
        std::vector<BufferElement> m_elements;
        uint32_t m_stride = 0;
    };

    class VertexBuffer{
    public:
        virtual ~VertexBuffer(){}

        virtual void bind() const = 0;
        virtual void unbind() const = 0;

        virtual const BufferLayout& getLayout() const = 0;
        virtual void setLayout(const BufferLayout& layout) = 0;

        static VertexBuffer* create(float* vertices, uint32_t size);
    };

    class IndexBuffer{
    public:
        virtual ~IndexBuffer(){}

        virtual void bind() const = 0;
        virtual void unbind() const = 0;

        virtual uint32_t getCount() const = 0;

        static IndexBuffer* create(uint32_t* indices, uint32_t size);
    };
}