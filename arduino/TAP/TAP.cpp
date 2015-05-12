#if (ARDUINO >= 100)
#include <Arduino.h> // capital A so it is error prone on case-sensitive filesystems
#else
#include <WProgram.h>
#endif

#include "TAP.h"

void TapMessage::clear() {
  memset(this, 0, sizeof(this));
}

void TapMessage::setUnsignedInt8( uint8_t node_id, uint8_t package_type, uint8_t value ) {
  this->clear();
  this->node_id       = node_id;
  this->package_type  = package_type;
  this->package_contents.data_contents.data_type         = TAP_DT_UINT8;
  this->package_contents.data_contents.data.unsignedInt8 = value;
  this->size = sizeof( value );
}

void TapMessage::setSignedInt8( uint8_t node_id, uint8_t package_type, int8_t value ) {
  this->clear();
  this->node_id           = node_id;
  this->package_type    = package_type;
  this->package_contents.data_contents.data_type       = TAP_DT_INT8;
  this->package_contents.data_contents.data.signedInt8 = value;
  this->size = sizeof( value );
}

void TapMessage::setUnsignedInt16( uint8_t node_id, uint8_t package_type, uint16_t value ) {
  this->clear();
  this->node_id = node_id;
  this->package_type   = package_type;
  this->package_contents.data_contents.data_type          = TAP_DT_UINT16;
  this->package_contents.data_contents.data.unsignedInt16 = value;
  this->size = sizeof( value );
}

void TapMessage::setSignedInt16( uint8_t node_id, uint8_t package_type, int16_t value ) {
  this->clear();
  this->node_id = node_id;
  this->package_type = package_type;
  this->package_contents.data_contents.data_type          = TAP_DT_INT16;
  this->package_contents.data_contents.data.signedInt16 = value;
  this->size = sizeof( value );
}

void TapMessage::setUnsignedInt32( uint8_t node_id, uint8_t package_type, uint32_t value ) {
  this->clear();
  this->node_id = node_id;
  this->package_type       = package_type;
  this->package_contents.data_contents.data_type          = TAP_DT_UINT32;
  this->package_contents.data_contents.data.unsignedInt32 = value;
  this->size = sizeof( value );
}

void TapMessage::setSignedInt32( uint8_t node_id, uint8_t package_type, int32_t value ) {
  this->clear();
  this->node_id = node_id;
  this->package_type   = package_type;
  this->package_contents.data_contents.data_type          = TAP_DT_INT32;
  this->package_contents.data_contents.data.signedInt32 = value;
  this->size = sizeof( value );
}


void TapMessage::setCommand( uint8_t node_id, uint8_t package_type, char * command_data, uint8_t command_data_length ) {
  this->clear();
  this->node_id = node_id;
  this->package_type   = package_type;
  //TODO: the memcpy stuff
}

uint8_t TapMessage::getSize() {
  if(this->package_type >= TAP_PT_CMD_PING) {
    return 2 + this->size;
  }
  return 3 + this->size;
}

