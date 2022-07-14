/*
 * chunktype.hpp
 *
 *  Created on: 26 Jan 2015
 *      Author: Khanh Tran
 */

#ifndef RIFF_READER_TMG_RIFF_CHUNKTYPE_H_
#define RIFF_READER_TMG_RIFF_CHUNKTYPE_H_

#include "types.h"
#include "namespace.h"

RIFF_READER_BEGIN_NAMESPACE

struct ChunkType {
  static fourcc_t const RIFF = FourCC<'R','I','F','F'>::value;
  static fourcc_t const LIST = FourCC<'L','I','S','T'>::value;
};

RIFF_READER_END_NAMESPACE

#endif /* RIFF_READER_TMG_RIFF_CHUNKTYPE_H_ */
