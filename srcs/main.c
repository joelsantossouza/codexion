/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 15:18:59 by joesanto          #+#    #+#             */
/*   Updated: 2026/02/09 20:25:48 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include "codexion.h"

static
void	clean(t_coder coders[], t_dongle dongles[])
{
	const t_codexion_config	*config = get_codexion_config();

	if (coders)
		destroy_coders(config->number_of_coders, coders);
	if (dongles)
		destroy_dongles(config->number_of_coders, dongles);
}

static
void	join_all(pthread_t *monitor_thread, t_coder coders[])
{
	const t_codexion_config	*config = get_codexion_config();
	uint32_t				i;

	i = -1;
	while (++i < config->number_of_coders)
		pthread_join(coders[i].thread, NULL);
	pthread_join(*monitor_thread, NULL);
}

static
int	handle_special_cases(void)
{
	const t_codexion_config	*config = get_codexion_config();

	if (config->number_of_coders == 0 || config->number_of_compiles_required == 0)
		return (1);
	if (config->number_of_coders == 1)
	{
		printf("0 1 has taken a dongle\n");
		usleep(config->time_to_burnout * 1000);
		printf("%lu 1 burned out\n", config->time_to_burnout);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_codexion_config			config;
	pthread_t					monitor_thread;
	static	t_coder				coders[MAX_CODERS];
	static	t_dongle			dongles[MAX_CODERS];
	const enum e_exit_status	parse_status = codexion_parser(
		&config, argc - 1, argv + 1
	);

	if (argc == 2 && strcmp(argv[1], "--help") == 0)
		return (printf("%s", PROGRAM_USAGE), 0);
	if (parse_status != SUCCESS)
		return (err_log(parse_status), 1);
	set_program_start(&config);
	set_codexion_config(&config);
	if (handle_special_cases() != 0)
		return (0);
	if (init_dongles(config.number_of_coders, dongles) != 0)
		return (err_log(ERR_DONGLES_INIT), 1);
	if (init_coders(config.number_of_coders, coders, dongles) != 0)
		return (clean(NULL, dongles), err_log(ERR_CODERS_INIT), 1);
	if (start_monitor(&monitor_thread, coders) != 0)
		return (clean(coders, dongles), err_log(ERR_THREAD_INIT), 1);
	init_coder_log();
	if (start_coders(config.number_of_coders, coders, START_PATTERN) != 0)
		return (clean(coders, dongles), err_log(ERR_THREAD_INIT), 1);
	return (join_all(&monitor_thread, coders), clean(coders, dongles), 0);
}
