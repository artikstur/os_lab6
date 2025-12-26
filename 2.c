#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

int my_num = 1;
int my_gen = 0;
int parent_num = 0;

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
            parent_num = my_num;
            my_num = (my_num-1) * K + (i + 2);
            my_gen++; 
            make_tree(gen_left - 1, K);
            return;
        }
    }
}

int main(int argc, char *argv[]) {
    int G = atoi(argv[1]);
    int K = atoi(argv[2]);

    make_tree(G, K);
    int t = my_num * 200;
     for (int repeat = 0; repeat < 2; repeat++) {
        for (int i = 0; i < my_gen; i++) {
            printf("  ");
        }
        printf("num=%d parent=%d pid=%d ppid=%d time=%lld t=%d (iteration %d)\n",
               my_num, parent_num, getpid(), getppid(), now_ms(), t, repeat + 1);
        usleep(t * 1000);
    }
    return 0;
}
