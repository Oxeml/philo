/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oemelyan <oemelyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 20:46:11 by oemelyan          #+#    #+#             */
/*   Updated: 2024/04/30 15:29:37 by oemelyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint64_t get_time(void)
{
	struct timeval		time;

	if (gettimeofday(&time, NULL) == -1)
		return(0);
	return((time.tv_sec * (uint64_t)1000) + (time.tv_usec / 1000));
}

int ft_usleep(unsigned int time)
{
	long int		start;

	start = get_time();
	while(get_time() - start < time)
		usleep(100);
	return(0);
}

void take_the_fork(t_philo *ph)
{
	uint64_t		t;

	t = get_time();
	pthread_mutex_lock(&ph->input->lock);
	printf("philo id: %d\n", ph->id);
	printf("start time: %llu\n", ph->input->start_time);
	printf("fork time: %llu\n", t);
	if (!ph->is_dead)
		printf("%llu %d has taken a fork\n", t - ph->input->start_time, ph->id);
	pthread_mutex_unlock(&ph->input->lock);
}

void eat_pasta(t_philo *ph)
{
	uint64_t		t;

	t = get_time();
	pthread_mutex_lock(&ph->input->lock);
	if (!ph->is_dead)
		printf("%llu %d is eating\n\n", t - ph->input->start_time, ph->id);
	pthread_mutex_unlock(&ph->input->lock);
	ft_usleep(ph->input->time_to_eat);
}

// void	philo_flow(t_input *start)
// {
// 	(void)start;
// 	uint64_t			take_fork;
// 	uint64_t			start_eating;
// 	uint64_t			start_sleeping;
// 	uint64_t			thinking;
// 	uint64_t			start_time;
// 	uint64_t			cycle_end;

// 	start_time = get_time();
// 	take_fork = get_time();
// 	start_eating = get_time();
// 	ft_usleep(start->time_to_eat);
// 	start_sleeping = get_time();
// 	ft_usleep(start->time_to_sleep);
// 	thinking = get_time();
// 	ft_usleep(100);
// 	cycle_end = get_time();

// 	printf("%llu 1 has taken a fork\n", take_fork - start_time);
// 	printf("%llu is eating\n", start_eating - start_time);
// 	printf("time needed to eat: %llu\n", start->time_to_eat);
// 	printf("%llu is sleeping\n", start_sleeping - start_time);
// 	printf("time to sleep: %llu\n", start->time_to_sleep);
// 	printf("%llu is thinking\n", thinking - start_time);
// 	printf("the whole cycle took: %llu\n", cycle_end - start_time);
// }