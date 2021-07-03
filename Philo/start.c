#include "philo.h"

void	sleeping(t_tab *par)
{
	printf("sleeping!\n");
}

void	eat(t_tab *par)
{
	printf("eat!\n");
	usleep(par->eat*1000);
}

void	think(t_tab *par)
{
	printf("think!\n");
}

void	*routine(void *some)
{
	t_tab	*par;

	par = (t_tab *)some;
	while (1)
	{
		think(par);
		sleeping(par);
		eat(par);
	}
//	printf("Tread!\n");
	return NULL;
}

void	start_phil(t_tab *par)
{
	int	i;

	i = 0;
	par->thread = (pthread_t *)malloc(sizeof(pthread_t) * (par->phil + 1)); // +1 ?
	par->mut = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * (par->phil + 1)); // +1 ?
	if (!(par->thread) || !(par->mut))
		ft_error("Error: malloc");
	while(par->phil > i)
	{
		//usleep(500); // ?
		if (pthread_create((par->thread) + i, NULL, &routine, (void *)par))
			ft_error("Error: pthread_create");
		if (pthread_join(par->thread[i], NULL))
			ft_error("Error: pthread_join");
		i++;
	}
}
