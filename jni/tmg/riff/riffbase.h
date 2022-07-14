/*
 * riffbase.h
 *
 *  Created on: 28 Jan 2015
 *      Author: Khanh Tran
 */

#ifndef RIFF_READER_TMG_RIFF_RIFFBASE_H_
#define RIFF_READER_TMG_RIFF_RIFFBASE_H_

#include <iostream>
#include <string>

#include "types.h"
#include "chunktype.h"
#include "namespace.h"

RIFF_READER_BEGIN_NAMESPACE

class RiffBase {
public:
  RiffBase()
  : _position(0), _id(0), _size(0) {
  }

  RiffBase(uint32_t pos, fourcc_t id, uint32_t size)
  : _position(pos), _id(id), _size(size) {
  }

  virtual ~RiffBase() {
  }

  virtual fourcc_t getId() const {
    return _id;
  }

  virtual uint32_t getSize() const {
    return _size;
  }

  virtual uint32_t getBeginPosition() const {
    return _position;
  }

  virtual uint32_t getEndPosition() const {
    return _position + _size + (_size & 0x1);
  }

  virtual void print(std::ostream& os) const {
    os << fourccAsString(getId()) << " - (len = " << getSize()
    << ", off = " << getBeginPosition() << ")\n";
  }

  template <typename _Type>
  bool readData(std::istream& is, _Type& data) const {
    return readData(is, reinterpret_cast<char*>(&data), sizeof(_Type));
  }

  bool readData(std::istream& is, std::string& data) const {
    auto size = getSize();
    data.resize(size);

    return readData(is, const_cast<char*>(data.c_str()), size);
  }

  bool readData(std::istream& is, char* data, uint32_t size) const {
    if (is.good())
    {
      auto cpos = is.tellg();

      auto id = RiffBase::getId();
      if (id != ChunkType::RIFF && id != ChunkType::LIST && size <= getSize())
      {
        auto pos = getBeginPosition();
        is.seekg(pos, std::ios::beg);

        if (pos == is.tellg() && is.read(data, size).gcount() == size) {
          return true;
        }
        else
        {
          is.clear();
          is.seekg(cpos, std::ios::beg);
        }
      }
    }

    return false;
  }
protected:
  uint32_t _position;
  fourcc_t _id;
  uint32_t _size;
};

RIFF_READER_END_NAMESPACE

#endif /* RIFF_READER_TMG_RIFF_RIFFBASE_H_ */
