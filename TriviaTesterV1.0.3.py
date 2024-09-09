import json
import socket
import math
import sys
import os

##############
### Consts ###
##############

FIRST_ARG_IDX = 1

# Packet Menu Options
LOGIN = 1
SIGNUP = 2
LOGOUT = 3

#######################
### Message Related ###
#######################

def send(sock, dict = {}):
	send_from = 0
	string_dic = ""
	if dict is not {}:
		string_dic = json.dumps(dict)
	print("Enter the message code (1 Byte): ")
	id = (int)(1).to_bytes(1, byteorder='big')
	message = id + len(string_dic).to_bytes(4, byteorder='big') + string_dic.encode("ASCII");
	print(message)
	while send_from < len(message):
		send_from += sock.send(message[send_from:])
		
def recv(sock):
	id = sock.recv(1)
	length = int.from_bytes(sock.recv(4), byteorder='big')
	message = ""
	while len(message) < length:
		message += (sock.recv(length)).decode("ASCII")
	return message

def signup(sock):
	
	##### Mandatory user attributes ####
	username = input("Enter username: ")
	password = input("Enter password: ")
	email = input("Enter email: ")

	##### Bonus attributes for V1.0.0 (not mandatory) #####
	# birth = input("Enter birthdate (dd/MM/yyyy): ")
	# phone = input("Enter phone number: ")
	# address = input("Enter address: ")
	
	dic = {"username": username, 
		   "password": password, 
		   "email": email, 
		#    "birthdate": birth, 
		#    "phone": phone, 
		#    "address": address
		}

	send(sock, dic)

def login(sock):
	
	dic = {"username": "aaa", 
		   "password": "111"}
	send(sock, dic)

def logout(sock):
	send(sock)

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

####################
### Menu Related ###
####################

def intro_screen():
	print ("\n"
	+ " ____  ____  ____  _  _  ____    __      ____  ____  ___  ____  ____  ____  \n"
	+ "(_  _)(  _ \(_  _)( \/ )(_  _)  /__\    (_  _)( ___)/ __)(_  _)( ___)(  _ \ \n"
	+ "  )(   )   / _)(_  \  /  _)(_  /(__)\     )(   )__) \__ \  )(   )__)  )   / \n"
	+ " (__) (_)\_)(____)  \/  (____)(__)(__)   (__) (____)(___/ (__) (____)(_)\_) \n")

def print_select_test_menu():
    cprint("Please choose what to send: \n", "black", "white")
    cprint("[1] --- login request ", "blue", "black")
    cprint("[2] --- signup request ", "magenta", "black")
    cprint("[3] --- signout request ", "green", "black")

def send_packet(option, client_socket):
    if option == LOGIN:
        login(client_socket)
    elif option == SIGNUP:
        signup(client_socket)
    elif option == LOGOUT:
        login(client_socket)
    else:
        raise TypeError

try:
    os.system('cls')
    intro_screen()

	# get port number
    port = "8820"
    if int(port) < 1024 or int(port) > 65535:
	    raise ValueError 
    print("\ntrying to connect...\n")

    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect(('localhost', int(port)))

    # connection established
    print_select_test_menu()
    choice = 1
    send_packet(choice, client_socket)

    print("\nPacket sent. Waiting for server response...\n")
    
	# message sent, waiting for server's response
    message = str(recv(client_socket))
    cprint("Received response from server:\n" + message, "yellow", "black")

except TypeError:
	wrong_option_error()

except ValueError:
	port_error_message()

except ConnectionRefusedError:
	connection_error_message()
	