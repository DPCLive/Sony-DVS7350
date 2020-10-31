const SerialPort = require('serialport')

const Readline = SerialPort.parsers.Readline;
let array = new Array();
var indexDeLecture = 0;

const port = new SerialPort('COM10', { 
    baudRate: 38400, 
    databits: 8, 
    parity: 'even', 
    stopBits: 1, 
    flowControl: false
})


const parser = new Readline()
port.pipe(parser)


port.open(function (err) {
  if (err) {
    return console.log('Error opening port: ', err.message)
  }
})



port.on('data', function (data) {
	bufToArray(data);
})



function bufToArray(buffer) {
  var buf = Buffer.from(buffer.toString(),'hex');
  for (data of buf){ 
  array.push(data.toString(16));
  }
  return array;
}


const interv = setInterval(Response, 0);


function Response(){
var commands = [];
    //console.log(array);
    //console.log(indexDeLecture)
    if(array.length > 6){
		switch(array[indexDeLecture]){
            case '0':{
                switch(array[indexDeLecture+1]){
                    case '30':{
                        commands.push('8484');
                        WriteResponse(commands);
                        array.splice(0, 2); 
                        indexDeLecture=0;
                    }
                    break;   
                }
            }
            break; 
            case '2':{
                switch(array[indexDeLecture+1]){
                    case '0':{
                        switch(array[indexDeLecture+2]){
                            //020000
                            case '0':{
                                commands.push('03008092');
                                WriteResponse(commands);
                                array.splice(0, indexDeLecture+3); 
                                indexDeLecture=0;
                            }
                            break; 
                            //020001
                            case '1':{
                                commands.push('03008117');
                                WriteResponse(commands);
                                array.splice(0, indexDeLecture+3); 
                                indexDeLecture=0;
                            }
                            break;       
                                //}
                            //}
                            //break;        
                        }
                    }
                    break;
                }
            }
            break;
            case '3':{
                switch(array[indexDeLecture+1]){
                    case '10':{
                        switch(array[indexDeLecture+2]){
                            case '1b':{
                                switch(array[indexDeLecture+3]){
                                    //03101b0d
                                    case 'd':{
                                        commands.push('04109b0d00');
                                        WriteResponse(commands);
                                        array.splice(0, indexDeLecture+4); 
                                        indexDeLecture=0;
                                    }
                                    break;
                                }
                            }
                            break;
                        }
                    }
                    break;
                    case '20':{
                        switch(array[indexDeLecture+2]){
                            case '10':{
                                switch(array[indexDeLecture+3]){
                                    //03201009
                                    case '9':{
                                        commands.push('0420900901');
                                        WriteResponse(commands);
                                        array.splice(0, indexDeLecture+4); 
                                        indexDeLecture=0;
                                    }
                                    break;
                                    //03201019
                                    case '19':{
                                        commands.push('052090190007');
                                        WriteResponse(commands);
                                        array.splice(0, indexDeLecture+4); 
                                        indexDeLecture=0;
                                    }
                                    break;
                                    default:
                                        //indexDeLecture++;
                                        //clearInterval(interv);
                                        break;     
                                }
                            }
                            break;
                            case '11':{
                                switch(array[indexDeLecture+3]){
                                    //0320110d
                                    case 'd':{
                                        commands.push('0420910d01');
                                        WriteResponse(commands);
                                        array.splice(0, indexDeLecture+4); 
                                        indexDeLecture=0;
                                    }
                                    break;
                                    //03201120
                                    case '20':{
                                        commands.push('0420912000');
                                        WriteResponse(commands);
                                        array.splice(0, indexDeLecture+4); 
                                        indexDeLecture=0;
                                    }
                                    break;
                                    //03201138
                                    case '38':{
                                        commands.push('0420913800');
                                        WriteResponse(commands);
                                        array.splice(0, indexDeLecture+4); 
                                        indexDeLecture=0;
                                    }
                                    break;
                                    default:
                                        //indexDeLecture++;
                                        //clearInterval(interv);
                                        break;        
                                }
                            }
                            break;             
                        }
                    }
                    break;
                    case 'a':{
                        switch(array[indexDeLecture+2]){
                            case '1b':{
                                switch(array[indexDeLecture+3]){
                                    //030a1b0d
                                    case 'd':{
                                        commands.push('040a9b0d00');
                                        WriteResponse(commands);
                                        array.splice(0, indexDeLecture+4); 
                                        indexDeLecture=0;
                                    }
                                    break;
                                }
                            }
                            break;
                        }
                    }
                    break;
                    case 'c':{
                        switch(array[indexDeLecture+2]){
                            case '1b':{
                                switch(array[indexDeLecture+3]){
                                    //030c1b0d
                                    case 'd':{
                                        commands.push('040c9b0d00');
                                        WriteResponse(commands);
                                        array.splice(0, indexDeLecture+4); 
                                        indexDeLecture=0;
                                    }
                                    break;
                                }
                            }
                            break;
                        }
                    }
                    break;
                    default:
                    indexDeLecture++;
                    //clearInterval(interv);
                    break;
                }   
            }
            break;
            default:
                indexDeLecture++;
                //
                break;
        }
	
    }
	
}
 
   function WriteResponse(commands){
    var d = new Date();
        console.log(d.getTime(), Buffer.from(commands.join(''), 'hex'));
        //clearInterval(interv);
        port.write(commands.join(''));
    }