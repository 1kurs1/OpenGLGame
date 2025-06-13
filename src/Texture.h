#pragma once

#include "Renderer.h"

class Texture{
public:
    Texture(const std::string& path);
    ~Texture();

    void bind(uint32_t slot = 0) const;
    void unbind() const;

    inline int getWidth() const { return m_width; }
    inline int getHeight() const { return m_height; }
    inline int getBitsPerPixel() const { return m_bitsPerPixel; }

private:
    uint32_t m_rendererID;
    std::string m_filePath;
    unsigned char* m_localBuffer;
    int m_width, m_height, m_bitsPerPixel;
};