/* Copyright (C) Marko Petrovic 2023
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 2 of the License, or 
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
* or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License along with this program. 
* If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef IP_SOCKET_H
#define IP_SOCKET_H

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <stdbool.h>

#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
/*
Description:
	Printf()	- Normal printf() function, but with added newline at the end of writing and stdout buffer flushing
	Rest functions are equivalent of normal syscalls, but with error handling:
	Write(2)	- write(2) syscall sa ispisivanjem poruke o gresci na stdout ako do nje dodje.
	Bind(2)		- bind(2) syscall sa ispisivanjem poruke o gresci na stdout ako do nje dodje.
	Listen(2)	- listen(2) syscall sa ispisivanjem poruke o gresci na stdout ako do nje dodje.
	Accept(2)	- accept(2) syscall sa ispisivanjem poruke o gresci na stdout ako do nje dodje.
	Connect(2)	- connect(2) syscall sa ispisivanjem poruke o gresci na stdout ako do nje dodje.
*/
int Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
	int stat = connect(sockfd, addr, addrlen);
	if(stat == -1)
	{
		printf("%s", "connect(");
		printf("%d", sockfd);
		printf("%s", ", ...) FAILED: ");
		printf("%d", errno);
		printf("%s", "\n");
		fflush(stdout);
	}
	return stat;
}
int Accept(int sockfd, struct sockaddr *restrict addr, socklen_t *restrict addrlen)
{
	int fd = accept(sockfd, addr, addrlen);
	if(fd == -1)
	{
		printf("%s", "accept(");
		printf("%d", sockfd);
		printf("%s", ", ...) FAILED: ");
		printf("%d", errno);
		printf("%s", "\n");
		fflush(stdout);
	}
	return fd;
}
int Write(int fd, const void *buf, size_t count)
{
	int stat = write(fd, buf, count);
	if (stat == -1)
	{
		printf("%s", "write(");
		printf("%d", fd);
		printf("%s", ", ");
		printf("%s", buf);
		printf("%s", ", ");
		printf("%d", count);
		printf("%s", ") FAILED: ");
		printf("%d", errno);
		printf("%s", "\n");
		fflush(stdout);
	}
}
int Printf(void *data)
{
	int num = printf("%s", data);
	printf("%s", "\n");
	fflush(stdout);
	return num;
}
int Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
	int stat = bind(sockfd, addr, addrlen);
	if(stat == -1)
	{
		printf("%s", "bind(");
		printf("%d", sockfd);
		printf("%s", ", ...) FAILED: ");
		printf("%d", errno);
		printf("%s", "\n");
		fflush(stdout);
	}
}
int Listen(int sockfd, int backlog)
{
	int stat = listen(sockfd, backlog);
	if (stat == -1)
	{
		printf("%s", "listen(");
		printf("%d", sockfd);
		printf("%s", ", ");
		printf("%d", backlog);
		printf("%s", ") FAILED: ");
		printf("%d", errno);
		printf("%s", "\n");
		fflush(stdout);
	}
	return stat;
}

#endif
