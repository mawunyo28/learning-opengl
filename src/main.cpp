#include <iostream>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "Timer.h"

void processInput(GLFWwindow *window);
void frame_buffer_callback(GLFWwindow *window, int width, int height);

void check_compilation_status(GLenum pname, GLenum shader_type, GLuint shader);
void check_linking_status(GLenum pname, GLuint shader_program);
const char *shaderName(GLenum shader_type);

const char *WINDOW_TITLE = "Opengl Journey";
const int WINDOW_WIDTH = 800, WINDOW_HEIGHT = 600;

const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main() {\n"
                                 "    gl_Position = vec4(aPos, 1.0);\n"
                                 "}\n";

const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main() {\n"
                                   "   FragColor = vec4(1.0f, 0.72f, 0.24f, 1.0f);\n"
                                   "}\n";

int main()
{
    #pragma region OPENGL and GLAD INITIALLIZATION
    Timer timer("main");

    Timer *init_timer = new Timer("initializations");
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);

    if (window == NULL)
    {
        std::cout << "Unable to create GLFW window" << std::endl;
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Unable to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glfwSetFramebufferSizeCallback(window, frame_buffer_callback);

    delete init_timer;

    #pragma endregion

    #pragma region SHADERS
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);

    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);

    check_compilation_status(GL_COMPILE_STATUS, GL_VERTEX_SHADER, vertexShader);
    check_compilation_status(GL_COMPILE_STATUS, GL_FRAGMENT_SHADER, fragmentShader);

    unsigned int shader_program = glCreateProgram();
    glAttachShader(shader_program, vertexShader);
    glAttachShader(shader_program, fragmentShader);

    glLinkProgram(shader_program);

    check_linking_status(GL_LINK_STATUS, shader_program );

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    #pragma endregion
    
    #pragma region DATA and objects(buffers and arrays)
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0, 0.5f, 0.0f};

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), reinterpret_cast<void *>(0));

    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    #pragma endregion

    #pragma region PROGRAM LOOP
    while (!glfwWindowShouldClose(window))
    {
        // Timer* timer(new Timer("while loop"));
        processInput(window);
        glClearColor(float(125 / 255), 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader_program);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwPollEvents();
        glfwSwapBuffers(window);

        // delete timer;
    }
    #pragma endregion

    glfwTerminate();

    return 0;
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        Timer* timer = new Timer("closing window with escape");
        glfwSetWindowShouldClose(window, true);
        delete timer;
    }
}

void frame_buffer_callback(GLFWwindow *window, int width, int height)
{
    Timer timer("frame_buffer");
    glViewport(0, 0, width, height);
}

const char *shaderName(GLenum shader_type)
{
    Timer timer("get Shader name");
    if (shader_type == GL_VERTEX_SHADER)
        return static_cast<const char *>("VERTEX");
    else if (shader_type == GL_FRAGMENT_SHADER)
        return static_cast<const char *>("FRAGMENT");
    else
        return static_cast<const char *>("");
}

void check_compilation_status(GLenum pname, GLenum shader_type, GLuint shader)
{
    Timer timer("check_compilation_status");
    int success;
    char infoLog[512];

    glGetShaderiv(shader, pname, &success);

    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::" << shaderName(shader_type) << "::COMPILATION_FAILED \n"
                  << infoLog << std::endl;
    }
}

void check_linking_status(GLenum pname, GLuint shader_program)
{
    Timer timer("check_linking_status");
    int success;
    char infoLog[512];
    glGetProgramiv(shader_program, pname, &success);

    if(!success)
    {
        glGetProgramInfoLog(shader_program, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" 
        << infoLog << std::endl;
    }

}
