#include "philo.h"

void	slee(t_phil *phil)
{
	printf("Philo N%d sleeping thread = %p\n", phil->name, &phil->thread);
	usleep(phil->sleep*10000);
}

void	eat(t_phil *phil)
{
	printf("Philo N%d eating\n", phil->name);
	usleep(phil->eat*1000);
}

void	think(t_phil *phil)
{
	printf("Philo N%d thinking\n", phil->name);
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
	while (i)
	{
		think(phil);
		eat(phil);
		slee(phil);
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
		if (pthread_detach(par->each[i].thread))
			ft_error("Error: pthread_join");
//		if (pthread_join(par->each[i].thread, NULL))
//			ft_error("Error: pthread_join"); // понять как их отпустить и чтобы программа не закончилась
	}
}
