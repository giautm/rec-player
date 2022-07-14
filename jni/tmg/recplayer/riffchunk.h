/*
 * chunk.hpp
 *
 *  Created on: 26 Jan 2015
 *      Author: Khanh Tran
 */

#ifndef RIFF_READER_TMG_RIFF_CHUNK_H_
#define RIFF_READER_TMG_RIFF_CHUNK_H_

#include <string>

#include "chunktype.h"
#include "riffbase.h"
#include "types.h"
#include "namespace.h"

RIFF_READER_BEGIN_NAMESPACE

class RiffChunk : public RiffBase {
public:
  RiffChunk(uint32_t position, ckhead_t const& chunk)
  : RiffBase(position, chunk) {
  }

  virtual ~RiffChunk() {
  }

  virtual uint32_t getEndPosition() const {
    auto position = RiffBase::getEndPosition();

    auto id = getId();
    if (id == ChunkType::_00dc || id == ChunkType::_01wb) {
      return ((position + 511) & ~0x1ff);
    }

    return position;
  }
};

RIFF_READER_END_NAMESPACE

#endif /* RIFF_READER_TMG_RIFF_CHUNK_H_ */
