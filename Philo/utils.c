#include "philo.h"

unsigned long long	ms_now(t_info *info)
{
	struct timeval		tv;
	unsigned long long	msec;

	if (gettimeofday(&tv, NULL))
	{
		pthread_mutex_lock(&info->check);
		ft_exit(info);
		info->is_act = 0;
		pthread_mutex_unlock(&info->the_end);
		usleep(10000);
	}
	msec = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (msec);
}

void	smart_usleep(unsigned long long start, int wait, t_info *info)
{
	while ((start + (unsigned long long)wait) > ms_now(info))
		usleep(500);
}

void	ft_exit(t_info *info)
{
	int	i;

	i = info->p_num;
	while (i--)
	{
		pthread_mutex_destroy(&info->forks[i]);
		pthread_mutex_destroy(&info->each[i].death_ch);
	}
	pthread_mutex_destroy(&info->check);
	free(info->forks);
	free(info->each);
}

void	*monitor(void *some)
{
	t_phil	*each;

	each = (t_phil *)some;
	while (each->info->is_act == 1)
	{
		usleep(1000);
		pthread_mutex_lock(&each->death_ch);
		if ((int)(ms_now(each->info) - each->last_eat) > each->info->die
				&& each->info->is_act == 1)
		{
			pthread_mutex_lock(&each->info->check);
			each->info->is_act = 0;
			printf("%llu %d is died. Out of %llu ms\n", ms_now(each->info)
				- each->info->beg_time, each->name,
				(ms_now(each->info) - each->last_eat - each->info->die));
			usleep(10000);
			pthread_mutex_unlock(&each->info->the_end);
			return (NULL);
		}
		pthread_mutex_unlock(&each->death_ch);
	}
	return (NULL);
}
