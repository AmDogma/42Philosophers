#include "philo.h"

static void	smart_print(char *str, t_phil *each)
{
	pthread_mutex_lock(&each->info->check);
	if (each->info->is_act == 1)
		printf("%llu %d %s\n", ms_now() - each->info->beg_time,
			each->name, str);
	pthread_mutex_unlock(&each->info->check);
}

static void	action(t_phil *each)
{
	pthread_mutex_lock(each->left);
	smart_print("has taken a l_fork", each);
	pthread_mutex_lock(each->right);
	smart_print("has taken a r_fork", each);
	pthread_mutex_lock(&each->info->check);
	each->last_eat = ms_now();
	pthread_mutex_unlock(&each->info->check);
	smart_print("is eating", each);
	smart_usleep(ms_now(), each->info->eat);
	pthread_mutex_unlock(each->left);
	pthread_mutex_unlock(each->right);
	smart_print("is sleeping", each);
	smart_usleep(ms_now(), each->info->sleep);
	smart_print("is thinking", each);
}

static void	*routine(void *some)
{
	t_phil	*each;
	int		i;

	each = (t_phil *)some;
	i = 1;
	if (each->h_many_each == -1)
		i = 0;
	each->last_eat = ms_now();
	if (each->name % 2 == 0)
		smart_usleep(ms_now(), (each->info->eat));
	while (each->h_many_each && each->info->is_act == 1)
	{
		action(each);
		each->h_many_each -= i;
	}
	pthread_mutex_lock(&each->info->check);
	each->living = 0;
	pthread_mutex_unlock(&each->info->check);
	return (NULL);
}

void	start_phil(t_info *info)
{
	int	i;

	i = -1;
	while (info->p_num > ++i)
	{
		if (pthread_create(&info->each[i].thread, NULL, &routine,
				(void *)(info->each + i)) || pthread_create(&info->each[i].mon,
				NULL, &monitor, (void *)(info->each + i)))
			print_err("Error: pthread_create\n", info);
		if (pthread_detach(info->each[i].thread))
			print_err("Error: pthread_detach\n", info);
	}
	while (i--)
		if (pthread_join(info->each[i].mon, NULL))
			print_err("Error: pthread_join\n", info);
}
