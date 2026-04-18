#pragma once

#include "Hazel/Core.h"
#include <cstddef>
#include <cstdint>

namespace Hazel
{

    class HAZEL_API VertexBuffer
    {
    public:
        virtual ~VertexBuffer() {}

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        static VertexBuffer *Create(float *vertices, uint32_t size);
    };

    class HAZEL_API IndexBuffer
    {
    public:
        virtual ~IndexBuffer() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual uint32_t GetCount() const = 0;

        static IndexBuffer *Create(uint32_t *indices, uint32_t size);
    };

} // namespace Hazel