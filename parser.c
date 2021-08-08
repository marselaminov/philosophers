#include "philo.h"

int	ft_not_digit(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (1);
		i++;
	}
	return (0);
}

int	ft_atoi(char *str)
{
	int		res;
	int		sign;
	int		i;

	res = 0;
	sign = 0;
	i = 0;
	while ((str[i] == ' ') || (str[i] == '\t') || (str[i] == '\n')
		|| (str[i] == '\v') || (str[i] == '\r') || (str[i] == '\f'))
		i++;
	if (str[i] == '-')
		sign = 1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] && (str[i] >= '0') && (str[i] <= '9'))
	{
		res = res * 10;
		res += (int)str[i] - '0';
		i++;
	}
	if (sign == 1)
		return (-res);
	else
		return (res);
}

int	ft_correct_args(char **av)
{
	int	i;
	int	n;

	i = 0;
	while (av[++i])
	{
		if (ft_not_digit(av[i]))
			return (0);
		n = ft_atoi(av[i]);
		if (n < 0)
			return (0);
	}
	return (1);
}

int	ft_parser(char *av[], t_param *prm)
{
	if (!ft_correct_args(av))
		return (0);
	prm->philos_num = ft_atoi(av[1]);
	if (!prm->philos_num || prm->philos_num > 200)
		return (0);
	prm->time_to_die = ft_atoi(av[2]);
	prm->time_to_eat = ft_atoi(av[3]);
	prm->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		prm->loop_eat = ft_atoi(av[5]);
	else
		prm->loop_eat = 0;
	return (1);
}
