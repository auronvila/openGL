//
// Created by Auron Vila on 17.03.2025.
//
#include<iostream>
#include <GL/glew.h>
#include<Logger.h>


void GlClearError() {
    while (glGetError() != GL_NO_ERROR);
}


bool GlLogCall(const char *function, const char *file, int line) {
    while (GLenum error = glGetError()) {
        Log("[OpenGl Error]: (", "Code:", error, "): ", "Line:", line, " ", function, " ", file);
        return false;
    }
    return true;
}
