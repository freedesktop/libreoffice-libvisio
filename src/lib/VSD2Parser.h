/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* libvisio
 * Version: MPL 1.1 / GPLv2+ / LGPLv2+
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License or as specified alternatively below. You may obtain a copy of
 * the License at http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * Major Contributor(s):
 * Copyright (C) 2011 Fridrich Strba <fridrich.strba@bluewin.ch>
 * Copyright (C) 2011 Eilidh McAdam <tibbylickle@gmail.com>
 *
 *
 * All Rights Reserved.
 *
 * For minor contributions see the git repository.
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPLv2+"), or
 * the GNU Lesser General Public License Version 2 or later (the "LGPLv2+"),
 * in which case the provisions of the GPLv2+ or the LGPLv2+ are applicable
 * instead of those above.
 */

#ifndef __VSD2PARSER_H__
#define __VSD2PARSER_H__

#include <stdio.h>
#include <iostream>
#include <libwpd/libwpd.h>
#include <libwpg/libwpg.h>
#include "VSD5Parser.h"
#include "VSDInternalStream.h"

namespace libvisio
{

class VSD2Parser : public VSD5Parser
{
public:
  explicit VSD2Parser(WPXInputStream *input, libwpg::WPGPaintInterface *painter);
  ~VSD2Parser();

protected:
  virtual bool getChunkHeader(WPXInputStream *input);
  // virtual void handleChunks(WPXInputStream * /* input */, unsigned /* level */) {}
  virtual void handleBlob(WPXInputStream *input, unsigned level);

private:
  VSD2Parser();
  VSD2Parser(const VSDParser &);
  VSD2Parser &operator=(const VSDParser &);
};

} // namespace libvisio

#endif // __VSD2PARSER_H__
/* vim:set shiftwidth=2 softtabstop=2 expandtab: */