#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <time.h>

void show_info(const char *tag)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);

    struct tm tm_buf;
    localtime_r(&tv.tv_sec, &tm_buf);

    printf("[%s] PID=%d PPID=%d TIME=%02d:%02d:%02d:%03ld\n",
           tag,
           getpid(),
           getppid(),
           tm_buf.tm_hour,
           tm_buf.tm_min,
           tm_buf.tm_sec,
           tv.tv_usec / 1000);
}

int main(void)
{
    pid_t c1, c2;

    c1 = fork();
    if (c1 == 0)
    {
        show_info("child_1");
        usleep(500000);
        return 0;
    }

    c2 = fork();
    if (c2 == 0)
    {
        show_info("child_2");
        usleep(500000);
        return 0;
    }

    show_info("parent");
    usleep(100000);
    
    system("ps -x | grep child_proc");

    wait(NULL);
    wait(NULL);

    return 0;
}
