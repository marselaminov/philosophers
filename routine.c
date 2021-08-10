/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legunshi <legunshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 17:34:00 by legunshi          #+#    #+#             */
/*   Updated: 2021/08/10 17:39:35 by legunshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_show_msg(t_philo *ph, char *str)
{
	pthread_mutex_lock(ph->show_msg);
	printf("%ld\t", ft_get_current_time()
		- *ph->start);
	printf("%d\t%s\n", ph->i, str);
	if (ft_strcmp(str, RED"died"RESET))
		pthread_mutex_unlock(ph->show_msg);
}

int	ft_death_check_utils(t_all *all, int *i)
{
	if (ft_get_current_time() - all->philos[*i].last_eat_time
		> all->params.time_to_die)
	{
		ft_show_msg(&all->philos[*i], RED"died"RESET);
		return (1);
	}
	return (0);
}

void	ft_death_check(t_all *all)
{
	int	num;

	while (LOOP)
	{
		num = -1;
		all->eat_full = 0;
		while (++num < all->params.philos_num)
		{
			pthread_mutex_lock(&all->philos[num].die);
			if (ft_death_check_utils(all, &num))
				return ;
			if (all->philos[num].num_of_eat >= all->params.loop_eat
				&& all->params.loop_eat != 0)
				all->eat_full = all->eat_full + 1;
			if (all->eat_full == all->params.philos_num)
			{
				pthread_mutex_lock(all->show_msg);
				printf(BLUE"Philosophers are fed\n"RESET);
				return ;
			}
			pthread_mutex_unlock(&all->philos[num].die);
		}
	}
}

void	ft_philo_eat(t_philo *ph)
{
	pthread_mutex_lock(&ph->die);
	ft_show_msg(ph, CYAN"is eating"RESET);
	ph->num_of_eat = ph->num_of_eat + 1;
	ph->last_eat_time = ft_get_current_time();
	pthread_mutex_unlock(&ph->die);
}

void	ft_check_philo_index(t_philo *philo)
{
	long	current_time;

	if (philo->i % 2 != 0)
	{
		current_time = ft_get_current_time();
		while (ft_get_current_time() < (current_time
				+ philo->params->time_to_eat))
			usleep(100);
	}
}
