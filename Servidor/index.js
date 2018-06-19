var express = require('express');
var app =  express();
var server = require('http').Server(app);
var io = require('socket.io')(server);
app.use(express.static("public"));



app.get('/', function(req, res){
    res.status(200).send("hola mundo");
});
const SerialPort = require('serialport');
const ReadLine = SerialPort.parsers.Readline;

const mySerial = new SerialPort("COM6", {
  baudRate: 9600
});

const parser = mySerial.pipe(new ReadLine({ delimiter: '\n' }));
parser.on('open', function(){
    console.log('puerto abierto');
});

parser.on('data', function(data){
    var datos = data;
    console.log(datos.toString());
    if(data.charAt(0) == 'm'){
        io.emit('mq2',data.match(/(\d+)/g));

    }
    if(data.charAt(0) == 'h'){
        io.emit('humedad',data.match(/(\d+)/g));
    }
    if(data.charAt(0) == 't'){
        io.emit('temperatura',data.match(/(\d+)/g));
        
    }
    if(data.charAt(0) == 'p'){
        io.emit('pir',data.match(/(\d+)/g));
    }
    
    else {
        io.emit('error',"error en recepcion de datos");
    }
    
});





server.listen(8080, function(){
    console.log("running server");
});

mySerial.on('err', function(err){
    console.log(err.message);
});
