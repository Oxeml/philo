/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oemelyan <oemelyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:51:13 by oemelyan          #+#    #+#             */
/*   Updated: 2024/05/09 14:18:42 by oemelyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_out(char *s, t_philo *philo)
{
	u_int64_t		t;

	pthread_mutex_lock(&philo->private_lock);
	t = get_time();
	printf("%lld %d %s", t - philo->input->start_time, philo->id, s);
	pthread_mutex_unlock(&philo->private_lock);
}

void take_forks(t_philo *philo)
{
	uint64_t		t;

	if (!philo->input->dead_man)
	{
		t = get_time();
		pthread_mutex_lock(philo->lfork_lock);
		if (philo->input->philo_num == 1)
		{
			pthread_mutex_unlock(philo->lfork_lock);
			ft_usleep(philo->input->time_to_die);
			return ;
		}
		pthread_mutex_lock(philo->rfork_lock);
		pthread_mutex_lock(&philo->input->global_lock);
		if (!philo->input->dead_man)
		{
			print_out("has taken a fork\n", philo);
			print_out("has taken a fork\n", philo);
		}
		pthread_mutex_unlock(&philo->input->global_lock);
	}
}

void eat_pasta(t_philo *ph)
{
	uint64_t		t;

	if (!ph->input->dead_man)
	{
		t = get_time();
		pthread_mutex_lock(&ph->input->global_lock);
		if (!ph->is_dead)
			printf("%llu %d is eating\n\n", t - ph->input->start_time, ph->id);
		pthread_mutex_unlock(&ph->input->global_lock);
		pthread_mutex_lock(&ph->private_lock);
		ph->time_last_eaten = t - ph->input->start_time;
		if (ph->meals_left > 0)
			ph->meals_left--;
		pthread_mutex_unlock(&ph->private_lock);
		ft_usleep(ph->input->time_to_eat);
	}
}

void go_sleep(t_philo *ph)
{
	uint64_t		t;

	t = get_time();
	pthread_mutex_lock(&ph->input->global_lock);
	if (!ph->input->dead_man)
	{
		printf("%llu %d is sleeping\n\n", t - ph->input->start_time, ph->id);
		pthread_mutex_unlock(&ph->input->global_lock);
		ft_usleep(ph->input->time_to_sleep);
	}
	pthread_mutex_unlock(&ph->input->global_lock);
}