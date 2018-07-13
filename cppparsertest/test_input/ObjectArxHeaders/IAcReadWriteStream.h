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
//  DESCRIPTION: IAcReadStream and IAcWriteStream general purpose
//  filing interfaces

#pragma once

/// <summary>
/// Interface for a readable stream.
/// </summary>
class __declspec(novtable) IAcReadStream
{
  public:
    /// <summary>
    /// return codes
    /// </summary>
    enum {
            /// <summary>
            /// No errors occurred
            /// </summary>
            eOk = 0,
            /// <summary>
            /// This function is not supported for this stream object
            /// </summary>
            eNotSupported = 1,
            /// <summary>
            /// The stream is not open
            /// </summary>
            eNotOpen = 2,
            /// <summary>
            /// One of the arguments is an invalid value
            /// </summary>
            eInvalidArg = 3,
            /// <summary>
            /// The stream is at the end of the file
            /// </summary>
            eEndOfFile = 4,
            /// <summary>
            /// The disk to which the stream is writing is full
            /// </summary>
            eDiskFull = 5,
            /// <summary>
            /// The stream is disconnected
            /// </summary>
            eDisconnected = 6,
            /// <summary>
            /// Unknown error
            /// </summary>
            eJustAnError = 7
    };

    /// <summary>
    /// seek mode arguments
    /// </summary>
    enum {
            /// <summary>
            /// Seek from start of stream
            /// </summary>
            eFromStart = 0,
            /// <summary>
            /// Seek from current stream position
            /// </summary>
            eFromCurrent = 1,
            /// <summary>
            /// Seek from end of stream
            /// </summary>
            eFromEnd = 2
    };

    /// <summary>
    /// This function sets the stream position to be nDistance from the nMode stream
    /// location.  If nDistance is negative, then the new position will be that distance
    /// earlier in the stream, otherwise it will be nDistance after the nMode location.
    /// </summary>
    /// <param name="nDistance">Input distance to seek from nMode position</param>
    /// <param name="nMode">Input seek mode</param>
    /// <returns>Returns a status (such as eOk) indicating the outcome of the seek operation.</returns>
    virtual int  seek(Adesk::Int64 nDistance, int nMode) { 
        ADESK_UNREFED_PARAM(nDistance);
        ADESK_UNREFED_PARAM(nMode);
        return eNotSupported; 
    }

    /// <summary>
    /// This function sets nOffset to the current stream position relative to the start of the stream.
    /// </summary>
    /// <returns>Returns the distance from the start of the stream to the current read/write position.  Returns -1 by default.</returns>
    virtual Adesk::Int64 tell() { return -1; }

    /// <summary>
    /// This function reads nNumBytes bytes of data from the stream and copies it into the location
    /// pointed to by pDestBuf.  The value pointed to by pNumRead is set to the number of bytes
    /// actually read and copied to pDestBuf.
    /// Some implementations may return eOk when the number of bytes read is less than
    /// the number requested.  Others may return eEndOfFile in that case.
    /// </summary>
    /// NOTE: when implementing a class derived from IAcReadStream, the read() method must be
    /// overridden, but all other IAcReadStream methods can be the default implementations.
    /// <param name="pDestBuf">Input pointer to location to copy stream data to</param>
    /// <param name="nNumBytes">Input number of bytes to read from stream</param>
    /// <param name="pNumRead">Output number of bytes read from stream</param>
    /// <returns>Returns a status (such as eOk) indicating the outcome of the read operation.</returns>
    virtual int read(void* pDestBuf, size_t nNumBytes,
                                     size_t *pNumRead) = 0;

    /// <summary>
    /// This function closes the stream, and may also deallocate the stream object.
    /// </summary>
    /// <returns>Returns a status (such as eOk) indicating the outcome of the close operation.</returns>
    virtual int  close() { return eNotSupported; }

    /// <summary>
    /// Auxiliary method for implementation-specific functionality.
    /// </summary>
    /// <param name="nArg">Input value, implementation dependent</param>
    /// <returns>An implementation dependent value.</returns>
    virtual Adesk::Int64 control(Adesk::Int64 nArg) {
        ADESK_UNREFED_PARAM(nArg);
        return 0; 
    }

  protected:
    /// <summary>
    /// Destructor
    /// </summary>
    virtual ~IAcReadStream() {}     // no explicit deletes
};

/// <summary>
/// Interface for a read/write stream.
/// </summary>
class __declspec(novtable) IAcWriteStream : public IAcReadStream
{
  public:
    /// <summary>
    /// This function copies nNumBytes bytes of data from the location pointed to by pSrcBuf to the
    /// stream.  The value pointed to by pNumWritten is set to the number of bytes actually copied
    /// to the stream.
    /// </summary>
    /// NOTE: When implementing a class derived from IAcWriteStream, the write() method must be
    /// overridden, but all other IAcWriteStream methods can be the default implementations.
    /// <param name="pSrcBuf">Input pointer to location of data to be written to the stream</param>
    /// <param name="nNumBytes">Input number of bytes to write to the stream</param>
    /// <param name="pNumWritten">Output number of bytes written to the stream</param>
    /// <returns>Returns a status (such as eOk) indicating the outcome of the write operation.</returns>
    virtual int write(const void* pSrcBuf, size_t nNumBytes,
                      size_t *pNumWritten) = 0;

    /// <summary>
    /// This function flushes any buffers used by the stream.
    /// </summary>
    /// <returns>Returns a status (such as eOk) indicating the outcome of the operation.</returns>
    virtual int flushBuffers() { return eNotSupported; }

    /// <summary>
    /// This function sets the current stream position as the end of file.
    /// </summary>
    /// <returns>Returns a status (such as eOk) indicating the outcome of the operation.</returns>
    virtual int setEndOfFile() { return eNotSupported; }
  protected:
    /// <summary>
    /// Destructor
    /// </summary>
    virtual ~IAcWriteStream() {} // no explicit deletes
};

