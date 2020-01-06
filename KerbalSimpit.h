/** @file KerbalSimpit.h
    The KerbalSimpit library.
*/
#ifndef KerbalSimpit_h
#define KerbalSimpit_h

#include <Arduino.h>

#include "KerbalSimpitMessageTypes.h"
#include "PayloadStructs.h"

const char KERBALSIMPIT_VERSION[] = "1.1.5"; /**< Library version sent to the plugin for compatibility checking. */
const byte MAX_PAYLOAD_SIZE = 32; /**< Maximum payload size does not include header. */

/** The KerbalSimpit class manages a serial connection to KSP.
    It automates the handshaking process, and provides utility
    functions to encapsulate most message types in and out of
    the game.
 */
class KerbalSimpit
{
 public:
  /** Default constructor.
      @param serial The serial instance this instance will use to communicate
      with the plugin. Usually "Serial".
  */
  KerbalSimpit(Stream &serial);
  /** Initialise the serial connection.
      Performs handshaking with the plugin. Note that the KSPit library
      *does not* call the `begin()` method on the serial object. You'll need
      to ensure you've run `Serial.begin(115200)` (or similar) before calling
      this method.
  */
  bool init();
  /** Specify a callback function to handle messages received from the plugin.
      @see messageHandler
      @param messageHandler The callback function.
  */
  void inboundHandler(void (*messageHandler)(byte messageType,
                                            byte msg[], byte msgSize));
  /** Subscribe to a channel of messages coming from the plugin.
      This function sends a channel subscription message to the plugin,
      indicating that this device would like to receive messages send
      to a given channel.
      @param channelID The ID of the channel to subscribe to.
  */
  void registerChannel(byte channelID);
  /** Unsubscribe from a channel of messages coming from the plugin.
      This function sends a channel subscription message to the plugin,
      indicating that no further messages for the given channel should
      be sent to this device.
      @param channelID The ID of the channel to unsubscribe from.
  */
  void deregisterChannel(byte channelID);
  // This template based on Nick Gammon's I2C_Anything lib:
  // http://www.gammon.com.au/forum/?id=10896&reply=8#reply8
  /** Send a formatted KSPit packet.
      Sends the given message as payload of a KSPit message.
      @param messageType The ID of the message channel.
      @param msg Any object to be sent. The expected object depends on
      the message type. No type checking is done by this library.
  */
  template <typename T> void send(byte messageType, T& msg) {
    send(messageType, (byte *) &msg, sizeof(msg));
  }
  /** Send a formatted KSPit packet.
      Sends the given message as payload of a KSPit message.
      @param messageType The ID of the message channel.
      @param msg A byte array representing the message contents.
      @param msgSize The size of msg.
  */
  void send(byte messageType, byte msg[], byte msgSize);
  /** Regular library update function.
      This function polls the serial device for new data, and performs other
      tasks that must be done regularly. The function should be called from
      an Arduino sketch `loop()` method.
  */
  void update();

  // Helper functions
 
  /** Activate Custom Action Group.
      Sends a message to activate the given Custom Action Group.
      @param actiongroup The ID of the Custom Action Group to activate.
  */
  void activateCAG(byte actiongroup);
 
  /** Deactivate Custom Action Group.
      Sends a message to deactivate the given Custom Action Group.
      @param actiongroup The ID of the Custom Action Group to deactivate.
  */
  void deactivateCAG(byte actiongroup);
 
  /** Toggle Custom Action Group.
      Sends a message to toggle the state of the given Custom Action Group.
      @param actiongroup The ID of the Custom Action Group to toggle.
  */
  void toggleCAG(byte actiongroup);
 
  /** Activate Action Group.
      Sends a message to activate the given standard Action Group(s).
      @param action A bitfield representing one or more Action Groups
      to activate.
  */
  void activateAction(byte action);
  
  /** Deactivate Action Group.
      Sends a message to deactivate the given standard Action Group(s).
      @param action A bitfield representing one or more Action Groups
      to deactivate.
  */
  void deactivateAction(byte action);
 
  /** Toggle Action Group.
      Sends a message to toggle the state of the given standard Action Group(s).
      @param action A bitfield representing one or more Action Groups
      to toggle.
  */
  void toggleAction(byte action);

 private:
  byte _readBuffer;
  byte _inboundType;
  byte _inboundSize;
  byte _inboundBuffer[MAX_PAYLOAD_SIZE];
  byte _outboundBuffer[MAX_PAYLOAD_SIZE];
  byte _outboundSize;
  Stream *_serial;

  enum ReceiveState_t
  {
    WaitingFirstByte,
    WaitingSecondByte,
    WaitingSize,
    WaitingType,
    WaitingData,
  };
  ReceiveState_t _receiveState;
  byte _receivedIndex;

  /** Callback function to handle messages from the plugin.
      This function is called by the library when full, correct
      messages are received from the plugin.
      @param messageType The ID of the message channel.
      @param msg A byte array representing the message contents. Note that
      the library does not attempt to transform this byte stream at all,
      and it is up to the user to convert it to the message-specific
      format.
      @param msgSize The size of the msg array.
  */
  void (*_messageHandler)(byte messageType, byte msg[], byte msgSize);
};

#endif
