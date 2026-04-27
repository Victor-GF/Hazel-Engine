#pragma once

#include "Hazel/Core.h"
#include <cstddef>
#include <cstdint>
#include <initializer_list>
#include <string_view>
#include <vector>

namespace Hazel
{
    enum class ShaderDataType : uint8_t
    {
        None = 0,
        Float,
        Float2,
        Float3,
        Float4,
        Mat3,
        Mat4,
        Int,
        Int2,
        Int3,
        Int4,
        Bool,
    };

    static constexpr uint32_t ShaderDataTypeSize(ShaderDataType type)
    {
        constexpr auto FLOAT_SIZE = 4;
        constexpr auto INT_SIZE = 4;
        constexpr auto MAT3_SIZE = 4 * 3 * 3;
        constexpr auto MAT4_SIZE = 4 * 4 * 4;
        constexpr auto BOOL_SIZE = 1;

        switch (type)
        {
        case ShaderDataType::Float:
            return FLOAT_SIZE;
        case ShaderDataType::Float2:
            return FLOAT_SIZE * 2;
        case ShaderDataType::Float3:
            return FLOAT_SIZE * 3;
        case ShaderDataType::Float4:
            return FLOAT_SIZE * 4;
        case ShaderDataType::Mat3:
            return MAT3_SIZE;
        case ShaderDataType::Mat4:
            return MAT4_SIZE;
        case ShaderDataType::Int:
            return INT_SIZE;
        case ShaderDataType::Int2:
            return INT_SIZE * 2;
        case ShaderDataType::Int3:
            return INT_SIZE * 3;
        case ShaderDataType::Int4:
            return INT_SIZE * 4;
        case ShaderDataType::Bool:
            return BOOL_SIZE;
        case ShaderDataType::None:
            break;
        }

        HAZEL_CORE_ASSERT(false, "Unknown ShaderDataType!");
        return 0;
    }

    static constexpr uint32_t ShaderDataTypeCount(ShaderDataType type)
    {
        constexpr auto COUNT_ONE = 1;
        constexpr auto COUNT_TWO = 2;
        constexpr auto COUNT_THREE = 3;
        constexpr auto COUNT_FOUR = 4;
        switch (type)
        {
        case ShaderDataType::Float:
            return COUNT_ONE;
        case ShaderDataType::Float2:
            return COUNT_TWO;
        case ShaderDataType::Float3:
            return COUNT_THREE;
        case ShaderDataType::Float4:
            return COUNT_FOUR;
        case ShaderDataType::Mat3:
            return COUNT_THREE * COUNT_THREE;
        case ShaderDataType::Mat4:
            return COUNT_FOUR * COUNT_FOUR;
        case ShaderDataType::Int:
            return COUNT_ONE;
        case ShaderDataType::Int2:
            return COUNT_TWO;
        case ShaderDataType::Int3:
            return COUNT_THREE;
        case ShaderDataType::Int4:
            return COUNT_FOUR;
        case ShaderDataType::Bool:
            return COUNT_ONE;
        case ShaderDataType::None:
            break;
        }

        HAZEL_CORE_ASSERT(false, "Unknown ShaderDataType!");
        return 0;
    }

    struct BufferElement
    {
        std::string_view Name;
        uint32_t Offset, Size, Count;
        ShaderDataType Type;
        bool Normalized;

        BufferElement() {}

        BufferElement(ShaderDataType type, const std::string_view &name, bool normalized = false)
            : Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
        {
        }
    };

    class HAZEL_API BufferLayout
    {
        std::vector<BufferElement> m_Elements;
        uint32_t m_Stride = 0;

        void CalculateOffsetsAndStride()
        {
            uint32_t offset{};
            m_Stride = 0;
            for (auto &element : m_Elements)
            {
                element.Offset = offset;
                offset += element.Size;
                m_Stride += element.Size;
            }
        }

    public:
        BufferLayout() {}
        BufferLayout(const std::initializer_list<BufferElement> &elements) : m_Elements(elements)
        {
            CalculateOffsetsAndStride();
        }

        inline uint32_t GetStride() const { return m_Stride; }
        inline const std::vector<BufferElement> &GetElements() const { return m_Elements; }

        constexpr std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
        constexpr std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
        constexpr std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
        constexpr std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }
    };

    class HAZEL_API VertexBuffer
    {
    public:
        virtual ~VertexBuffer() {}

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual const BufferLayout &GetLayout() const = 0;
        virtual void SetLayout(const BufferLayout &layout) = 0;

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