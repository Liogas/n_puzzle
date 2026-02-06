/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setupHeurisitics.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 15:48:23 by glions            #+#    #+#             */
/*   Updated: 2026/02/06 12:49:00 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETUPHEURISTICS_HPP
# define SETUPHEURISTICS_HPP

# include "AlgoStar.hpp"
# include "heuristics.hpp"

int distManhattan(const Node &a, const Node &b);
int	distLinearConflict(const Node &a, const Node &b);

#endif