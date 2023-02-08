#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <time.h>

time_t exam_time;
void print_time_diff(time_t start, time_t end);

static void hdl (int sig, siginfo_t *siginfo, void *context)
{
    time_t now = time(NULL);
    print_time_diff(now, exam_time);
    alarm(5);
}

void print_time_diff(time_t start, time_t end)
{
    int seconds = (int)difftime(end, start);
    int days = seconds / 86400;
    seconds %= 86400;
    int hours = seconds / 3600;
    seconds %=  3600;
    int minutes = seconds / 60;
    seconds %= 60;
    printf("%d day(s), %d hour(s), %d minute(s), %d second(s)\n", days, hours, minutes, seconds);
}

int main (int argc, char *argv[])
{
	struct sigaction act;
	memset (&act, '\0', sizeof(act));

	/* Use the sa_sigaction field because the handles has two additional parameters */

	act.sa_sigaction = &hdl;

	/* The SA_SIGINFO flag tells sigaction() to use the sa_sigaction field, not sa_handler. */

	act.sa_flags = SA_SIGINFO;

	if (sigaction(SIGALRM, &act, NULL) < 0) {
		perror ("sigaction");
		return 1;
	}
	
	struct tm exam_tm = {.tm_hour=18,       // 6pm (18 hours since midnight)
			     .tm_mday=12,       // 12th day of the month
			     .tm_mon=11,        // december (11 months since january)
			     .tm_year=118,      // 2018 (118 years since 1900)
			     .tm_isdst=0};

	exam_time = mktime(&exam_tm);
	
        raise(SIGALRM);
	
	while (1)
	    sleep(10);

	return 0;
}


