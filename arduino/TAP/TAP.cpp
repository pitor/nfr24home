#if (ARDUINO >= 100)
#include <Arduino.h> // capital A so it is error prone on case-sensitive filesystems
#else
#include <WProgram.h>
#endif

#include "TAP.h"

void TapMessage::clear() {
  memset(this, 0, sizeof(this));
}

void TapMessage::setUnsignedInt8( uint8_t node_id, uint8_t measurement_type, uint8_t value ) {
  this->clear();
  this->node_id       = node_id;
  this->package_type  = measurement_type;
  this->package_contents.data_contents.data_type         = TAP_DT_UINT8;
  this->package_contents.data_contents.data.unsignedInt8 = value;
  this->size = sizeof( value );
}

void TapMessage::setSignedInt8( uint8_t node_id, uint8_t measurement_type, int8_t value ) {
  this->clear();
  this->node_id           = node_id;
  this->package_type    = measurement_type;
  this->package_contents.data_contents.data_type       = TAP_DT_INT8;
  this->package_contents.data_contents.data.signedInt8 = value;
  this->size = sizeof( value );
}

void TapMessage::setUnsignedInt16( uint8_t node_id, uint8_t measurement_type, uint16_t value ) {
  this->clear();
  this->node_id = node_id;
  this->package_type   = measurement_type;
  this->package_contents.data_contents.data_type          = TAP_DT_UINT16;
  this->package_contents.data_contents.data.unsignedInt16 = value;
  this->size = sizeof( value );
}

void TapMessage::setSignedInt16( uint8_t node_id, uint8_t measurement_type, int16_t value ) {
  this->clear();
  this->node_id = node_id;
  this->package_type = measurement_type;
  this->package_contents.data_contents.data_type          = TAP_DT_INT16;
  this->package_contents.data_contents.data.signedInt16 = value;
  this->size = sizeof( value );
}

void TapMessage::setUnsignedInt32( uint8_t node_id, uint8_t measurement_type, uint32_t value ) {
  this->clear();
  this->node_id = node_id;
  this->package_type       = measurement_type;
  this->package_contents.data_contents.data_type          = TAP_DT_UINT32;
  this->package_contents.data_contents.data.unsignedInt32 = value;
  this->size = sizeof( value );
}

void TapMessage::setSignedInt32( uint8_t node_id, uint8_t measurement_type, int32_t value ) {
  this->clear();
  this->node_id = node_id;
  this->package_type   = measurement_type;
  this->package_contents.data_contents.data_type          = TAP_DT_INT32;
  this->package_contents.data_contents.data.signedInt32 = value;
  this->size = sizeof( value );
}


uint8_t TapMessage::getSize() {
  if(this->package_type == TAP_PT_COMMAND) {
    return 2 + sizeof( this->package_contents.command_contents);
  }
  return 3 + this->size;
}

