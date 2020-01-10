#pragma once
#include "../CoreDef.h"

namespace MySTL
{
    class Arena
    {
    public:
        Arena();
        ~Arena();

        void Alloc(U64 size_of_memory);
        void Free() const;
        void Resize(U64 size_of_memory);
        void Reset() const;

    public:
        template <typename T>
        T* Push(int count = 1)
        {
            return (T*)Push(sizeof(T) * count);
        }

        template <typename T>
        size_t Size() const
        {
            return m_used_size / sizeof(T);
        }

        template <typename T>
        T* Front()
        {
            return (T*)Front();
        }

    private:
        MemoryPtr Front() const;
        MemoryPtr Push(size_t size);

    private:
        MemoryPtr m_allocated_memory = nullptr;
        size_t m_maximum_size = 0;
        size_t m_used_size = 0;
    };
}
