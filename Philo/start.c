#include "philo.h"

void	sleeping(t_phil *each)
{
	smart_print("is sleeping", each);
	smart_usleep(ms_now(), (unsigned long)(each->sleep));
	smart_print("is thinking", each);
}

void	eat(t_phil *each)
{
	pthread_mutex_lock(each->left);
	smart_print("has taken a l_fork", each);
	pthread_mutex_lock(each->right);
	smart_print("has taken a r_fork", each);
	pthread_mutex_lock(&each->death_ch);
	each->last_eat = ms_now();
	pthread_mutex_unlock(&each->death_ch);
	smart_print("is eating", each);
	smart_usleep(ms_now(), (unsigned long)(each->eat));
	pthread_mutex_unlock(each->left);
	pthread_mutex_unlock(each->right);
}

void	*routine(void *some)
{
	t_phil	*each;
	int		i;

	each = (t_phil *)some;
	i = 1;
	if (each->h_many)
	{
		i = each->h_many;
		each->h_many = 1;
	}
	each->last_eat = ms_now();
	if (each->name % 2 == 0)
		smart_usleep(ms_now(), (unsigned long)(each->eat));
	while (i) // what first
	{
		eat(each);
		sleeping(each);
		i -= each->h_many;
	}
	return (NULL);
}

void	start_phil(t_info *info)
{
	int	i;

	i = -1;
	pthread_mutex_init(&info->the_end, NULL);
	pthread_mutex_lock(&info->the_end);
	while(info->p_num > ++i)
	{
		if (pthread_create(&info->each[i].thread, NULL, &routine, (void *)(info->each + i)))
			ft_error("Error: pthread_create"); // замена
		if (pthread_create(&info->each[i].monitor, NULL, &monitor, (void *)(info->each + i)))
			ft_error("Error: pthread_create"); // замена
//		if (pthread_detach(par->each[i].mon))
//			ft_error("Error: pthread_join");
	}
//	while(--i > 0)
//
////		if (pthread_detach(par->each[i].thread))
////			ft_error("Error: pthread_join");
}
