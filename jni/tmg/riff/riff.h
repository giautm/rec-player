/*
 * riff.h
 *
 *  Created on: 29 Jan 2015
 *      Author: Khanh Tran
 */

#ifndef RIFF_READER_TMG_RIFF_RIFF_H_
#define RIFF_READER_TMG_RIFF_RIFF_H_

#include "namespace.h"
#include "types.h"
#include "chunktype.h"
#include "riffbase.h"
#include "riffchunk.h"
#include "rifflist.h"

RIFF_READER_BEGIN_NAMESPACE

RiffBase* parseRiff(std::istream& is);

RIFF_READER_END_NAMESPACE

#endif /* RIFF_H_ */
