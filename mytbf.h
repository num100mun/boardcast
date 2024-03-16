////
//// Created by 18746 on 2024/3/9.
////
//
//#ifndef IPV4_MYTBF_H
//#define IPV4_MYTBF_H
//#include "include.h"
//#include <mutex>
//#include <thread>
//#include <condition_variable>
//#include "threadpool.h"
//using namespace std;
//
//class mytbf {
//public:
//    int _cps;
//    int _burst;
//    int _token;
//    mutex _mutex;
//    condition_variable _cv;
//
//    mytbf(int cps, int burst) : _cps(cps), _burst(burst), _token(0) {}
//
//    int mytbf_fetch_token(int size) {
//        unique_lock<mutex> lock(_mutex);
//        if (_token == 0)
//            _cv.wait(lock, [this]() { return _token > 0; });
//        int re = min(_token, size);
//        _token -= re;
//        return re;
//    }
//
//    void mytbf_return_token(int size) {
//        unique_lock<mutex> lock(_mutex);
//        _token = min(_burst, _token + size);
//        _cv.notify_one();
//    }
//
//    int mytbf_check_token() {
//        return _token;
//    }
//};
//class mytbf_mang {
//private:
//    vector<unique_ptr<mytbf>> mytbf_list;
//    mutex _mutex;
//    condition_variable _cv;
//
//
//    mytbf_mang() {
//        auto lam = [this]() {
//            while (true) {
//                mytbf_list.reserve(10);
//                for (int i = 0; i < 10; ++i) {
//                    unique_ptr<mytbf> ptr = make_unique<mytbf>(i, i * 10);
//                    mytbf_list.push_back(move(ptr));
//                }
//
//
//                this_thread::sleep_for(chrono::seconds(1));
//                unique_lock<mutex> lock(_mutex);
//                for (auto & tbf : mytbf_list) {
//                    {
////                        unique_lock<mutex> tbf_lock(_mutex);
//                    tbf->_token = min(tbf->_burst, tbf->_token + tbf->_cps);
////                    tbf->_cv.notify_one();
//                        cout << "is run" << endl;
//                    }
//                }
//            }
//        };
//        pool.enqueue(lam); // 使用线程池的 enqueue 方法
//    }
//
//public:
//    static mytbf_mang& get_instance() {
//        static mytbf_mang instance;
//        return instance;
//    }
//
//    mytbf* get_tbf(int cps = 0, int burst = 0) {
//        lock_guard<mutex> guard(_mutex);
//        mytbf_list.emplace_back(make_unique<mytbf>(cps, burst));
//        return mytbf_list.back().get();
//    }
//
//    void destroy(mytbf* tbf) {
//        lock_guard<mutex> guard(_mutex);
//        for (auto it = mytbf_list.begin(); it != mytbf_list.end(); ++it) {
//            if (it->get() == tbf) {
//                it = mytbf_list.erase(it);
//                break;
//            }
//        }
//    }
//};
//
//
//
//#endif //IPV4_MYTBF_H
