/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion_config_control.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 18:26:20 by joesanto          #+#    #+#             */
/*   Updated: 2026/02/10 09:56:16 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

const t_codexion_config	*codexion_config_control(
	const t_codexion_config *set_config)
{
	static t_codexion_config	codexion_config;

	if (set_config)
		codexion_config = *set_config;
	return ((const t_codexion_config *)&codexion_config);
}

void	set_program_start(t_codexion_config *config)
{
	const uint64_t	time_to_burnout_ms = config->time_to_burnout;
	struct timeval	now;
	struct timespec	*start_deadline_ts;

	if (gettimeofday(&now, NULL) == -1)
	{
		config->start_deadline_ms = 0;
		config->start_deadline_ts = (struct timespec){0};
		return ;
	}
	config->program_start_ms = now.tv_sec * 1000 + now.tv_usec / 1000;
	config->start_deadline_ms = config->program_start_ms + time_to_burnout_ms;

	start_deadline_ts = &config->start_deadline_ts;
	start_deadline_ts->tv_sec = now.tv_sec + time_to_burnout_ms / 1000;
	start_deadline_ts->tv_nsec = now.tv_usec * 1000 + (time_to_burnout_ms % 1000 * 1000000);
	if (start_deadline_ts->tv_nsec >= 1000000000)
	{
		start_deadline_ts->tv_sec += start_deadline_ts->tv_nsec / 1000000000;
		start_deadline_ts->tv_nsec %= 1000000000;
	}
}
