#pragma once

#include <glm/glm.hpp>

#include "VertexArray.h"

namespace Confuse{
    class RendererAPI{
    public:
        enum class API{
            None = 0,
            OpenGL = 1
        };

    public:
        virtual void setClearColor(const glm::vec4& color) = 0;
        virtual void clear() = 0;

        virtual void drawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;

        inline static API getAPI(){return s_api;}

    private:
        static API s_api;
    }; 
}