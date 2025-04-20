cmake_minimum_required(VERSION 3.29)
project(openGl)

set(CMAKE_CXX_STANDARD 20)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/Dependencies/GLFW/include)
include_directories(${CMAKE_SOURCE_DIR}/src/vendor/stb_image)
include_directories(${CMAKE_SOURCE_DIR}/src/vendor/glm)
include_directories(${CMAKE_SOURCE_DIR}/src/vendor/imgui)
include_directories(/opt/homebrew/include)
include_directories(${CMAKE_SOURCE_DIR}/res/helper)

# ImGui sources
set(IMGUI_SRC
        ${CMAKE_SOURCE_DIR}/src/vendor/imgui/imgui.cpp
        ${CMAKE_SOURCE_DIR}/src/vendor/imgui/imgui_draw.cpp
        ${CMAKE_SOURCE_DIR}/src/vendor/imgui/imgui_tables.cpp
        ${CMAKE_SOURCE_DIR}/src/vendor/imgui/imgui_widgets.cpp
        ${CMAKE_SOURCE_DIR}/src/vendor/imgui/backends/imgui_impl_glfw.cpp
        ${CMAKE_SOURCE_DIR}/src/vendor/imgui/backends/imgui_impl_opengl3.cpp
)

add_library(imgui STATIC ${IMGUI_SRC})

target_include_directories(imgui PUBLIC
        ${CMAKE_SOURCE_DIR}/src/vendor/imgui
        ${CMAKE_SOURCE_DIR}/src/vendor/imgui/backends
)

# Executable target
add_executable(openGl
        src/Application.cpp
        src/Renderer.h src/Renderer.cpp
        src/VertexBuffer.h src/VertexBuffer.cpp
        src/IndexBuffer.h src/IndexBuffer.cpp
        src/VertexArray.h src/VertexArray.cpp
        src/VertexBufferLayout.h src/VertexBufferLayout.cpp
        src/Shader.h src/Shader.cpp
        src/Texture.h src/Texture.cpp
        src/vendor/stb_image/stb_image.h
        src/vendor/stb_image/stb_image.cpp
)

# Link libraries
target_link_libraries(openGl
        ${CMAKE_SOURCE_DIR}/Dependencies/GLFW/lib-arm64/libglfw3.a
        imgui
        /opt/homebrew/lib/libGLEW.a
        "-framework Cocoa"
        "-framework OpenGL"
        "-framework IOKit"
        "-framework CoreFoundation"
        "-framework CoreVideo"
)
