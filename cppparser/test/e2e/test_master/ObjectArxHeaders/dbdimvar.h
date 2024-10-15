#ifndef DBDIMVAR_H
#  define DBDIMVAR_H
//
//
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
//
// DESCRIPTION: 
// The api for dimensioning variables shared by 
//  AcDbDatabase, 
//  AcDbDimstyleTableRecord, and 
//  AcDbDimension
    
    //  -------------------------  Dimension Style get methods
    //
virtual int dimadec() const;
virtual bool dimalt() const;
virtual int dimaltd() const;
virtual double dimaltf() const;
virtual double dimaltrnd() const;
virtual int dimalttd() const;
virtual int dimalttz() const;
virtual int dimaltu() const;
virtual int dimaltz() const;
virtual const ACHAR* dimapost() const;
virtual int dimarcsym() const;
virtual double dimasz() const;
virtual int dimatfit() const;
virtual int dimaunit() const;
virtual int dimazin() const;
virtual AcDbObjectId dimblk() const;
virtual AcDbObjectId dimblk1() const;
virtual AcDbObjectId dimblk2() const;
virtual double dimcen() const;
virtual AcCmColor dimclrd() const;
virtual AcCmColor dimclre() const;
virtual AcCmColor dimclrt() const;
virtual int dimdec() const;
virtual double dimdle() const;
virtual double dimdli() const;
virtual ACHAR dimdsep() const;
virtual double dimexe() const;
virtual double dimexo() const;
virtual int dimfrac() const;
virtual double dimgap() const;
virtual double dimjogang() const;
virtual int dimjust() const;
virtual AcDbObjectId dimldrblk() const;
virtual double dimlfac() const;
virtual bool dimlim() const;
virtual AcDbObjectId dimltex1() const;
virtual AcDbObjectId dimltex2() const;
virtual AcDbObjectId dimltype() const;
virtual int dimlunit() const;
virtual AcDb::LineWeight dimlwd() const;
virtual AcDb::LineWeight dimlwe() const;
virtual const ACHAR* dimpost() const;
virtual double dimrnd() const;
virtual bool dimsah() const;
virtual double dimscale() const;
virtual bool dimsd1() const;
virtual bool dimsd2() const;
virtual bool dimse1() const;
virtual bool dimse2() const;
virtual bool dimsoxd() const;
virtual int dimtad() const;
virtual int dimtdec() const;
virtual double dimtfac() const;
virtual int dimtfill() const;
virtual AcCmColor dimtfillclr() const;
virtual bool dimtih() const;
virtual bool dimtix() const;
virtual double dimtm() const;
virtual int dimtmove() const;
virtual bool dimtofl() const;
virtual bool dimtoh() const;
virtual bool dimtol() const;
virtual int dimtolj() const;
virtual double dimtp() const;
virtual double dimtsz() const;
virtual double dimtvp() const;
virtual AcDbObjectId dimtxsty() const;
virtual double dimtxt() const;
virtual int dimtzin() const;
virtual bool dimupt() const;
virtual int dimzin() const;
virtual bool dimfxlenOn() const;
virtual double dimfxlen() const;
virtual bool dimtxtdirection() const;
virtual double dimmzf() const;
virtual const ACHAR* dimmzs() const;
virtual double dimaltmzf() const;
virtual const ACHAR* dimaltmzs() const;
    //  -------------------------  Dimension Style set methods
    //
