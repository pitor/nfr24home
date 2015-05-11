function TAP() {
    var self = this;
    // Package types
    self.PT_UNSPECIFIED = 0x00;
    self.PT_TEMPERATURE = 0x01;
    self.PT_HUMIDITY    = 0x02;
    self.PT_PRESSURE    = 0x03;
    self.PT_TEXT        = 0x04;
    self.PT_ONEBYTE     = 0x05;

    // Commands begin at 0x80
    self.PT_CMD_PING            = 0x80
    self.PT_CMD_REQUEST_DATA    = 0x81;
    self.PT_CMD_DEVICE_SPECIFIC = 0x82;

    // Data types
    self.DT_INT8          = 0x01;
    self.DT_UINT8         = 0x02;
    self.DT_INT16         = 0x03;
    self.DT_UINT16        = 0x04;
    self.DT_INT32         = 0x05;
    self.DT_UINT32        = 0x06;
    self.DT_FLOAT32       = 0x07;
    self.DT_FLOAT64       = 0x08;
    self.DT_FIXED_COMMA32 = 0x09;
    self.DT_TEXT          = 0x0a;

    var _val = null;

    self.value = function() {
        return _val;
    },

    self.parse = function( buf ) {
	if(buf.length < 3)
	    throw new TError('LENGTH', "minimum length is 3 bytes");
	var nodeId      = buf.readUInt8(0);
	var packageType = buf.readUInt8(1);
	var dataType    = buf.readUInt8(2);

	if(packageType >= self.PT_CMD_PING ) {

	    var commandData = [];
	    for( var ix = 3; ix<buf.length; ix++)
		commandData.push( buffer[ix] );

	    return {
		node_id: nodeId,
		package_type: packageType,
		command_data: commandData,
		original_buffer: buf,
	    };
	} 
	else {
	    switch(dataType) {
	    case self.DT_INT8   : _val = buf.readInt8( 3 ); break;
	    case self.DT_UINT8  : _val = buf.readUInt8( 3 ); break; 
	    case self.DT_INT16  : _val = buf.readInt16BE( 3 ); break;
	    case self.DT_UINT16 : _val = buf.readUInt16BE( 3 ); break; 
	    case self.DT_INT32  : _val = buf.readInt32BE( 3 ); break;
	    case self.DT_UINT32 : _val = buf.readUInt32BE( 3 ); break; 
	    case self.DT_FLOAT32: _val = buf.readFloatBE( 3 ); break;
	    case self.DT_FLOAT64: _val = buf.readDoubleBE( 3 ); break;
	    default: throw new TError( 'DATATYPE', "Unknown datatype" );
	    };

	    return {
		node_id: nodeId,
		package_type: packageType,
		data_type: dataType,
		value: _val,
	    };

	}

    };


}

function TError( code, message) {
    this.code = code;
    this.message = message;
}

module.exports = exports = TAP;