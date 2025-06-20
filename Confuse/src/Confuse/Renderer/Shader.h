#pragma once

#include <string>
#include <cstdint>

namespace Confuse{
    class Shader{
    public:
        virtual ~Shader() = default;

        virtual void bind() const = 0;
        virtual void unbind() const = 0;

        static Shader* create(const std::string& vertexSrc, const std::string& fragmentSrc);
    };
}