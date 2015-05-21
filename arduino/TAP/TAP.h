/* This Air Protocol */
#ifndef __TAP_H__

// package types
typedef enum {
  // Data package types
  TAP_PT_UNSPECIFIED = 0x00,
  TAP_PT_TEMPERATURE = 0x01,
  TAP_PT_HUMIDITY    = 0x02,
  TAP_PT_PRESSURE    = 0x03,
  TAP_PT_TEXT        = 0x04,
  TAP_PT_ONEBYTE     = 0x05,

  //Command package types
  TAP_PT_CMD_PING            = 0x80,
  TAP_PT_CMD_REQUEST_DATA    = 0x81,
  TAP_PT_CMD_DEVICE_SPECIFIC = 0x82

} tap_package_type_enum;


// datatypes
typedef enum {
  TAP_DT_INT8          = 0x01,
  TAP_DT_UINT8         = 0x02,
  TAP_DT_INT16         = 0x03,
  TAP_DT_UINT16        = 0x04,
  TAP_DT_INT32         = 0x05,
  TAP_DT_UINT32        = 0x06,
  TAP_DT_FLOAT32       = 0x07,
  TAP_DT_FLOAT64       = 0x08,
  TAP_DT_FIXED_COMMA32 = 0x09,
  TAP_DT_TEXT          = 0x0a
} tap_data_type_enum;

typedef union {
  int8_t  signedInt8;
  uint8_t unsignedInt8;
  int16_t  signedInt16;
  uint16_t unsignedInt16;
  int32_t signedInt32;
  uint32_t unsignedInt32;
  float float32;
  char text[10];
} tap_data_t;


typedef union {
    char command_data[10];
  struct  {
    uint8_t data_type;
    tap_data_t data; 
  } data_contents;
} tap_package_contents_t;

class TapMessage {
public:
  uint8_t node_id;
  uint8_t package_type;
  tap_package_contents_t package_contents;
  
  void clear();
  void setUnsignedInt8  ( uint8_t node_id, tap_package_type_enum package_type, uint8_t value );
  void setSignedInt8    ( uint8_t node_id, tap_package_type_enum package_type, int8_t value );
  void setUnsignedInt16 ( uint8_t node_id, tap_package_type_enum package_type, uint16_t value );
  void setSignedInt16   ( uint8_t node_id, tap_package_type_enum package_type, int16_t value );
  void setUnsignedInt32 ( uint8_t node_id, tap_package_type_enum package_type, uint32_t value );
  void setSignedInt32   ( uint8_t node_id, tap_package_type_enum package_type, int32_t value );
  void setCommand       ( uint8_t node_id, tap_package_type_enum package_type, char * command_data, uint8_t command_data_length );

  int parse( char * buffer, uint8_t buffer_length);

  uint8_t getSize();
 private:
  uint8_t size;

};




#define __TAP_H__
#endif

