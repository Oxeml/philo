/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oemelyan <oemelyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:58:11 by oemelyan          #+#    #+#             */
/*   Updated: 2024/05/10 13:52:45 by oemelyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void forks(t_input *start)
{
	int		i;

	i = 0;
	while (i < start->philo_num)
	{
		pthread_mutex_init(&start->fork_locks[i], NULL);
		i++;
	}
}

void init_philos(t_input *start, t_philo *ph)
{
	int		i;
	int		index;

	i = 0;
	index = 1;
	while(i < start->philo_num)
	{
		ph[i].id = index;
		ph[i].input = start;
		ph[i].lfork_lock = &start->fork_locks[i];
		if (i == 0)
			ph[i].rfork_lock = &start->fork_locks[start->philo_num - 1];
		else
			ph[i].rfork_lock = &start->fork_locks[i - 1];
		ph[i].is_dead = 0;
		ph[i].checked_by_monitor = 0;
		ph[i].meals_left = start->meals;
		ph[i].global = &start->global_lock;
		ph[i].time_last_eaten = 0;
		pthread_mutex_init(&ph[i].private_lock, NULL);
		i++;
		index++;
	}
	forks(start);
}
