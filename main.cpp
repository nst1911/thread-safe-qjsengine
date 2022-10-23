#include <QCoreApplication>
#include <QJSEngine>
#include <QThread>
#include <QTimer>
#include <QDebug>
#include "testthread.h"

int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);

    QJSEngine engine;
    engine.installExtensions(QJSEngine::ConsoleExtension);
    engine.evaluate("var iteration = 0;");

    /* 1. Using QJSEngine in its own thread (main thread) */
//    QJSValue function = engine.evaluate("(function() { if (++iteration % 100 == 0) console.log(iteration); })");;
//    while (true)
//        function.call({1,2,3,4,5,6,7,8,9,0}); }

    /* 2. Using QJSEngine in different thread (not safe version) */
//    auto thread = new TestThread_NotSafe(&engine);
//    thread->start();

    /* 3. Using QJSEngine in different thread (safe version) */
    auto thread = new TestThread_Safe(&engine);
    thread->start();

    return app.exec();
}
