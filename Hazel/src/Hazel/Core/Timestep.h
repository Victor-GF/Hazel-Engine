#pragma once

namespace Hazel {

    class HAZEL_API Timestep
    {
        float m_Time;

    public:
        Timestep(float time = 0.0f)
            : m_Time(time)
        {
        }

        operator float() const { return m_Time; }

        float GetSeconds() const { return m_Time; }
        float GetMilliseconds() const { return m_Time * 1'000.0f; }
    };
}