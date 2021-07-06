#include "philo.h"

void smart_print(char *str, t_phil *each)
{
	pthread_mutex_lock(each->check);
	printf("%lu %d %s\n", msec_c() - each->begin, each->name, str);
	pthread_mutex_unlock(each->check);
}

unsigned long	msec_c(void)
{
	struct timeval tv;

	if (gettimeofday(&tv, NULL))
		ft_error("Error: gettimeofday");
	return ((unsigned long)((tv.tv_sec * 1000) + (tv.tv_usec / 1000)));
}

void smart_usleep(unsigned long start, unsigned long wait)
{
	while ((start + wait) > msec_c())
		usleep(500);
}

void smart_die(char *str, t_phil *each)
{
	pthread_mutex_lock(each->check);
	printf("%lu, %d, %s. Out of %lu mseconds\n", msec_c() - each->begin, each->name, str, (unsigned long)(msec_c() - each->timer - each->die));
	exit(1);
}
