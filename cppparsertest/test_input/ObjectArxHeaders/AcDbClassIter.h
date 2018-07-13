//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////


#pragma once
#include "dbmain.h"

#pragma pack (push, 4)

class ADESK_NO_VTABLE AcDbClassIterator
{
  public:
    //
    // Factory methods.  Allocation and deallocation.
    // ----------------
    //
    // Create and return a new, unattached iterator.
    ACDBCORE2D_PORT static AcDbClassIterator * newIterator();

    // Destroy an iterator
    // pIter : input pointer to the iterator
    ACDBCORE2D_PORT static void deleteIterator(AcDbClassIterator *pIter);


    //
    // Iteration methods
    // -----------------
    //
    // Flag values passed to start() method.  Specify type of iteration.
    enum { kAllClasses = 0x01,        // returns all classes in the db
           kCustomClasses   = 0x02,   // returns only custom classes
           kProxyClasses    = 0x04 }; // returns only proxy classes

    // Attach this iterator to a database and begin iteration.
    // pDb : input pointer to a drawing database
    // nFlags : input flags specifying how to iterate
    virtual Acad::ErrorStatus start(AcDbDatabase *pDb, int nFlags) = 0;

    // Advance the iterator to the next class
    // Returns true if there is a next class, false if iteration is done
    virtual bool next() = 0;

    // Returns false if there is a next class, true if iteration is done
    virtual bool done() const = 0;

    // Resets this iterator.  Detaches it from its current database.
    virtual void detach() = 0;


    //
    // Querying methods
    // ----------------
    //
    // Return name of current class.
    virtual const ACHAR *name() const = 0;

    // Return name of current class's application (enabler).
    virtual const ACHAR *appName() const = 0;

    // Return dxf name of current class
    virtual const ACHAR *dxfName() const = 0;

    // Return number of instances of current class.  This may be
    // approximate, if not all objects have been loaded into memory
    // or if objects have been erased.
    virtual Adesk::UInt32 numInstances() const = 0;

    // Return true if the current class is a proxy (i.e. its
    // enabler is not loaded), false if enabler is loaded.
    virtual bool isProxy() const = 0;

    // Return true if the current class is an entity (i.e. is directly
    // or indirectly derived from AcDbEntity), false if not.
    virtual bool isEntity() const = 0;


  protected:
    // The ctor and dtor are only here to prevent attempts at
    // direct instantiation or deletion of this class.  Please use
    // the factory methods to create and destroy iterator objects.
    AcDbClassIterator();
    virtual ~AcDbClassIterator();
};

#pragma pack (pop)

