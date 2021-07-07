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
		usleep(600);
}

void *monitor(void *some)
{
	t_phil	*each;

	each = (t_phil *)some;

	while(each->name)
	{
		usleep(2000);
		pthread_mutex_lock(&each->death);
		if ((msec_c() - (unsigned long)each->timer) > (unsigned long)each->die)
		{
			pthread_mutex_lock(each->check);
			printf("%lu, %d, is died. Out of %lu mseconds\n", msec_c() - each->begin, each->name, (unsigned long)(msec_c() - each->timer - each->die));
			exit(1);
		}
		pthread_mutex_unlock(&each->death);
	}
	return NULL;
}
