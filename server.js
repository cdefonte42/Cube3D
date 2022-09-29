var net = require('net');

let C = {
	Reset : "\x1b[0m",
	Bright : "\x1b[1m",
	Dim : "\x1b[2m",
	Underscore : "\x1b[4m",
	Blink : "\x1b[5m",
	Reverse : "\x1b[7m",
	Hidden : "\x1b[8m",
	
	Black : "\x1b[30m",
	Red : "\x1b[31m",
	Green : "\x1b[32m",
	Yellow : "\x1b[33m",
	Blue : "\x1b[34m",
	Magenta : "\x1b[35m",
	Cyan : "\x1b[36m",
	White : "\x1b[37m",
}

class Client {
	constructor(socket) {
		this.socket = socket;
		this.port = socket.remotePort;
		this.x = 0.0;
		this.y = 0.0;
		this.id = 0;
	}
}

var clients = [];

function sendMessageToAllClients(message, author) {
	for (var i = 0; i < clients.length; i++) {
		if (author == null || clients[i].port != author.port) {
			clients[i].socket.write(message);
			// console.log(i, message);
		}
	}
}

var server = net.createServer(function(socket) {
	console.log(C.Green+'Client connected: ' + socket.remoteAddress + ':' + socket.remotePort);

	if (clients.length > 4)
		return ;
	let client = new Client(socket);
	if (clients.length > 0) {
		client.id = clients[clients.length - 1].id + 1;
		let message = `n:${client.id}`;
		sendMessageToAllClients(message, client);
	}
	clients.push(client);

	socket.on('end', function() {
		clients.forEach((element, index) => {
			if (element.port == socket.remotePort) {
				clients.splice(index, 1);
				sendMessageToAllClients(`d:${element.id}`, client);
			}
		});

		clients.forEach((element, index) => {
			element.id = index;
		});
		console.log(C.Red+'Client disconnected: ' + socket.remoteAddress + ':' + socket.remotePort);
	});

	socket.on('data', function(data) {
		// console.log(C.Cyan+`Client data ${client.id}: ${data}`);
		
		if (clients.length > 1) {
			
			let message = `p:${client.id}:${data}`;
			sendMessageToAllClients(message, client);
		}
	});

	socket.on("error", function(err) {
		console.log(C.Yellow+'Client error: ' + err);

		clients.forEach((element, index) => {
			if (element.port == socket.remotePort) {
				clients.splice(index, 1);
			}
		});

		clients.forEach((element, index) => {
			element.id = index;
		});
		console.log(C.Red+'Client disconnected: ' + socket.remoteAddress + ':' + socket.remotePort);
	});

	socket.write('w');
	socket.pipe(socket);
}).listen(1977, function() {
	console.log('Server started');
});



// server.listen(1977, '127.0.0.1');
