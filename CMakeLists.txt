#this makes compiling c++ code way easier. 

cmake_minimum_required(VERSION 4.1.3) 
project(OpenGLProject) #defines name of project and can specify languages 

#add source files (update more later if needed) 
add_executable(OpenGLProject
    draw_triangle.cpp
    glad.c
)

#include directories 
target_include_directories(OpenGLProject PRIVATE 
    ${CMAKE_SOURCE_DIR}/include 
)

#GLFW headers installed via homebrew 
target_include_directories(OpenGLProject PRIVATE 
    /opt/homebrew/include
)

#link GLFW library (homebrew)
target_link_directories(OpenGLProject PRIVATE 
    /opt/homebrew/opt/glfw/lib
)

#Link libraries 
target_link_libraries(OpenGLProject
    glfw
    "-framework OpenGL" #linking openGL 
)
