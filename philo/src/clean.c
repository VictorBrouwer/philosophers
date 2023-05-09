/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrouwer <vbrouwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:18:53 by vbrouwer          #+#    #+#             */
/*   Updated: 2023/05/09 14:41:15 by vbrouwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_forks(pthread_mutex_t *forks, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	free(forks);
}

void	clean_info(t_info *info, int num)
{
	clean_forks(info->forks, info->philo_count);
	free(info->threads);
	if (num == 0)
		return ;
	if (num >= 1)
		pthread_mutex_destroy(&info->start_mutex);
	if (num >= 2)
		pthread_mutex_destroy(&info->full_philo_mutex);
	if (num >= 3)
		pthread_mutex_destroy(&info->death_mutex);
}

void	clean_philos(t_philo *philos, int count)
{
	int	i;

	clean_info(philos->info, 3);
	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&philos[i].print_mutex);
		pthread_mutex_destroy(&philos[i].meals_mutex);
		i++;
	}
	free(philos);
}

void	ft_putstr_fd(const char *s, int fd)
{
	int	x;

	x = 0;
	while (s[x])
	{
		write(fd, &s[x], 1);
		x++;
	}
}
