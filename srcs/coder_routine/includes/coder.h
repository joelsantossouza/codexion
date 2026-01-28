/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 16:24:01 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/28 16:26:37 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODER_H
# define CODER_H

# include <stdint.h>

typedef struct s_dongle t_dongle;

typedef struct s_coder
{
	uint32_t		id;
	t_dongle		*left_dongle;
	t_dongle		*right_dongle;
	uint64_t		deadline_ms;
	struct timespec	deadline_ts;
}	t_coder;

#endif
