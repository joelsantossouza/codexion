/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   release_two_dongles.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 10:57:46 by joesanto          #+#    #+#             */
/*   Updated: 2026/02/06 13:37:58 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coder.h"
#include "time_utils.h"
#include "dongle_protocols.h"

static
void	release_dongle(t_dongle *dongle)
{
	pthread_mutex_lock(&dongle->mutex);
	dongle->is_being_used = false;
	dongle->cooldown_end_ms = millis() + *dongle->cooldown;
	pthread_mutex_unlock(&dongle->mutex);
}

void	release_two_dongles(t_coder *coder, uint32_t ncoders)
{
	const uint32_t	coder_idx = coder->id - 1;
	t_signal		*left_signal;
	t_signal		*right_signal;

	release_dongle(coder->left_dongle);
	release_dongle(coder->right_dongle);

	left_signal = table_get_signal((coder_idx - 1 + ncoders) % ncoders);
	right_signal = table_get_signal((coder_idx + 1) % ncoders);

	pthread_mutex_lock(&left_signal->mutex);
	pthread_cond_broadcast(&left_signal->cond);
	pthread_mutex_unlock(&left_signal->mutex);

	pthread_mutex_lock(&right_signal->mutex);
	pthread_cond_broadcast(&right_signal->cond);
	pthread_mutex_unlock(&right_signal->mutex);
}
