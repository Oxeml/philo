/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oemelyan <oemelyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 19:43:55 by oemelyan          #+#    #+#             */
/*   Updated: 2024/05/10 15:12:40 by oemelyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_if_num(char	*s)
{
	while (*s >= '0' && *s <= '9' && *s != '\0')
	{
		s++;
	}
	if (*s != '\0')
		return (-1);
	else
		return (0);
}

int	ac_check(int ac, t_input *start)
{
	int		i;

	i = 1;
	while (i < ac)
	{
		if (check_if_num(start->av[i]) == -1)
			return (-1);
		i++;
	}
	if (!(ac == 6 || ac == 5))
		return (-1);
	else
		return (0);
}

int	main(int ac, char **av)
{
	t_input		start;
	t_philo		*ph;

	ph = NULL;
	start.av = av;
	start.meals = -1;
	if (ac_check(ac, &start) == -1)
	{
		write(1, "invalid arguments", 17);
		return (1);
	}
	parsing(&start, ac);
	ph = malloc(sizeof(t_philo) * start.philo_num);
	init_philos(&start, ph);
	start.philos = ph;
	do_threads(&start, ph);
	ft_exit(0, &start, ph);
	return (0);
}
