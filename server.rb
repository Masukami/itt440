require 'socket' #socket library

PORT = 1036
socket = TCPServer.new('0.0.0.0', PORT)
client = socket.accept

def handle_connection(client)
	puts "New client detected! : #{client}"
	client.write("Hello! This is Masukami's Server")
	client.close
end

puts "Listening on #{PORT}"

while client = socket.accept
	Thread.new { handle_connection(client) }
end
