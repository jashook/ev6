#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>

int main()
{

   int status;
   int socketd; 
  
   struct addrinfo host_information;   // holds the information for the host

   struct addrinfo* host_information_ll;  // linked list of host_informations

   memset(&host_information, 0, sizeof host_information); // zero out the struct

   host_information.ai_family = AF_UNSPEC;
   host_information.ai_socktype = SOCK_STREAM;

   status = getaddrinfo("www.google.com", "80", &host_information, &host_information_ll);

   if (status != 0)
   {
       printf("%s", gai_strerror(status));
   }

   socketd = socket(host_information_ll->ai_family, host_information_ll->ai_socktype, host_information_ll->ai_protocol);

   status = connect(socket, host_information_ll->ai_addr, host_information_ll->ai_addrlen);

   char* _Message = "GET / HTTP/1.1\nhost: www.google.com\n\n";

   int len;

   ssize_t bytes_sent;

   len = strlen(_Message);

   bytes_sent = send(socket, _Message, len, 0);

   ssize_t bytes_recieved;
   
   char incoming_data_buffer[1000];

   bytes_recieved = recv(socketd, incoming_data_buffer, 1000, 0);

   // If no data arrives, the program will just wait here until some data arrives.

   if (bytes_recieved == 0) printf("host shut down.\n");

   if (bytes_recieved == -1) printf("recieve error!\n");

   printf(bytes_recieved);
   printf(" bytes recieved :\n");
   printf(incoming_data_buffer);

   return 0;

}
