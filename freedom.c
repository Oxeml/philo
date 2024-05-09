/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freedom.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oemelyan <oemelyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 20:49:45 by oemelyan          #+#    #+#             */
/*   Updated: 2024/05/09 14:36:59 by oemelyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void free_start(t_input *start)
{
	int		i;

	i = 0;
	while(i < start->philo_num)
	{
		pthread_mutex_destroy(&start->fork_locks[i]);
		i++;
	}
	pthread_mutex_destroy(&start->global_lock);
	free(start->fork_locks);
}

void free_philo(t_philo *ph)
{
	int		i;
	int		num;

	num = (ph)[0].input->philo_num;

	// free(ph[0].eminem);
	printf("free check: %d\n", ph[0].input->philo_num);
	i = 0;
	while(i < num)
	{
		//free(ph[i].eminem);
		pthread_mutex_destroy(&ph[i].private_lock);
		pthread_mutex_destroy(ph[i].lfork_lock);
		pthread_mutex_destroy(ph[i].rfork_lock);
		i++;
	}
	free(ph);
}

void ft_exit(int  err, t_input *start, t_philo *ph)
{
	if (ph)
		free_philo(ph);
	if (start)
		free_start(start);
	if (err)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}
