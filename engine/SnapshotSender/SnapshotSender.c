#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include "dataArr.h"
#include "SnapshotSender.h"

int udp_send_nonblocking(
    int sockfd,
    const uint8_t *data,
    size_t len,
    const char *ip,
    uint16_t port)
{
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);

    if (inet_pton(AF_INET, ip, &addr.sin_addr) != 1)
        return -1;

    ssize_t sent = sendto(
        sockfd,
        data,
        len,
        0,
        (struct sockaddr*)&addr,
        sizeof(addr)
    );

    if (sent < 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) {
            return 0; // сокет временно не готов
        }
        return -1; // ошибка
    }

    return (int)sent;
}

int create_udp_socket_nonblocking(void)
{
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0)
        return -1;

    int flags = fcntl(sock, F_GETFL, 0);
    if (flags < 0)
        return -1;

    if (fcntl(sock, F_SETFL, flags | O_NONBLOCK) < 0)
        return -1;

    return sock;
}


void snapshotSender(dataArr* arr) {
    int sock = create_udp_socket_nonblocking();
    if (sock < 0) {
        perror("socket");
        return;
    }

    uint8_t buffer[] = {1, 2, 3, 4, 5};

    

    int result = udp_send_nonblocking(
        sock,
        arr->data[0],
        102,
        "127.0.0.1",
        9000
    );

    if (result < 0)
        perror("send");
    else if (result == 0)
        printf("Socket not ready\n");
    else
        printf("Sent %d bytes\n", result);

    close(sock);
    return;
}