#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

char * server_filename = "/tmp/socket-server";

int main(void)
{
    int s;
    struct sockaddr_un srv_un = {0};

    if ((s = socket(AF_UNIX, SOCK_DGRAM, 0)) == -1) {
        perror("socket server");
        exit(1);
    }

    srv_un.sun_family = AF_UNIX;
    strncpy(srv_un.sun_path, server_filename, sizeof(srv_un.sun_path));
    /*If you leave the file behind when you're finished, or perhaps crash after binding, the next bind will fail
     *     / with "address in use". Which just means, the file is already there.*/
    unlink(srv_un.sun_path);

    if (bind(s, (struct sockaddr *)&srv_un, sizeof(srv_un)) == -1) {
        perror("bind server");
        exit(1);
    }
    socklen_t addre_len;
    struct sockaddr_un remote_un = {0};
    int ret;
    char buf[1024] = {0};
    for(;;) {
        memset(buf, 0, sizeof(buf));
        //read(s, buf, sizeof(buf));
        ret = recvfrom(s, buf, sizeof(buf), 0,
                (struct sockaddr*)&remote_un, &addre_len);
        if (ret == -1) {
            perror("error when recvfrom, ");
        }
        printf("RECEIVED: %s\n", buf);
        sprintf(buf, "Got it!\n");
        ret = sendto(s, buf, sizeof(buf), 0,
                (struct sockaddr*)&remote_un, addre_len); 
        usleep(50000);
    }

    close(s);

    return 0;
}
