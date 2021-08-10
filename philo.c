/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legunshi <legunshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 17:33:44 by legunshi          #+#    #+#             */
/*   Updated: 2021/08/10 17:35:34 by legunshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_get_current_time(void)
{
	long			time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time);
}

void	ft_destroy_mutexes(t_all *all)
{
	int	num;

	num = -1;
	while (++num < all->params.philos_num)
	{
		pthread_mutex_destroy(&all->mutexes[num]);
		pthread_mutex_destroy(&all->philos[num].die);
	}
	pthread_mutex_destroy(all->show_msg);
}

void	*ft_routine(void *av)
{
	t_philo	*ph;
	long	current_time;

	ph = (t_philo *)av;
	ft_check_philo_index(ph);
	while (LOOP)
	{
		pthread_mutex_lock(ph->left_f);
		ft_show_msg(ph, GREEN"has taken a left fork"RESET);
		pthread_mutex_lock(ph->right_f);
		ft_show_msg(ph, GREEN"has taken a right fork"RESET);
		ft_philo_eat(ph);
		current_time = ft_get_current_time();
		while (ft_get_current_time() < (current_time + ph->params->time_to_eat))
			usleep(100);
		pthread_mutex_unlock(ph->left_f);
		pthread_mutex_unlock(ph->right_f);
		ft_show_msg(ph, YELLOW"is sleeping"RESET);
		current_time = ft_get_current_time();
		while (ft_get_current_time() < (current_time
				+ ph->params->time_to_sleep))
			usleep(100);
		ft_show_msg(ph, MAGENTA"is thinking"RESET);
	}
	return (NULL);
}

void	ft_launch_threads(t_all *all)
{
	int	num;

	num = -1;
	all->start = ft_get_current_time();
	while (++num < all->params.philos_num)
	{
		all->philos[num].last_eat_time = ft_get_current_time();
		pthread_create(&all->philos[num].id, NULL,
			ft_routine, &all->philos[num]);
		pthread_detach(all->philos[num].id);
	}
}

int	main(int ac, char *av[])
{
	t_all	all;

	if (ac < 5 || ac > 6 || !ft_parser(av, &all.params))
	{
		printf(RED"Incorrect arguments!"RESET"\n");
		return (1);
	}
	ft_init_forks(&all);
	ft_init_philosophers(&all);
	ft_launch_threads(&all);
	ft_death_check(&all);
	ft_destroy_mutexes(&all);
	free(all.show_msg);
	free(all.mutexes);
	free(all.philos);
	return (0);
}
