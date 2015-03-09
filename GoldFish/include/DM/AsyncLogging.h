/*
 *  The asynchronous log class
 */

#ifndef ASYNCLOGGING_H
#define ASYNCLOGGING_H

#include <muduo/base/BlockingQueue.h>
#include <muduo/base/BoundedBlockingQueue.h>
#include <muduo/base/CountDownLatch.h>
#include <muduo/base/Mutex.h>
#include <muduo/base/Thread.h>

#include <muduo/base/LogStream.h>

#include <boost/bind.hpp>
#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

class AsyncLogging : boost::noncopyable
{
public:

    AsyncLogging(muduo::string const& basename,
        size_t rollSize,
        int flushInterval = 3);

    ~AsyncLogging()
    {
        if (_running)
        {
            stop();
        }
    }

    void append(char const* logline, int len);

    void start()
    {
        _running = true;
        _thread.start();
        _latch.wait();
    }

    void stop()
    {
        _running = false;
        _cond.notify();
        _thread.join();
    }

private:

    // declare but not define, prevent compiler-synthesized functions
    AsyncLogging(AsyncLogging const&);  // ptr_container
    void operator=(AsyncLogging const&);  // ptr_container

    void threadFunc();

    typedef muduo::detail::FixedBuffer<muduo::detail::kLargeBuffer> Buffer;
    typedef boost::ptr_vector<Buffer> BufferVector;
    typedef BufferVector::auto_type BufferPtr;

    int const _flushInterval;
    bool _running;
    muduo::string _basename;
    size_t _rollSize;
    muduo::Thread _thread;
    muduo::CountDownLatch _latch;
    muduo::MutexLock _mutex;
    muduo::Condition _cond;
    BufferPtr _currentBuffer;
    BufferPtr _nextBuffer;
    BufferVector _buffers;
};

#endif
