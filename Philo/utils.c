#include "philo.h"

void smart_print(char *str, t_phil *each)
{
	pthread_mutex_lock(&each->info->check);
	if (each->info->live == 1)
		printf("%lu %d %s\n", msec_c() - each->info->begin, each->name, str);
	pthread_mutex_unlock(&each->info->check);
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

void ft_exit(t_info *info)
{
	while(info->p_num--)
	{
		pthread_mutex_destroy(&info->forks[info->p_num]);
		pthread_mutex_destroy(&info->each[info->p_num].death_ch);
	}
	pthread_mutex_destroy(&info->check);
	free(info->forks);
	free(info->each);
}

void *monitor(void *some)
{
	t_phil	*each;

	each = (t_phil *)some;
	while(each->info->live == 1)
	{
		usleep(1000);
		pthread_mutex_lock(&each->death_ch);
		if ((msec_c() - (unsigned long)each->last_eat) > (unsigned long)each->die)
		{
			pthread_mutex_lock(&each->info->check);
			if (each->info->live)
				printf("%lu, %d, is died. Out of %lu mseconds\n", msec_c() - each->info->begin, each->name, (unsigned long)(msec_c() - each->last_eat - each->die));
			each->info->live = 0;
			pthread_mutex_unlock(&each->info->the_end);
			usleep(10000);
		}
		pthread_mutex_unlock(&each->death_ch);
	}
	return (NULL);
}
