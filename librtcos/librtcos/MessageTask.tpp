#pragma once

namespace rtcos
{
    template <class T>
    inline MessageTask<T>::MessageTask(Queue<T>& q, const T& initial)
        : queue(q)
        , message(initial)
    {
    }

    template <class T>
    void MessageTask<T>::execute()
    {
        disableQueueInterrupt();
        message = queue.get();
        queue.remove();
        enableQueueInterrupt();

        process(message);
    }
}
