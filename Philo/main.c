#include "philo.h"

void	ft_error(char *message)
{
	int	i;

	i = 0;
	while (message + i && message[i] != '\0')
		write(1, (message + i++), 1);
	write(1, "\n", 1);
	exit (-1);
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
	if (*num)
		i = -1;
	return(i);
}

void parse_param(t_tab *par, char **argv)
{
	par->phil = ft_num(argv[1]);
	par->die = ft_num(argv[2]);
	par->eat = ft_num(argv[3]);
	par->sleep = ft_num(argv[4]);
	if (par->phil < 1 || par->sleep < 1 || par->eat < 1 || par->die < 1)
		ft_error("Error: Wrong arguments");
	if (argv[5])
		par->times = ft_num(argv[5]);
	else
		par->times = -1;
	if (argv[5] && par->times < 1)
		ft_error("Error: Wrong arguments");
}

int philo(int argc, char **argv) // main
{
	t_tab par;

	if (argc < 5 || argc > 6)
		ft_error("Error: Wrong number of arguments");
	parse_param(&par, argv);
	start_phil(&par);
	return 0;
}

int main() // del
{
	unsigned long real_time;

	real_time = msec_c();
	printf("%ld\n", real_time);
	usleep(200*1000);

	real_time = msec_c() - real_time;
	printf("%ld\n", real_time);

	char *argv[] = {"phil", "5", "800", "200", "200", NULL};
	philo(5, argv);
	return 0;
}
