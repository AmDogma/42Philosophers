#include "philo.h"

unsigned long long	ms_now(t_info *info)
{
	struct timeval		tv;
	unsigned long long	msec;

	msec = info->beg_time;
	gettimeofday(&tv, NULL);
	msec = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (msec);
}

void	smart_usleep(unsigned long long start, int wait, t_info *info)
{
	sem_wait(info->check);
	if (info->is_act == 0)
		start = ms_now(info);
	sem_post(info->check);
	while ((start + (unsigned long long)wait) > ms_now(info))
		usleep(500);
}

int	print_err(char *str, t_info *info)
{
	sem_wait(info->check);
	info->is_act = 0;
	sem_post(info->check);
	printf("%s\n", str);
	return (-1);
}

void	*monitor(void *some)
{
	t_phil	*each;

	each = (t_phil *)some;
	while (each->info->is_act == 1 && each->living == 1)
	{
		usleep(1000);
		sem_wait(each->info->check);
		if ((int)(ms_now(each->info) - each->last_eat) > each->info->die
				&& each->info->is_act == 1 && each->living == 1)
		{
			each->info->is_act = 0;
			printf("%llu %d is died. Out of %llu ms\n", ms_now(each->info)
				- each->info->beg_time, each->name,
				(ms_now(each->info) - each->last_eat - each->info->die));
		}
		sem_post(each->info->check);
	}
	return (NULL);
}
