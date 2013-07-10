/*
Copyright (c) 2013 Khaled Mammou - Advanced Micro Devices, Inc.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#pragma once
#ifndef X3DGC_TRIANGLE_LIST_DECODER_H
#define X3DGC_TRIANGLE_LIST_DECODER_H

#include "x3dgc_Common.h"
#include "x3dgc_TriangleFans.h"
#include "x3dgc_BinaryStream.h"
#include "x3dgc_AdjacencyInfo.h"

namespace x3dgc
{
    
    //! 
    class TriangleListDecoder
    {
    public:    
        //! Constructor.
                                    TriangleListDecoder(void)
                                    {
                                        m_vertexCount            = 0;
                                        m_triangleCount          = 0;
                                        m_numTriangles           = 0;
                                        m_numVertices            = 0;
                                        m_triangles              = 0;
                                        m_numConqueredTriangles  = 0;
                                        m_numVisitedVertices     = 0;
                                        m_visitedVertices        = 0;
                                        m_visitedVerticesValence = 0;
                                        m_maxNumVertices         = 0;
                                        m_maxNumTriangles        = 0;
                                        m_itNumTFans             = 0;
                                        m_itDegree               = 0;
                                        m_itConfig               = 0;
                                        m_itOperation            = 0;
                                        m_itIndex                = 0;
                                    };
        //! Destructor.
                                    ~TriangleListDecoder(void){};

        X3DGCSC3DMCBinarization     GetBinarization() const { return m_binarization; }
        void                        SetBinarization(X3DGCSC3DMCBinarization binarization) { m_binarization = binarization; }
        const AdjacencyInfo &       GetVertexToTriangle() const { return m_vertexToTriangle;}
        X3DGCErrorCode              Decode(long * const triangles,
                                           const long numTriangles,
                                           const long numVertices,
                                           const BinaryStream & bstream,
                                           unsigned long & iterator)
                                    {
                                        unsigned long maxSizeV2T = bstream.ReadUInt32(iterator);
                                        Init(triangles, numTriangles, numVertices, maxSizeV2T);
                                        m_ctfans.Load(bstream, iterator);
                                        Decompress();
                                        return X3DGC_OK;
                                    }

        private:
        X3DGCErrorCode              Init(long * const triangles, 
                                         const long numTriangles,
                                         const long numVertices,
                                         const long maxSizeV2T);
        X3DGCErrorCode              Decompress();
        X3DGCErrorCode              CompueLocalConnectivityInfo(const long focusVertex);
        X3DGCErrorCode              DecompressTFAN(const long focusVertex);

        unsigned long               m_itNumTFans;
        unsigned long               m_itDegree;
        unsigned long               m_itConfig;
        unsigned long               m_itOperation;
        unsigned long               m_itIndex;
        long                        m_maxNumVertices;
        long                        m_maxNumTriangles;
        long                        m_numTriangles;
        long                        m_numVertices;
        long *                      m_triangles;
        long                        m_vertexCount;    
        long                        m_triangleCount;
        long                        m_numConqueredTriangles;
        long                        m_numVisitedVertices;
        long *                      m_visitedVertices;
        long *                      m_visitedVerticesValence;
        AdjacencyInfo               m_vertexToTriangle;
        CompressedTriangleFans      m_ctfans;
        TriangleFans                m_tfans;
        X3DGCSC3DMCBinarization     m_binarization;
    };
}
#endif // X3DGC_TRIANGLE_LIST_DECODER_H
