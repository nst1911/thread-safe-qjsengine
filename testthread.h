#ifndef TESTTHREAD_H
#define TESTTHREAD_H

#include "threadsafeqjsengine.h"

class TestThread_NotSafe : public QThread
{
    Q_OBJECT

    QJSEngine* m_engine;

    void run() override {
        QJSValue function = m_engine->evaluate("(function() { if (++iteration % 100 == 0) console.log(iteration); })");;
        while (true)
            function.call({1,2,3,4,5,6,7,8,9,0}); }

public:
    TestThread_NotSafe(QJSEngine* engine) : m_engine(engine) {}
};

class TestThread_Safe : public QThread
{
    Q_OBJECT

    QJSEngine* m_engine;

    void run() override {
        QJSValue function = ThreadSafeQJSEngine::call(m_engine, [&]{ return m_engine->evaluate("(function() { if (++iteration % 100 == 0) console.log(iteration); })");});
        while (true)
            ThreadSafeQJSEngine::call(m_engine, [&]{function.call({1,2,3,4,5,6,7,8,9,0});});
    }

public:
    TestThread_Safe(QJSEngine* engine) : m_engine(engine) {}
};

#endif // TESTTHREAD_H
