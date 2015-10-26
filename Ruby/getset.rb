require 'socket'

PORT = 2808
socket = TCPServer.new('0.0.0.0', PORT)

#getsockopt(level,optname)
#setsockopt(level,optname,val)

optval = socket.getsockopt(Socket::SOL_SOCKET, Socket::SO_SNDBUF);
optval = optval.unpack "i"
puts "SNDBUF Early Option : #{optval}"
socket.setsockopt(Socket::SOL_SOCKET, Socket::SO_SNDBUF, 5342);
optval = socket.getsockopt(Socket::SOL_SOCKET, Socket::SO_SNDBUF);
optval = optval.unpack "i"
puts "SNDBUF After Edit : #{optval}"
	
