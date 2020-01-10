#include "MemoryArena.h"
#include <cassert>

namespace MySTL
{
    MemoryArena::MemoryArena()
    {
    }

    MemoryArena::~MemoryArena()
    {
    }

    void MemoryArena::Alloc(U64 size_of_memory)
    {
        assert(m_allocated_memory == nullptr);
        m_allocated_memory = malloc(size_of_memory);
        memset(m_allocated_memory, 0, size_of_memory);
        m_maximum_size = size_of_memory;
        m_used_size    = 0;
    }

    void MemoryArena::Free() const
    {
        free(m_allocated_memory);
    }

    void MemoryArena::Resize(U64 size_of_memory)
    {
        if (m_allocated_memory != nullptr)
        {
            MemoryPtr temp = realloc(m_allocated_memory, size_of_memory);
            if (temp != nullptr)
            {
                m_allocated_memory = temp;
            }
            //free(m_allocated_memory);
        }
        m_maximum_size = size_of_memory;
        if (m_used_size >= size_of_memory)
        {
            m_used_size = size_of_memory;
        }
        else
        {
            memset(((MemoryUnit)m_allocated_memory + m_used_size), 0, (size_of_memory - m_used_size));
        }
    }

    void MemoryArena::Reset() const
    {
        memset(m_allocated_memory, 0, m_maximum_size);
    }

    MemoryPtr MemoryArena::Front() const
    {
        return m_allocated_memory;
    }

    MemoryPtr MemoryArena::Push(size_t size)
    {
        assert(m_used_size + size <= m_maximum_size);
        MemoryPtr memory = (MemoryUnit)m_allocated_memory + m_used_size;
        m_used_size += size;
        return memory;
    }
}
