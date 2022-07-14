/*
 * reader.cpp
 *
 *  Created on: 26 Jan 2015
 *      Author: Khanh Tran
 */

#include <tmg/riff/riff.h>

#include <stdlib.h> // for NULL
#include <iostream>

#include <tmg/riff/stacked_task.h>

RIFF_READER_BEGIN_NAMESPACE

template<typename _Type>
inline bool read(std::istream& is, _Type& r) {
  if (is.good()) {
    is.read(reinterpret_cast<char*>(&r), (std::streamsize)sizeof(_Type));

    return is.good() && is.gcount() == sizeof(_Type);
  }

  return false;
}

RiffBase* readChunk(std::istream& is) {
  RiffBase* chunk = NULL;

  struct {
    fourcc_t id;
    uint32_t size;
  }header;

  if (read(is, header)) {
    uint32_t position = is.tellg();

    if (header.id == ChunkType::RIFF || header.id == ChunkType::LIST) {
      fourcc_t type = 0;
      if (read(is, type) && type != 0) {
        chunk = new RiffList(position, header.id, header.size, type);
      }
    }
    else {
      chunk = new RiffChunk(position, header.id, header.size);
      is.seekg(chunk->getEndPosition(), std::ios::beg);
    }
  }

  return chunk;
}

RiffBase* parseRiff(std::istream& is) {
  if (is.good()) {
    is.seekg(0, std::ios::beg);

    auto riff = readChunk(is);
    if (riff != NULL && riff->RiffBase::getId() == ChunkType::RIFF) {
      bool success = stackedTask(riff,
          [&is](RiffBase* top) -> bool {
            return top->getEndPosition() <= is.tellg();
          },
          [&is](RiffBase* top, bool& pushToStack, bool& cancel) -> RiffBase* {
            auto chunk = readChunk(is);
            if (chunk) {
              auto id = chunk->RiffBase::getId();
              if (id == ChunkType::RIFF || id == ChunkType::LIST) {
                pushToStack = true;
              }

              dynamic_cast<RiffList&>(*top).addChunk(chunk);
            }
            else {
              cancel = true;
            }

            return chunk;
          });

      if (!success) {
        delete riff;
        riff = NULL;
      }

      is.clear();
      is.seekg(0, std::ios::beg);
    }

    return riff;
  }

  return NULL;
}

RIFF_READER_END_NAMESPACE
