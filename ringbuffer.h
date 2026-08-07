#ifndef RINGBUFFER_H
#define RINGBUFFER_H
#include <vector>
#include <QVector>
#include <algorithm>

class RingBuffer
{
private:
    std::vector<float> m_buffer;
    int m_head = 0;
    bool m_full = false;
    int m_capacity;

public:
    explicit RingBuffer(int capacity = 4096);

    void push(float sample);
    std::vector<float> data() const;
    QVector<float> qData() const;
    void clear();
    int size() const;
};

#endif // RINGBUFFER_H
