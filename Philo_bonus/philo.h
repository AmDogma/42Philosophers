#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>
# include <fcntl.h>
# include <semaphore.h>
# include <signal.h>
# include <sys/wait.h>

typedef struct s_phil
{
	int					name;
	int					h_many_each;
	unsigned long long	last_eat;
	pthread_t			mon;
	pid_t				pid;
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
	sem_t				*forks;
	sem_t				*check;
	t_phil				*each;
}	t_info;

unsigned long long	ms_now(void);
void				start_phil(t_info *info);
int					print_err(char *str, t_info *info);
void				monitor(t_phil	*each);
void				smart_usleep(unsigned long long start, int wait);
void				*routine(void *some);

#endif
