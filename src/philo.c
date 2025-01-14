/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilfver <msilfver@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 12:47:40 by msilfver          #+#    #+#             */
/*   Updated: 2024/07/03 17:06:00 by msilfver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int argc, char **argv)
{
	t_info	info;

	if (argc == 5 || argc == 6)
	{
		if (check_args(argc, argv) == 1)
		{
			printf(RED "%s\n" RESET, ERR_INT);
			return (1);
		}
		if (init_info(argc, argv, &info) == 1)
			return (1);
		if (init_thp(&info) == 1)
			return (1);
		init_philos(&info);
		info.start_time = get_time();
		if (info.nbr_philo == 1)
			one_philo(&info);
		else
			start_dining(&info);
		end_dining(&info);
	}
	else
		printf(RED "%s\n" RESET, ERR_INP);
	return (0);
}
