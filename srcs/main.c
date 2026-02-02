/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 15:18:59 by joesanto          #+#    #+#             */
/*   Updated: 2026/02/02 12:54:13 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include "codexion.h"

int	main(int argc, char **argv)
{
	t_codexion_config			config;
	static	t_coder				coders[MAX_CODERS];
	static	t_dongle			dongles[MAX_CODERS];
	static pthread_mutex_t		log_mutex = PTHREAD_MUTEX_INITIALIZER;
	const enum e_exit_status	parse_status = codexion_parser(
		&config, argc - 1, argv + 1
	);

	if (parse_status != SUCCESS)
		return (fprintf(stderr, "%s", get_error_msg(parse_status)), 1);
	set_codexion_config(&config);
	if (init_dongles(config.number_of_coders, dongles) != 0)
		return (fprintf(stderr, ERR_DONGLES_INIT_MSG), 1);
	if (init_coders(config.number_of_coders, coders, dongles, &log_mutex) != 0)
	{
		destroy_dongles(config.number_of_coders, dongles);
		return (fprintf(stderr, ERR_CODERS_INIT_MSG), 1);
	}
	init_coder_log();
	// IMPROVE ME
	if (config.number_of_compiles_required == 0)
		return (0);
	uint32_t	i = 0;
	while (i < config.number_of_coders)
	{
		pthread_create(&coders[i].thread, NULL, (t_routine)coder_routine, &coders[i]);
		i += 2;
	}
	usleep(100);
	i = 1;
	while (i < config.number_of_coders)
	{
		pthread_create(&coders[i].thread, NULL, (t_routine)coder_routine, &coders[i]);
		i += 2;
	}
	i = -1;

	pthread_t	monitor_thread;
	pthread_create(&monitor_thread, NULL, (t_routine)monitor_routine, coders);

	while (++i < config.number_of_coders)
		pthread_join(coders[i].thread, NULL);
	pthread_join(monitor_thread, NULL);
	return (0);
}
