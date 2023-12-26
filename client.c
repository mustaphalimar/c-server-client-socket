#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{

    char *ip = "127.0.0.1";
    int port = 5566;

    int sock;
    struct sockaddr_in addr;
    socklen_t addr_size;
    char buffer[1024];
    int n;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        perror("Erreur au socket.");
        exit(1);
    }
    printf("[+]TCP server crée\n");

    memset(&addr, '\0', sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = port;
    addr.sin_addr.s_addr = inet_addr(ip);

    connect(sock, (struct sockaddr *)&addr, sizeof(addr));
    printf("Connecté au serveur\n");

    while (1)
    {
        char message[50];
        printf("Entrer le message  : ");
        // scanf("%s", &message);
        fgets(message, sizeof(message), stdin);

        bzero(buffer, 1024);

        int isBye;

        if (strcmp(message, "bye") == 0)
        {
            isBye = 1;
        }
        strcpy(buffer, message);
        printf("Client: %s\n", buffer);
        send(sock, message, strlen(message), 0);

        if (isBye == 1)
        {
            printf("Reçu 'bye' du client. Fermeture du serveur.\n");
            close(sock);
            exit(0);
        }

        bzero(buffer, 1024);
        recv(sock, buffer, sizeof(buffer), 0);
        printf("Server: %s\n", buffer);
    }

    close(sock);
    printf("Déconnecté au serveur.\n");

    return 0;
}
