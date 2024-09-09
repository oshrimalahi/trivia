import socket
import sys
import os
import json

#######################
### Message Related ###
#######################

def send(sock, dict = {}):
	send_from = 0
	string_dic = ""
	if dict is not {}:
		string_dic = json.dumps(dict)
	message = (111).to_bytes(1, byteorder='big') + len(string_dic).to_bytes(4, byteorder='big') + string_dic.encode("ASCII");
	while send_from < len(message):
		send_from += sock.send(message[send_from:])
		
def recv(sock):
	id = sock.recv(1)
	length = int.from_bytes(sock.recv(4), byteorder='big')
	message = ""
	while len(message) < length:
		message += (sock.recv(length)).decode("ASCII")
	return message

def json_packet(sock):
    dict = {"username": "Tomer", 
           "password": "1235"}
    send(sock, dict)
    message = str(recv(sock))
    j = json.loads(message)
    print(str(j))
    if( str(j) == "['status', 16]"):
        cprint("message received successfully with SUCCESS code", "green", "black")
    else:
        cprint("Received wrong json, expected '{\"status\": 16}' but received '" + str(message) + "'" , "red", "black")
    exit()

#####################
### Error Related ###
#####################

def print_error_message(err_msg):
    cprint(err_msg, "red", "black")
    os.system('pause')

def connection_error_message():
	print_error_message("Could not connect to the server,\nplease check if the server is accepting connections")

def wrong_option_error():
    print_error_message("wrong choice, please select a valid option")

def port_error_message():
    print_error_message("wrong port number, port number should be 1024-65535")

#######################
### Display Related ###
#######################

# copied from https://pypi.org/project/colorama/
from colorama import init, Fore, Back, Style
init()

def cprint(msg, foreground = "black", background = "white"):
    fground = foreground.upper()
    bground = background.upper()
    style = getattr(Fore, fground) + getattr(Back, bground)
    print(style + msg + Style.RESET_ALL)

####################
### Menu Related ###
####################

def intro_screen():
	print ("\n"
	+ " ____  ____  ____  _  _  ____    __      ____  ____  ___  ____  ____  ____  \n"
	+ "(_  _)(  _ \(_  _)( \/ )(_  _)  /__\    (_  _)( ___)/ __)(_  _)( ___)(  _ \ \n"
	+ "  )(   )   / _)(_  \  /  _)(_  /(__)\     )(   )__) \__ \  )(   )__)  )   / \n"
	+ " (__) (_)\_)(____)  \/  (____)(__)(__)   (__) (____)(___/ (__) (____)(_)\_) \n\n"
    + "                                                                     V1.0.2 \n")

try:
    os.system('cls')
    intro_screen()

	# get port number
    port = input("Enter the server port number: ")
    if int(port) < 1024 or int(port) > 65535:
	    raise ValueError 
    print("\ntrying to connect...\n")

    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect(('localhost', int(port)))

    print("\nSending a message according to protocol: \n"+ 
           "code: \'111\' (1 Byte)\n" +
           "length: 24 (4 Bytes)\n" +
           "data: \'{\"username\": \"Tomer\", \"password\": \"1234\"}\' (41 Bytes)\n")
    json_packet(client_socket)

except TypeError:
	wrong_option_error()

except ValueError:
	port_error_message()

except ConnectionRefusedError:
	connection_error_message()