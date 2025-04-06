//
// Created by Auron Vila on 5.04.2025.
//

#ifndef RENDERER_H
#define RENDERER_H

#include<GL/glew.h>
#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"

#define ASSERT(x) if (!(x)) __builtin_trap();
#define GLCall(x) GLClearError();\
x;\
ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();

bool GLLogCall(const char *function, const char *file, int line);

class Renderer {
public:
    void Draw(const VertexArray &va, const IndexBuffer &ib, const Shader &shader) const;

    void Clear() const;

private:
};

#endif //RENDERER_H
