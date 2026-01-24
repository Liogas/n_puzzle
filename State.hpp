/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   State.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 11:32:06 by glions            #+#    #+#             */
/*   Updated: 2026/01/24 01:36:14 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATE_HPP
# define STATE_HPP

# include <iostream>
# include <vector>
# include <cstdlib>
# include <unordered_map>

struct Pos
{
	int	y;
	int	x;
};

class State
{
	public:
		State(std::vector<std::vector<int>> grid);
		
		const std::vector<std::vector<int>>	&getValues() const;
		bool 								operator==(const State &o) const;
		bool 								operator!=(const State &o) const;
		Pos									getEmptySlot() const;
		std::vector<State>					genNeighbors();
		void								genNeighbor(std::vector<State> &n,
												int dirY, int dirX);

	private:
		std::vector<std::vector<int>> values;
};

std::ostream &operator<<(std::ostream &os, const State &state);
	

struct StateHash
{
	std::size_t operator()(const State &s) const
	{
		size_t h = 0;
		for (size_t i = 0; i < s.getValues().size(); i++)
		{
			for (size_t j = 0; j < s.getValues()[i].size(); j++)
				h = h * 31 + std::hash<int>()(s.getValues()[i][j]);
		}
		return (h);
	}
};

struct	Elem
{
	int		distance;
	int		estimate;
	State 	state;
};

struct Cmp
{
	bool operator()(const Elem &a, const Elem &b) const
	{
		return (a.distance + a.estimate > b.distance + b.estimate);
	}
};



#endif