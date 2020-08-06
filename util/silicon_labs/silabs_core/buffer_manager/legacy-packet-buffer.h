uint8_t *emberGetLinkedBuffersPointer(Buffer buffer, uint8_t index);

EmberStatus emberReallyAppendToLinkedBuffers(EmberMessageBuffer *buffer,
                                             uint8_t *contents,
                                             uint8_t length,
                                             bool reallyAppend);
EmberStatus emberReallySetLinkedBuffersLength(Buffer *buffer,
                                              uint8_t newLength);

uint8_t emberGetLinkedBuffersByte(Buffer buffer, uint8_t index);
void emberSetLinkedBuffersByte(EmberMessageBuffer buffer, uint8_t index, uint8_t byte);

Buffer emberCopyLinkedBuffers(Buffer buffer);
void emberCopyBufferBytes(Buffer to,
                          uint16_t toIndex,
                          Buffer from,
                          uint16_t fromIndex,
                          uint16_t count);

uint16_t emberGetLinkedBuffersLowHighInt16u(Buffer buffer,
                                            uint8_t index);
void emberSetLinkedBuffersLowHighInt16u(Buffer buffer,
                                        uint8_t index,
                                        uint16_t value);
uint32_t emberGetLinkedBuffersLowHighInt32u(EmberMessageBuffer buffer,
                                            uint8_t index);
void emberSetLinkedBuffersLowHighInt32u(EmberMessageBuffer buffer,
                                        uint8_t index,
                                        uint32_t value);

EmberMessageBuffer
emberFillStackBuffer(unsigned int count, ...);

#define emberLinkedBufferContents(buffer) emberMessageBufferContents(buffer)

#define emberReleaseMessageBuffer(buffer) do {} while (0);
#define emberHoldMessageBuffer(buffer) do {} while (0);

#define emberAppendToLinkedBuffers(buffer, contents, length) \
  emberReallyAppendToLinkedBuffers(&(buffer), (contents), (length), true)

#define emberExtendLinkedBuffer(buffer, length) \
  emberReallyAppendToLinkedBuffers(&(buffer), NULL, (length), false)

#define emberSetLinkedBuffersLength(buffer, newlength) \
  emberReallySetLinkedBuffersLength(&(buffer), newlength)

#define emberSetMessageBufferLength emberSetLinkedBuffersLength

/*
   //----------------------------------------------------------------
   // Macros for the MessageBuffer interface.

 */
#define emberMessageBufferContents emGetBufferPointer
#define emberMessageBufferLength emGetBufferLength

#define emPacketHeaderPayload(header) emGetPayloadLink(header)

#define emSetPacketHeaderPayload(header, payload) \
  emSetPayloadLink((header), (payload))

#define emberFillLinkedBuffers(contents, length) \
  emReallyFillBuffer((contents), (length), false)
/*

 #define emberFillLinkedAsyncBuffers(contents, length) \
   emReallyFillBuffer((contents), (length), true)

 */
#define emMessageBufferQueueAdd emBufferQueueAdd
#define emMessageBufferQueueRemoveHead emBufferQueueRemoveHead
#define emMessageBufferQueueRemove emBufferQueueRemove
#define emMessageBufferQueueIsEmpty emBufferQueueIsEmpty

#undef EMBER_NULL_MESSAGE_BUFFER
#define EMBER_NULL_MESSAGE_BUFFER NULL_BUFFER

#define emberCopyFromLinkedBuffers(buffer, startIndex, contents, length) \
  emReallyCopyToLinkedBuffers((const uint8_t *) (contents), (buffer), (startIndex), (length), 0)

#define emberCopyToLinkedBuffers(contents, buffer, startIndex, length) \
  emReallyCopyToLinkedBuffers((const uint8_t *) (contents), (buffer), (startIndex), (length), 1)

#define emberAllocateStackBuffer() \
  emReallyAllocateBuffer(0, false)

#define PACKET_BUFFER_SIZE 32
