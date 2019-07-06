#!/usr/bin/python3
# coding: utf-8

import os

class Controller:
	def	__init__(self):
		self.SERVER_PORT	=	8888
		self.BUFF_SIZE		=	1024
		self.BUFF_SIZE_CHECK=	4096
		self.ENCODING_METHOD=	"utf-8"

	def	get_filepath(self):
		valid_file = False
		while not valid_file:
			try:
				pathname = str(input())
				if pathname.endswith(".cor"):
					if not os.path.islink(pathname):
						self.champ_file = open(pathname, "rb")
						valid_file = True
						self.filepath = pathname
					else:
						print("[-] Symbolic links are not supported.\n\t>>", end="")
				else:
					print("[-] File: %s doesn't have .cor extension.\n\t>>", end="")
			except EnvironmentError:
				print("[-] No such file or directory: '%s'\n\t>>" % str(pathname), end="")
			except KeyboardInterrupt:
				print("\n[*] Disconnection requested.")
				self.close_connections()
		self._send_file()

	def	get_file(self):
		self.checklist = {
			"received": False,
			"sent": False
		}
		print("Your opponent choose his champion...", flush=True)
		while all(self.checklist.values()) is False:
			try:
				if not self.checklist["received"]:
					self.receive_champ()
				if not self.checklist["sent"]:
					self.get_confirmation()
			except KeyboardInterrupt:
				print("\n[*] Disconnection requested.")
				self.close_connections()

	def	send_bin(self, pathname):
		command = os.popen("md5 %s" % pathname)
		result = command.read()
		checksum = result.split(' ')[0]
		return bytes(checksum, 'utf-8')

	def	check_bin(self, md5sums):
		if md5sums[0] == md5sums[1]:
			return 0
		return -1
