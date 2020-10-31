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

function ledOFF() {
    socket.emit('ledOFF');
	console.log('ledOFF');
}

// read the data from the message that the server sent and ring doorbell if correct message
socket.on('server-msg', function(msg) {
    switch(msg) {
        case 'dark':
            var doorbell = document.getElementById("doorbell");
            doorbell.loop = false;
            console.log('black');
            doorbell.play();
            break;
    }
});
