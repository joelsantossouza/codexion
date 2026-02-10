/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 16:21:38 by joesanto          #+#    #+#             */
/*   Updated: 2026/02/10 09:22:08 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdint.h>
#include "coder_internal.h"
#include "dongle_protocols.h"
#include "codexion_config_control.h"
#include "codexion.h"

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

int	init_coders(uint32_t ncoders, t_coder coders[ncoders],
				t_dongle dongles[ncoders])
{
	const t_codexion_config	*config = get_codexion_config();
	static pthread_mutex_t	log_mutex = PTHREAD_MUTEX_INITIALIZER;
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
		init_deadline(&coders[i], config);
		coders[i].compilations_done = 0;
		coders[i].log_mutex = &log_mutex;
		coders[i].left_dongle = &dongles[i];
		coders[i].right_dongle = &dongles[(i + 1) % ncoders];
		coders[i].left_neighbor = &coders[(i - 1 + ncoders) % ncoders];
		coders[i].right_neighbor = &coders[(i + 1) % ncoders];
		coders[i].enter_on_dongle_queue = config->scheduler;
	}
	return (0);
}

void	reset_deadline(t_coder *coder, uint64_t time_to_burnout_ms)
{
	struct timeval	now;
	struct timespec	*deadline_ts;

	if (gettimeofday(&now, NULL) == -1)
	{
		coder->deadline_ms = 0;
		coder->deadline_ts = (struct timespec){0};
		return ;
	}
	pthread_mutex_lock(&coder->mutex);
	coder->deadline_ms = now.tv_sec * 1000 + now.tv_usec / 1000 + time_to_burnout_ms;
	pthread_mutex_unlock(&coder->mutex);

	deadline_ts = &coder->deadline_ts;
	deadline_ts->tv_sec = now.tv_sec + time_to_burnout_ms / 1000;
	deadline_ts->tv_nsec = now.tv_usec * 1000 + (time_to_burnout_ms % 1000 * 1000000);
	if (deadline_ts->tv_nsec >= 1000000000)
	{
		deadline_ts->tv_sec += deadline_ts->tv_nsec / 1000000000;
		deadline_ts->tv_nsec %= 1000000000;
	}
}

bool	am_i_alive(t_coder *coder)
{
	bool	is_alive;

	pthread_mutex_lock(&coder->mutex);
	is_alive = millis() < coder->deadline_ms;
	pthread_mutex_unlock(&coder->mutex);
	return (is_alive);
}

void	update_compilations_done(t_coder *coder)
{
	pthread_mutex_lock(&coder->mutex);
	coder->compilations_done++;
	pthread_mutex_unlock(&coder->mutex);
}
