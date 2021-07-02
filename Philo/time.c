#include "philo.h"

unsigned long	msec_c(void)
{
	struct timeval tv;

	if (gettimeofday(&tv, NULL))
		ft_error("Error: gettimeofday");
	//printf("%ld", (unsigned long)((tv.tv_sec * 1000) + (tv.tv_usec / 1000)));
	return ((unsigned long)((tv.tv_sec * 1000) + (tv.tv_usec / 1000)));
}
