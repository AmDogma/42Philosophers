#include "philo.h"

void	start_phil(t_tab *par)
{
	int	i;

	i = 0;
	par->thread = malloc(sizeof(pthread_t) * (par->phil + 1));
	par->mut = malloc(sizeof(pthread_mutex_t) * (par->phil + 1));
	while(par->phil > i)
	{
		usleep(500); // ?
		if (pthread_create(tab->(thread, NULL, &routine, &philos[i]))
			ft_error("Error: pthread_create");
		i++;
	}
}
