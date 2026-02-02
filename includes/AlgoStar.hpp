/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AlgoStar.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 10:53:17 by glions            #+#    #+#             */
/*   Updated: 2026/02/02 12:03:07 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGOSTAR_HPP
# define ALGOSTAR_HPP

# include <algorithm>
# include <unordered_map>
# include <unordered_set>
# include <queue>
# include <functional>
# include "Node.hpp"

enum class HeuristicType
{
	Manhattan
};

using Heuristic = std::function<int(const Node&, const Node&)>;

class AlgoStar
{
	public:
		AlgoStar(const Node &start, const Node &goal);
		bool start(HeuristicType h);
		bool addHeuristic(HeuristicType h, Heuristic fn);
	private:
		Node _start;
		Node _goal;	
		std::priority_queue<Node, std::vector<Node>, NodeCmp> _opened;
		std::unordered_set<Node, NodeHash> _closed;
		std::unordered_map<HeuristicType, Heuristic> _heuristics;
};



#endif