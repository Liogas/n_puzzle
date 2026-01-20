/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 11:35:39 by glions            #+#    #+#             */
/*   Updated: 2026/01/20 13:51:35 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unordered_map>
#include <iostream>
#include <queue>

void	exo1()
{
	std::unordered_map<std::string, int> fruits;

	fruits["pommes"] = 5;
	fruits["bananes"] = 2;
	fruits["cerises"] = 3;

	std::cout << "Nombre de pommes -> " << fruits["pommes"] << std::endl;

	for (auto& pair : fruits)
		std::cout << pair.first << " -> " << pair.second << std::endl;

	std::string test = "poires";
	std::cout << test;
	if (fruits.find(test) != fruits.end())
		std::cout << " est present" << std::endl;
	else
		std::cout << " n'est pas present" << std::endl;
}

void	exo2()
{
	std::unordered_map<char, int> letters;
	std::string string = "aaabbccccdddddd";

	for (char c : string)
		letters[c]++;

	for (std::pair<const char, int>& pair: letters)
		std::cout << pair.first << " -> " << pair.second << std::endl;
}

void	exo3()
{
	struct Point
	{
		int	x;
		int	y;

		bool operator==(const Point& other) const
		{
			return (x == other.x && y == other.y);
		}
	};

	struct PointHash
	{
		std::size_t operator()(const Point &p) const
		{
			return (std::hash<int>()(p.x) ^ (std::hash<int>()(p.y) << 1));
		}
	};

	std::unordered_map<Point, std::string, PointHash> points;
	points[{0, 0}] = "origine";
	points[{1, 2}] = "point A";
	points[{3, 5}] = "point B";

	for (std::pair<const Point, std::string>& pair : points)
		std::cout << "[" << pair.first.x << ";" << pair.first.y << "]" << " -> " << pair.second << std::endl;
}

void	exo4()
{
	struct State
	{
		int	value;

		bool operator==(const State &other) const
		{
			return (value == other.value);
		}
	};

	struct StateHash
	{
		std::size_t operator()(const State &s) const
		{
			return (std::hash<int>()(s.value));
		}
	};

	std::unordered_map<State, int, StateHash> states;
	int tab[] = {1 ,2, 3, 2, 1, 4, 3, 3};
	for (int i : tab)
	{
		states[State{i}]++;
	}

	for (std::pair<const State, int>& pair : states)
	{
		std::cout << pair.first.value << " -> " << pair.second << std::endl;
	}
}

void	exo5()
{
	struct State
	{
		int	value;

		bool operator==(const State &other) const
		{
			return (value == other.value);
		}
	};

	struct StateHash
	{
		std::size_t operator()(const State &s) const
		{
			return (std::hash<int>()(s.value));
		}
	};

	std::unordered_map<State, bool, StateHash> visited;
	
	std::queue<State> tmp;
	tmp.push(State{2});
	while (!tmp.empty())
	{
		State val = tmp.front();
		std::cout << "Traitement de " << val.value << std::endl;
		if (visited.find(val) == visited.end())
		{
			std::cout << val.value << " est maintenant visite" << std::endl;
			visited[val] = true;
			if (val.value > 0 && visited.find(State{val.value - 1}) == visited.end())
			{
				tmp.push(State{val.value - 1});
				std::cout << "Nouveau voisin -> " << val.value - 1 << std::endl;
			}
			if (val.value < 5 && visited.find(State{val.value + 1}) == visited.end())
			{
				std::cout << "Nouveau voisin -> " << val.value + 1 << std::endl;
				tmp.push({val.value + 1});
			}
		}
		tmp.pop();
	}
}

void exo6()
{
	struct State
	{
		int	value;

		bool operator==(const State &other) const
		{
			return (value == other.value);
		}
	};

	struct StateHash
	{
		std::size_t operator()(const State &s) const
		{
			return (std::hash<int>()(s.value));
		}
	};

	std::unordered_map<State, int, StateHash> distances;
	
	std::queue<State> tmp;
	State start = State{4};
	tmp.push(start);
	distances[start] = 0;
	State dest = State{3};
	while (!tmp.empty())
	{
		State val = tmp.front();
		std::cout << "Traitement de " << val.value << std::endl;
		if (val.value > 0 && distances.find(State{val.value - 1}) == distances.end())
		{
			tmp.push(State{val.value - 1});
			distances[State{val.value - 1}] = distances[val] + 1;
			std::cout << "Nouveau voisin -> " << val.value - 1 << " distance -> " << distances[State{val.value - 1}] << std::endl;
		}
		if (val.value < 5 && distances.find(State{val.value + 1}) == distances.end())
		{
			tmp.push({val.value + 1});
			distances[State{val.value + 1}] = distances[val] + 1;
			std::cout << "Nouveau voisin -> " << val.value + 1 << " distance -> " << distances[State{val.value + 1}] << std::endl;
		}
		tmp.pop();
	}
	std::cout << "Distance entre " << start.value << " et " << dest.value << " -> " << distances[dest] << std::endl; 
}

void	exo7()
{
	struct State
	{
		int	value;

		bool operator==(const State &other) const
		{
			return (value == other.value);
		}

		bool operator!=(const State &other) const
		{
			return (value != other.value);
		}
	};

	struct StateHash
	{
		std::size_t operator()(const State &s) const
		{
			return (std::hash<int>()(s.value));
		}
	};

	struct	Elem
	{
		int		distance;
		State 	state;
	};

	struct Cmp
	{
		bool operator()(Elem &a, Elem &b)
		{
			return (a.distance > b.distance);
		}
	};

	std::unordered_map<State, int, StateHash> distances;
	std::unordered_map<State, State, StateHash> fathers;
	
	std::priority_queue<Elem, std::vector<Elem>, Cmp> tmp;
	State start = State{1};
	tmp.push(Elem{.distance= 0, .state= start});
	distances[start] = 0;
	State dest = State{4};
	while (!tmp.empty())
	{
		Elem val = tmp.top();
		std::cout << "Traitement de " << val.state.value << std::endl;
		if (val.state.value > 0)
		{
			int d = distances[val.state] + 1;
			if ((distances.find(State{val.state.value - 1}) != distances.end()
				&& distances.find(State{val.state.value - 1})->second > d)
				|| distances.find(State{val.state.value - 1}) == distances.end())
			{
				distances[State{val.state.value - 1 }] = d;
				fathers[State{val.state.value - 1}] = val.state;
				tmp.push(Elem({.distance= distances[State{val.state.value - 1}], .state= State({val.state.value - 1})}));
				std::cout << "Voisin1 -> " << val.state.value - 1 << " distance -> ";
				std::cout << distances[State{val.state.value - 1}] << " parent -> " << fathers[State{val.state.value - 1}].value << std::endl;
			}
		}
		if (val.state.value < 5)
		{
			int d = distances[val.state] + 3;
			if ((distances.find(State{val.state.value + 1}) != distances.end()
				&& distances.find(State{val.state.value + 1})->second > d)
				|| distances.find(State{val.state.value + 1}) == distances.end())
			{
				distances[State{val.state.value + 1 }] = d;
				fathers[State{val.state.value + 1}] = val.state;
				tmp.push(Elem({.distance= distances[State{val.state.value + 1}], .state= State({val.state.value + 1})}));
				std::cout << "Voisin2 -> " << val.state.value + 1 << " distance -> ";
				std::cout << distances[State{val.state.value + 1}] << " parent -> " << fathers[State{val.state.value + 1}].value << std::endl;
			}
		}
		tmp.pop();
	}
	std::cout << "Distance entre " << start.value << " et " << dest.value << " -> " << distances[dest] << std::endl;
	std::cout << "Parcours entre les deux points : " << std::endl;
	std::cout << dest.value << std::endl;
	while (dest != start)
	{
		dest = State{fathers[dest]};
		std::cout << dest.value << std::endl;
	}
}

int	main()
{
	// exo1();
	// exo2();
	// exo3();
	// exo4();
	// exo5();
	// exo6();
	exo7();
	return (0);
}
