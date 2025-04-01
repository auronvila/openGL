//
// Created by Auron Vila on 1.04.2025.
//

#include "Renderer.h"
#include "Logger.h"

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