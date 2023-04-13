/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrouwer <vbrouwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 12:35:52 by vbrouwer          #+#    #+#             */
/*   Updated: 2023/04/12 16:10:58 by vbrouwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_info	*info;

	if (argc != 5 && argc != 6)
		exit(EXIT_FAILURE);
	info = malloc(sizeof(t_info));
	init_info(argv, argc, info);
	multi_thread(info);
	return (0);
}

void	init_info(char **argv, int argc, t_info *info)
{
	int					i;

	info->philo_count = ft_atoi_prot(argv[1]);
	info->forks = malloc(sizeof(pthread_mutex_t) * info->philo_count);
	i = 0;
	while (i < info->philo_count)
	{
		pthread_mutex_init(&info->forks[i], NULL);
		i++;
	}
	info->philos = init_philos(info->philo_count, info->forks, argv, argc);
}

t_philo	*init_philos(int philo_count, pthread_mutex_t *forks, char **argv, int argc)
{
	t_philo				*philos;
	int					i;

	i = 0;
	philos = malloc(sizeof(t_philo) * philo_count);
	if (!philos)
		exit(EXIT_FAILURE);
	while (i < philo_count)
	{
		philos[i].id = i + 1;
		philos[i].fork_1 = &forks[i];
		if (i < (philo_count - 1))
			philos[i].fork_2 = &forks[i + 1];
		else
			philos[i].fork_2 = &forks[0];
		philos[i].time_to_die = ft_atoi_prot(argv[2]);
		philos[i].time_to_eat = ft_atoi_prot(argv[3]);
		philos[i].time_to_sleep = ft_atoi_prot(argv[4]);
		philos[i].is_dead = 0;
		philos[i].time_last_meal = 0;
		if (argc == 6)
			philos[i].meals_to_finish = ft_atoi_prot(argv[5]);
		else
			philos[i].meals_to_finish = -1;
		i++;
	}
	return (philos);
}

int	ft_atoi_prot(const char *str)
{
	int	x;
	int	sign;
	int	result;

	x = 0;
	sign = 1;
	result = 0;
	while (str[x] == 32 || (str[x] >= 9 && str[x] <= 13))
		x++;
	if (str[x] == '-')
	{
		sign = -1;
		x++;
	}
	else if (str[x] == '+')
		x++;
	while (str[x] && str[x] >= '0' && str[x] <= '9')
	{
		result = result * 10;
		result = result + (str[x] - '0');
		if (result < 0 && (result != INT_MIN || sign == 1))
			exit(EXIT_FAILURE);
		x++;
	}
	return (result * sign);
}