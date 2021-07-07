#include "philo.h"

void	sleeping(t_phil *each)
{
	smart_print("is sleeping", each);
	smart_usleep(msec_c(), (unsigned long)(each->sleep));
	smart_print("is thinking", each);
}

void	eat(t_phil *each)
{
	pthread_mutex_lock(each->left);
	smart_print("has taken a l_fork", each);
	pthread_mutex_lock(each->right);
	smart_print("has taken a r_fork", each);
	smart_print("is eating", each);

	pthread_mutex_lock(&each->death);
	each->timer = msec_c();
	pthread_mutex_unlock(&each->death);

	smart_usleep(msec_c(), (unsigned long)(each->eat));
	pthread_mutex_unlock(each->left);
	pthread_mutex_unlock(each->right);
}

void	*routine(void *some)
{
	t_phil	*each;
	int		i;

	each = (t_phil *)some;
	i = 1;
	if (each->times)
	{
		i = each->times;
		each->times = 1;
	}
	each->timer = msec_c();
	if (each->name % 2 == 0)
		smart_usleep(msec_c(), (unsigned long)(each->eat));
	while (i) // what first
	{
		eat(each);
		sleeping(each);
		i -= each->times;
	}
	pthread_mutex_lock(&each->death);
	return NULL;
}

void	start_phil(t_info *par)
{
	int	i;

	i = -1;
	while(par->p_num > ++i)
	{
		// нужно тут сделать смарт выход
		if (pthread_create(&par->each[i].thread, NULL, &routine, (void *)(par->each + i)))
			ft_error("Error: pthread_create"); // замена
		if (pthread_create(&par->each[i].mon, NULL, &monitor, (void *)(par->each + i)))
			ft_error("Error: pthread_create"); // замена
	}
	while(--i > 0)
	{
		if (pthread_join(par->each[i].thread, NULL))
			ft_error("Error: pthread_join");
	}
//	pthread_mutex_destroy(<#pthread_mutex_t * _Nonnull#>);
}
