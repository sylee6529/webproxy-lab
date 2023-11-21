
#include "csapp.h"

/* getnameinfo - sa에 대응되는 host와 service String으로 변환하고
 *               이를 host와 service 버퍼로 복사하는 함수
 * sa: salen 크기의 소켓 주소 구조체를 가르킴
 * host: hostlen 길이의 버퍼를 가르킴
 * service: servlen 길이의 버퍼를 가르킴
 */
void Getnameinfo(const struct sockaddr *sa, socklen_t salen, char *host,
                 size_t hostlen, char *serv, size_t servlen, int flags) {
    int rc;

    if ((rc = getnameinfo(sa, salen, host, hostlen, serv, servlen, flags)) != 0)
        gai_error(rc, "Getnameinfo error");
}

/* 소켓 구조체의 연결 리스트를 반환 */
void Freeaddrinfo(struct addrinfo *res) {
    freeaddrinfo(res);
}

/* error code를 리턴했을 때, 코드를 메시지 String으로 변환하여 출력 */
void gai_error(int code, char *msg) {
    fprintf(stderr, "%s: %s\n", msg, gai_strerror(code));
    exit(0);
}

/* NSLOOKUP과 유사한 동작을 하는 코드 - 도메인 이름을 입력하면 IP 주소를 출력 */
int main(int argc, char **argv) {
    struct addrinfo *p, *listp, hints;  // hints는 선택적으로 사용 가능한 인자, getaddrinfo가 리턴하는 소켓 주소 리스트의 상세한 제어를 위한 구조체
    char buf[MAXLINE];
    int rc, flags;

    if (argc != 2) {
        fprintf(stderr, "usage: %s <domain name>\n", argv[0]);
        exit(0);
    }

    memset(&hints, 0, sizeof(struct addrinfo));  // hints 구조체를 초기화
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;  // SOCK_STREAM 으로 설정하면 리스트가 각 고유의 주소에 대해 자신의 소켓 주소가
                                      // 연결의 끝점으로 사용될 수 있는 addrinfo 구조체는 최대 한 개로 제한
    if ((rc = getaddrinfo(argv[1], NULL, &hints, &listp)) != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(rc));
        exit(1);
    }

    flags = NI_NUMERICHOST;  // 플래그를 NI_NEMERICHOST로 설정하면, addrinfo의 service 인자는 포트번호여야 한다

    // addrinfo 구조체 리스트를 하나씩 방문하며 찾는다
    for (p = listp; p; p = p->ai_next) {
        Getnameinfo(p->ai_addr, p->ai_addrlen, buf, MAXLINE, NULL, 0, flags);
        printf("%s\n", buf);
    }

    Freeaddrinfo(listp);
    exit(0);
}
