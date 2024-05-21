#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#define ACK "ACK"
#define PORT 8080
#define MAX 10

static const int magic = 1337;
static const char* out_image = "out.jpeg";
static const char* out_stream = "rtsp://localhost:8554/stream";

int handle_socket_connection(int client) {
	static const size_t max_buf_size = 64 * 1024;

	char buf[max_buf_size];
	FILE *fd = NULL;
	unsigned int len;
	int n;

	if (send(client, &magic, sizeof(int), 0) < 0) {
		printf("failed to establish connection with client\n");
		//return 1;
		pthread_exit(1);
	}

	printf("successfully establish connection with client\n");

	if ((fd = fopen(out_image, "wb")) == NULL) {
		printf("failed to create %s file\n", out_image);
		//return 1;
		pthread_exit(1);
	}

	fclose(fd);

	int pid;
	// start child process
	if ((pid = fork()) == 0) {
		sleep(3);
		if (execlp(
			"ffmpeg", 
			"ffmpeg", 
			"-re",
			"-loop",
			"1",
			"-i", 
			out_image,
			"-f",
			"rtsp",
			out_stream,
			NULL
		) < 0) {
			printf("failed to start ffmpeg process: %s\n", strerror(errno));
			pthread_exit(1);
		}
	}

	printf("started new child process(pid=%d)\n", pid);

	for (;;) {
		if (recv(client, &len, sizeof(unsigned char) * 2, MSG_WAITALL) < 0) {
			printf("failed to receive len-message\n");
			break;
		}

		if (send(client, &magic, sizeof(int), 0) < 0) {
			printf("failed to ACK message\n");
			break;
		}

		if ((n = recv(client, buf, len + 2, MSG_WAITALL)) < 0) {
			printf("failed to read data from client: %s\n", strerror(errno));
			break;
		}

		printf("received data: %d\n", n);

		int fd = open(out_image, O_WRONLY);
		if (fd < 0) {
			printf("failed to open image file: %s\n", out_image);
			//return 1;
			pthread_exit(1);
		}

		if (write(fd, buf, n + 2) < 0) {
			printf("failed to write to the file: %s\n", strerror(errno));
		}

		close(fd);

		// sync client
		if (send(client, &magic, sizeof(int), 0) < 0) {
			printf("failed to ACK message\n");
			break;
		}
	}

	pthread_exit(0);
	//return 0;
}

int main(void) {
	ssize_t ret;
	int server_fd, connfd, len;
	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (-1 == server_fd) {
		printf("failed to init socket: %s\n", strerror(errno));
		return 1;
	}

	struct sockaddr_in server = {
		.sin_family = AF_INET,
		.sin_port = htons(PORT),
		.sin_addr = { .s_addr = htonl(INADDR_ANY) },
	};

	ret = bind(server_fd, (struct sockaddr*) &server, sizeof(server));
	if (ret != 0) {
		printf("failed to bind server: %s\n", strerror(errno));
		return 1;
	}

	ret = listen(server_fd, MAX);
	if (ret != 0) {
		printf("failed to listen on server: %s\n", strerror(errno));
		return 1;
	}

	printf("server listening...\n");

	for (;;) {
		struct sockaddr_in client = {0};
		int client_len = sizeof(client);
		int client_fd = accept(server_fd, (struct sockaddr *) &client, &client_len);
		if (-1 == client_fd) {
			printf("failed to accept client: %s\n", strerror(errno));
			return 1;
		}

		pthread_t thread;
		if (pthread_create(
			&thread,
			NULL,
			handle_socket_connection,
			(void *)client_fd
		) < 0) {
			printf("failed to create handle thread: %s\n", strerror(errno));
			close(client_fd);
			continue;
		}

		printf("started new handle thread\n");
	}
	return 0;
}
