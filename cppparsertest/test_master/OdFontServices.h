#ifndef _OdFontServices_h_Included_
#	define _OdFontServices_h_Included_
#	include "RxObject.h"
#	include "Gi/GiTextStyle.h"
#	include "Gi/GiExport.h"
class OdDbDatabase;
/** Description: 
    This class is the base class for classes that provide platform-dependent font services for DWGdirect. 
 
    Library: Gi 
    {group:Other_Classes} 
*/
class FIRSTDLL_EXPORT OdFontServices : public OdRxObject
{
public:
  /** Description: 
    Returns the specified OdGiTextStyle record for the specified OdDbDatabase object. 
    Arguments: 
    textStyle (O) Receives the TextStyle record. 
    pDb (I) Pointer to the *database*. 
  */
	virtual void loadStyleRec(OdGiTextStyle& textStyle, OdDbDatabase* pDb) const = 0;
  /** Description: 
    Returns the FontFilePath for the specified OdGiTextStyle and OdDbDatabase objects. 
    Arguments: 
    textStyle (I) TextStyle object. 
    pDb (I) Pointer to the *database*. 
  */
	virtual OdString getFontFilePath(OdGiTextStyle& textStyle, OdDbDatabase* pDb) const = 0;
  /** Description: 
    Returns the BigFontFilePath for the specified OdGiTextStyle and OdDbDatabase objects. 
    Arguments: 
    textStyle (I) TextStyle object. 
    pDb (I) Pointer to the *database*. 
  */
	virtual OdString getBigFontFilePath(OdGiTextStyle& textStyle, OdDbDatabase* pDb) const = 0;
  /** Description: 
    Returns the default OdFont object associated with this FontServices object. 
  */
	virtual OdFontPtr defaultFont() const = 0;
};
#	define ODDB_FONT_SERVICES	DD_T("OdDbFontServices") 
/** Description: 
    This template class is a specialization of the OdSmartPtr class for OdFontServices object pointers. 
*/
typedef OdSmartPtr<OdFontServices> OdFontServicesPtr;
#endif
