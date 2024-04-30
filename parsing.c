/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oemelyan <oemelyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 20:28:24 by oemelyan          #+#    #+#             */
/*   Updated: 2024/04/29 22:33:48 by oemelyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		get_number(char *s)
{
	int result;

	result = 0;

	while(*s >= '0' && *s <= '9' && *s != '\0')
	{
		result = result * 10;
		result += *s - '0';
		s++;
	}
	return(result);
}

u_int64_t	get_input_time(char *s)
{
	u_int64_t		result;

	result = 0;
	while(*s >= '0' && *s <= '9' && *s != '\0')
	{
		result = result * 10;
		result += *s - '0';
		s++;
	}
	return(result);
}

void	parsing(t_input *start, int ac)
{
	start->philo_num = get_number(start->av[1]);
	if(start->philo_num < 1 || start->philo_num > 200)
	{
		write(1, "invalid input", 13);
		return ;
	}
	pthread_mutex_init(&start->lock, NULL);
	start->start_time = get_time();
	start->time_to_die = get_input_time(start->av[2]);
	start->time_to_eat = get_input_time(start->av[3]);
	start->time_to_sleep = get_input_time(start->av[4]);
	if (ac == 6)
		start->meals = get_number(start->av[5]);
}