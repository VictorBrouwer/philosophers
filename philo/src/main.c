/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrouwer <vbrouwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 12:35:52 by vbrouwer          #+#    #+#             */
/*   Updated: 2023/05/08 11:21:43 by vbrouwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_philo			*philos;
	t_info			info;

	if (argc != 5 && argc != 6)
		return (ft_putstr_fd("wrong number of arguments", STDERR_FILENO), 0);
	if (check_args(argv, argc) == 1)
		return (ft_putstr_fd("error", STDERR_FILENO), 0);
	if (init_info(argv, argc, &info) == 1)
		return (ft_putstr_fd("error", STDERR_FILENO), 0);
	philos = init_philos(&info);
	if (multi_thread(philos) == 0)
		observe(philos);
	join_philos(philos);
	clean(philos);
	return (0);
}

int	init_info(char **argv, int argc, t_info *info)
{
	info->philo_count = ft_atoi_prot(argv[1]);
	info->full_philo_count = 0;
	info->time_to_die = ft_atoi_prot(argv[2]);
	info->time_to_eat = ft_atoi_prot(argv[3]);
	info->time_to_sleep = ft_atoi_prot(argv[4]);
	if (argc == 6)
		info->meals_to_finish = ft_atoi_prot(argv[5]);
	else
		info->meals_to_finish = -1;
	info->forks = init_forks(info->philo_count);
	if (info->forks == NULL)
		return (ERROR);
	info->threads = malloc(sizeof(pthread_t) * info->philo_count);
	if (!info->threads)
		return (ft_putstr_fd("malloc ", STDERR_FILENO), ERROR);
	pthread_mutex_init(&info->start_mutex, NULL);
	pthread_mutex_init(&info->full_philo_mutex, NULL);
	info->is_dead = 0;
	pthread_mutex_init(&info->death_mutex, NULL);
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
		pthread_mutex_init(&forks[i], NULL);
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
		return (NULL);
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
		pthread_mutex_init(&philos[i].print_mutex, NULL);
		pthread_mutex_init(&philos[i].meals_mutex, NULL);
		i++;
	}
	return (philos);
}
