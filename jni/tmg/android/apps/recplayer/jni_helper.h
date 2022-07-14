/*
 * jni_helper.h
 *
 *  Created on: 31 Jan 2015
 *      Author: Khanh Tran
 */

#ifndef JNI_HELPER_H_
#define JNI_HELPER_H_

#include <jni.h>
#include <iostream>

class cstring {
public:
  cstring(JNIEnv * env, jstring str) :
      _jenv(env), _jstr(str), _cstr(env->GetStringUTFChars(_jstr, 0)) {
  }

  virtual ~cstring() {
    if (_jenv && _cstr) {
      _jenv->ReleaseStringUTFChars(_jstr, _cstr);
    }
  }

  operator bool() const {
    return (_cstr != 0);
  }

  char const* c_str() const {
    return _cstr;
  }

private:
  JNIEnv* _jenv;
  jstring _jstr;
  char const* _cstr;
};

inline std::ostream& operator<<(std::ostream& os, cstring const& cstr) {
  return os << cstr.c_str();
}

#endif /* JNI_HELPER_H_ */
