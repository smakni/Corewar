#!/usr/bin/python

import sys, os
import re
import socket
import time
import subprocess
from controller import Controller

PATH_TO_COREWAR=	"../corewar"

class Client(Controller):
	def	__init__(self, host):
		Controller.__init__(self)
		self.s = socket.socket()
		self.host = host
		self.port = self.SERVER_PORT

	def	connect(self):
		self.s.connect((self.host, self.port))
		msg = self.s.recv(128)
		msg = msg.decode(self.ENCODING_METHOD)
		if msg != "":
			print(msg + "\n\t>>", end="")
		self.get_filepath()

	def	_send_file(self):
		buffer = self.champ_file.read(self.BUFF_SIZE)
		while buffer:
			self.s.send(buffer)
			buffer = self.champ_file.read(self.BUFF_SIZE)
		self.get_file()

	def	receive_champ(self):
		client_champ = open("server_champ.cor", "wb")
		buffer = self.s.recv(self.BUFF_SIZE)
		while len(buffer) >= self.BUFF_SIZE:
			client_champ.write(buffer)
			buffer = self.s.recv(self.BUFF_SIZE)
		client_champ.write(buffer)
		client_champ.close()
		print("[+] Your opponent's champion has been written in server_champ.cor.")
		self.checklist["received"] = True
		time.sleep(1)
		self.s.send(b"RECEIVED")

	def	get_confirmation(self):
		confirmation = self.s.recv(8)
		if confirmation.decode(self.ENCODING_METHOD) == "RECEIVED":
			self.checklist["sent"] = True

	def	exchange_bin(self):
		client_bin = self.send_bin(PATH_TO_COREWAR)
		self.s.send(client_bin)
		server_bin = self.s.recv(64)
		if self.check_bin((server_bin, client_bin)) == -1:
			return -1
		return 0

	def	close_connections(self):
		self.s.close()
		try:
			sys.exit(0)
		except SystemExit:
			os._exit(0)

def	main(argc, argv):
	usage = "Usage: client.py host_addr\n\t`client.py 192.168.0.1`"
	if argc != 1:
		print("Wrong number of arguments.\n%s" % usage)
		sys.exit(-1)
	host = argv[0]
	valid_arg = re.match(r"^(\d{1,3}.){3}\d{1,3}$", host)
	if valid_arg is None:
		print("Not a valid argument.\n%s" % usage)
		sys.exit(-1)
	cl = Client(host)
	cl.connect()
	if cl.exchange_bin() == -1:
		print("[-] Client and Server are not running the same version of Corewar.\nExit")
		sys.exit(-1)
	print("[+] You are running the same version, the game can begin")
	print(">>GAME START<<\nYour opponent plays first !\n")
	try:
		subprocess.call(["./%s" % PATH_TO_COREWAR, "server_champ.cor", cl.filepath, "-visu"])
		os.system("read -p 'Press Enter to continue...'")
	except KeyboardInterrupt:
		print("\n[*] Interruption requested.")
		cl.close_connections()	
	cl.close_connections()

if __name__ == "__main__":
	main(len(sys.argv[1:]), sys.argv[1:])
