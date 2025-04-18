//
// Created by Auron Vila on 18.04.2025.
//

#ifndef TEXTURE_H
#define TEXTURE_H

#include"Renderer.h"

class Texture {
private:
    unsigned int m_RendererId;
    std::string m_FilePath;
    unsigned char *m_LocalBuffer;
    int m_Width, m_Height, m_BPP;

public:
    Texture(const std::string &filePath);

    ~Texture();

    void Bind(unsigned int slot = 0) const;

    void Unbind() const;

    inline int GetWidth() { return m_Width; }
    inline int GetHeight() { return m_Height; }
};

#endif //TEXTURE_H
