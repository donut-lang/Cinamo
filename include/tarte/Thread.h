/* coding: utf-8 */
/**
 * Tarte
 *
 * Copyright 2012-2013, PSI
 * Dual licensed under the BSD or GPL Version 3 (or any later) licenses.
 * !! GPL is STRONGLY recommended !!
 * see: http://donut-lang.org/license/
 */

#pragma once
#include "Common.h"
#include "Platform.h"

#if TARTE_WINDOWS || TARTE_ANDROID
#include <boost/thread.hpp>
#include <boost/interprocess/detail/atomic.hpp>
#include <boost/atomic.hpp>
namespace std {
using boost::mutex;
using boost::recursive_mutex;
using boost::lock_guard;
using boost::condition_variable;
using boost::unique_lock;
using boost::thread;
using boost::atomic;
namespace chrono {
using namespace boost::chrono;
}
}
#else
#include <thread>
#include <condition_variable>
#include <mutex>
#include <atomic>
#endif
