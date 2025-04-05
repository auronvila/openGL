cmake_minimum_required(VERSION 3.29)
project(openGl)

set(CMAKE_CXX_STANDARD 20)

# Include GLFW and GLEW headers
include_directories(${CMAKE_SOURCE_DIR}/Dependencies/GLFW/include)
include_directories(/opt/homebrew/include)
include_directories(${CMAKE_SOURCE_DIR}/res/helper)


# Create executable
add_executable(openGl
        src/Application.cpp

        src/Renderer.h
        src/Renderer.cpp

        src/VertexBuffer.h
        src/VertexBuffer.cpp

        src/IndexBuffer.h
        src/IndexBuffer.cpp

        src/VertexArray.cpp
        src/VertexArray.h

        src/VertexBufferLayout.h
        src/VertexBufferLayout.cpp
)

# Link GLFW and GLEW
target_link_libraries(openGl
        ${CMAKE_SOURCE_DIR}/Dependencies/GLFW/lib-arm64/libglfw3.a
        /opt/homebrew/lib/libGLEW.a
        "-framework Cocoa"
        "-framework OpenGL"
        "-framework IOKit"
        "-framework CoreFoundation"
        "-framework CoreVideo"
)
