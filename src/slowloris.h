#include <stdio.h>                                                                                                                                     
#include <stdlib.h>

/*****************************************
 *                                       *
 *      Author  : Youri Klaassens        *
 *      Alias   : Xhendos                *
 *      Date    : 25th of August, 2017   *
 *                                       *
 *                                       *
 *****************************************/


char *get_message = "GET / HTTP/1.1\r\n";

/*
 * Contains the method socket()
 * Contains the method connect()
 * Contains the method send()
 * Defines SHUT_RDWR - This flag closes the socket for sending and receiving any data.
 */
#include <sys/socket.h>

/*
 * Contains the method inet_addr() - Convert string IPv4 dotted notation into binary data in network byte order.
 * contains the method htons() - Convert host to network short (Used for port number)
 */
#include <arpa/inet.h>

/*
 * Describes the structure sockaddr_in - Contains information such as IP, port and family ID.
 *
 */
#include <netinet/in.h>

/*
 * Contains the method pthread_create()
 * Contains the method pthread_join()
 */
#include <pthread.h>

/*
 * Contains the method strlen() - Returns the size of the string without null terminator \0.
 *
 */
#include <string.h>

/*
 * Contains the method time() - (Used to feed srand())
 * (Note: srand(unsigned int seed) is in library stdlib.h)
 */

/*
 * Contains the method nanosleep()
 * Describes the structure timespec
 */
#include <time.h>


#include <unistd.h>         
