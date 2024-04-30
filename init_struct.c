/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oemelyan <oemelyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:21:40 by oemelyan          #+#    #+#             */
/*   Updated: 2024/04/30 16:43:26 by oemelyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *routine(void *arg)
{
	int i = 0;
	t_philo		*philo;

	philo = (t_philo*)arg;
	while (i < 5)
	{
		printf("---start philo %d routine-----\n\n", philo->id);
		if (philo->input->philo_num == 1)
			break ;
		pthread_mutex_lock(&philo->lock_lfork);
		pthread_mutex_lock(&philo->lock_rfork);
		if (philo->l_fork == 0 && (*philo->r_fork) == 0)
		{
			philo->l_fork = 1;
			(*philo->r_fork) = 1;
		}
		else
		{
			printf("philo %d: forks are busy\n", philo->id);
		}
		printf("philo %d: left fork: %d, right fork: %d\n",philo->id, philo->l_fork, (*philo->r_fork));
		pthread_mutex_unlock(&philo->lock_lfork);
		pthread_mutex_unlock(&philo->lock_rfork);
		take_the_fork(philo);
		philo->current_time = get_time();
		eat_pasta(philo);
		printf("philo %d: left fork: %d, right fork: %d\n",philo->id, philo->l_fork, (*philo->r_fork));
		philo->l_fork = 0;
		(*philo->r_fork) = 0;
		printf("philo %d, left fork: %d, right fork: %d\n",philo->id, philo->l_fork, (*philo->r_fork));
		printf("---finish philo %d routine-----\n", philo->id);
		i++;
	}
	return NULL;
}

void exit_on_error(t_philo *ph)
{
	printf("some error\n");
	free_everything(ph);
	exit(EXIT_FAILURE);
}

void init_struct(t_input *start, t_philo **ph)
{
	int			i;
	int			index;

	*ph = malloc(sizeof(t_philo) * start->philo_num + 1);
	if (!(*ph)) {
		printf("Malloc fail!");
		return;
	}
	i = 0;
	index = 1;
	while (i < start->philo_num)
	{
		(*ph)[i].input = start;
		(*ph)[i].id = index;
		(*ph)[i].l_fork = 0;
		if (i == 0)
			(*ph)[i].r_fork = &(*ph)[start->philo_num - 1].l_fork; //should it be a pointer
		else
			(*ph)[i].r_fork = &(*ph)[i - 1].l_fork;
		(*ph)[i].is_dead = 0;
		i++;
		index++;
	}
}

void init_mutexes(t_input *start, t_philo **ph)
{
	int			i;

	i = 0;
	while (i < start->philo_num)
	{
		pthread_mutex_init(&(*ph)[i].lock_lfork, NULL);
		pthread_mutex_init(&(*ph)[i].lock_rfork, NULL);
		pthread_mutex_init(&(*ph)[i].private_lock, NULL);
		i++;
	}
}

void do_threads(t_input *start, t_philo *ph)
{
	int		i;

	i = 0;
	while (i < start->philo_num)
	{
		if (pthread_create(&ph[i].eminem, NULL, &routine, &ph[i]) != 0)
			exit_on_error(ph);
		i++;
	}

	i = 0;
	while (i < start->philo_num)
	{
		if (pthread_join(ph[i].eminem, NULL) != 0)
			exit_on_error(ph);
		i++;
	}
}
