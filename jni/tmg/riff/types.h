/*
 * types.h
 *
 *  Created on: 27 Jan 2015
 *      Author: Khanh Tran
 */

#ifndef RIFF_READER_TMG_RIFF_TYPES_H_
#define RIFF_READER_TMG_RIFF_TYPES_H_

#include <sys/endian.h>
#include <stdint.h>
#include <string>

#include "namespace.h"

RIFF_READER_BEGIN_NAMESPACE

typedef uint32_t fourcc_t;

template <char a, char b, char c, char d>
struct FourCC {
#if _BYTE_ORDER == _LITTLE_ENDIAN
  static fourcc_t const value =
  (fourcc_t)a |
  (fourcc_t)b << 8 |
  (fourcc_t)c << 16 |
  (fourcc_t)d << 24;
#elif _BYTE_ORDER == _BIG_ENDIAN
  static fourcc_t const value =
  (fourcc_t)a << 24 |
  (fourcc_t)b << 16 |
  (fourcc_t)c << 8 |
  (fourcc_t)d;
#endif /* _BYTE_ORDER */
};

inline
std::string fourccAsString(fourcc_t const& fourcc) {
  if (fourcc == 0) {
    return std::string();
  }

  char const* idPtr = reinterpret_cast<char const*>(&fourcc);
  return std::string(idPtr, idPtr + sizeof(fourcc_t));
}

RIFF_READER_END_NAMESPACE

#endif /* RIFF_READER_TMG_RIFF_TYPES_H_ */
