#include "ringbuffer.h"



RingBuffer::RingBuffer(int capacity)
    : m_capacity(capacity),
    m_buffer(capacity)
{

}

void RingBuffer::push(float sample)
{
    m_buffer[m_head] = sample;
    m_head = (m_head + 1) % m_capacity;

    if(m_head == 0){
        m_full = true;
    }
}

std::vector<float> RingBuffer::data() const
{
    std::vector<float> res;
    int size;

    if(m_full){
        size = m_capacity;
    }
    else{
        size = m_head;
    }

    res.reserve(size);

    if(!m_full){
        for (int i = 0; i<m_head; i++){
            res.push_back(m_buffer[i]);
        }
    }
    else{
        //идём с головы
        for(int i = 0; i<m_capacity; i++){
            int id = (m_head + i) % m_capacity;
            res.push_back(m_buffer[id]);
        }
    }
    return res;
}

QVector<float> RingBuffer::qData() const
{
    QVector<float> res;


    int currentSize;

    if(m_full)
        currentSize = m_capacity;
    else
        currentSize = m_head;


    res.reserve(currentSize);


    if(!m_full)
    {
        for(int i = 0; i < m_head; i++)
        {
            res.push_back(m_buffer[i]);
        }
    }
    else
    {
        for(int i = 0; i < m_capacity; i++)
        {
            int id = (m_head + i) % m_capacity;

            res.push_back(m_buffer[id]);
        }
    }


    return res;
}

void RingBuffer::clear()
{
    std::fill(m_buffer.begin(), m_buffer.end(), 0.0f);

    m_head = 0;
    m_full = false;
}

int RingBuffer::size() const
{
    if(m_full){
        return m_capacity;
    }
    return m_head;
}

void RingBuffer::removeFirst(int count)
{
    if (count <= 0){return;}

    int current_size = size();

    if(count >= current_size){
        clear();
    }
    else{
        m_head = (m_head + count) % m_capacity;

        if(m_full){
            m_full = false;
        }
    }
}

