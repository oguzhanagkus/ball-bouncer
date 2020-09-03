main: server.o client.o

server.o: server.c
	gcc server.c -o server -Wall -Wextra

client.o: client.c
	gcc client.c -o client -Wall -Wextra

run_server:
	./server

run_client:
	./client

clean:
	rm server client

leak_test_server:
	valgrind --leak-check=full --show-leak-kinds=all ./server

leak_test_client:
	valgrind --leak-check=full --show-leak-kinds=all ./client
