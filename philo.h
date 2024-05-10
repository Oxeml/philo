/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oemelyan <oemelyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 20:19:13 by oemelyan          #+#    #+#             */
/*   Updated: 2024/05/10 12:56:45 by oemelyan         ###   ########.fr       */
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

typedef struct s_philo t_philo;

typedef struct s_input
{
	char				**av;
	int					philo_num;
	int					meals;
	int					dead_man;
	int					they_full;
	u_int64_t			start_time;
	u_int64_t			time_to_die;
	u_int64_t			time_to_eat;
	u_int64_t			time_to_sleep;
	pthread_mutex_t		global_lock;
	pthread_mutex_t		*fork_locks;
	t_philo				*philos;
}	t_input;

typedef struct s_philo
{
	int						id;
	pthread_t				eminem;
	int						checked_by_monitor;
	pthread_mutex_t			private_lock;
	pthread_mutex_t			*lfork_lock;
	pthread_mutex_t			*rfork_lock;
	uint64_t				current_time;
	double					time_last_eaten;
	int						is_dead;
	int						meals_left;
	pthread_mutex_t			*global;
	t_input					*input;
}	t_philo;

//parsing
void		parsing(t_input *start, int ac);
int			ac_check(int ac, t_input *start);
void		init_philos(t_input *start, t_philo *ph);
uint64_t	get_time(void);
int			ft_usleep(unsigned int time);
void		*ft_calloc(size_t count, size_t size);
void		ft_bzero(void *str, size_t n);

//main part
void do_threads(t_input *start, t_philo *ph);
void		print_out(char *s, t_philo *philo);
void		take_forks(t_philo *philo);
void		eat_pasta(t_philo *ph);
void		go_sleep(t_philo *ph);
void		monitor(t_input *start, t_philo *ph);

//cleaning up
void 		ft_exit(int  err, t_input *start, t_philo *ph);
void		free_start(t_input *start);
void		free_philo(t_philo *ph);
#endif