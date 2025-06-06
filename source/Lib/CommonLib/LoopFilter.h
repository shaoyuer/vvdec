/* -----------------------------------------------------------------------------
The copyright in this software is being made available under the Clear BSD
License, included below. No patent rights, trademark rights and/or 
other Intellectual Property Rights other than the copyrights concerning 
the Software are granted under this license.

The Clear BSD License

Copyright (c) 2018-2024, Fraunhofer-Gesellschaft zur Förderung der angewandten Forschung e.V. & The VVdeC Authors.
All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted (subject to the limitations in the disclaimer below) provided that
the following conditions are met:

     * Redistributions of source code must retain the above copyright notice,
     this list of conditions and the following disclaimer.

     * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in the
     documentation and/or other materials provided with the distribution.

     * Neither the name of the copyright holder nor the names of its
     contributors may be used to endorse or promote products derived from this
     software without specific prior written permission.

NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY
THIS LICENSE. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.


------------------------------------------------------------------------------------------- */

/** \file     LoopFilter.h
    \brief    deblocking filter (header)
*/

#pragma once

#include "CommonDef.h"
#include "Unit.h"

//! \ingroup CommonLib
//! \{

#define DEBLOCK_SMALLEST_BLOCK  8

namespace vvdec
{
#if defined(TARGET_SIMD_X86)  && ENABLE_SIMD_DBLF
using namespace x86_simd;
#endif
  
// ====================================================================================================================
// Class definition
// ====================================================================================================================

/// deblocking filter class
class LoopFilter
{
private:
  /// CU-level deblocking function
  template<DeblockEdgeDir edgeDir>
  void xDeblockCtuArea            ( CodingStructure& cs, const UnitArea& area, const ChannelType chType ) const;

  // set / get functions
  LFCUParam xGetLoopfilterParam   ( const CodingUnit& cu ) const;

  void calcFilterStrengths        ( const CodingUnit& cu ) const;

  // filtering functions
  template<DeblockEdgeDir edgeDir>
  void xGetBoundaryStrengthSingle ( LoopFilterParam& lfp, const CodingUnit& cu, const Position &localPos, const CodingUnit &cuP, CtuData& ctuData, bool pqSameCtu, bool useSimd ) const;
  template<DeblockEdgeDir edgeDir>
  void xSetEdgeFilterInsidePu     ( const CodingUnit &cu, const Area &area, const bool bValue, CtuData& ctuData ) const;

  template<DeblockEdgeDir edgeDir>
  void xSetMaxFilterLengthPQFromTransformSizes( const CodingUnit& cu, const TransformUnit& currTU, const bool bValue, bool deriveBdStrngt, CtuData& ctuData, bool pqSameCtu ) const;
  template<DeblockEdgeDir edgeDir>
  void xSetMaxFilterLengthPQForCodingSubBlocks( const CodingUnit& cu, CtuData& ctuData ) const;

  template<DeblockEdgeDir edgeDir>
  void xEdgeFilterLuma            ( CodingStructure& cs, const Position& pos, const LoopFilterParam& lfp, const Slice& slice ) const;
  template<DeblockEdgeDir edgeDir>
  void xEdgeFilterChroma          ( CodingStructure& cs, const Position& pos, const LoopFilterParam& lfp, const Slice& slice ) const;

#if LUMA_ADAPTIVE_DEBLOCKING_FILTER_QP_OFFSET
  void deriveLADFShift            ( const Pel* src, const ptrdiff_t stride, int& shift, const DeblockEdgeDir edgeDir, const SPS& sps ) const;

#endif
  static const uint16_t sm_tcTable  [MAX_QP + 3];
  static const uint8_t  sm_betaTable[MAX_QP + 1];

  void( *xPelFilterLuma  )( Pel* piSrc, const ptrdiff_t step, const ptrdiff_t offset, const int tc, const bool sw, const int iThrCut, const bool bFilterSecondP, const bool bFilterSecondQ, const ClpRng& clpRng );
  void( *xFilteringPandQ )( Pel* src, ptrdiff_t step, const ptrdiff_t offset, int numberPSide, int numberQSide, int tc );

#if defined(TARGET_SIMD_X86)  && ENABLE_SIMD_DBLF
  void initLoopFilterX86();
  template <X86_VEXT vext>
  void _initLoopFilterX86();
#endif
  inline void xDeriveEdgefilterParam( const Position pos, const int numVerVirBndry, const int numHorVirBndry, const int verVirBndryPos[], const int horVirBndryPos[], bool& verEdgeFilter, bool& horEdgeFilter ) const;

public:

  LoopFilter();
  ~LoopFilter();

  /// picture-level deblocking filter
  void loopFilterCTU              ( CodingStructure& cs, const ChannelType chType, const int ctuCol, const int ctuLine, const int offset = 0, DeblockEdgeDir edgeDir = NUM_EDGE_DIR ) const;
  void calcFilterStrengthsCTU     ( CodingStructure& cs, const int ctuRsAddr );
};

}
