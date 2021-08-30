build:
	g++ server.c -lssl -lcrypto -o server
	g++ client.c -lssl -lcrypto -o client

gen:
	bash ./gen.sh

run:
	./server 7838 1 server.crt server_rsa_private.pem.unsecure
	./client 127.0.0.1 7838 client.crt client_rsa_private.pem.unsecure


clean:
	-rm server client
	-rm *.csr *.crt *.srl *.pem 	*.unsecure
