var socket = io();

function ledRED() {
    socket.emit('ledRED');
	console.log('ledRED');

}

function ledBLUE() {
    socket.emit('ledBLUE');
	console.log('ledBLUE');
}

function ledGREEN() {
    socket.emit('ledGREEN');
	console.log('ledGREEN');
}
// send out ledOFF message over socket
function ledOFF() {
    socket.emit('ledOFF');
	console.log('ledOFF');
    var doorbell = document.getElementById("doorbell");
    doorbell.loop = false;
    doorbell.play();
}

// read the data from the message that the server sent and change the
// background of the webpage based on the data in the message
socket.on('server-msg', function(msg) {
    console.log('msg:', msg);
    switch(msg) {
        case 'light':
            document.body.style.backgroundColor = 'white';
            console.log('white')
            break;
        case 'dark':
            document.body.style.backgroundColor = 'black';
            console.log('black');
            break;
    }
});
