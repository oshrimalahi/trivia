import socket

def main():
    SERVER_ADDRESS = 'localhost'
    PORT = 8820

    try:
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
            sock.connect((SERVER_ADDRESS, PORT))
            print("Connected to server")

            rec_data = sock.recv(5).decode()
            print(rec_data)

            if rec_data == "Hello":
                sock.send(rec_data.encode())

    except socket.error as e:
        print(f"Socket error: {e}")
    except Exception as e:
        print(f"An error occurred: {e}")

if __name__ == "__main__":
    main()