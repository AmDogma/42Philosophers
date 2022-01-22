#include "philo.h"

static void	ft_exit(t_info *info)
{
	int	i;
	int	stat;

	i = 0;
	while (info->p_num > i)
	{
		waitpid(-1, &stat, WUNTRACED);
		if (WIFEXITED(stat))
		{
			stat = WEXITSTATUS(stat);
			if (stat == 2)
				break ;
			else
				i++;
		}
	}
	i = -1;
	while (info->p_num > ++i)
		kill(info->each[i].pid, SIGTERM);
	sem_close(info->forks);
	sem_close(info->check);
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
	info->each[i].info = info;
	info->each[i].h_many_each = info->h_many;
}

static int	parse_param(t_info *info)
{
	int	i;

	i = 0;
	sem_unlink("/check");
	sem_unlink("/forks");
	info->forks = sem_open("/forks", O_CREAT | O_EXCL, 0644, info->p_num);
	info->check = sem_open("/check", O_CREAT | O_EXCL, 0644, 1);
	info->each = (t_phil *)malloc(sizeof(t_phil) * info->p_num);
	if (!info->each)
		return (print_err("Error: malloc", info));
	while (info->p_num > i)
		init_phil(info, i++);
	info->beg_time = ms_now();
	return (0);
}

int	main(int argc, char **argv)
{
	t_info	info;

	info.is_act = 1;
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
