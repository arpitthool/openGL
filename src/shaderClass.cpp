#include "shaderClass.h"

std::string get_file_contents(const char* filename) // to read the shader files
{
    std::ifstream in(filename, std::ios::binary);
    if (in)
    {
        std::string contents;
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
        return contents;
    }
    throw(errno);
}

Shader::Shader(const char* vertexFilePath, const char* fragmentFilePath) // shader constructor
{
    std::string vertexCode = get_file_contents(vertexFilePath);
    std::string fragmentCode = get_file_contents(fragmentFilePath);

    const char* vertexShaderSource = vertexCode.c_str();
    const char* fragmentShaderSource = fragmentCode.c_str();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER); // Create a vertex shader object
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); // Set the source code of the vertex shader
    glCompileShader(vertexShader); // Compile the vertex shader

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); // Create a fragment shader object
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL); // Set the source code of the fragment shader
    glCompileShader(fragmentShader); // Compile the fragment shader

    ID = glCreateProgram(); // Create a shader program object
    glAttachShader(ID, vertexShader); // Attach the vertex shader to the shader program
    glAttachShader(ID, fragmentShader); // Attach the fragment shader to the shader program
    glLinkProgram(ID); // Link the shader program

    glDeleteShader(vertexShader); // Delete the vertex shader
    glDeleteShader(fragmentShader); // Delete the fragment shader

}

void Shader::activate() {
    glUseProgram(ID); // Use the shader program
}

void Shader::deleteShader() {
    glDeleteProgram(ID); // Delete the shader program
}