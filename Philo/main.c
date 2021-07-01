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
	while (*num >= 0 && *num <= 9)
		i = i * 10 + i;
	if (*num)
		i = -1;
	return(i);
}

int main(int argc, char **argv)
{
	t_tab par;

	if (argc != 5)
		ft_error("Error: Wrong number of arguments");
	par.phil = ft_num(argv[1]);
	par.die = ft_num(argv[2]);
	par.eat = ft_num(argv[3]);
	par.sleep = ft_num(argv[4]);
	if (par.phil < 1 || par.sleep < 1 || par.eat < 1 || par.die < 1)
		ft_error("Error: Wrong arguments");
	return 0;
}
