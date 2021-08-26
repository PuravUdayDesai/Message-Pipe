CC=gcc

test: main.c des_64_models.c des_64.c general_methods.c initial_permutation.c inverse_initial_permutation.c key_generation.c p_box.c s_box.c strings.c priority_queue.c queue.c hashtable.c
	$(CC) main.c des_64_models.c des_64.c general_methods.c initial_permutation.c inverse_initial_permutation.c key_generation.c p_box.c s_box.c strings.c priority_queue.c queue.c hashtable.c -o obj/main.o -lm

client: client.c des_64_models.c des_64.c general_methods.c initial_permutation.c inverse_initial_permutation.c key_generation.c p_box.c s_box.c strings.c priority_queue.c queue.c hashtable.c
	$(CC) client.c des_64_models.c des_64.c general_methods.c initial_permutation.c inverse_initial_permutation.c key_generation.c p_box.c s_box.c strings.c priority_queue.c queue.c hashtable.c -o obj/client.o -pthread -lm

server: server.c des_64_models.c des_64.c general_methods.c initial_permutation.c inverse_initial_permutation.c key_generation.c p_box.c s_box.c strings.c priority_queue.c queue.c hashtable.c
	$(CC) server.c des_64_models.c des_64.c general_methods.c initial_permutation.c inverse_initial_permutation.c key_generation.c p_box.c s_box.c strings.c priority_queue.c queue.c hashtable.c -o obj/server.o -pthread -lm