// Copyright (c) 2014, Solrex Yang
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 
// * Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
// 
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
// 
// * Neither the name of the {organization} nor the names of its
//   contributors may be used to endorse or promote products derived from
//   this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
// Acknowledgment: This Singleton idea is borrowed from
// https://github.com/chenshuo/muduo with some tiny modifications.

#ifndef OOO_SINGLETON_H_INCLUDED
#define OOO_SINGLETON_H_INCLUDED

#include <pthread.h>

namespace ooo {

/// @brief Thread-safe, no-manual destroy Singleton template
template<typename T>
class Singleton {
public:
    /// @brief Get the singleton instance
    static T* get() {
        pthread_once(&_p_once, &Singleton::_new);
        return _instance;
    }

private:
    Singleton();
    ~Singleton();
    Singleton(const Singleton &);
    const Singleton& operator=(const Singleton &);

    /// @brief Construct the singleton instance
    static void _new() {
        _instance = new T();
    }

    /// @brief  Destruct the singleton instance
    /// @note Only work with gcc
    __attribute__((destructor)) static void _delete() {
        typedef char T_must_be_complete[sizeof(T) == 0 ? -1 : 1];
        (void) sizeof (T_must_be_complete);
        delete _instance;
    }

    static pthread_once_t _p_once;      ///< Initialization once control
    static T*             _instance;    ///< The singleton instance
};

template<typename T>
pthread_once_t Singleton<T>::_p_once = PTHREAD_ONCE_INIT;

template<typename T>
T* Singleton<T>::_instance= NULL;

}

#endif

