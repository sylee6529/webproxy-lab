
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

    if ((rc = getnameinfo(sa, salen, host, hostlen, serv,
                          servlen, flags)) != 0)
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
    struct addrinfo *p, *listp, hints;
    char buf[MAXLINE];
    int rc, flags;

    if (argc != 2) {
        fprintf(stderr, "usage: %s <domain name>\n", argv[0]);
        exit(0);
    }

    memset(&hints, 0, sizeof(struct addrinfo));  // hints 구조체를 초기화
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    if ((rc = getaddrinfo(argv[1], NULL, &hints, &listp)) != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(rc));
        exit(1);
    }

    flags = NI_NUMERICHOST;  // getnameinfo()는 기본적으로 /etc/services에 찾아가서 포트번호 대신 서비스 이름을 탐색하여 리턴하는데,
                             // 이 플래그를 설정하면 탐색과정 생략, 포트번호만 간단히 리턴

    // addrinfo 구조체 리스트를 하나씩 방문하며 찾는다
    for (p = listp; p; p = p->ai_next) {
        Getnameinfo(p->ai_addr, p->ai_addrlen, buf, MAXLINE, NULL, 0, flags);
        printf("%s\n", buf);
    }

    Freeaddrinfo(listp);
    exit(0);
}
