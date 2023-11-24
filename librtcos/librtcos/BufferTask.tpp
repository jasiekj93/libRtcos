#pragma once

namespace rtcos
{
    template <class T>
    inline BufferTask<T>::BufferTask(ShadowBuffer<T>& b)
        : buffer(b)
    {
    }

    template <class T>
    inline void BufferTask<T>::execute()
    {
        disableBufferInterrupt();
        buffer.swap();
        enableBufferInterrupt();

        auto& output = buffer.getOutput();
        process(output.getData(), output.getSize());
        output.clear();
    }
}
