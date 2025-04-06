//
// Created by Auron Vila on 5.04.2025.
//

#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H
#include "VertexBuffer.h"

class VertexBufferLayout;

class VertexArray {
public:
    VertexArray();

    ~VertexArray();

    void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout &layout);

    void Bind() const;

    void Unbind() const;

private:
    unsigned int m_RendererId;
};


#endif //VERTEXARRAY_H
