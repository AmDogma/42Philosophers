#include "philo.h"

void	slee(t_phil *phil)
{
	printf("Philo N%d sleeping\n", phil->name);
	usleep(phil->sleep * 1000);
}

void	eat(t_phil *phil)
{
	pthread_mutex_lock(phil->left);
	printf("Philo N%d has take left fork\n", phil->name);
	pthread_mutex_lock(phil->right);
	printf("Philo N%d has take right fork\n", phil->name);
	if (msec_c() - phil->timer > (unsigned long)phil->die)
	{
		printf("Philo N%d DIED DIED DIED DIED DIED\n, time = %lu\n", phil->name, (msec_c() - phil->timer));
		exit(1);
	}
	else
		printf("Philo N%d NOt died, time = %lu\n", phil->name, (msec_c() - phil->timer));
	phil->timer = msec_c();
	printf("Philo N%d eating\n", phil->name);
	usleep(phil->eat * 1000);
	pthread_mutex_unlock(phil->left);
	pthread_mutex_unlock(phil->right);
}

void	think(t_phil *phil)
{
	printf("Philo N%d thinking\n", phil->name);
//	◦ timestamp_in_ms X has taken a fork ◦ timestamp_in_ms X is eating
//	◦ timestamp_in_ms X is sleeping
//	◦ timestamp_in_ms X is thinking
//	◦ timestamp_in_ms X died
}

void	*routine(void *some)
{
	t_phil	*phil;
	int		i;

	phil = (t_phil *)some;
	i = 1;
	if (phil->times)
	{
		i = phil->times;
		phil->times = 1;
	}
	phil->timer = msec_c();
	if (phil->name % 2 == 0)
		usleep((phil->eat * 1000) - 2000);
	while (i) // what first
	{
		eat(phil);
		slee(phil);
		think(phil);
		i -= phil->times;
	}
	return NULL;
}

void	start_phil(t_info *par)
{
	int	i;

	i = -1;
	while(par->p_num > ++i)
	{
		if (pthread_create(&par->each[i].thread, NULL, &routine, (void *)(par->each + i)))
			ft_error("Error: pthread_create");
//		if (pthread_detach(par->each[i].thread))
//			ft_error("Error: pthread_join");

	}
	while(--i > 0)
		if (pthread_join(par->each[i].thread, NULL))
			ft_error("Error: pthread_join"); // понять как их отпустить и чтобы программа не закончилась
//	pthread_mutex_destroy(<#pthread_mutex_t * _Nonnull#>);
}
