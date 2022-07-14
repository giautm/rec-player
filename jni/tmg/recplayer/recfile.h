/*
 * recfile.h
 *
 *  Created on: 29 Jan 2015
 *      Author: Khanh Tran
 */

#ifndef PLAYREC_TMG_RECFILE_RECFILE_H_
#define PLAYREC_TMG_RECFILE_RECFILE_H_

#include <iostream>
#include <fstream>
#include <string>

#include "../riff/riff.h"

#include "types.h"
#include "namespace.h"

RECPLAYER_BEGIN_NAMESPACE

class RecFile {
public:
  RecFile(std::string const& filename);
  ~RecFile();

  uint32_t getFrameScale() const {
    // TODO: hard-code for simple testing!!!
    return 1000;
  }

  uint32_t getFrameRate() const {
    // TODO: hard-code for simple testing!!!
    return 15000;
  }

  uint32_t getWidth() const {
    // TODO: hard-code for simple testing!!!
    return 640;
  }

  uint32_t getHeight() const {
    // TODO: hard-code for simple testing!!!
    return 480;
  }

  uint32_t getFrameCount() const;

  void addFrame(riff::RiffBase* frame);
  bool readFrame(char* buffer);
  char* readFrame(uint32_t& size);
  bool open();
private:
  std::ifstream _file;

  struct impl;
  impl* _impl;

  int currentFrames;
};

RECPLAYER_END_NAMESPACE

#endif /* PLAYREC_TMG_RECFILE_RECFILE_H_ */

