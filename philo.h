/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oemelyan <oemelyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 20:19:13 by oemelyan          #+#    #+#             */
/*   Updated: 2024/04/30 12:21:21 by oemelyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include <inttypes.h>
#include <unistd.h>

typedef struct s_input
{
	char				**av;
	int					philo_num;
	int					meals;
	u_int64_t			start_time;
	u_int64_t			time_to_die;
	u_int64_t			time_to_eat;
	u_int64_t			time_to_sleep;
	pthread_mutex_t		lock;
}	t_input;

// 1 shared mutex
// 2 mutexes for forks (left fork and right fork)
// each philo has private mutex

// Inside thread:
// Eat --> Sleep --> Think
// evens eat first  --> then odds eat


// Main process:
// while (true) {
// 	// loop over your array:
// 	// 1. check if all philos eaten enough
//			- Set flag to exit threads
// 	// 2. 1 died -> exit program
//			- Set flag to exit threads
// }


typedef struct philo
{
	int						id;
	pthread_t				eminem;
	pthread_mutex_t			lock_lfork;
	pthread_mutex_t			lock_rfork;
	pthread_mutex_t			private_lock;
	int						l_fork;
	int						*r_fork;
	uint64_t				current_time;
	double					time_last_eaten;
	int						is_dead;
	t_input					*input;
}	t_philo;

//parsing
void		parsing(t_input *start, int ac);
int			ac_check(int ac, t_input *start);
void		init_struct(t_input *start, t_philo **ph);
void		init_mutexes(t_input *start, t_philo **ph);
int			ft_usleep(unsigned int time);
int			ft_usleep(unsigned int time);

//main part
uint64_t	get_time(void);
void		do_threads(t_input *start, t_philo *ph);
void		*routine(void *arg);
void		take_the_fork(t_philo *ph);
void		eat_pasta(t_philo *ph);

//cleaning up
void		free_everything(t_philo *ph);
#endif