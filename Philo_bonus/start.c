#include "philo.h"

static void	smart_print(char *str, t_phil *each)
{
	sem_wait(each->info->check);
	printf("%llu %d %s\n", ms_now() - each->info->beg_time, each->name, str);
	sem_post(each->info->check);
}

static void	daily(t_phil *each)
{
	sem_wait(each->info->forks);
	smart_print("has taken a fork", each);
	sem_wait(each->info->forks);
	smart_print("has taken a fork", each);
	sem_wait(each->info->check);
	each->last_eat = ms_now();
	sem_post(each->info->check);
	smart_print("is eating", each);
	smart_usleep(ms_now(), each->info->eat);
	sem_post(each->info->forks);
	sem_post(each->info->forks);
	smart_print("is sleeping", each);
	smart_usleep(ms_now(), each->info->sleep);
	smart_print("is thinking", each);
}

void	*routine(void	*some)
{
	int		i;
	t_phil	*each;

	each = (t_phil *)some;
	i = 1;
	if (each->h_many_each == -1)
		i = 0;
	each->last_eat = ms_now();
	sem_post(each->info->check);
	if (each->name % 2 == 0)
		smart_usleep(ms_now(), (each->info->eat));
	while (each->h_many_each && each->info->is_act == 1)
	{
		daily(each);
		each->h_many_each -= i;
	}
	sem_wait(each->info->check);
	each->info->is_act = 0;
	sem_post(each->info->check);
	return (NULL);
}

void	start_phil(t_info *info)
{
	int		i;
	pid_t	pid;

	i = -1;
	sem_wait(info->check);
	while (info->p_num > ++i)
	{
		pid = fork();
		if (pid < 0)
			print_err("Error: can't make fork", info);
		else if (pid == 0)
		{
			monitor(info->each + i);
			break ;
		}
		else
			info->each[i].pid = pid;
	}
	sem_post(info->check);
}
