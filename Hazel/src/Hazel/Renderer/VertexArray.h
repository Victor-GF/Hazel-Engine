#pragma once

#include "Hazel/Core.h"
#include <cstddef>
#include <cstdint>
#include <initializer_list>
#include <string_view>
#include <vector>
#include <memory>
#include "Buffer.h"

namespace Hazel {
    class HAZEL_API VertexArray
    {
    public:
        virtual ~VertexArray() {}

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) = 0;
        virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) = 0;

        virtual std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() noexcept = 0;
        virtual std::shared_ptr<IndexBuffer>& GetIndexBuffer() noexcept = 0;

        static VertexArray *Create();
    };
}