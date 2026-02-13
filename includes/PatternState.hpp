/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PatternState.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 13:39:48 by glions            #+#    #+#             */
/*   Updated: 2026/02/13 14:31:03 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATTERNSTATE_HPP
# define PATTERNSTATE_HPP

# include <iostream>
# include <vector>
# include <unordered_set>
# include "Node.hpp"

class PatternState
{
	public:
		PatternState();
		PatternState(int size);
		// operators
		bool operator==(const PatternState &other) const;
		// getters
		std::vector<int>	getGrid() const;
		// setters
		void	setValueGrid(int pos, int val);
		void	setBlankIndex(int pos);
		// methods
		std::vector<PatternState>	genNeighbors(int size) const;
		PatternState	makePatternState(
			const Node &node,
			const std::unordered_set<int> &pattern
		);
	private:
		// props
		std::vector<int>	_grid;
		int					_blankIndex;
};

struct PatternHash
{
	size_t operator()(const PatternState &s) const
	{
		size_t h = 0;
		for (int v : s.getGrid())
			h += h * 31 + std::hash<int>()(v);
		return (h);
	}
};

#endif