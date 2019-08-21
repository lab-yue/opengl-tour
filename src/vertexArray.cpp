#include "vertexArray.h"
#include "renderer.h"
#include <iostream>

VertexArray::VertexArray()
{
    GLCall(glGenVertexArrays(1, &m_RendererID));
    Bind();
}

VertexArray::~VertexArray()
{
    GLCall(glDeleteVertexArrays(1, &m_RendererID))
}

void VertexArray::Bind() const
{
    GLCall(glBindVertexArray(m_RendererID));
}

void VertexArray::Unbind() const
{
    GLCall(glBindVertexArray(0));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) const
{
    const auto& elements = layout.GetElements();
    unsigned int offset = 0;
    for (unsigned int i=0; i < elements.size(); i++)
    {
        const auto& element = elements[i];
        std::cout << "[AttribPointer] " << element.count << " <> " << element.type << " <> " << element.normalized << std::endl;
        GLCall( glEnableVertexAttribArray(i));
        GLCall( glVertexAttribPointer(
            i,
            element.count,
            element.type,
            element.normalized,
            layout.GetStride(),
            (const void *)(intptr_t)offset)
        );
        offset += element.count * vertexBufferElement::GetSizeOfType(element.type);
    }
}
