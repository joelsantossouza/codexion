/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_coder_event.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 16:51:51 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/28 22:58:12 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdint.h>
#include "coder_internal.h"

static inline
uint64_t	udigit_count(uint64_t nbr)
{
	uint64_t	len;

	len = 1;
	while (nbr >= 10)
	{
		nbr /= 10;
		len++;
	}
	return (len);
}

static inline
uint64_t	buffer_ultoa(uint64_t nbr, char buffer[UINT64_MAXLEN])
{
	const uint64_t	nbr_len = udigit_count(nbr);
	uint64_t		size;

	size = nbr_len;
	buffer[size] = 0;
	while (size-- > 0)
	{
		buffer[size] = nbr % 10 + '0';
		nbr /= 10;
	}
	return (nbr_len);
}

static inline
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*pdest;
	const unsigned char	*psrc;

	pdest = (unsigned char *) dest;
	psrc = (const unsigned char *) src;
	while (n >= 8)
	{
		*(size_t *) pdest = *(size_t *) psrc;
		pdest += 8;
		psrc += 8;
		n -= 8;
	}
	while (n--)
		*pdest++ = *psrc++;
	return (dest);
}

int	log_coder_event(t_coder *coder, enum e_event_id event_id)
{
	char			log[LOG_BUFFER_SIZE];
	uint32_t		log_len;
	static const char	*events_msg[MAX_EVENTS] = {
		MSG_TAKEN_DONGLE,
		MSG_COMPILING,
		MSG_DEBUGGING,
		MSG_REFACTORING,
		MSG_BURNOUT
	};
	static const uint32_t	events_msg_len[MAX_EVENTS] = {
		MSG_TAKEN_DONGLE_STRLEN,
		MSG_COMPILING_STRLEN,
		MSG_DEBUGGING_STRLEN,
		MSG_REFACTORING_STRLEN,
		MSG_BURNOUT_STRLEN
	};

	if (event_id >= MAX_EVENTS || is_simulation_running() == false)
		return (-1);
	log_len = buffer_ultoa(timestamp_ms(0), log);
	log_len += buffer_ultoa(coder->id, log + log_len);
	ft_memcpy(log + log_len, events_msg[event_id], events_msg_len[event_id]);
	log_len += events_msg_len[event_id];
	log[log_len++] = '\n';
	pthread_mutex_lock();
	write(STDOUT_FILENO, log, log_len);
	pthread_mutex_unlock();
	return (log_len);
}
