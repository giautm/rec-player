/*
 * types.h
 *
 *  Created on: 31 Jan 2015
 *      Author: Khanh Tran
 */

#ifndef TYPES_H_
#define TYPES_H_

#include <stdint.h>

#include "namespace.h"

RECPLAYER_BEGIN_NAMESPACE

struct MainAVIHeader {
  uint32_t dwMicroSecPerFrame;
  uint32_t dwMaxBytesPerSec;
  uint32_t dwPaddingGranularity;

  uint32_t dwFlags;
  uint32_t dwTotalFrames;
  uint32_t dwInitialFrames;
  uint32_t dwStreams;
  uint32_t dwSuggestedBufferSize;

  uint32_t dwWidth;
  uint32_t dwHeight;

  uint32_t dwReserved[4];
};

struct RECT {
  int32_t left;
  int32_t top;
  int32_t right;
  int32_t bottom;
};

struct AVIStreamHeader {
  riff::fourcc_t fccType;
  riff::fourcc_t fccHandler;
  uint32_t dwFlags;
  uint32_t dwPriority;
  uint32_t dwInitialFrames;
  uint32_t dwScale;
  uint32_t dwRate;
  uint32_t dwStart;
  uint32_t dwLength;
  uint32_t dwSuggestedBufferSize;
  uint32_t dwQuality;
  uint32_t dwSampleSize;
  RECT rcFrame;
};

struct OTH_DATA_T {
  uint8_t rec_next;
  uint8_t rsv[1];
  uint16_t file_num;
  uint32_t s_tick;
  uint32_t t_tick;
  uint32_t e_tick;
  uint32_t s_offset;
  uint32_t t_offset;
  uint32_t e_offset;
  char hex_name[8];
  uint32_t free_clust;
  uint8_t csize;
  char rsv2[3];
  uint32_t recid;
};

RECPLAYER_END_NAMESPACE

#endif /* TYPES_H_ */
