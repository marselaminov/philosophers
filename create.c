/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legunshi <legunshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 17:32:20 by legunshi          #+#    #+#             */
/*   Updated: 2021/08/10 17:37:53 by legunshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init_forks(t_all *all)
{
	int	i;

	i = -1;
	all->mutexes = (pthread_mutex_t *)malloc(sizeof
			(pthread_mutex_t) * all->params.philos_num);
	if (!all->mutexes)
		ft_close();
	while (++i < all->params.philos_num)
		pthread_mutex_init(&all->mutexes[i], NULL);
	all->show_msg = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(all->show_msg, NULL);
}

void	ft_init_philosophers(t_all *all)
{
	int	num;

	num = -1;
	all->philos = (t_philo *)malloc(sizeof(t_philo)
			* all->params.philos_num);
	if (!all->philos)
		ft_close();
	while (++num < all->params.philos_num)
	{
		all->philos[num].i = num + 1;
		all->philos[num].left_f = &all->mutexes[num];
		if (num + 1 == all->params.philos_num)
			all->philos[num].right_f = &all->mutexes[0];
		else
			all->philos[num].right_f = &all->mutexes[num + 1];
		pthread_mutex_init(&all->philos[num].die, NULL);
		all->philos[num].params = &all->params;
		all->philos[num].start = &all->start;
		all->philos[num].show_msg = all->show_msg;
		all->philos[num].num_of_eat = 0;
	}
}
