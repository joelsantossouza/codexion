/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   public_codexion_parser.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 16:03:28 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/27 15:02:27 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_PARSER_H
# define CODEXION_PARSER_H

# include <stdint.h>

typedef struct s_codexion
{
	uint32_t		number_of_coders;
	uint32_t		time_to_burnout;
	uint32_t		time_to_compile;
	uint32_t		time_to_debug;
	uint32_t		time_to_refactor;
	uint32_t		number_of_compiles_required;
	uint32_t		dongle_cooldown;
	//t_wait_turn_f	wait_turn;
}	t_codexion;

int	codexion_parser(t_codexion *codexion, int argc, char **argv);

#endif
