/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AStar.tpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 11:08:55 by glions            #+#    #+#             */
/*   Updated: 2026/02/20 11:50:01 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AStar.hpp"

template<AStarState State>
std::vector<State> reconstructPath(std::shared_ptr<Node<State>> node)
{
	std::cout << "Je veux reconstruire le path" << std::endl;
    std::vector<State> path;
    while (node != nullptr)
    {
        path.push_back(node->state);
        node = node->parent;
    }
    std::reverse(path.begin(), path.end());
    return path;
}

// template<AStarState State>
void	showAStarData(
	int &e,
	int &m
)
{
	std::cout << "Result: "<< std::endl;
	std::cout << "Time complexity: " << e << std::endl;
	std::cout << "Size complexity: " << m << std::endl;
	// std::cout << "Number of moves: " << d[g] << std::endl;
}

template<
	AStarState State,
	typename NeighborsFn,
	typename DistFn,
	typename HeurFn
>
std::vector<State> AStar(
	const State		&start,
	const State		&goal,
	NeighborsFn 	genNeighbors,
	DistFn 			calDist,
	HeurFn			calHeur
)
{
	std::priority_queue
	<
		std::shared_ptr<Node<State>>,
		std::vector<std::shared_ptr<Node<State>>>,
		CmpNode<State>
	> 								openList;
	std::unordered_set<State>		closeList;
	std::unordered_map<State, int>	distances;
	int								maxState = 0, expandedNodes = 0;

	auto startNode = std::make_shared<Node<State>>(Node<State>{
		start, 0, calHeur(start, goal), nullptr
	});
	openList.push(startNode);
	while (!openList.empty())
	{
		auto curr = openList.top();
		openList.pop();
		expandedNodes++;
		if (openList.size() + closeList.size() > (unsigned long)maxState)
			maxState = openList.size() + closeList.size();
		if (curr->state == goal)
		{
			showAStarData(expandedNodes, maxState);
			return {reconstructPath(curr)};
		}
		closeList.insert(curr->state);
		for (State n : genNeighbors(curr->state))
		{
			if (closeList.count(n))
				continue ;
			int g = curr->g + calDist(curr->state, n);
			if (!distances.count(n) || g < distances[n])
			{
				auto nNode = std::make_shared<Node<State>>(Node<State>{
					n, g, calHeur(n, goal), curr
				});
				openList.push(nNode);
			}
		}
	}
	return {};
};


