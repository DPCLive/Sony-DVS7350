const bytey = require('bytey');
const convertHrtime = require('convert-hrtime');
var bufStr = "0030030";
const val = bufStr.replace(/ /g,"");
// Convert hex string to byte-array.
 ///var first = bytey.hexStringToByteArray('00 30 00 30');
 var buf = Buffer.from(val, 'hex');
// -> [ 104, 54, 40, 249, 237, 181, 233, 209 ]

console.log("test");

//var y = new Uint8Array(first);
//console.log(y[0]);
//console.log(convertHrtime(process.hrtime(process.hrtime())));
 /*var test = bytey.byteArrayToHexString([00, 30, 00, 30]);
 console.log(convertHrtime(process.hrtime(process.hrtime())).milliseconds + " : " + test); 
  var test1 = bytey.byteArrayToHexString([84, 84, 84, 84]);

 console.log(convertHrtime(process.hrtime(process.hrtime())).milliseconds + " : " + test1);*/
 //)