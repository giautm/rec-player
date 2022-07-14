/*
 * chunk.hpp
 *
 *  Created on: 26 Jan 2015
 *      Author: Khanh Tran
 */

#ifndef RIFF_READER_TMG_RIFF_CHUNK_H_
#define RIFF_READER_TMG_RIFF_CHUNK_H_

#include "chunktype.h"
#include "riffbase.h"
#include "types.h"
#include "namespace.h"

RIFF_READER_BEGIN_NAMESPACE

class RiffChunk : public RiffBase {
public:
  RiffChunk(uint32_t pos, fourcc_t id, uint32_t size)
  : RiffBase(pos, id, size) {
  }

  virtual ~RiffChunk() {
  }

  virtual uint32_t getEndPosition() const {
    auto position = RiffBase::getEndPosition();

    auto id = getId();
    if (id == FourCC<'0','0','d','c'>::value || id == FourCC<'0','1','w','b'>::value) {
      return ((position + 511) & ~0x1ff);
    }

    return position;
  }
};

RIFF_READER_END_NAMESPACE

#endif /* RIFF_READER_TMG_RIFF_CHUNK_H_ */
