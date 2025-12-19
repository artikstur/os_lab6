#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

int my_num = 1;

long long now_ms() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (long long)tv.tv_sec * 1000LL + tv.tv_usec / 1000;
}

void make_tree(int gen_left, int K) {
    if (gen_left == 0) return;

    for (int i = 0; i < K; i++) {
        pid_t pid = fork();

        if (pid == 0) {
            my_num = my_num * K + (i + 1);
            make_tree(gen_left - 1, K);
            return;
        }
    }
}

int main(int argc, char *argv[]) {
    int G = atoi(argv[1]);
    int K = atoi(argv[2]);

    make_tree(G, K);

    while (1) {
        int t = my_num * 200;
        printf("num=%d pid=%d ppid=%d time=%lld t=%d\n",
               my_num, getpid(), getppid(), now_ms(), t);
        usleep(t * 1000);
    }
}