virtual Acad::ErrorStatus setDimadec(int v);
virtual Acad::ErrorStatus setDimalt(bool v);
virtual Acad::ErrorStatus setDimaltd(int v);
virtual Acad::ErrorStatus setDimaltf(double v);
virtual Acad::ErrorStatus setDimaltmzf(double v);
virtual Acad::ErrorStatus setDimaltmzs(const ACHAR* v);
virtual Acad::ErrorStatus setDimaltrnd(double v);
virtual Acad::ErrorStatus setDimalttd(int v);
virtual Acad::ErrorStatus setDimalttz(int v);
virtual Acad::ErrorStatus setDimaltu(int v);
virtual Acad::ErrorStatus setDimaltz(int v);
virtual Acad::ErrorStatus setDimapost(const ACHAR* v);
virtual Acad::ErrorStatus setDimarcsym(int v);
virtual Acad::ErrorStatus setDimasz(double v);
virtual Acad::ErrorStatus setDimatfit(int v);
virtual Acad::ErrorStatus setDimaunit(int v);
virtual Acad::ErrorStatus setDimazin(int v);
virtual Acad::ErrorStatus setDimblk(AcDbObjectId v);
virtual Acad::ErrorStatus setDimblk1(AcDbObjectId v);
virtual Acad::ErrorStatus setDimblk2(AcDbObjectId v);
virtual Acad::ErrorStatus setDimcen(double v);
virtual Acad::ErrorStatus setDimclrd(const AcCmColor& v);
virtual Acad::ErrorStatus setDimclre(const AcCmColor& v);
virtual Acad::ErrorStatus setDimclrt(const AcCmColor& v);
virtual Acad::ErrorStatus setDimdec(int v);
virtual Acad::ErrorStatus setDimdle(double v);
virtual Acad::ErrorStatus setDimdli(double v);
virtual Acad::ErrorStatus setDimdsep(ACHAR v);
virtual Acad::ErrorStatus setDimexe(double v);
virtual Acad::ErrorStatus setDimexo(double v);
virtual Acad::ErrorStatus setDimfrac(int v);
virtual Acad::ErrorStatus setDimgap(double v);
virtual Acad::ErrorStatus setDimjogang(double v);
virtual Acad::ErrorStatus setDimjust(int v);
virtual Acad::ErrorStatus setDimldrblk(AcDbObjectId v);
virtual Acad::ErrorStatus setDimlfac(double v);
virtual Acad::ErrorStatus setDimlim(bool v);
virtual Acad::ErrorStatus setDimltex1(AcDbObjectId v);
virtual Acad::ErrorStatus setDimltex2(AcDbObjectId v);
virtual Acad::ErrorStatus setDimltype(AcDbObjectId v);
virtual Acad::ErrorStatus setDimlunit(int v);
virtual Acad::ErrorStatus setDimlwd(AcDb::LineWeight v);
virtual Acad::ErrorStatus setDimlwe(AcDb::LineWeight v);
virtual Acad::ErrorStatus setDimmzf(double v);
virtual Acad::ErrorStatus setDimmzs(const ACHAR* v);
virtual Acad::ErrorStatus setDimpost(const ACHAR* v);
virtual Acad::ErrorStatus setDimrnd(double v);
virtual Acad::ErrorStatus setDimsah(bool v);
virtual Acad::ErrorStatus setDimscale(double v);
virtual Acad::ErrorStatus setDimsd1(bool v);
virtual Acad::ErrorStatus setDimsd2(bool v);
virtual Acad::ErrorStatus setDimse1(bool v);
virtual Acad::ErrorStatus setDimse2(bool v);
virtual Acad::ErrorStatus setDimsoxd(bool v);
virtual Acad::ErrorStatus setDimtad(int v);
virtual Acad::ErrorStatus setDimtdec(int v);
virtual Acad::ErrorStatus setDimtfac(double v);
virtual Acad::ErrorStatus setDimtfill(int v);
virtual Acad::ErrorStatus setDimtfillclr(const AcCmColor& v);
virtual Acad::ErrorStatus setDimtih(bool v);
virtual Acad::ErrorStatus setDimtix(bool v);
virtual Acad::ErrorStatus setDimtm(double v);
virtual Acad::ErrorStatus setDimtmove(int v);
virtual Acad::ErrorStatus setDimtofl(bool v);
virtual Acad::ErrorStatus setDimtoh(bool v);
virtual Acad::ErrorStatus setDimtol(bool v);
virtual Acad::ErrorStatus setDimtolj(int v);
virtual Acad::ErrorStatus setDimtp(double v);
virtual Acad::ErrorStatus setDimtsz(double v);
virtual Acad::ErrorStatus setDimtvp(double v);
virtual Acad::ErrorStatus setDimtxsty(AcDbObjectId v);
virtual Acad::ErrorStatus setDimtxt(double v);
virtual Acad::ErrorStatus setDimtxtdirection(bool v);
virtual Acad::ErrorStatus setDimtzin(int v);
virtual Acad::ErrorStatus setDimupt(bool v);
virtual Acad::ErrorStatus setDimzin(int v);
virtual Acad::ErrorStatus setDimblk(const ACHAR* v);
virtual Acad::ErrorStatus setDimblk1(const ACHAR* v);
virtual Acad::ErrorStatus setDimblk2(const ACHAR* v);
virtual Acad::ErrorStatus setDimldrblk(const ACHAR* v);
virtual Acad::ErrorStatus setDimfxlenOn(bool v);
virtual Acad::ErrorStatus setDimfxlen(double v);
#endif
