#ifndef THREADSAFEQJSENGINE_H
#define THREADSAFEQJSENGINE_H

#include <QJSEngine>
#include <QThread>

namespace ThreadSafeQJSEngine {

template <typename F>
auto call(QJSEngine* engine, F&& f) -> typename std::enable_if<!std::is_void<decltype(f())>::value, decltype(f())>::type
{
    if (QThread::currentThread() != engine->thread())
    {
        decltype(f()) result;
        QMetaObject::invokeMethod(engine, std::forward<F>(f), Qt::BlockingQueuedConnection, &result);
        return result;
    }
    else
    {
        return std::forward<F>(f)();
    }
}

template <typename F>
auto call(QJSEngine* engine, F&& f) -> typename std::enable_if<std::is_void<decltype(f())>::value, void>::type
{
    if (QThread::currentThread() != engine->thread())
    {
        QMetaObject::invokeMethod(engine, std::forward<F>(f), Qt::BlockingQueuedConnection);
    }
    else
    {
        std::forward<F>(f)();
    }
}

};

#endif // THREADSAFEQJSENGINE_H
