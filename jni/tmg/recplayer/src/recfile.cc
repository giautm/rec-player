/*
 * recfile.cc
 *
 *  Created on: 6 Feb 2015
 *      Author: Khanh Tran
 */

#include <tmg/recplayer/recfile.h>

RECPLAYER_BEGIN_NAMESPACE

using namespace riff;

static char const* const TAG = "RECFILE";

static fourcc_t const JUNK = FourCC<'J','U','N','K'>::value;
static fourcc_t const AVI_ = FourCC<'A','V','I',' '>::value;

static fourcc_t const hdrl = FourCC<'h','d','r','l'>::value;
static fourcc_t const avih = FourCC<'a','v','i','h'>::value;

static fourcc_t const vids = FourCC<'v','i','d','s'>::value;
static fourcc_t const auds = FourCC<'a','u','d','s'>::value;

static fourcc_t const strl = FourCC<'s','t','r','l'>::value;
static fourcc_t const strh = FourCC<'s','t','r','h'>::value;
static fourcc_t const strf = FourCC<'s','t','r','f'>::value;

static fourcc_t const INFO = FourCC<'I','N','F','O'>::value;
static fourcc_t const CANO = FourCC<'C','A','N','O'>::value;
static fourcc_t const PASS = FourCC<'P','A','S','S'>::value;
static fourcc_t const OTH_ = FourCC<'O','T','H',' '>::value;

static fourcc_t const movi = FourCC<'m','o','v','i'>::value;
static fourcc_t const _99aa = FourCC<'9','9','a','a'>::value;
static fourcc_t const _05fp = FourCC<'0','5','f','p'>::value;
static fourcc_t const _02ut = FourCC<'0','2','u','t'>::value;
static fourcc_t const _06gp = FourCC<'0','6','g','p'>::value;
static fourcc_t const _04ka = FourCC<'0','4','k','a'>::value;
static fourcc_t const _00dc = FourCC<'0','0','d','c'>::value;
static fourcc_t const _01wb = FourCC<'0','1','w','b'>::value;

struct RecFile::impl {
  RiffBase* _riff;

  RiffBase* _listHdrl; // LIST "hdrl"
  RiffBase* _listInfo;// LIST "INFO"
  RiffBase* _listMovi;// LIST "movi"

  std::vector<RiffBase*> _frames;
  std::vector<RiffBase*> _audios;
  std::vector<RiffBase*> _sensor;
  std::vector<RiffBase*> _gps;
  std::vector<RiffBase*> _utc;

  impl()
  :_riff(0), _listHdrl(0), _listInfo(0), _listMovi(0) {
  }
};

RecFile::RecFile(std::string const& filename)
: _file(filename.c_str()), _impl(new impl), currentFrames(0) {
}

RecFile::~RecFile() {
  if (_impl) {
    delete _impl;
  }
}

bool RecFile::open() {
  if (_file.is_open()) {
    _impl->_riff = parseRiff(_file);
    if (_impl->_riff) {
      foreachChunk(*(_impl->_riff), [this] (RiffBase* chunk) {
            switch (chunk->getId()) {
              case movi:
              _impl->_listMovi = chunk;
              break;
            }
          });

      foreachChunk(*(_impl->_listMovi),[this] (RiffBase* chunk) {
            switch (chunk->getId()) {
              case _00dc:
              _impl->_frames.push_back(chunk);
              break;
            }
          });
      return true;
    }
  }

  return false;
}

bool RecFile::readFrame(char* buffer) {
  if (_file.is_open()) {
    if (currentFrames >= _impl->_frames.size()) {
      currentFrames = 0;
    }

    riff::RiffBase* chunk = _impl->_frames[currentFrames++];
    if (chunk) {
      return chunk->readData(_file, buffer, chunk->getSize());
    }

  }

  return false;
}

char* RecFile::readFrame(uint32_t& size) {
  if (_file.is_open()) {
    if (currentFrames >= _impl->_frames.size()) {
      currentFrames = 0;
    }

    riff::RiffBase* chunk = _impl->_frames[currentFrames++];
    if (chunk) {
      size = chunk->getSize();
      char* buffer = new char[size];
      if (chunk->readData(_file, buffer, size)) {
        return buffer;
      }
      else {
        delete buffer;
      }
    }
  }

  return NULL;
}
RECPLAYER_END_NAMESPACE
