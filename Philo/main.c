#include "philo.h"

void	ft_error(char *message) // убрать
{
	int	i;

	i = 0;
	while (message + i && message[i] != '\0')
		write(1, (message + i++), 1);
	write(1, "\n", 1);
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

void init_phil(t_info *info, int i)
{
	info->each[i].name = i + 1;
	pthread_mutex_init(&info->each[i].death_ch, NULL);
	info->each[i].info = info;
	info->each[i].die = ft_num(info->av[2]);
	info->each[i].eat = ft_num(info->av[3]);
	info->each[i].sleep = ft_num(info->av[4]);
	info->each[i].h_many = 0;
	if (info->ac == 6)
		info->each[i].h_many = ft_num(info->av[5]);
	pthread_mutex_init(info->forks + i, NULL);
	info->each[i].left = info->forks + i;
	if (info->p_num != i + 1)
		info->each[i].right = info->forks + i + 1;
	else
		info->each[i].right = info->forks;
}

void parse_param(t_info *info, char **argv, int argc)
{
	int i;

	i = -1;
	info->p_num = ft_num(argv[1]);
	info->ac = argc;
	info->av = argv;
	info->live = 1;
	info->each = (t_phil *)malloc(sizeof(t_phil) * info->p_num);
	info->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * info->p_num);
	if (!info->each || !info->forks)
		ft_error("Error: malloc");
	pthread_mutex_init(&info->check, NULL);
	info->begin = msec_c();
	while (info->p_num > ++i)
		init_phil(info, i);

}

int philo(int argc, char **argv) // main
{
	t_info par;

	if (argc < 5 || argc > 6)
		ft_error("Error: Wrong number of arguments");
	
	parse_param(&par, argv, argc);
	start_phil(&par);
	pthread_mutex_lock(&par.the_end);
	ft_exit(&par);
	pthread_mutex_destroy(&par.the_end);
	return 0;
}

int main() // del
{
	char *argv[] = {"phil", "2", "400", "200", "200", "11"};
	philo(6, argv);

	return 0;
}
