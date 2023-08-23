var wSocket = new WebSocket('ws://localhost:1234');

wSocket.onopen = function(evt) {
    alert('connection established');
}

wSocket.onclose = function(evt) {
    alert('connection closed');
}

wSocket.onmessage = function(evt) {
    //console.log(evt.data);    
    writeMessage(evt.data)
}

wSocket.onerror = function(evt) {
    //console.log(evt.data);
    alert('error: ' + evt.data)
}

function writeMessage(data) {
    var area = document.getElementById('area');
    area.value = area.value + '\r\n' + data;
}
