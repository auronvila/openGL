#define GLEW_STATIC
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include<fstream>
#include<string>
#include<sstream>
#include<Logger.h>
#include "Renderer.h"
#include"VertexBuffer.h"
#include"IndexBuffer.h"


struct ShaderProgramSource {
    std::string VertexSource;
    std::string FragmentSource;
};

static ShaderProgramSource ParseShader(const std::string &filePath) {
    std::ifstream stream(filePath);

    if (!stream.is_open()) {
        std::cerr << "Error: Unable to open shader file: " << filePath << std::endl;
        return {"", ""};
    }

    enum class ShaderType {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1,
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType shaderType = ShaderType::NONE;

    while (getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                shaderType = ShaderType::VERTEX;
                Log("[INFO] Found Vertex Shader");
            } else if (line.find("fragment") != std::string::npos) {
                shaderType = ShaderType::FRAGMENT;
                Log("[INFO] Found Fragment Shader");
            }
        } else if (shaderType != ShaderType::NONE) {
            ss[(int) shaderType] << line << '\n';
        }
    }

    return {ss[0].str(), ss[1].str()};
}

static unsigned int CompiledShader(unsigned int type, const std::string &source) {
    unsigned int id = glCreateShader(type);
    const char *src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

        std::vector<char> message(length);
        glGetShaderInfoLog(id, length, &length, message.data());

        Log("Failed to compile ", type == GL_VERTEX_SHADER ? "vertex shader" : "fragment shader", ":\n",
            message.data());

        glDeleteShader(id);
        return 0;
    }

    return id;
}

static unsigned int CreateShader(const std::string &vertexShader, const std::string &fragmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vs = CompiledShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompiledShader(GL_FRAGMENT_SHADER, fragmentShader);

    if (vs == 0 || fs == 0) {
        std::cerr << "Shader compilation failed. Aborting shader creation." << std::endl;
        return 0;
    }

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);

    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (success == GL_FALSE) {
        int length;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);

        std::vector<char> message(length);
        glGetProgramInfoLog(program, length, &length, message.data());

        std::cerr << "Shader program linking failed:\n" << message.data() << std::endl;

        glDeleteProgram(program);
        return 0;
    }

    glValidateProgram(program);
    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

int main() {
    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);


    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
        Log("Something wrong with glew initialization"); {
        float positions[] = {
            -0.5f, -0.5f, // 0
            0.5f, -0.5f, // 1
            0.5f, 0.5f, // 2
            -0.5f, 0.5f, // 3
        };

        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0,
        };

        unsigned int vao;
        GLCall(glGenVertexArrays(1,&vao));
        GLCall(glBindVertexArray(vao));

        VertexBuffer vb(positions, 4 * 2 * sizeof(float));

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2,GL_FLOAT,GL_FALSE, sizeof(float) * 2, 0);

        IndexBuffer ib(indices, 6);

        ShaderProgramSource source = ParseShader("../res/shaders/Basic.shader");

        unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
        glUseProgram(shader);

        GLCall(int location = glGetUniformLocation(shader,"u_color"));
        ASSERT(location!=-1)
        GLCall(glUniform4f(location,0.2f,0.3f,0.8f,1.0f));

        GLCall(glBindVertexArray(0));
        GLCall(glUseProgram(0));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

        float r = 0.2f;
        float increment = 0.05f;

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window)) {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);

            GLCall(glUseProgram(shader));
            GLCall(glUniform4f(location,r,0.3f,0.8f,1.0f));

            GLCall(glBindVertexArray(vao));
            ib.Bind();

            GLCall(glDrawElements(GL_TRIANGLES, 6,GL_UNSIGNED_INT, nullptr));

            if (r > 1.0f) {
                increment = -0.05f;
            } else if (r < 0.0f) {
                increment = 0.05f;
            }
            r += increment;

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }

        glDeleteProgram(shader);
    }
    glfwTerminate();

    return 0;
}
