/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 11:02:04 by glions            #+#    #+#             */
/*   Updated: 2026/02/02 12:09:26 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_HPP
# define NODE_HPP

# include <queue>
# include <iostream>

class Node
{
	public:
		Node(const std::vector<std::vector<int>> &grid, int g, int h);
		const std::vector<std::vector<int>>	&getGrid() const;
		int	getF() const;
	private:
		int	_g;
		int	_h;
		int	_f;
		std::vector<std::vector<int>> _grid;
		Node	*_father;
};

struct NodeHash
{
	std::size_t operator()(const Node &n) const
	{
		size_t h = 0;
		for (size_t i = 0; i < n.getGrid().size(); i++)
		{
			for (size_t j = 0; j < n.getGrid()[i].size(); j++)
				h = h * 31 + std::hash<int>()(n.getGrid()[i][j]);
		}
		return (h);
	}
};

struct NodeCmp
{
	bool operator()(const Node &a, const Node &b) const
	{
		return (a.getF() > b.getF());
	}
};

#endif