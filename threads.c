/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oemelyan <oemelyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:49:46 by oemelyan          #+#    #+#             */
/*   Updated: 2024/05/10 13:57:43 by oemelyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo*)arg;
	if (philo->id % 2 == 0)
		ft_usleep(60);
	while (1)
	{
		pthread_mutex_lock(philo->global);
		if (philo->input->dead_man)
		{
			pthread_mutex_unlock(philo->global);
			break ;
		}
		pthread_mutex_unlock(philo->global);
		if (philo->input->philo_num == 1)
			return NULL;
		take_forks(philo);
		eat_pasta(philo);
		pthread_mutex_unlock(philo->lfork_lock);
		pthread_mutex_unlock(philo->rfork_lock);
		go_sleep(philo);
		pthread_mutex_lock(philo->global);
		if (philo->input->dead_man)
		{
			// printf("philo %d finish\n", philo->id);
			pthread_mutex_unlock(philo->global);
			break ;
		}
		pthread_mutex_unlock(philo->global);
		print_out("is thinking\n", philo);
	}
	return NULL;
}

void do_threads(t_input *start, t_philo *ph)
{
	int		i;

	i = 0;
	while (i < start->philo_num)
	{
		//(ph)[i].eminem = ft_calloc(sizeof(pthread_t), 1);
		if (pthread_create(&(ph)[i].eminem, NULL, &routine, &ph[i]))
		{
			write(2, "threads create failure\n", 23);
			break ;
		}
		i++;
	}
	i = 0;
	monitor(start, ph);
	while (i < start->philo_num)
	{
		if (pthread_join((ph)[i].eminem, NULL) != 0)
		{
			write(2, "threads join failure\n", 23);
			break ;
		}
		i++;
	}
}
