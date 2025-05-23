//
// Created by Auron Vila on 5.04.2025.
//

#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

class VertexBuffer {
private:
    unsigned int m_RendererId;

public:
    VertexBuffer(const void* data,unsigned int size);
    ~VertexBuffer();

    void Bind() const;
    void UnBind() const;
};

#endif //VERTEXBUFFER_H
