//////////////////////////////////////////////////////////////////////////////
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
// Name:    AcApDocWindow
// Remarks: Defines the interface of AcApDocWindow and AcApDocWindowManager.
//
//          AcApDocWindow is an abstraction of MDI child window inside AutoCAD,
//          including both DWG and non-DWG windows. It should only be used by features
//          that uses or interacts with non-DWG window in AutoCAD. 
//
//          The API exposed in this file serves two purpose:
//          1. Allow client code to iterate, monitor and performs basic actions
//          on all child windows in AutoCAD.
//
//          2. Provide the capability for client code to define their custom 
//          non-DWG window and show in AutoCAD. 
//
//////////////////////////////////////////////////////////////////////////////

#pragma once

#include "adesk.h"
#include "acdocman.h"

#include "AcApWindow.h"

class AcApDocWindowImp;

/// <summary>Defines reactor interface for <code>AcApDocWindow</code> class. </summary>
class AcApDocWindowReactor
{
public:
    /// <summary>Fired when the document window finished loading its content. Typically, the document
    /// instance would be available for use upon this event. </summary>
    /// <remarks>This event is fired one time only. </remarks>
    ACAD_PORT virtual void documentWindowLoaded();

    /// <summary>Fired when the document window needs updating. </summary>
    /// <remarks>This event is fired one time only. </remarks>
    ACAD_PORT virtual void documentWindowUpdated();
};

/// <summary>Represents a child window inside AutoCAD main frame, either a DWG window or 
/// a non-DWG window.</summary>
class AcApDocWindow : public AcApWindow
{
// Properties
public:
    /// <summary>Gets the document associated with the window. </summary>
    /// <returns>Returns the document instance if available. Returns nullptr if documentWindowLoaded event
    /// has not been fired or the window does not use any document. </returns>
    /// <remarks>For DWG window, the document instance is of type AcApDocument. For other windows, the 
    /// document could be of any type derived from <code>AcRxObject</code>.</remarks>
    ACAD_PORT AcRxObject* document();

    /// <summary>Gets the title of the window. </summary>
    ACAD_PORT const ACHAR* title() const;

    /// <summary>Sets the title of the window. </summary>
    /// <param name="title">New title of the window. </param>
    /// <remarks>This only has effect before this window is added to document window manager.</remarks>
    ACAD_PORT void setTitle(const ACHAR* title);

    /// <summary>Gets the value indicating whether the document window can be closed. </summary>
    ACAD_PORT bool canClose() const;

    /// <summary>Sets the CanClose of the window. </summary>
    /// <param name="bCanClose">New CanClose of the window. </param>
    /// <remarks>This only change private value before this window is added to document window manager.
    /// MFC window close button and private value change after this window is added to document window manager.</remarks>
    ACAD_PORT void setCanClose(bool bCanClose);

// Operations
public:
    /// <summary>Closes the window. </summary>
    ACAD_PORT void close();

    /// <summary>Activates the window. </summary>
    ACAD_PORT void activate();

    /// <summary>Enables/Disables the window </summary>
    /// <param name="bEnable">Specify true to enable window and false to disable it.</param>
    ACAD_PORT void enable(bool bEnable);

    /// <summary>Adds a reactor instance of type <code>AcApDocWindowReactor</code> to handle events from
    /// this window. </summary>
    /// <param name="reactor">The reactor instance to be added.</param>
    ACAD_PORT void addReactor(AcApDocWindowReactor* reactor);

    /// <summary>Removes a reactor instance of type <code>AcApDocWindowReactor</code> that has been added previously. </summary>
    /// <param name="reactor">The reactor instance to be removed.</param>
    ACAD_PORT void removeReactor(AcApDocWindowReactor* reactor);

protected:
    /// <summary>Sets the document instance associated with the window. </summary>
    /// <param name="document">The document instance.</param>
    /// <remarks>Derived type should initialize the document instance and call this function inside
    /// overloaded version of <code>onLoad()</code>.</remarks>
    ACAD_PORT virtual void setDocument(AcRxObject* document);

// Events
protected:
    /// <summary>Called when the document window is being created.</summary>
    /// <param name="hWnd">The native handle of the newly created window.</param>
    /// <remarks>Derived types should override this function to initialize the content
    /// of the document window.</remarks>
    ACAD_PORT virtual void onCreate(HWND hWnd);

    /// <summary>Called when the document window is loading its content. </summary>
    /// <remarks>Derived types should override this function if it needs to load a document, or any other content. 
    /// If the derived type does not override this function, the documentWindowLoaded() event is fired immediately after
    /// the documentWindowCreated() event on AcApDocWindowManager.</remarks>
    ACAD_PORT virtual void onLoad();

    /// <summary>Called when the document window is activated.</summary>
    ACAD_PORT virtual void onActivate();

    /// <summary>Called when the document window is destroyed.</summary>
    ACAD_PORT virtual void onDestroy();

    /// <summary>Called when the document window is updated.</summary>
    ACAD_PORT virtual void onUpdate();

public:
    /// <summary>Initializes an instance of AcApDocWindow.</summary>
    /// <remarks>Non-DWG windows must be added to AcApDocWnidowManager by calling addDocumentWindow()</remarks>
    ACAD_PORT AcApDocWindow();

    /// <summary>Initializes an instance of AcApDocWindow.</summary>
    ACAD_PORT virtual ~AcApDocWindow();

// IAdHostWindow memebers
public:
    /// <summary>Obtains the native window handle.</summary>
    ACAD_PORT virtual HWND windowHandle() ADESK_OVERRIDE;

private:
    AcApDocWindow(const AcApDocWindow&);
    AcApDocWindow& operator=(const AcApDocWindow&);

