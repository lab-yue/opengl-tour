#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "renderer.h"
#include "vertexBuffer.h"
#include "indexBuffer.h"
#include "vertexArray.h"

static unsigned int CompileShader(unsigned int type, const std::string& source)
{
    auto id = glCreateShader(type);
    auto typeName = type == GL_VERTEX_SHADER ? "vertex" : "fragment";
    const char* src = source.c_str();
    glShaderSource(id,1,&src,nullptr);
    glCompileShader(id);

    int result;

    glGetShaderiv(id,GL_COMPILE_STATUS,&result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id,GL_INFO_LOG_LENGTH,&length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id,length,&length,message);
        std::cout << "Failed to Compile "<< typeName << "shader" << std::endl;
        std::cout << message << std::endl;
    }
    else
    {
    //    std::cout << typeName << std::endl;
    //    std::cout << source << std::endl;
    }
    
    return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    auto program = glCreateProgram();
    auto vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    auto fs = CompileShader(GL_FRAGMENT_SHADER,fragmentShader);

    glAttachShader(program,vs);
    glAttachShader(program,fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        std::cout << "glewInit Error" << std::endl;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;

    float positions[] = {
        -0.5f,-0.5f,
         0.5f,-0.5f,
         0.5f, 0.5f,
        -0.5f, 0.5f
    };
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    VertexArray va;
    VertexBuffer vb(positions, 4 * 2 * sizeof(float));
    VertexBufferLayout layout;

    layout.Push<float>(2);
    va.AddBuffer(vb, layout);

    IndexBuffer ib(indices, 6);

    std::string vertexShader = R"(
        #version 330 core

        layout(location = 0) in vec4 position;

        void main()
        {
            gl_Position = position;
        }
    )";

    std::string fragShader = R"(
        #version 330 core

        layout(location = 0) out vec4 color;

        uniform vec4 u_Color;

        void main()
        {
            color = u_Color;
        }
    )";

    auto shader = CreateShader(vertexShader,fragShader);
    glUseProgram(shader);

    int location = glGetUniformLocation(shader, "u_Color");
    glUniform4f(location,0.2f,0.3f,0.8f,1.0f);
    float r = 0.0f;
    float increment = 0.05f;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glUniform4f(location,r,0.3f,0.8f,1.0f);

        va.Bind();
        //GLCall(glBindVertexArray(vao));
        ib.Bind();

        GLCall(glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,nullptr));

        if (r> 1.0f)
            increment = -0.05f;
        else if (r < 0.0f)
            increment = 0.05f;
        r += increment;
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteProgram(shader);

    glfwTerminate();
    return 0;
}