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
#define IP      "127.0.0.1"


int main(){

    int sockfd, len;
    struct sockaddr_in dest;
    char buffer[MAXBUF + 1] = "hello world!\n";


    /* 创建一个 socket 用于 tcp 通信 */
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket");
        exit(errno);
    }
    printf("socket created\n");


    /* 初始化服务器端（对方）的地址和端口信息 */
    bzero(&dest, sizeof(dest));
    dest.sin_family = AF_INET;
    dest.sin_port = htons(PORT);
    if (inet_aton(IP, (struct in_addr *) &dest.sin_addr.s_addr) == 0) {
        perror(IP);
        exit(errno);
    }
    printf("address created\n");


    /* 连接服务器 */
    if (connect(sockfd, (struct sockaddr *) &dest, sizeof(dest)) != 0) {
        perror("Connect ");
        exit(errno);
    }
    printf("server connected\n");

    int write_num = write(sockfd, buffer, strlen(buffer));


    int recv_len = read(sockfd, buffer, MAXBUF); // 注意这里是在 new_fd 上接收数据
    printf("%s\n",buffer);


    close(sockfd);


    return 0;
}