/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 16:21:38 by joesanto          #+#    #+#             */
/*   Updated: 2026/02/02 13:05:05 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "coder_internal.h"
#include "dongle_protocols.h"
#include "codexion_config_control.h"
#include "codexion.h"

void	update_compilations_done(t_coder *coder)
{
	pthread_mutex_lock(&coder->mutex);
	coder->compilations_done++;
	pthread_mutex_unlock(&coder->mutex);
}

void	reset_deadline(t_coder *coder, uint64_t time_to_burnout_ms)
{
	pthread_mutex_lock(&coder->mutex);
	coder->deadline_ms = millis() + time_to_burnout_ms;
	pthread_mutex_unlock(&coder->mutex);
	set_abstime(&coder->deadline_ts, time_to_burnout_ms);
}

int	destroy_coders(uint32_t ncoders, t_coder coders[ncoders])
{
	const uint32_t	last_coder = ncoders - 1;
	uint32_t		i;

	if (ncoders == 0)
		return (0);
	i = -1;
	while (++i < last_coder)
	{
		pthread_mutex_destroy(&coders[i].mutex);
		pthread_cond_destroy(&coders[i].cond);
	}
	pthread_mutex_destroy(&coders[i].mutex);
	return (pthread_cond_destroy(&coders[i].cond));
}

int	init_coders(uint32_t ncoders, t_coder coders[ncoders], t_dongle dongles[ncoders], pthread_mutex_t *log_mutex)
{
	const t_codexion_config	*config = get_codexion_config();
	int						exit_status;
	uint32_t				i;

	i = -1;
	while (++i < ncoders)
	{
		coders[i].id = i + 1;
		exit_status = pthread_mutex_init(&coders[i].mutex, NULL);
		if (exit_status != 0)
			return (destroy_coders(i, coders), exit_status);
		exit_status = pthread_cond_init(&coders[i].cond, NULL);
		if (exit_status != 0)
		{
			pthread_mutex_destroy(&coders[i].mutex);
			return (destroy_coders(i, coders), exit_status);
		}
		coders[i].deadline_ms = UINT64_MAX;
		coders[i].compilations_done = 0;
		coders[i].log_mutex = log_mutex;
		coders[i].left_dongle = &dongles[i];
		coders[i].right_dongle = &dongles[(i + 1) % ncoders];
		coders[i].left_neighboor = &coders[(i - 1 + ncoders) % ncoders];
		coders[i].right_neighboor = &coders[(i + 1) % ncoders];
		coders[i].wait_my_turn = config->wait_turn;
	}
	return (0);
}
