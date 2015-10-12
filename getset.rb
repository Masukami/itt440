require 'socket'

PORT = 2808
socket = TCPServer.new('0.0.0.0', PORT)

#getsockopt(level,optname)
#setsockopt(level,optname,val)

optval = socket.getsockopt(Socket::SOL_SOCKET, Socket::SO_SNDLOWAT);
puts "SNDBUF Early Option : #{Socket::SO_SNDLOWAT}"
socket.setsockopt(Socket::SOL_SOCKET, Socket::SO_SNDLOWAT, 5342);
puts "SNDBUF After Edit : #{Socket::SO_SNDLOWAT}"

