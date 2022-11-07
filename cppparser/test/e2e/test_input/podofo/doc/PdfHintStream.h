/***************************************************************************
 *   Copyright (C) 2006 by Dominik Seichter                                *
 *   domseichter@web.de                                                    *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Library General Public License as       *
 *   published by the Free Software Foundation; either version 2 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with this program; if not, write to the                 *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 *                                                                         *
 *   In addition, as a special exception, the copyright holders give       *
 *   permission to link the code of portions of this program with the      *
 *   OpenSSL library under certain conditions as described in each         *
 *   individual source file, and distribute linked combinations            *
 *   including the two.                                                    *
 *   You must obey the GNU General Public License in all respects          *
 *   for all of the code used other than OpenSSL.  If you modify           *
 *   file(s) with this exception, you may extend this exception to your    *
 *   version of the file(s), but you are not obligated to do so.  If you   *
 *   do not wish to do so, delete this exception statement from your       *
 *   version.  If you delete this exception statement from all source      *
 *   files in the program, then also delete it here.                       *
 ***************************************************************************/

#ifndef _PDF_HINT_STREAM_H_
#define _PDF_HINT_STREAM_H_

#include "podofo/base/PdfDefines.h"
#include "podofo/base/PdfWriter.h"
#include "PdfElement.h"

namespace PoDoFo {

class PdfPagesTree;

namespace NonPublic {

// PdfHintStream is not part of the public API and is NOT exported as part of
// the DLL/shared library interface. Do not rely on it.

class PdfHintStream : public PdfElement {
 public:
    PdfHintStream( PdfVecObjects* pParent, PdfPagesTree* pPagesTree );
    ~PdfHintStream();

    /** Create the hint stream 
     *  \param pXRef pointer to a valid XREF table structure
     */
    //void Create( TVecXRefTable* pXRef );

    /** Write a pdf_uint16 to the stream in big endian format.
     *  \param val the value to write to the stream
     */
    void WriteUInt16( pdf_uint16 val );

    /** Write a pdf_uint32 to the stream in big endian format.
     *  \param val the value to write to the stream
     */
    void WriteUInt32( pdf_uint32 );

 private:
    //void CreatePageHintTable( TVecXRefTable* pXRef );
    void CreateSharedObjectHintTable();
 
 private:
    PdfPagesTree* m_pPagesTree;
};

}; // end namespace NonPublic

}; // end namespace PoDoFo

#endif /* _PDF_HINT_STREAM_H_ */
