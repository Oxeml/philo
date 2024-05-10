/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oemelyan <oemelyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 15:17:37 by oemelyan          #+#    #+#             */
/*   Updated: 2024/05/10 15:16:20 by oemelyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint64_t	get_time(void)
{
	struct timeval		time;

	if (gettimeofday(&time, NULL) == -1)
		return (0);
	return ((time.tv_sec * (uint64_t)1000) + (time.tv_usec / 1000));
}

int	ft_usleep(unsigned int time)
{
	long int		start;

	start = get_time();
	while (get_time() - start < time)
		usleep(100);
	return (0);
}

void	print_out(char *s, t_philo *philo)
{
	u_int64_t		t;

	pthread_mutex_lock(&philo->private_lock);
	t = get_time();
	printf("%llu %d %s", t - philo->input->start_time, philo->id, s);
	pthread_mutex_unlock(&philo->private_lock);
}
