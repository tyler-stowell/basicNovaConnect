#include "networking.h"
#include <string.h>

ssize_t writen(int fd, const void *vptr, size_t n)
{
	size_t nleft;
	ssize_t nwritten;
	const char *ptr;

	ptr = vptr;
	nleft = n;
	while (nleft > 0)
	{
		if ( (nwritten = write(fd, ptr, nleft)) <= 0)
		{
			if (nwritten < 0 && errno == EINTR)
				nwritten = 0;
			else
				return -1;
		}

		nleft -= nwritten;
		ptr += nwritten;
	}
	return n;
}

int main (int argc, char ** argv)
{
	int listenfd, connfd;
	pid_t childpid;
	socklen_t clilen;
	struct sockaddr_in cliaddr, servaddr;

	if ( (listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		return 1;

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);

	if (bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr)))
		return 1;

	printf("Port binded\n");

	if (listen(listenfd, LISTENQ))
		return 1;

	printf("Listening...\n");

	clilen = sizeof(cliaddr);
	if ( (connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &clilen)) < 0)
		return 1;

	printf("Client connected!\n");

	ssize_t n;
	char buf[MAXLINE];

	while ( (n = read(connfd, buf, MAXLINE)) > 0)
		if (writen(connfd, buf, n) < 0)
			return 1;

	if (n < 0)
		return 1;

	close(connfd);
	return 0;
}
