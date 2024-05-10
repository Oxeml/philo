/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freedom.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oemelyan <oemelyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 20:49:45 by oemelyan          #+#    #+#             */
/*   Updated: 2024/05/10 15:17:29 by oemelyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_philo(t_philo *ph)
{
	int		i;
	int		num;

	num = (ph)[0].input->philo_num;
	i = 0;
	while (i < num)
	{
		pthread_mutex_destroy(&ph[i].private_lock);
		i++;
	}
	free(ph);
}

void	ft_exit(int err, t_input *start, t_philo *ph)
{
	if (ph)
		free_philo(ph);
	pthread_mutex_destroy(&start->global_lock);
	pthread_mutex_destroy(start->fork_locks);
	free(start->fork_locks);
	if (err)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}
