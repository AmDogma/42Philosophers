#include <stdio.h> // delete
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>

typedef struct	s_phil
{
	int				name;
	int				die;  // unsigned long
	int				eat;  // unsigned long
	int				sleep;  // unsigned long
	int				h_many;
	unsigned long	last_eat;
	pthread_mutex_t	death_ch;
	pthread_mutex_t *left;
	pthread_mutex_t *right;
	pthread_t		thread;
	pthread_t		monitor;
	struct s_info	*info;
}	t_phil;

typedef struct	s_info
{
	int				p_num;
	int				live;
	int				ac; // можно удалить если все будет в инфо
	char			**av; // можно удалить если все будет в инфо
	unsigned long	begin;
	pthread_mutex_t *forks;
	pthread_mutex_t check;
	pthread_mutex_t the_end;
	t_phil			*each;
}	t_info;

void			ft_error(char *message);
unsigned long	ms_now(void);
void			start_phil(t_info *par);
void			smart_print(char *str, t_phil *each);
void			smart_usleep(unsigned long start, unsigned long wait);
void			*monitor(void *some);
void			ft_exit(t_info *par);
