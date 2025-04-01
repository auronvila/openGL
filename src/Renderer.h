//
// Created by Auron Vila on 1.04.2025.
//

#ifndef RENDERER_H
#define RENDERER_H
#include <GL/glew.h>

#define ASSERT(x) if(!(x)) __builtin_debugtrap();
#define GLCall(x) GlClearError();\
x;\
ASSERT(GlLogCall(#x,__FILE__,__LINE__))

void GlClearError();

bool GlLogCall(const char *function, const char *file, int line);


#endif //RENDERER_H
