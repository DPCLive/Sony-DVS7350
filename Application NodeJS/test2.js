const readline = require("readline");
var fs = require('fs');

let array = new Array();
var indexDeLecture = 0;


const rl = readline.createInterface({
    input: fs.createReadStream('req.txt')
});

rl.on('line', function(data) {
    console.log(data)
    bufToArray(data);
});



function bufToArray(buffer) {
  var buf = Buffer.from(buffer.toString(),'hex');
  if(buf.readInt8(0).toString(16) == '0'){
      console.log('true')
  }

  /*for (data of buf){ 
  array.push(data.toString(16));
  }
  return array;*/
}


//const interv = setInterval(Response, 0);


function Response(){
var commands = [];
var d = new Date();

    //console.log(array);
    //console.log(indexDeLecture)
    /*var test = array.join('');
    console.log(test)*/
    /*if(array[indexDeLecture] == '0' && array[indexDeLecture+1] == '30'){
        array.splice(indexDeLecture, indexDeLecture+2);
        indexDeLecture=0;
        console.log(d.getTime(),'8484')
    }else if(array[indexDeLecture] == '3' && array[indexDeLecture+1] == '20' && array[indexDeLecture+2] == '10' && array[indexDeLecture+3] == '9'){
        array.splice(indexDeLecture, indexDeLecture+4);
    console.log(d.getTime(),'320109')
    }else{
       // console.log(d.getTime(), array);
       indexDeLecture++;
    }*/
}
 
   function WriteResponse(commands){
    var d = new Date();
        console.log(d.getTime(), Buffer.from(commands.join(''), 'hex'));
        //clearInterval(interv);
        //port.write(testu);
    }