// Copyright CERN and copyright holders of ALICE O2. This software is
// distributed under the terms of the GNU General Public License v3 (GPL
// Version 3), copied verbatim in the file "COPYING".
//
// See http://alice-o2.web.cern.ch/license for full licensing information.
//
// In applying this license CERN does not waive the privileges and immunities
// granted to it by virtue of its status as an Intergovernmental Organization
// or submit itself to any jurisdiction.

// Copyright CERN and copyright holders of ALICE O2. This software is
// distributed under the terms of the GNU General Public License v3 (GPL
// Version 3), copied verbatim in the file "COPYING".
//
// See http://alice-o2.web.cern.ch/license for full licensing information.
//
// In applying this license CERN does not waive the privileges and immunities
// granted to it by virtue of its status as an Intergovernmental Organization
// or submit itself to any jurisdiction.

/// \file SwtWord.cxx
/// \brief Implementation of the SwtWord class
///
/// \author Kostas Alexopoulos (kostas.alexopoulos@cern.ch)

#include <cstdint>
#include <cstddef>
#include <iomanip>

#include "Alf/SwtWord.h"

namespace o2
{
namespace alf
{

SwtWord::SwtWord(SwtWord::Size size) : mLow(0),
                                       mMed(0),
                                       mHigh(0),
                                       mSize(size)
{
}

SwtWord::SwtWord(uint32_t low, uint32_t med, uint16_t high, SwtWord::Size size) : mLow(low),
                                                                                  mMed(med),
                                                                                  mHigh(high),
                                                                                  mSize(size)
{
}

SwtWord::SwtWord(uint64_t swtInt, SwtWord::Size size)
{
  mLow = swtInt & 0xffffffff;
  mMed = (swtInt >> 32) & 0xffffffff;
  mHigh = 0;
  mSize = size;
}

bool SwtWord::operator==(const SwtWord& swtWord)
{
  return (mLow == swtWord.mLow) && (mMed == swtWord.mMed) && ((mHigh & 0xff) == (swtWord.mHigh & 0xff));
}

bool SwtWord::operator!=(const SwtWord& swtWord)
{
  return (mLow != swtWord.mLow) || (mMed != swtWord.mMed) || ((mHigh & 0xff) != (swtWord.mHigh & 0xff));
}

void SwtWord::setLow(uint32_t low)
{
  mLow = low;
}

void SwtWord::setMed(uint32_t med)
{
  mMed = med;
}

void SwtWord::setHigh(uint16_t high)
{
  mHigh = high & 0xfff;
}

void SwtWord::setSize(Size size)
{
  mSize = size;
}

uint32_t SwtWord::getLow() const
{
  return mLow;
}

uint32_t SwtWord::getMed() const
{
  return mMed;
}

uint16_t SwtWord::getHigh() const
{
  return mHigh & 0xfff;
}

SwtWord::Size SwtWord::getSize() const
{
  return mSize;
}

std::ostream& operator<<(std::ostream& output, const SwtWord& swtWord)
{
  output << "0x" << std::setfill('0') << std::hex << std::setw(3) << swtWord.getHigh()
         << std::setfill('0') << std::setw(8) << swtWord.getMed() << std::setfill('0') << std::setw(8) << swtWord.getLow();
  return output;
}

} // namespace alf
} // namespace o2
