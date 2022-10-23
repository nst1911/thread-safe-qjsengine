# ThreadSafeQJSEngine

`ThreadSafeQJSEngine` is a set of functions allowing to invoke `QJSEngine` and `QJSValue` objects methods in the engine's thread with blocking queued calls. 

# Why?

Thread-safe status of `QJSEngine` is not clarified enough - using it in multithreaded programs lead to undefined behaviour and unexcepted crashes inside `QJSEngine`'s implementation. 
I've found a workaround to solve this problem at the [bugreport](https://bugreports.qt.io/browse/QTBUG-83410) and adapted for my purposes. I hope my code may help people with similar issues.

# Examples and use cases

Example of using these functions is in `TestThread_Safe::run()` method (`testthread.h`).

main.cpp provides three situations:
1) Using `QJSEngine` as usual in its own thread (main thread): no crashes.
2) Using `QJSEngine` as usual in different thread (not the thread where an engine object was created): **an unexpected crash** (`SEGFAULT`) will be thrown in some time.
3) Using `ThreadSafeQJSEngine` functions to wrap `QJSEngine` method calls in blocking queue: no crashes.

