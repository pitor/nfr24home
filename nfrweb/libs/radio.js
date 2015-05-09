// see https://gist.github.com/natevw/5789019 for pins
var NRF24 = require("nrf");
var TAP   = require("./TAP");

var values = [];

Buffer.prototype.reverse = function() {
    var start = 0;
    var stop  = this.length - 1;
    while( start < stop ) {
	var tmp = this[ start ];
	this[start] = this[stop];
	this[stop]  = tmp ;
	stop--;
	start++;
    }
    return this;
}

options = {
    cePin: 22,
    irqPin: 24,
    channel: 0x02,
    spiDev: "/dev/spidev0.0",
    pipes: [0x1000000001, 0x1000000002],
    transmitPower: "PA_MAX",
    dataRate: '250kbps',
    crcBytes: 2,
};



function setOptions( opt ) {
    for( var key in opt ) {
	if(options.hasOwnProperty( key ))
	    options[key] = opt[key];
	else
	    consol.log("Unknown option %s", key);
    }
}

function start() {
    var nrf = NRF24.connect(options.spiDev, options.cePin, options.irqPin);
    //nrf._debug = true;
    nrf.channel( options.channel )
	.transmitPower( options.transmitPower )
	.dataRate( options.dataRate )
	.crcBytes( options.crcBytes )
	.autoRetransmit({count:15, delay:4000})
	.begin(function () {

	    var rx = nrf.openPipe('rx', options.pipes[0]);
	    var tx = nrf.openPipe('tx', options.pipes[1]);

	    var tap = new TAP();

	    rx.on('data', function (d) {
		d.reverse();
		var data = tap.parse( d );
		console.log("Got data %j", data);
		values.push(tap.value());
		while(values.length > 20)
		    values.shift()
	    });

	    tx.on('error', function (e) {
		console.warn("Error sending.", e);
	    });

	    tx.on('ready', function() {
		console.log("TX Ready");
		setInterval(function() {
		    var buf = Buffer("Ich bin");
		    console.log("Sending %s", buf);
		    tx.write(buf.reverse());
		}, 5000);
	    });
	});
}

module.exports = exports = {
    start      : start,
    setOptions : setOptions,
    values     : function() { return values}
};
