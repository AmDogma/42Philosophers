#include <stdio.h> // delete
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>

typedef struct	s_tab
{
	int				phil;
	int				die;
	int				eat;
	int				sleep;
	pthread_mutex_t *mut;
	pthread_t		*thread;
}	t_tab;

void			ft_error(char *message);
unsigned long	msec_c(void);
void			start_phil(t_tab *par);
