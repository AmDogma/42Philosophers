#include "philo.h"

static void	ft_exit(t_info *info)
{
	int	i;

	i = info->p_num;
	usleep(info->die);
	while (i--)
		pthread_mutex_destroy(&info->forks[i]);
	pthread_mutex_destroy(&info->check);
	if (info->forks)
		free(info->forks);
	if (info->each)
		free(info->each);
}

static int	ft_num(char *num)
{
	long long	i;

	i = 0;
	while (*num >= '0' && *num <= '9')
	{
		i = (i * 10) + (*num - '0');
		num++;
		if (i > INT_MAX || i < 0)
			return (0);
	}
	if (*num)
		return (0);
	return ((int)i);
}

static void	init_phil(t_info *info, int i)
{
	info->each[i].name = i + 1;
	info->each[i].living = 1;
	info->each[i].info = info;
	info->each[i].h_many_each = info->h_many;
	pthread_mutex_init(info->forks + i, NULL);
	info->each[i].left = info->forks + i;
	if (info->p_num != i + 1)
		info->each[i].right = info->forks + i + 1;
	else
		info->each[i].right = info->forks;
}

static int	parse_param(t_info *info)
{
	int	i;

	i = 0;
	info->is_act = 1;
	info->each = (t_phil *)malloc(sizeof(t_phil) * info->p_num);
	info->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* info->p_num);
	if (!info->each || !info->forks)
		return (print_err("Error: malloc", info));
	pthread_mutex_init(&info->check, NULL);
	while (info->p_num > i)
		init_phil(info, i++);
	info->beg_time = ms_now();
	return (0);
}

int	main(int argc, char **argv)
{
	t_info	info;

	info.h_many = -1;
	if (argc < 5 || argc > 6)
		return (print_err("Error: Wrong number of arguments", &info));
	info.p_num = ft_num(argv[1]);
	info.die = ft_num(argv[2]);
	info.eat = ft_num(argv[3]);
	info.sleep = ft_num(argv[4]);
	if (argc == 6)
		info.h_many = ft_num(argv[5]);
	if (info.p_num > 300 || !info.p_num || info.die < 60 || info.eat < 60
		|| info.sleep < 60 || !info.h_many)
		return (print_err("Error: Wrong arguments", &info));
	parse_param(&info);
	start_phil(&info);
	ft_exit(&info);
	return (0);
}
