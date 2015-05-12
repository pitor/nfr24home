/* This Air Protocol */
#ifndef __TAP_H__

// package types
#define TAP_PT_UNSPECIFIED 0x00
#define TAP_PT_TEMPERATURE 0x01
#define TAP_PT_HUMIDITY    0x02
#define TAP_PT_PRESSURE    0x03
#define TAP_PT_TEXT        0x04
#define TAP_PT_ONEBYTE     0x05

// commands
#define TAP_PT_CMD_PING            0x80
#define TAP_PT_CMD_REQUEST_DATA    0x81
#define TAP_PT_CMD_DEVICE_SPECIFIC 0x82

// datatypes
#define TAP_DT_INT8           0x01
#define TAP_DT_UINT8          0x02
#define TAP_DT_INT16          0x03
#define TAP_DT_UINT16         0x04
#define TAP_DT_INT32          0x05
#define TAP_DT_UINT32         0x06
#define TAP_DT_FLOAT32        0x07
#define TAP_DT_FLOAT64        0x08
#define TAP_DT_FIXED_COMMA32  0x09
#define TAP_DT_TEXT           0x0a

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
  void setUnsignedInt8  ( uint8_t node_id, uint8_t package_type, uint8_t value );
  void setSignedInt8    ( uint8_t node_id, uint8_t package_type, int8_t value );
  void setUnsignedInt16 ( uint8_t node_id, uint8_t package_type, uint16_t value );
  void setSignedInt16   ( uint8_t node_id, uint8_t package_type, int16_t value );
  void setUnsignedInt32 ( uint8_t node_id, uint8_t package_type, uint32_t value );
  void setSignedInt32   ( uint8_t node_id, uint8_t package_type, int32_t value );
  void setCommand       ( uint8_t node_id, uint8_t package_type, char * command_data, uint8_t command_data_length );

  int parse( char * buffer, uint8_t buffer_length);

  uint8_t getSize();
 private:
  uint8_t size;

};




#define __TAP_H__
#endif

