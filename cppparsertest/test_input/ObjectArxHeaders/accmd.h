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
//  DESCRIPTION: Definitions for the AutoCAD native command definition
//               mechanism.
//

// NOTE: before adding any new command constants here,
// check with the undocumented ACRX_CMD_... constants
// defined in coresrc/command.cpp to make sure that
// there is no overlap.
//
// ARX command bits which are not exported yet, but which could
// be of use in the R13 time frame.  We should look at these in
// R14 to determine if they should be exported. BCH 10/3/95
// The value of ACRX_CMD_NOPAPERSPACE was changed from 0x10 to
// 0x40 by submission S049-JH2 because it conflicted with the
// value of ACRX_CMD_NOMULTIPLE.  JH 1/3/97.
//

#ifndef   _ACCMD_H
#define   _ACCMD_H

#include "adesk.h"
#include "AdAChar.h"
#include "accmd-defs.h"
#include "rxresource.h"

#define ACRX_COMMAND_DOCK  	ACRX_T("ACAD_REGISTERED_COMMANDS")

typedef void (*AcRxFunctionPtr) ();

#pragma pack (push, 8)
class AcEdCommand;

struct AcEdCommandStruc {
    AcRxFunctionPtr fcnAddr;
    long            flags;
    void	        *app;

	//This member should obviate the need to the ones above
	//since they are already contained in AcEdCommand.
	AcEdCommand		*cmd;
};
#pragma pack (pop)

#if defined(__cplusplus)

#include "dbmain.h"
#include "rxobject.h"

class AcRxDictionary;
class AcEdUIContext;
class AcEdCommandReactor;

#pragma pack (push, 8)

class AcEdCommand: public AcRxObject 
{ 
public:
    ACRX_DECLARE_MEMBERS(AcEdCommand);

    virtual void            commandUndef(bool undefIt) = 0;
    virtual Adesk::Int32    commandFlags() const = 0;
    virtual AcRxFunctionPtr functionAddr() const = 0;
    virtual void            functionAddr(AcRxFunctionPtr fhdl) = 0;
    virtual void            *commandApp() const = 0;
    virtual AcEdUIContext   *UIContext() const = 0;
    virtual int             functionCode() const = 0;
    virtual void            functionCode(int fcode) = 0;

    virtual const ACHAR *   globalName() const = 0;
    virtual const ACHAR *   localName() const = 0;

    virtual const AcRxResourceInstance& resourceInstance() const = 0;

    void addReactor(AcEdCommandReactor* pReactor);
    void removeReactor(AcEdCommandReactor* pReactor);

    Adesk::UInt8 defaultCommandVersion() const;
};


enum AcEdCommandStatusFlags
{
    kCmdStatusNone   = 0x00000,
    kCmdStatusCancel = 0x00001,
    kCmdStatusFailed = 0x00002,
};

AcEdCommandStatusFlags& operator|=(AcEdCommandStatusFlags& f, int i); // operator to allow usage of |= and &=
AcEdCommandStatusFlags& operator&=(AcEdCommandStatusFlags& f, int i);

class AcEdImpCommandEventArgs;
class AcEdCommandEventArgs
{
public:
    const ACHAR* groupName() const;
    AcEdCommandStatusFlags status() const;
    void setStatus(AcEdCommandStatusFlags flags);

protected:
    friend class AcEdImpCommandEventArgs;
    AcEdImpCommandEventArgs* m_pImp;

    AcEdCommandEventArgs(AcEdImpCommandEventArgs* pImp);
    AcEdCommandEventArgs(const AcEdCommandEventArgs& other);
    AcEdCommandEventArgs& operator=(const AcEdCommandEventArgs& other);
};


