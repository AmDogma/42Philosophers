#include "philo.h"

static void	smart_print(char *str, t_phil *each)
{
	pthread_mutex_lock(&each->info->check);
	if (each->info->is_act == 1)
		printf("%llu %d %s\n", ms_now(each->info) - each->info->beg_time,
			each->name, str);
	pthread_mutex_unlock(&each->info->check);
}

static void	sleeping(t_phil *each)
{
	smart_print("is sleeping", each);
	smart_usleep(ms_now(each->info), each->info->sleep, each->info);
	smart_print("is thinking", each);
}

static void	eat(t_phil *each)
{
	pthread_mutex_lock(each->left);
	smart_print("has taken a l_fork", each);
	pthread_mutex_lock(each->right);
	smart_print("has taken a r_fork", each);
	pthread_mutex_lock(&each->death_ch);
	each->last_eat = ms_now(each->info);
	pthread_mutex_unlock(&each->death_ch);
	smart_print("is eating", each);
	smart_usleep(ms_now(each->info), each->info->eat, each->info);
	pthread_mutex_unlock(each->left);
	pthread_mutex_unlock(each->right);
}

static void	*routine(void *some)
{
	t_phil	*each;
	int		i;

	each = (t_phil *)some;
	i = 1;
	if (each->h_many_each)
	{
		i = each->h_many_each;
		each->h_many_each = 1;
	}
	each->last_eat = ms_now(each->info);
	if (each->name % 2 == 0)
		smart_usleep(ms_now(each->info), (each->info->eat), each->info);
	while (i && each->info->is_act == 1)
	{
		eat(each);
		sleeping(each);
		i -= each->h_many_each;
	}
	return (NULL);
}

void	start_phil(t_info *info)
{
	int	i;

	i = 0;
	pthread_mutex_init(&info->the_end, NULL);
	pthread_mutex_lock(&info->the_end);
	while (info->p_num > i)
	{
		if (pthread_create(&info->each[i].thread, NULL, &routine,
				(void *)(info->each + i)) || pthread_create(&info->each[i].mon,
					NULL, &monitor, (void *)(info->each + i)))
		{
			smart_print("Error: pthread_create\n", info->each + i);
			ft_exit(info);
		}
		if (pthread_detach(info->each[i].mon)
			|| pthread_detach(info->each[i].thread))
		{
			smart_print("Error: pthread_detach\n", info->each + i);
			ft_exit(info);
		}
		i++;
	}
}
