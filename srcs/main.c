/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 15:18:59 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/31 20:08:34 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include "codexion.h"

int	main(int argc, char **argv)
{
	t_coder						coders[MAX_CODERS];
	t_dongle					dongles[MAX_CODERS];
	t_codexion_config			config;
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
	int i = 0;
	while (i < config.number_of_coders)
	{
		pthread_create(&coders[i].thread, NULL, (t_routine)coder_routine, &coders[i]);
		i += 2;
	}
	i = 1;
	while (i < config.number_of_coders)
	{
		pthread_create(&coders[i].thread, NULL, (t_routine)coder_routine, &coders[i]);
		i += 2;
	}
	i = -1;
	while (++i < config.number_of_coders)
		pthread_join(coders[i].thread, NULL);
	return (0);
}