    friend class AcApDocWindowImp;
};

/// <summary>Derived type from AcApDocWindow which represents a DWG child window.</summary>
class AcApDwgDocWindow : public AcApDocWindow
{
public:
    /// <summary>Gets the <code>AcApDocument</code> document instance associated with this DWG window.</summary>
    ACAD_PORT AcApDocument* document();

private:
    AcApDwgDocWindow();

    friend class AcApDocWindowImp;
};

class AcApDocWindowManagerImp;
class AcApDocWindowIteratorImp;

/// <summary>Iterator of document windows.</summary>
class AcApDocWindowIterator
{
public:
    /// <summary>Gets a value indicating whether the iterator has reached its end.</summary>
    ACAD_PORT bool done() const;

    /// <summary>Steps to the next item.</summary>
    ACAD_PORT void step();

    /// <summary>Gets the document window instance of the current item.</summary>
    ACAD_PORT AcApDocWindow* current();

private:
    AcApDocWindowIterator();

public:
    ACAD_PORT ~AcApDocWindowIterator();

private:
    AcApDocWindowIteratorImp* m_pImp;

    friend class AcApDocWindowManagerImp;
};

/// <summary>Defines reactor interface for <code>AcApDocWindowManager</code> class. </summary>
class AcApDocWindowManagerReactor
{
public:
    /// <summary>Fired when a document window is created, and added to the document window collection.</summary>
    /// <param name="docWindow">The document window just created. </param>
    /// <remarks>At this stage the onCreate(HWND) function on the docWindow has finished execution, and
    /// view elements are already initialized. </remarks>
    ACAD_PORT virtual void documentWindowCreated(AcApDocWindow* docWindow);

    /// <summary>Fired when a document window is activated.</summary>
    /// <param name="docWindow">The document window being activated. </param>
    ACAD_PORT virtual void documentWindowActivated(AcApDocWindow* docWindow);

    /// <summary>Fired when a document window is destroyed and removed from the document window collection.</summary>
    /// <param name="docWindow">The document window being destroyed. </param>
    /// <remarks>Upon this event the document window is already removed from document window manager, while
    /// <code>onDestroy()</code> logic has not been executed yet.</remarks>
    ACAD_PORT virtual void documentWindowDestroyed(AcApDocWindow* docWindow);

    /// <summary>Fired when a document window is moved.</summary>
    /// <param name="docWindow">The document window instance being moved. </param>
    /// <param name="newIndex">The new index of the document window in the list of windows. </param>
    /// <param name="oldIndex">The old index of the document window before it was moved. </param>
    ACAD_PORT virtual void documentWindowMoved(AcApDocWindow* docWindow, int newIndex, int oldIndex);

    /// <summary>Fired when an old document window is replaced by a new document window. </summary>
    /// <param name="newDocWindow">The new document window that is going to replace the old instance.</param>
    /// <param name="oldDocWindow">The old document window being replaced. </param>
    /// <remarks>Notifications documentWindowCreated/documentWindowDestroyed are not fired for either 
    /// of these two windows.</remarks>
    ACAD_PORT virtual void documentWindowReplaced(AcApDocWindow* newDocWindow, AcApDocWindow* oldDocWindow);
};

class AcApDocWindowManagerImp;

/// <summary>The manager for all child windows inside AutoCAD main frame.</summary>
class AcApDocWindowManager
{
public:
    /// <summary>Gets the current active document window.</summary>
    /// <returns>Returns the active document window, or nullptr if no window is active.</returns>
    ACAD_PORT AcApDocWindow* activeDocumentWindow();

    /// <summary>Gets the total number of document windows.</summary>
    ACAD_PORT int documentWindowCount() const;

    /// <summary>Adds a custom non-DWG window as a child window in AutoCAD main frame.</summary>
    /// <param name="docWindow">The document window to be added. </param>
    /// <returns>Returns true if the document window is added successfully. </returns>
    /// <remarks>If the docWindow is added successfully, subsequent call to docWindow->windowHandle() would
    /// return valid handle. The docWindow instance will be deleted automatically after the window 
    /// is closed.</remarks>
    ACAD_PORT bool addDocumentWindow(AcApDocWindow* docWindow);

    /// <summary>Moves a document window to the new index.</summary>
    /// <param name="docWindow">The document window to be moved. </param>
    /// <param name="newIndex">The new index of the document window .</param>
    /// <returns>Returns true if the document window is moved successfully. </returns>
    ACAD_PORT bool moveDocumentWindow(AcApDocWindow* docWindow, int newIndex);

    /// <summary>Creates a new iterator instance. The client calling this function is responsible
    /// for deleting the instance.</summary>
    /// <returns>Returns a new iterator of document windows. The iterator must be deleted by the caller 
    /// after use. </returns>
    ACAD_PORT AcApDocWindowIterator* newIterator() const;

    /// <summary>Adds a reactor instance of type <code>AcApDocWindowManagerReactor</code> to handle changes
    /// of document window collection.</summary>
    ACAD_PORT void addReactor(AcApDocWindowManagerReactor* pReactor);

    /// <summary>Removes a reactor instance of type <code>AcApDocWindowManagerReactor</code> that was previously
    /// added.</summary>
    ACAD_PORT void removeReactor(AcApDocWindowManagerReactor* pReactor);

private:
    AcApDocWindowManager();
    ~AcApDocWindowManager();

    AcApDocWindowManagerImp* m_pImp;

    friend class AcApDocWindowManagerImp;
};

/// <summary>Gets the singleton instance of <code>AcApDocWindowManager</code>. </summary>
ACAD_PORT AcApDocWindowManager* acDocWindowManagerPtr();
#define acDocWindowManager acDocWindowManagerPtr()
