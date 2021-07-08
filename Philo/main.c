#include "philo.h"

static int	ft_print(char *str) // убрать лишняя
{
	printf("%s\n", str);
	return(-1);
}

static int ft_num(char *num)
{
	long long i;

	i = 0;
	while (*num >= '0' && *num <= '9')
	{
		i = (i * 10) + (*num - '0');
		num++;
		if (i > 2147483647 || i < 0)
			return(0);
	}
	if (*num || !i)
		return(0);
	return ((int)i);
}

void init_phil(t_info *info, int i)
{
	info->each[i].name = i + 1;
	info->each[i].info = info;
	info->each[i].h_many_each = info->h_many;
	pthread_mutex_init(&info->each[i].death_ch, NULL);
	pthread_mutex_init(info->forks + i, NULL);
	info->each[i].left = info->forks + i;
	if (info->p_num != i + 1)
		info->each[i].right = info->forks + i + 1;
	else
		info->each[i].right = info->forks;
}

static int parse_param(t_info *info)
{
	int i;

	i = 0;
	info->is_act = 1;
	info->each = (t_phil *)malloc(sizeof(t_phil) * info->p_num);
	info->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * info->p_num);
	if (!info->each || !info->forks)
		return(ft_print("Error: malloc"));
	pthread_mutex_init(&info->check, NULL);
	while (info->p_num > i)
		init_phil(info, i++);
	info->beg_time = ms_now(info);
	return (0);
}

int philo(int argc, char **argv) // main
{
	t_info 			info;

	info.h_many = 0;
	if (argc < 5 || argc > 6)
		return(ft_print("Error: Wrong number of arguments"));
	info.p_num = ft_num(argv[1]);
	info.die = ft_num(argv[2]);
	info.eat = ft_num(argv[3]);
	info.sleep = ft_num(argv[4]);
	if (argc == 6)
		info.h_many = ft_num(argv[5]);
	if (info.p_num > 300 || !info.p_num || info.die < 60 || info.eat < 60 || info.sleep < 60 || (argc == 6 && !info.h_many))
		return(ft_print("Error: Wrong arguments"));
	if (parse_param(&info))
		return (-1);
	start_phil(&info);
	pthread_mutex_lock(&info.the_end);
	ft_exit(&info);
	pthread_mutex_destroy(&info.the_end);
	return 0;
}

int main() // del
{
	char *argv[] = {"phil", "22", "401", "200", "200", "11"};
	philo(5, argv);
	return 0;
}
