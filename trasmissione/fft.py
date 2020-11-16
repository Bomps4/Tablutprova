import socket
import struct
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
BUFFER_SIZE = 512
def trasmit(TCP_PORT, ts):
	s.connect((TCP_IP, TCP_PORT))
	ts=ts.encode()
	impaccato=struct.pack('>I',len(ts))
	s.send(impaccato)
	s.send(ts)
	data=s.recv(BUFFER_SIZE)
	return data
