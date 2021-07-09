#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

typedef struct s_phil
{
	int					name;
	int					h_many_each;
	int					living;
	unsigned long long	last_eat;
	pthread_mutex_t		death_ch;
	pthread_mutex_t		*left;
	pthread_mutex_t		*right;
	pthread_t			thread;
	pthread_t			mon;
	struct s_info		*info;
}	t_phil;

typedef struct s_info
{
	int					p_num;
	int					die;
	int					eat;
	int					sleep;
	int					h_many;
	int					is_act;
	unsigned long long	beg_time;
	pthread_mutex_t		*forks;
	pthread_mutex_t		check;
	pthread_mutex_t		the_end;
	t_phil				*each;
}	t_info;

unsigned long long	ms_now(t_info *info);
void				start_phil(t_info *info);
int					print_err(char *str, t_info *info);
void				*monitor(void *some);
void				smart_usleep(unsigned long long start, int wait,
						 t_info *info);

#endif
