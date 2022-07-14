/*
 * RiffList.h
 *
 *  Created on: 26 Jan 2015
 *      Author: Khanh Tran
 */

#ifndef RIFF_READER_TMG_RIFF_RIFFLIST_H_
#define RIFF_READER_TMG_RIFF_RIFFLIST_H_

#include <vector>
#include <algorithm>

#include "riffbase.h"

RIFF_READER_BEGIN_NAMESPACE

struct chunk_has_id {
  chunk_has_id(fourcc_t chunkId)
  : _id(chunkId) {
  }

  bool operator ()(RiffBase const* const& chunk) const {
    return chunk->getId() == _id;
  }

private:
  fourcc_t _id;
};

class RiffList: public RiffBase {
public:
  RiffList(uint32_t pos, fourcc_t id, uint32_t size, fourcc_t type)
  : RiffBase(pos, id, size) , _chks(), _type(type) {
  }

  virtual ~RiffList() {
    clear();
  }

  void clear() {
    for (auto it : _chks) {
      if (it) {
        delete it;
      }
    }
    _chks.clear();
  }

  void addChunk(RiffBase* chunk) {
    _chks.push_back(chunk);
  }

  std::vector<RiffBase*> getSubChunks() const {
    return _chks;
  }

  RiffBase* findChunkById(fourcc_t const& chunkId) const {
    auto it = std::find_if(_chks.begin(), _chks.end(), chunk_has_id(chunkId));
    if (it != _chks.end()) {
      return (*it);
    }

    return NULL;
  }

  virtual fourcc_t getId() const {
    return _type;
  }

  virtual void print(std::ostream& os) const {
    os << fourccAsString(RiffBase::getId()) << " - ";
    RiffBase::print(os);

    for (auto it : _chks) {
      if (it) {
        it->print(os);
      }
    }

    os << "------ end of: " << fourccAsString(getId()) << " -----\n";
  }

private:
  std::vector<RiffBase*> _chks;
  fourcc_t _type;
};

template<typename _Pred> inline
bool foreachChunk(RiffBase const& chunk, _Pred pred) {
  try {
    auto&& list = dynamic_cast<RiffList const&>(chunk);
    auto&& chunks = list.getSubChunks();
    for (auto& it : chunks) {
      pred(it);
    }
    return true;
  }
  catch (...) {
    return false;
  }
}

RIFF_READER_END_NAMESPACE

#endif /* RIFF_READER_TMG_RIFF_RIFFLIST_H_ */
