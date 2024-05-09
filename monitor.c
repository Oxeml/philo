/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oemelyan <oemelyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 16:40:37 by oemelyan          #+#    #+#             */
/*   Updated: 2024/05/09 14:39:07 by oemelyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_feed(t_philo *ph, t_input *start)
{
	pthread_mutex_lock(&ph->private_lock);
	if (!ph->meals_left)
	{
		if (!ph->checked_by_monitor)
		{
			start->they_full++;
			ph->checked_by_monitor = 1;
		}
	}
	pthread_mutex_unlock(&ph->private_lock);
	pthread_mutex_lock(&ph->input->global_lock);
		if (start->they_full == start->philo_num)
		{
			start->dead_man = 1;
			printf("monitor: they all are full\n");
			pthread_mutex_unlock(&ph->input->global_lock);
			return (1);
		}
	pthread_mutex_unlock(&ph->input->global_lock);
	return(0);
}

int check_death(t_philo *ph)
{
	uint64_t		t;

	t = get_time();
	//printf("death status: %d\n", ph->input->dead_man);
	if ((t - ph->input->start_time - ph->time_last_eaten) > ph->input->time_to_die)
	{
		printf("time passed: %f\n", (t - ph->time_last_eaten - ph->input->start_time));
		pthread_mutex_lock(&ph->input->global_lock);
		ph->input->dead_man = 1;
		printf("philo %d died\n", ph->id);
		pthread_mutex_unlock(&ph->input->global_lock);
		return (1);
	}
	return(0);
}

void monitor(t_input *start, t_philo *ph)
{
	unsigned int	i;

	i = 0;
	while (1)
	{
		if (check_feed(&ph[i % start->philo_num], start))
			break ;
		if (check_death(&ph[i % start->philo_num]))
			break ;
		ft_usleep(60 / start->philo_num);
		i++;
	}
	return ;
}