import socket
import struct
import time
import json
import numpy as np
import sys
from ctypes import *
def process(data):
	lich=list('{},:[]')
	
	for c in lich:
		data=data.replace(c.encode(),b'')
	
	
	
	data=data.split(b'"')
	
	data=data[2:-4]
	data=np.array(data)
	#print(data!=b'')
	data=data[data!=b''].reshape((9,9))
	statuspp=((c_char * 9) * 9)()
	
	for i in range(9):
		for j in range(9):
			if(b'EMPTY' in data[i][j]):
				statuspp[i][j]=b'O'
			elif(b'BLACK' in data[i][j]):
				statuspp[i][j]=b'B'
			elif( b'WHITE' in data[i][j]):
				statuspp[i][j]=b'W'
			elif( b'KING' in data[i][j]):
				statuspp[i][j]=b'K'
	return statuspp

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
BUFFER_SIZE = 2048


def trasmit(TCP_IP,TCP_PORT, ts,i=0):
	
	print(len(ts))
	if(i!=0):
		for i in ts:
			print(i)
		table={"0":"a","1":"b","2":"c","3":"d","4":"e","5":"f","6":"g","7":"h","8":"i","a":"1","b":"2","c":"3","d":"4","e":"5","f":"6","g":"7","h":"8","i":"9"}
		dic={"from":table[ts[3]]+table[ts[2]],"to":table[ts[7]]+table[ts[6]]}
		y=json.dumps(dic)
		y=y.encode()
		impaccato=struct.pack('>I',len(y))
		print(y)
		s.send(impaccato)
		s.send(y)
	else:
		ts=ts.encode()
		impaccato=struct.pack('>I',len(ts))
		s.send(impaccato)
		s.send(ts)
	
def main ():
	TCP_PORT=0
	arguments=sys.argv
	TCP_IP=arguments[1]
	w_b=arguments[2].lower()
	tempo=int(arguments[3])
	if("white" in w_b):
		w_b=b'W'
		TCP_PORT=5800
	elif("black" in w_b):
		w_b=b'B'
		TCP_PORT=5801
	s.connect((TCP_IP, TCP_PORT))
	trasmit(TCP_IP,TCP_PORT, 'implicazionicomicheimplicite')
	
	data=s.recv(BUFFER_SIZE)

	while(len(data)<=8 or data==b'\x00'):
		data=s.recv(BUFFER_SIZE)

	
	if(w_b=='B'):
		data=s.recv(BUFFER_SIZE)
	while(len(data)<=8 or data==b'\x00'):
		data=s.recv(BUFFER_SIZE)
	
	data=process(data)
	so_file = "./underlying.so"
	c_lib = CDLL(so_file)
	deletare=c_lib.deletare
	deletare.restype=None
	execute=c_lib.execution
	execute.restype=POINTER(c_char)
	i=0
	while True:
		risultato=execute(data,c_char(w_b),c_int(tempo-3))
		valore=c_char_p.from_buffer(risultato).value[:6]
		trasmit(TCP_IP,TCP_PORT,str(valore),1)
		print("qui")
		deletare(risultato)
		data=s.recv(BUFFER_SIZE)
		while(len(data)<=8 or data==b'\x00'):
			data=s.recv(BUFFER_SIZE)
			if(len(data)==0):
				break
		print(data)
		data=process(data)
	s.close()
	
		
	
	
main()
