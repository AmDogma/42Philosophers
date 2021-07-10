#include "philo.h"

static void	smart_print(char *str, t_phil *each)
{
	sem_wait(each->info->check);
	if (each->info->is_act == 1)
		printf("%llu %d %s\n", ms_now(each->info) - each->info->beg_time,
			each->name, str);
	sem_post(each->info->check);
}

static void	daily(t_phil *each)
{
	sem_wait(each->info->forks);
	smart_print("has taken a fork", each);

	sem_wait(each->info->forks);
	smart_print("has taken a fork", each);
	
	sem_wait(each->info->check);
	each->last_eat = ms_now(each->info);
	sem_post(each->info->check);

	smart_print("is eating", each);
	smart_usleep(ms_now(each->info), each->info->eat, each->info);

	sem_post(each->info->forks);
	sem_post(each->info->forks);

	smart_print("is sleeping", each);
	smart_usleep(ms_now(each->info), each->info->sleep, each->info);
	smart_print("is thinking", each);
	
}

static void	routine(t_phil	*each)
{
	int		i;

	i = 1;
	if (each->h_many_each == -1)
		i = 0;
	each->last_eat = ms_now(each->info);
	if (each->name % 2 == 0)
		smart_usleep(ms_now(each->info), (each->info->eat), each->info);
	while (each->h_many_each && each->info->is_act == 1)
	{
		daily(each);
		each->h_many_each -= i;
	}
	sem_wait(each->info->check);
	each->living = 0;
	sem_post(each->info->check);
	printf("\ndone PHIL N%d\n", each->name);
	exit (1);
}

void	start_phil(t_info *info)
{
	int	i;
	pid_t pid;

	i = -1;
	while (info->p_num > ++i)
	{
		pid = fork();
		if (pid < 0)
			print_err("Error: can't make fork", info);
		else if (!pid)
			routine(info->each + i);
	}
	i = -1;
	while (info->p_num > ++i)
	{
		if (pthread_create(&info->each[i].mon,
				NULL, &monitor, (void *)(info->each + i)))
			print_err("Error: pthread_create\n", info);
	}
	while (i--)
		if (pthread_join(info->each[i].mon, NULL))
			print_err("Error: pthread_join\n", info);
}
