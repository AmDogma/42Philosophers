#include <stdio.h> // delete
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>

typedef struct	s_phil
{
	int				name;
	int				die;
	int				eat;
	int				sleep;
	int				times;
	int				prior;
	unsigned long	timer;
	unsigned long	begin;
	pthread_mutex_t *check;
	pthread_mutex_t	death;
	pthread_mutex_t *left;
	pthread_mutex_t *right;
	pthread_t		thread;
	pthread_t		mon;
//	struct s_info	*info;
}	t_phil;

typedef struct	s_info
{
	int				p_num;
	int				ac;
	char			**av;
	unsigned long	begin;
	pthread_mutex_t check;
	pthread_mutex_t *forks;
	t_phil			*each;
}	t_info;

void			ft_error(char *message);
unsigned long	msec_c(void);
void			start_phil(t_info *par);
void			smart_print(char *str, t_phil *each);
void			smart_usleep(unsigned long start, unsigned long wait);
void			*monitor(void *some);
