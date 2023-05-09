/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrouwer <vbrouwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 12:35:52 by vbrouwer          #+#    #+#             */
/*   Updated: 2023/05/09 13:21:22 by vbrouwer         ###   ########.fr       */
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
	if (philos == NULL)
		return (ft_putstr_fd("error", STDERR_FILENO), 0);
	if (multi_thread(philos) == 0)
		observe(philos);
	join_philos(philos);
	clean_philos(philos, philos->info->philo_count);
	return (0);
}
