#include <stdio.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <linux/sockios.h>
#include <linux/if.h>
#include <linux/ethtool.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int doit(int fd, char * from, char * to) {
    struct ifreq ifr;
    strncpy(ifr.ifr_name, from, sizeof(from));
    strncpy(ifr.ifr_newname, to, sizeof(to));
    printf("Old name is: %s\n", ifr.ifr_name);
    printf("Changing to: %s\n", ifr.ifr_newname);
    return ioctl(fd, SIOCSIFNAME, &ifr);
}

int main(int argc, char *argv[]) {
    int i;
    int fd;
    int rc;

    if (argc < 3) {
        printf("Usage: %s <from_iface> <to_iface>\n", argv[0]);
        exit(1);
    }

    fd = socket(AF_INET, SOCK_STREAM, 0);
    rc = doit(fd, argv[1], argv[2]);
    close(fd);

    return rc;
}

