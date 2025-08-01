/* Copyright 2011-2016 Pierre Ossman for Cendio AB
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307,
 * USA.
 */

#ifndef __PLATFORMPIXELBUFFER_H__
#define __PLATFORMPIXELBUFFER_H__

#if !defined(WIN32) && !defined(__APPLE__)
#include <X11/Xlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <X11/extensions/XShm.h>
#endif

#include <list>
#include <mutex>

#include <core/Region.h>

#include <rfb/PixelBuffer.h>

#include "Surface.h"

class PlatformPixelBuffer: public rfb::FullFramePixelBuffer, public Surface {
public:
  PlatformPixelBuffer(int width, int height);
  ~PlatformPixelBuffer();

  void commitBufferRW(const core::Rect& r) override;

  core::Rect getDamage(void);

  using rfb::FullFramePixelBuffer::width;
  using rfb::FullFramePixelBuffer::height;

protected:
  std::mutex mutex;
  core::Region damage;

#if !defined(WIN32) && !defined(__APPLE__)
protected:
  bool setupShm(int width, int height);

protected:
  XShmSegmentInfo *shminfo;
  XImage *xim;
#endif
};

#endif
