/*
 * Copyright 2019 Google LLC
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#ifndef GrClientMappedBufferManager_DEFINED
#  define GrClientMappedBufferManager_DEFINED
#  include "include/private/SkTArray.h"
#  include "src/core/SkMessageBus.h"
#  include "src/gpu/GrGpuBuffer.h"
#  include <forward_list>
class GrClientMappedBufferManager
{
public:
    /**
     * The message type that internal users of this should post to unmap the buffer.
     * Set fInboxID to inboxID(). fBuffer must have been previously passed to insert().
     */
  struct BufferFinishedMessage
  {
    sk_sp<GrGpuBuffer> fBuffer;
    uint32_t fInboxID;
  };
  using BufferFinishedMessageBus = SkMessageBus<BufferFinishedMessage>;
  GrClientMappedBufferManager(uint32_t contextID);
  GrClientMappedBufferManager(const GrClientMappedBufferManager&) = delete;
  GrClientMappedBufferManager(GrClientMappedBufferManager&&) = delete;
  ~GrClientMappedBufferManager();
  GrClientMappedBufferManager& operator=(const GrClientMappedBufferManager&);
  GrClientMappedBufferManager& operator=(GrClientMappedBufferManager&&);
    /** Initialize BufferFinishedMessage::fInboxID to this value. */
  uint32_t inboxID() const
  {
    return fFinishedBufferInbox.uniqueID();
  }
    /**
     * Let the manager know to expect a message with buffer 'b'. It's illegal for a buffer to be
     * inserted again before it is unmapped by process().
     */
  void insert(sk_sp<GrGpuBuffer> b);
    /** Poll for messages and unmap any incoming buffers. */
  void process();
    /** Notifies the manager that the context has been abandoned. No more unmaps() will occur.*/
  void abandon();
private:
  BufferFinishedMessageBus::Inbox fFinishedBufferInbox;
  std::forward_list<sk_sp<GrGpuBuffer>> fClientHeldBuffers;
  bool fAbandoned = false;
  void remove(const sk_sp<GrGpuBuffer>& b);
};
bool SkShouldPostMessageToBus(const GrClientMappedBufferManager::BufferFinishedMessage&, uint32_t msgBusUniqueID);
#endif
