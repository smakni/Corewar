#!/usr/bin/python

import sys, os
import socket
import time
import subprocess
from controller import Controller

PATH_TO_COREWAR=	"../corewar"

class Server(Controller):
	def __init__(self):
		Controller.__init__(self)
		self.s = socket.socket()
		self.host = socket.gethostname()
		self.port = self.SERVER_PORT
		print("Your IP address is: %s" % socket.gethostbyname(self.host))
		self.s.bind((self.host, self.port))

	def	listen_port(self):
		try:
			self.s.listen(1)
			client, addr = self.s.accept()
			self.client = {
				"obj": client,
				"addr": addr
			}
			print("[+] Got connection from %s" % str(addr))
			self.client["obj"].send(b"You are now connected to " + bytes(self.host, self.ENCODING_METHOD) + b".\nPlease enter the path to your .cor champion:")
			print("Please enter the path to your .cor champion:\n\t>>", end="")
			self.get_filepath()
		except KeyboardInterrupt:
			print("\n[*] Disconnection requested.")
			self.close_connections()

	def	_send_file(self):
		buffer = self.champ_file.read(self.BUFF_SIZE)
		while buffer:
			self.client["obj"].send(buffer)
			buffer = self.champ_file.read(self.BUFF_SIZE)
		self.get_file()

	def	receive_champ(self):
		client_champ = open("client_champ.cor", "wb")
		buffer = self.client["obj"].recv(self.BUFF_SIZE)
		while len(buffer) >= self.BUFF_SIZE:
			client_champ.write(buffer)
			buffer = self.client["obj"].recv(self.BUFF_SIZE)
		client_champ.write(buffer)
		client_champ.close()
		print("[+] Your opponent's champion has been written in client_champ.cor.")
		self.checklist["received"] = True
		time.sleep(1)
		self.client["obj"].send(b"RECEIVED")

	def	get_confirmation(self):
		confirmation = self.client["obj"].recv(8)
		if confirmation.decode(self.ENCODING_METHOD) == "RECEIVED":
			self.checklist["sent"] = True

	def	exchange_bin(self):
		server_bin = self.send_bin(PATH_TO_COREWAR)
		self.client["obj"].send(server_bin)
		client_bin = self.client["obj"].recv(64)
		if self.check_bin((server_bin, client_bin)) == -1:
			return -1
		return 0

	def	close_connections(self):
		if hasattr(self, "client"):
			self.client["obj"].close()
		self.s.close()
		try:
			sys.exit(0)
		except SystemExit:
			os._exit(0)

def	main():
	serv = Server()
	serv.listen_port()
	if serv.exchange_bin() == -1:
		print("[-] Client and Server are not running the same version of Corewar.\nExit")
		sys.exit(-1)
	print("[+] You are running the same version, the game can begin")
	print(">>GAME START<<\nYou play first !\n")
	try:
		subprocess.call(["./%s" % PATH_TO_COREWAR, serv.filepath, "client_champ.cor", "-visu"])
		os.system("read -p 'Press Enter to continue...'")
	except KeyboardInterrupt:
		print("\n[*] Interruption requested.")
		serv.close_connections()	
	serv.close_connections()

if __name__ == "__main__":
	main()