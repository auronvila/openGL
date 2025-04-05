//
// Created by Auron Vila on 5.04.2025.
//

#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H

class IndexBuffer {
private:
    unsigned int m_RendererId;
    unsigned int m_Count;

public:
    IndexBuffer(const unsigned int *data, unsigned int count);

    ~IndexBuffer();

    void Bind() const;

    void UnBind() const;

    inline unsigned int GetCount() const { return m_Count; }
};

#endif //INDEXBUFFER_H
