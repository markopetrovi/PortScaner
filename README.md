# PortScaner
IPv4 fast port scaner.
# INSTALL
Compile with 'gcc portscan.c -o portscan' or download pre-built binary executable portscan.

No special dependencies. As with all dynamically linked programs, just glibc is needed (libc.so.6) for program to start.

# Overview
Program first asks for IPv4 address of the device who's port will be scaned. Next the user should enter the starting port from which to scan.

Program will then print a bunch of Connect errors for closed ports until it gets to the open port on which it will establish connection. Then the user has the ability to send data to that port by writing to stdin and the data that server sends to the user will be printed on stdout.
