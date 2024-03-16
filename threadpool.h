//
// Created by 18746 on 2024/3/11.
//

#ifndef IPV4_THREADPOOL_H
#define IPV4_THREADPOOL_H
#include "include.h"
#include <thread>
#include <queue>
#include <functional>
#include <mutex>
#include <atomic>
#include <condition_variable>
using namespace std;
class threadpool{
private:
    vector<thread> _workers;
    queue<function<void()>> _tasks;
    mutex _mutex;
    condition_variable _cv;
    atomic<bool> _stop;

private:
    threadpool();
    threadpool(const threadpool &);
    threadpool operator=(const threadpool &);
    threadpool(int num_thread){
        for(int i=0; i< num_thread; i++){
            _workers.emplace_back([this](){
                while(true){
                    function<void()> task;
                    {
                        unique_lock<mutex> lock(_mutex);
                        _cv.wait(lock, [this]() {
                            return _stop || !_tasks.empty();
                        });
                        if(_stop && _tasks.empty())
                            return;
                        task = move(_tasks.front());
                        _tasks.pop();
                    }
                    task();
                }
            });
        }
    }


public:
    static threadpool & get_instance(){
        static threadpool t(THREAD_NUM);
        return t;
    }

    template<class F, class... Args>
    void enqueue(F && task, Args&&... args){
        {
            unique_lock<mutex> lock(_mutex);
            _tasks.emplace(bind(forward<F>(task), forward<Args>(args)...));

        }
        _cv.notify_one();
    }
    ~threadpool(){
        {
            unique_lock<mutex> lock(_mutex);
            _stop = true;
        }
        _cv.notify_all();
        for(thread &t: _workers)
            t.join();
    }

};
static threadpool & pool = threadpool::get_instance();
#endif //IPV4_THREADPOOL_H
