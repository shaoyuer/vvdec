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

/** \file     TrQuant_EMT.h
    \brief    transform and quantization class (header)
*/

#pragma once

#include "CommonDef.h"

namespace vvdec
{
#if defined(TARGET_SIMD_X86) && ENABLE_SIMD_TCOEFF_OPS
using namespace x86_simd;
#endif

struct TCoeffOps
{
  TCoeffOps();

#if defined(TARGET_SIMD_X86) && ENABLE_SIMD_TCOEFF_OPS
  void initTCoeffOpsX86();
  template<X86_VEXT vext>
  void _initTCoeffOpsX86();
#endif
  void( *cpyResiClip[7] ) ( const TCoeff*      src,        Pel*    dst, ptrdiff_t stride, unsigned width, unsigned height, const TCoeff outputMin, const TCoeff outputMax, const TCoeff round, const TCoeff shift );
  void( *fastInvCore[5] ) ( const TMatrixCoeff* it,  const TCoeff* src, TCoeff* dst, unsigned lines, unsigned reducedLines, unsigned rows );
  void( *roundClip4 )     (                                             TCoeff *dst, unsigned width, unsigned height, unsigned stride, const TCoeff outputMin, const TCoeff outputMax, const TCoeff round, const TCoeff shift );
  void( *roundClip8 )     (                                             TCoeff *dst, unsigned width, unsigned height, unsigned stride, const TCoeff outputMin, const TCoeff outputMax, const TCoeff round, const TCoeff shift );
};

extern TCoeffOps g_tCoeffOps;

////DCT-II transforms
void fastInverseDCT2_B2  (const TCoeff *src, TCoeff *dst, int shift, int line, int iSkipLine, int iSkipLine2, bool clip, const TCoeff outputMinimum, const TCoeff outputMaximum);
void fastInverseDCT2_B4  (const TCoeff *src, TCoeff *dst, int shift, int line, int iSkipLine, int iSkipLine2, bool clip, const TCoeff outputMinimum, const TCoeff outputMaximum);
void fastInverseDCT2_B8  (const TCoeff *src, TCoeff *dst, int shift, int line, int iSkipLine, int iSkipLine2, bool clip, const TCoeff outputMinimum, const TCoeff outputMaximum);
void fastInverseDCT2_B16 (const TCoeff *src, TCoeff *dst, int shift, int line, int iSkipLine, int iSkipLine2, bool clip, const TCoeff outputMinimum, const TCoeff outputMaximum);
void fastInverseDCT2_B32 (const TCoeff *src, TCoeff *dst, int shift, int line, int iSkipLine, int iSkipLine2, bool clip, const TCoeff outputMinimum, const TCoeff outputMaximum);
void fastInverseDCT2_B64 (const TCoeff *src, TCoeff *dst, int shift, int line, int iSkipLine, int iSkipLine2, bool clip, const TCoeff outputMinimum, const TCoeff outputMaximum);

//DST-VII transforms (EMT)
void fastInverseDST7_B4  (const TCoeff *src, TCoeff *dst, int shift, int line, int iSkipLine, int iSkipLine2, bool clip, const TCoeff outputMinimum, const TCoeff outputMaximum);
void fastInverseDST7_B8  (const TCoeff *src, TCoeff *dst, int shift, int line, int iSkipLine, int iSkipLine2, bool clip, const TCoeff outputMinimum, const TCoeff outputMaximum);
void fastInverseDST7_B16 (const TCoeff *src, TCoeff *dst, int shift, int line, int iSkipLine, int iSkipLine2, bool clip, const TCoeff outputMinimum, const TCoeff outputMaximum);
void fastInverseDST7_B32 (const TCoeff *src, TCoeff *dst, int shift, int line, int iSkipLine, int iSkipLine2, bool clip, const TCoeff outputMinimum, const TCoeff outputMaximum);

//DCT-VIII transforms (EMT)
void fastInverseDCT8_B4  (const TCoeff *src, TCoeff *dst, int shift, int line, int iSkipLine, int iSkipLine2, bool clip, const TCoeff outputMinimum, const TCoeff outputMaximum);
void fastInverseDCT8_B8  (const TCoeff *src, TCoeff *dst, int shift, int line, int iSkipLine, int iSkipLine2, bool clip, const TCoeff outputMinimum, const TCoeff outputMaximum);
void fastInverseDCT8_B16 (const TCoeff *src, TCoeff *dst, int shift, int line, int iSkipLine, int iSkipLine2, bool clip, const TCoeff outputMinimum, const TCoeff outputMaximum);
void fastInverseDCT8_B32 (const TCoeff *src, TCoeff *dst, int shift, int line, int iSkipLine, int iSkipLine2, bool clip, const TCoeff outputMinimum, const TCoeff outputMaximum);

}   // namespace vvdec
