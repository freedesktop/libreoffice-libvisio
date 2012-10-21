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
 * Copyright (C) 2012 Fridrich Strba <fridrich.strba@bluewin.ch>
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

#ifndef __VSDXMLPARSERBASE_H__
#define __VSDXMLPARSERBASE_H__

#include <map>
#include <stack>
#include <string>
#include <boost/optional.hpp>
#include "VSDXMLHelper.h"
#include "VSDCharacterList.h"
#include "VSDParagraphList.h"
#include "VSDShapeList.h"
#include "VSDStencils.h"

namespace libvisio
{

class VSDCollector;

class VSDXMLParserBase
{
public:
  explicit VSDXMLParserBase();
  virtual ~VSDXMLParserBase();
  virtual bool parseMain() = 0;
  virtual bool extractStencils() = 0;

protected:
  // Protected data
  VSDCollector *m_collector;
  VSDStencils m_stencils;
  VSDStencil *m_currentStencil;
  VSDShape m_shape;
  bool m_isStencilStarted;
  unsigned m_currentStencilID;

  bool m_extractStencils;
  bool m_isInStyles;
  unsigned m_currentLevel;
  unsigned m_currentShapeLevel;
  std::map<unsigned, Colour> m_colours;
  VSDFieldList m_fieldList;
  VSDShapeList m_shapeList;
  WPXBinaryData m_currentBinaryData;
  std::stack<VSDShape> m_shapeStack;
  std::stack<unsigned> m_shapeLevelStack;
  bool m_isShapeStarted;
  bool m_isPageStarted;
  VSDGeometryList *m_currentGeometryList;
  unsigned m_currentGeometryListIndex;

  // Helper functions

  int readByteData(unsigned char &value, xmlTextReaderPtr reader);
  int readByteData(boost::optional<unsigned char> &value, xmlTextReaderPtr reader);
  int readUnsignedData(boost::optional<unsigned> &value, xmlTextReaderPtr reader);
  int readLongData(boost::optional<long> &value, xmlTextReaderPtr reader);
  virtual int readLongData(long &value, xmlTextReaderPtr reader) = 0;
  int readDoubleData(boost::optional<double> &value, xmlTextReaderPtr reader);
  virtual int readDoubleData(double &value, xmlTextReaderPtr reader) = 0;
  int readBoolData(boost::optional<bool> &value, xmlTextReaderPtr reader);
  virtual int readBoolData(bool &value, xmlTextReaderPtr reader) = 0;
  virtual int readColourData(Colour &value, xmlTextReaderPtr reader) = 0;
  virtual int readExtendedColourData(Colour &value, long &idx, xmlTextReaderPtr reader) = 0;
  int readExtendedColourData(Colour &value, xmlTextReaderPtr reader);
  int readExtendedColourData(boost::optional<Colour> &value, xmlTextReaderPtr reader);
  virtual void _handleLevelChange(unsigned level);
  void _flushShape();
  virtual void copy_optional(std::map<unsigned, VSDGeometryList> &dest, const std::map<unsigned, VSDGeometryList> &source) = 0;

  virtual int getElementToken(xmlTextReaderPtr reader) = 0;
  virtual int getElementDepth(xmlTextReaderPtr reader) = 0;

  // Functions reading the DiagramML document content

  void readEllipticalArcTo(xmlTextReaderPtr reader);
  void readEllipse(xmlTextReaderPtr reader);
  void readGeometry(xmlTextReaderPtr reader);
  void readMoveTo(xmlTextReaderPtr reader);
  void readLineTo(xmlTextReaderPtr reader);
  void readArcTo(xmlTextReaderPtr reader);
  void readNURBSTo(xmlTextReaderPtr reader);
  void readPolylineTo(xmlTextReaderPtr reader);
  void readInfiniteLine(xmlTextReaderPtr reader);
  void readRelCubBezTo(xmlTextReaderPtr reader);
  void readRelEllipticalArcTo(xmlTextReaderPtr reader);
  void readRelLineTo(xmlTextReaderPtr reader);
  void readRelMoveTo(xmlTextReaderPtr reader);
  void readRelQuadBezTo(xmlTextReaderPtr reader);
  void readForeignData(xmlTextReaderPtr reader);
  virtual void getBinaryData(xmlTextReaderPtr reader) = 0;
  void readShape(xmlTextReaderPtr reader);
  void readColours(xmlTextReaderPtr reader);
  void readCharList(xmlTextReaderPtr reader);
  void readParaList(xmlTextReaderPtr reader);
  void readPage(xmlTextReaderPtr reader);
  void readText(xmlTextReaderPtr reader);
  void readCharIX(xmlTextReaderPtr reader);
  void readParaIX(xmlTextReaderPtr reader);

  void readNameList(xmlTextReaderPtr reader);
  void readName(xmlTextReaderPtr reader);

  void readFieldList(xmlTextReaderPtr reader);
  void readTextField(xmlTextReaderPtr reader);

  void readStyleSheet(xmlTextReaderPtr reader);
  void readPageSheet(xmlTextReaderPtr reader);

  void readSplineStart(xmlTextReaderPtr reader);
  void readSplineKnot(xmlTextReaderPtr reader);

  void readStencil(xmlTextReaderPtr reader);
  void readStencilShape(xmlTextReaderPtr reader);

  void readOLEList(xmlTextReaderPtr reader);
  void readOLEData(xmlTextReaderPtr reader);

private:
  VSDXMLParserBase(const VSDXMLParserBase &);
  VSDXMLParserBase &operator=(const VSDXMLParserBase &);
};

} // namespace libvisio

#endif // __VSDXMLPARSERBASE_H__
/* vim:set shiftwidth=2 softtabstop=2 expandtab: */