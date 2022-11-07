/***************************************************************************
 *   Copyright (C) 2011 by Dominik Seichter                                *
 *   domseichter@web.de                                                    *
 *                      by Petr Pytelka                                    *
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

#ifndef _PDF_SIGNATURE_FIELD_H_
#define _PDF_SIGNATURE_FIELD_H_

#include "PdfAnnotation.h"
#include "PdfField.h"
#include "podofo/base/PdfDate.h"

namespace PoDoFo {


/** Signature field
 */
class PODOFO_DOC_API PdfSignatureField :public PdfField
{
protected:
    PdfObject*     m_pSignatureObj;

    void Init();
public:

    typedef enum {
        ePdfCertPermission_NoPerms = 1,
        ePdfCertPermission_FormFill = 2,
        ePdfCertPermission_Annotations = 3,
    } EPdfCertPermission;

    /** Create a new PdfSignatureField
     */
    PdfSignatureField( PdfPage* pPage, const PdfRect & rRect, PdfDocument* pDoc );

    /** Create a new PdfSignatureField
     *  \param bInit creates a signature field with/without a /V key
     */
    PdfSignatureField( PdfAnnotation* pWidget, PdfAcroForm* pParent, PdfDocument* pDoc, bool bInit = true);

    /** Creates a PdfSignatureField from an existing PdfAnnotation, which should
     *  be an annotation with a field type Sig.
     *	\param pWidget the annotation to create from
     */
    PdfSignatureField( PdfAnnotation* pWidget );

    /** Set an appearance stream for this signature field
     *  to specify its visual appearance
     *  \param pObject an XObject
     *  \param eAppearance an appearance type to set
     *  \param state the state for which set it the pObject; states depend on the annotation type
     */
    void SetAppearanceStream(PdfXObject *pObject, EPdfAnnotationAppearance eAppearance = ePdfAnnotationAppearance_Normal, const PdfName & state = "" );

    /** Create space for signature
     *
     * \param signatureData String used to locate reserved space for signature.
     *   This string will be replaiced with signature.
     *
     * Structure of the PDF file - before signing:
     * <</ByteRange[ 0 1234567890 1234567890 1234567890]/Contents<signatureData>
     * Have to be replaiced with the following structure:
     * <</ByteRange[ 0 count pos count]/Contents<real signature ...0-padding>
     */
    void SetSignature(const PdfData &signatureData);

    /** Set reason of the signature
     *
     *  \param rsText the reason of signature
     */
    void SetSignatureReason(const PdfString & rsText);

    /** Set location of the signature
     *
     *  \param rsText the location of signature
     */
    void SetSignatureLocation(const PdfString & rsText);

    /** Set the creator of the signature
     *
     *  \param creator the creator of the signature
     */
    void SetSignatureCreator( const PdfName & creator );

    /** Date of signature
     */
    void SetSignatureDate(const PdfDate &sigDate);

    /** Add certification dictionaries and references to document catalog.
     *
     *  \param pDocumentCatalog the catalog of current document
     *  \param perm document modification permission
     */
    void AddCertificationReference(PdfObject *pDocumentCatalog, EPdfCertPermission perm = ePdfCertPermission_NoPerms);

    /** Returns signature object for this signature field.
     *  It can be NULL, when the signature field was created
     *  from an existing annotation and it didn't have set it.
     *
     *  \returns associated signature object, or NULL
     */
    PdfObject* GetSignatureObject( void ) const;

    /** Ensures that the signature field has set a signature object.
     *  The function does nothing, if the signature object is already
     *  set. This is useful for cases when the signature field had been
     *  created from an existing annotation, which didn't have it set.
     */
    void EnsureSignatureObject( void );
};

}

#endif
