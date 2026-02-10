/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_coder_event.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 16:51:51 by joesanto          #+#    #+#             */
/*   Updated: 2026/02/10 09:27:42 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdint.h>
#include <stdbool.h>
#include "coder_internal.h"
#include "simulation_control.h"
#include "time_utils.h"

static inline
char	*buffer_ultoa(uint64_t nbr, char buffer[UINT64_MAXLEN])
{
	uint64_t	nbr_len;
	uint64_t	nbr_tmp;
	char		*endptr;

	nbr_len = 1;
	nbr_tmp = nbr;
	while (nbr_tmp >= 10)
	{
		nbr_tmp /= 10;
		nbr_len++;
	}
	endptr = buffer + nbr_len;
	while (nbr_len-- > 0)
	{
		buffer[nbr_len] = nbr % 10 + '0';
		nbr /= 10;
	}
	return (endptr);
}

static inline
void	*ft_mempcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*pdest;
	const unsigned char	*psrc;
	const size_t		ptr_mask = sizeof(uintptr_t) - 1;

	pdest = (unsigned char *) dest;
	psrc = (const unsigned char *) src;
	while (n > 0 && (((uintptr_t)pdest | (uintptr_t)psrc) & ptr_mask))
	{
		*pdest++ = *psrc++;
		n--;
	}
	while (n >= 8)
	{
		*(size_t *) pdest = *(size_t *) psrc;
		pdest += 8;
		psrc += 8;
		n -= 8;
	}
	while (n--)
		*pdest++ = *psrc++;
	return (pdest);
}

void	init_coder_log(void)
{
	const t_codexion_config	*config = get_codexion_config();

	if (DEADLINE_START == PROGRAM_START)
		timestamp_ms(config->program_start_ms);
	else
		timestamp_ms(millis());
}

enum e_exit_status	log_coder_event(const t_coder *coder,
									enum e_event_id event)
{
	static const char		*events_msg[MAX_EVENTS] = {
		MSG_TAKEN_DONGLE, MSG_COMPILING, MSG_DEBUGGING,
		MSG_REFACTORING, MSG_BURNOUT
	};
	static const uint32_t	events_msg_len[MAX_EVENTS] = {
		MSG_TAKEN_DONGLE_STRLEN, MSG_COMPILING_STRLEN, MSG_DEBUGGING_STRLEN,
		MSG_REFACTORING_STRLEN, MSG_BURNOUT_STRLEN
	};
	char					log[LOG_BUFFER_SIZE];
	char					*log_ptr;

	if (event < 0 || event >= MAX_EVENTS)
		return (ERR_LOG_INVALID_EVENT);
	log_ptr = buffer_ultoa(timestamp_ms(0), log);
	*log_ptr++ = ' ';
	log_ptr = buffer_ultoa(coder->id, log_ptr);
	*log_ptr++ = ' ';
	log_ptr = ft_mempcpy(log_ptr, events_msg[event], events_msg_len[event]);
	*log_ptr++ = '\n';
	pthread_mutex_lock(coder->log_mutex);
	if (event != EVENT_BURNOUT && is_simulation_running() == false)
		return (pthread_mutex_unlock(coder->log_mutex), ERR_LOG_SIM_STOPPED);
	write(STDOUT_FILENO, log, log_ptr - log);
	pthread_mutex_unlock(coder->log_mutex);
	return (SUCCESS);
}