// AcEdCommandReactor - receives notifications on command start/end for 
// specific commands. Attach to desired AcEdCommand instances.
class AcEdCommandReactor : public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcEdCommandReactor);

    virtual void commandWillStart(AcEdCommand* pCmd, AcEdCommandEventArgs* data);
    virtual void     commandEnded(AcEdCommand* pCmd, AcEdCommandEventArgs* data);
    virtual void          goodbye(AcEdCommand* pCmd, AcEdCommandEventArgs* data); //sent just before cmd is to be deleted
};

// AcEdCommandReactor - notified when commands are added/removed 
// and also start/end.
// NOTE: If you need to monitor start/end of a specific command, recommend 
// using AcEdCommandReactor instead. This allows you to attach directly to 
// the desired command.
// 
class AcEdCommandStackReactor: public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcEdCommandStackReactor);

    virtual void commandAdded(    AcEdCommand* pCmd, AcEdCommandEventArgs* data);
    virtual void commandRemoved(  AcEdCommand* pCmd, AcEdCommandEventArgs* data);
    virtual void commandWillStart(AcEdCommand* pCmd, AcEdCommandEventArgs* data);
    virtual void commandEnded(    AcEdCommand* pCmd, AcEdCommandEventArgs* data);
};


class AcEdCommandIterator: public AcRxObject 
{ 
public:
    ACRX_DECLARE_MEMBERS(AcEdCommandIterator);

    virtual bool               done() const = 0;
    virtual bool               next() = 0;
    virtual const AcEdCommand* command() const = 0;
    virtual const ACHAR *      commandGroup() const = 0;
};




#define acedRegCmds \
AcEdCommandStack::cast(acrxSysRegistry()->at(ACRX_COMMAND_DOCK))

class AcEdCommandStack: public AcRxObject 
{ 
public:
    ACRX_DECLARE_MEMBERS(AcEdCommandStack);

    virtual bool              atPut(const ACHAR * cmdGroupName,
                                    AcRxDictionary*& cmdsGlobal,
                                    AcRxDictionary*& cmdsLocal) = 0;

    virtual Acad::ErrorStatus addCommand(const ACHAR * cmdGroupName,
                                         const ACHAR * cmdGlobalName,
                                         const ACHAR * cmdLocalName,
                                         Adesk::Int32 commandFlags,
                                         AcRxFunctionPtr FunctionAddr,
                                         AcEdUIContext *UIContext=NULL,
                                         int fcode=-1,
                                         const AcRxResourceInstance& resourceInstance = AcRxResourceInstance::empty(),
                                         AcEdCommand** cmdPtrRet=NULL) = 0;

    virtual AcEdCommandIterator* iterator() = 0;

    virtual AcEdCommand* lookupGlobalCmd(const ACHAR * cmdName) = 0;
    virtual AcEdCommand* lookupLocalCmd(const ACHAR * cmdName) = 0;
    virtual AcEdCommand* lookupCmd(const ACHAR * cmdName,
                                   bool globalFlag) = 0;
    virtual AcEdCommand* lookupCmd(const ACHAR * cmdName,
                                   bool globalFlag,
                                   bool allGroupsFlag) = 0;
    virtual AcEdCommand* lookupCmd(const ACHAR * cmdName,
                                   bool globalFlag,
                                   bool allGroupsFlag,
                                   bool skipUndefed) = 0;
    virtual AcEdCommand* lookupCmd2(const ACHAR * cmdName,
                                   bool globalFlag,
                                   bool allGroupsFlag,
                                   int skipFlags,
                                   bool match = false) = 0;

    virtual Acad::ErrorStatus popGroupToTop(const ACHAR * cmdGroupName) = 0;

    virtual Acad::ErrorStatus removeCmd(const ACHAR * cmdGroupName,
                                        const ACHAR * cmdGlobalName) = 0;

    virtual Acad::ErrorStatus removeGroup(const ACHAR * groupName) = 0;

    void addReactor(AcEdCommandStackReactor* pReactor);
    void removeReactor(AcEdCommandStackReactor* pReactor);
};



#pragma pack (pop)
#endif // cplusplus
#endif
