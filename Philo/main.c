#include "philo.h"

void	ft_error(char *message)
{
	int	i;

	i = 0;
	while (message + i && message[i] != '\0')
		write(1, (message + i++), 1);
	write(1, "\n", 1);
	exit (-1); // нельзя
}

int ft_num(char *num)
{
	int i;

	i = 0;
	while (*num >= '0' && *num <= '9')
	{
		i = (i * 10) + (*num - '0');
		num++;
	}
	if (*num || !i)
		ft_error("Error: Wrong arguments");
	return(i);
}

void init_phil(t_info *par, int i)
{
	//		par->each[i].info = par; // + structure
	par->each[i].name = i + 1;
	par->each[i].check = &par->check;
	pthread_mutex_init(&par->each[i].death, NULL);
	par->each[i].die = ft_num(par->av[2]);
	par->each[i].eat = ft_num(par->av[3]);
	par->each[i].sleep = ft_num(par->av[4]);
	par->each[i].times = 0;
	par->each[i].begin = par->begin;
	if (par->ac == 6)
		par->each[i].times = ft_num(par->av[5]);
	pthread_mutex_init(par->forks + i, NULL);
	par->each[i].left = par->forks + i;
	if (par->p_num != i + 1)
		par->each[i].right = par->forks + i + 1;
	else
		par->each[i].right = par->forks;
}

void parse_param(t_info *par, char **argv, int argc)
{
	int i;

	i = -1;
	if (argc < 5 || argc > 6)
		ft_error("Error: Wrong number of arguments");
	par->p_num = ft_num(argv[1]);
	par->ac = argc;
	par->av = argv;

	// можно замолочить в мейне и выход будет прост

	par->each = (t_phil *)malloc(sizeof(t_phil) * par->p_num);
	par->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * par->p_num);
	if (!par->each || !par->forks)
		ft_error("Error: malloc");

	pthread_mutex_init(&par->check, NULL);
	par->begin = msec_c();
	while (par->p_num > ++i)
		init_phil(par, i);

}

int philo(int argc, char **argv) // main
{
	t_info par;
	parse_param(&par, argv, argc);
	start_phil(&par);
	return 0;
}

int main() // del
{
	char *argv[] = {"phil", "200", "415", "200", "200", "22"};
	philo(6, argv);
	return 0;
}
