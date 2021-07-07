#include "philo.h"

void smart_print(char *str, t_phil *each)
{
	pthread_mutex_lock(&each->info->check);
	if (each->info->live == 1)
		printf("%lu %d %s\n", ms_now() - each->info->begin, each->name, str);
	pthread_mutex_unlock(&each->info->check);
}

unsigned long	ms_now(void)
{
	struct timeval tv;

	if (gettimeofday(&tv, NULL))
		ft_error("Error: gettimeofday");
	return ((unsigned long)((tv.tv_sec * 1000) + (tv.tv_usec / 1000)));
}

void smart_usleep(unsigned long start, unsigned long wait)
{
	while ((start + wait) > ms_now())
		usleep(500);
}

void ft_exit(t_info *info)
{
	int	i;

	i = info->p_num;
	while(i--)
	{
		pthread_mutex_destroy(&info->forks[i]);
		pthread_mutex_destroy(&info->each[i].death_ch);
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
		if ((ms_now() - (unsigned long)each->last_eat) > (unsigned long)each->die)
		{
			pthread_mutex_lock(&each->info->check);
			if (each->info->live)
				printf("%lu %d is died. Out of %lu mseconds\n", ms_now() - each->info->begin, each->name, (unsigned long)(ms_now() - each->last_eat - each->die));
			each->info->live = 0;
			pthread_mutex_unlock(&each->info->the_end);
			usleep(10000);
		}
		pthread_mutex_unlock(&each->death_ch);
	}
	return (NULL);
}
