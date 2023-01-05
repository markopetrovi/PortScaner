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

#include "IPSocket.h"
#include <signal.h>

int tcp_socket;
void handler(int signum)
{
	close(tcp_socket);
	tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
}
int main()
{
	struct sigaction sig;
	sig.sa_handler = &handler;
	sigaction(SIGALRM, (const struct sigaction *restrict) &sig, NULL);
	
	char ipaddress[16];
	unsigned int port;
	
	Printf("Enter IP address:");
	read(0, ipaddress, 16);
	Printf("Enter starting port:");
	scanf("%u", &port);
	
	struct sockaddr_in addr;
	inet_aton(ipaddress, (struct in_addr *) &addr.sin_addr);
	addr.sin_port = htons(port);
	addr.sin_family = AF_INET;
	
	tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
	socklen_t addrlen = sizeof(addr);
	
	int stat = -1;
	while(stat != 0 && port < 65536)
	{
		port++;
		addr.sin_port = htons(port);
		alarm(1);
		stat = Connect(tcp_socket, (struct sockaddr *) &addr, addrlen);
		alarm(0);
	}
	alarm(0);
	printf("%d%s", port, "\n");
	//close(tcp_socket);
	//return 0;
	
	//Connect(tcp_socket, (struct sockaddr *) &addr, addrlen);
	fcntl(tcp_socket, F_SETFL, O_NONBLOCK);
	char c[100];
	Printf("Start!");
	
	int count, i = 1;
	while(true)
	{
		count = read(0, c, 100);
		Write(tcp_socket, c, count);
		
		printf("%d", i);
		Printf(". packet sent");
		
		count = read(tcp_socket, c, 100);
		Write(1, c, count);
		i++;
	}
	
	close(tcp_socket);
	
	return 0;
}
