#include "philo.h"

unsigned long long	ms_now(void)
{
	struct timeval		tv;
	unsigned long long	msec;

	gettimeofday(&tv, NULL);
	msec = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (msec);
}

void	smart_usleep(unsigned long long start, int wait)
{
	while ((start + (unsigned long long)wait) > ms_now())
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

void	monitor(t_phil	*each)
{
	sem_wait(each->info->check);
	if (pthread_create(&each->mon,
			NULL, &routine, (void *)(each)))
		print_err("Error: pthread_create\n", each->info);
	if (pthread_detach(each->mon))
		print_err("Error: pthread_join\n", each->info);
	while (each->info->is_act == 1)
	{
		usleep(1000);
		sem_wait(each->info->check);
		if ((int)(ms_now() - each->last_eat) > each->info->die
			&& each->info->is_act == 1)
		{
			each->info->is_act = 0;
			printf("%llu %d is died. Out of %llu ms\n", ms_now()
				- each->info->beg_time, each->name,
				(ms_now() - each->last_eat - each->info->die));
			sem_close(each->info->check);
			exit (2);
		}
		else
			sem_post(each->info->check);
	}
	exit (1);
}
