#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

char * server_filename = "/tmp/socket-server";
char * client_filename = "/tmp/socket-client";

int main(void)
{

    int s;
    char obuf[100];
    struct sockaddr_un srv_un, cli_un = { 0 };

    srv_un.sun_family = AF_UNIX;
    strncpy(srv_un.sun_path, server_filename, sizeof(srv_un.sun_path));

    cli_un.sun_family = AF_UNIX;
    strncpy(cli_un.sun_path, client_filename, sizeof(cli_un.sun_path));
    unlink(cli_un.sun_path);

    if ((s = socket(AF_UNIX, SOCK_DGRAM, 0)) == -1) {
        perror("socket server");
        exit(1);
    }

    if (bind(s, (struct sockaddr *)&cli_un, sizeof(cli_un)) == -1) {
        perror("bind client");
        exit(1);
    }

/*
    if (connect(s, (struct sockaddr *) &srv_un, sizeof(srv_un)) == -1) {
        perror("connect client");
        exit(1);
    }

    printf("Connected.\n");
    while(printf("> "), fgets(obuf, 100, stdin), !feof(stdin)) {
        if (send(s, obuf, strlen(obuf), 0) == -1) {
            perror("send");
            exit(1);
        }
        break;
    }
*/
    sprintf(obuf, "test string");
    while (1) {
        usleep(5000); //5ms
        //if (send(s, obuf, strlen(obuf), 0) == -1) {
        if (sendto(s, obuf, strlen(obuf), 0,
                 (struct sockaddr *)&srv_un, sizeof(srv_un)) == -1) {
            perror("send");
            exit(1);
        }
        printf("send to server %d bytes\n", strlen(obuf));
        
        char buf[1024] = {0};
        read(s, buf, sizeof(buf));
        printf("received: %s\n", buf);
    }
    printf("Sent successfully.\n");
    close(s);

    return 0;
}
