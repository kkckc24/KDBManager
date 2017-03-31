/*
 * Copyright 2017 David Kang (kkckc24@gmail.com)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http: *www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef KMUTEX_H
#define	KMUTEX_H

#ifdef	__cplusplus
extern "C" {
#endif

    typedef pthread_t ithread_t;
    typedef pthread_mutex_t imutex_t;
    typedef pthread_attr_t ithread_attr_t;

#define _THREAD_ASSERT_ 1

#if _THREAD_ASSERT_
#include <assert.h>
#include <errno.h>
#endif

    class KMutex {
    public:

        KMutex() {
            int err = pthread_mutex_init(&myId, NULL);
#if _THREAD_ASSERT_
            assert(err == 0);
#endif
        }

        ~KMutex() {
            int err = pthread_mutex_destroy(&myId);
#if _THREAD_ASSERT_
            assert(err != EBUSY /* currently locked */);
            assert(err == 0);
#endif
        }

        void lock() {
            int err = pthread_mutex_lock(&myId);
#if _THREAD_ASSERT_            
            assert(err != EINVAL);
            assert(err != EPERM);
            assert(err == 0);
#endif            
        }

        void unlock() {
            int err = pthread_mutex_unlock(&myId);
#if _THREAD_ASSERT_                        
            assert(err != EINVAL);
            assert(err != EPERM);
            assert(err == 0);
#endif            
        }

    private:
        pthread_mutex_t myId;
    };


#ifdef	__cplusplus
}
#endif

#endif	/* KMUTEX_H */

