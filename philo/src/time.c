/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrouwer <vbrouwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 09:37:56 by vbrouwer          #+#    #+#             */
/*   Updated: 2023/05/11 14:44:13 by vbrouwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

unsigned long	get_time_start(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

unsigned long	get_time(t_philo *philo)
{
	return ((get_time_start() - philo->info->start_of_day));
}
