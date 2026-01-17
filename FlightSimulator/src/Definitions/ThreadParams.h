#pragma once

#include <thread>
#include <mutex>
#include <condition_variable>

namespace AFS {

struct SThreadParams
{
    std::thread* pThread;

    bool isStarted;
    bool isExitRequested;
    bool isExited;
    bool isSuspended;

    std::mutex suspendMutex;
    std::condition_variable suspendCV;

    SThreadParams()
        : pThread(nullptr)
        , isStarted(false)
        , isExitRequested(false)
        , isExited(false)
        , isSuspended(false)
    {
    }

    ~SThreadParams()
    {
        if (pThread != nullptr)
        {
            delete pThread;
            pThread = nullptr;
        }
    }
};

}
