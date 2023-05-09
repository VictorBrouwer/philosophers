/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrouwer <vbrouwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:11:20 by vbrouwer          #+#    #+#             */
/*   Updated: 2023/05/09 14:38:16 by vbrouwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_info(char **argv, int argc, t_info *info)
{
	info->philo_count = ft_atoi(argv[1]);
	info->full_philo_count = 0;
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		info->meals_to_finish = ft_atoi(argv[5]);
	else
		info->meals_to_finish = -1;
	info->forks = init_forks(info->philo_count);
	if (info->forks == NULL)
		return (ERROR);
	info->threads = malloc(sizeof(pthread_t) * info->philo_count);
	if (!info->threads)
		return (clean_forks(info->forks, info->philo_count), ERROR);
	if (pthread_mutex_init(&info->start_mutex, NULL) != 0)
		return (clean_info(info, 0), ERROR);
	if (pthread_mutex_init(&info->full_philo_mutex, NULL) != 0)
		return (clean_info(info, 1), ERROR);
	info->is_dead = 0;
	if (pthread_mutex_init(&info->death_mutex, NULL) != 0)
		return (clean_info(info, 2), ERROR);
	return (SUCCESS);
}

pthread_mutex_t	*init_forks(int philo_count)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = malloc(sizeof(pthread_mutex_t) * philo_count);
	if (!forks)
		return (ft_putstr_fd("malloc ", STDERR_FILENO), NULL);
	i = 0;
	while (i < philo_count)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
			return (clean_forks(forks, (i - 1)), NULL);
		i++;
	}
	return (forks);
}

t_philo	*init_philos(t_info *info)
{
	t_philo	*philos;
	int		i;

	philos = malloc(sizeof(t_philo) * info->philo_count);
	if (!philos)
		return (clean_info(info, 3), NULL);
	i = 0;
	while (i < info->philo_count)
	{
		philos[i].id = i + 1;
		philos[i].fork_1 = &info->forks[i];
		if (info->philo_count == 1)
			philos[i].fork_2 = NULL;
		else if (i < (info->philo_count - 1))
			philos[i].fork_2 = &info->forks[i + 1];
		else
			philos[i].fork_2 = &info->forks[0];
		philos[i].meals_done = 0;
		philos[i].time_last_meal = 0;
		philos[i].info = info;
		if (init_print_and_meals_mutex(&philos[i]) == ERROR)
			return (clean_philos(philos, (i - 1)), NULL);
		i++;
	}
	return (philos);
}

int	init_print_and_meals_mutex(t_philo *philo)
{
	if (pthread_mutex_init(&philo->print_mutex, NULL) != 0)
		return (ERROR);
	if (pthread_mutex_init(&philo->meals_mutex, NULL) != 0)
		return (pthread_mutex_destroy(&philo->print_mutex), ERROR);
	return (SUCCESS);
}
