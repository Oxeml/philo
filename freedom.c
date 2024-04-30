/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freedom.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oemelyan <oemelyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 20:49:45 by oemelyan          #+#    #+#             */
/*   Updated: 2024/04/29 23:02:38 by oemelyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void free_everything(t_philo *ph)
{
	int		i;
	int		num;

	num = ph[0].input->philo_num;
	i = 0;
	pthread_mutex_destroy(&ph[i].input->lock);
	while(i < num)
	{
		printf("free; %d\n", i);
		pthread_mutex_destroy(&(ph)[i].lock_lfork);
		pthread_mutex_destroy(&(ph)[i].lock_rfork);
		pthread_mutex_destroy(&(ph)[i].private_lock);
		i++;
	}
	free(ph);
}