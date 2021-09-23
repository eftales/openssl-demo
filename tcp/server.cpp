#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <resolv.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MAXBUF  3000
#define PORT    3000



int main(){
    int sockfd, new_fd;
    socklen_t len;
    struct sockaddr_in my_addr, their_addr;
    unsigned int myport, lisnum;
    char buf[MAXBUF + 1];


    /* 创建一个 socket 用于 tcp 通信 */
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket");
        exit(errno);
    }
    printf("socket created\n");


    bzero(&my_addr, sizeof(my_addr));
    my_addr.sin_family = PF_INET;
    my_addr.sin_port = htons(PORT);
    my_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr *) &my_addr, sizeof(struct sockaddr))
            == -1) {
        perror("bind");
        exit(1);
    }
    printf("binded\n");

    if (listen(sockfd, lisnum) == -1) {
        perror("listen");
        exit(1);
    } 
    printf("begin listen\n");

    len = sizeof(struct sockaddr);
    /* 等待客户端连上来 */
    if ((new_fd = accept(sockfd, (struct sockaddr *) &their_addr, &len)) == -1) {
        perror("accept");
        exit(errno);
    } 

    int recv_len = read(new_fd, buf, MAXBUF); // 注意这里是在 new_fd 上接收数据
    printf("%s\n",buf);

    int write_len = write(new_fd, "world hello!\n", strlen("world hello!\n")); // 注意这里是在 new_fd 上接收数据

    close(new_fd);
    close(sockfd);

    return 0;
}