#pragma once
#include "CoreMinimal.h"
#include "Node.h"

template <typename Type>
class AstarAlgo
{
	Size gridSize;
	vector<vector<Type>> grid;
public:
	INLINE u_int Heuristic(const Coords& _coordsA, const Coords& _coordsB)const
	{
		return abs(_coordsA.x - _coordsB.x) + abs(_coordsA.y - _coordsB.y);
	}

public:

	AstarAlgo(const vector<vector<Type>>& _grid)
	{
		grid = _grid;
		gridSize = Size(grid);
	}

private:
	bool IsValid(const Coords& _coords)const
	{
		return _coords>= 0 && _coords < gridSize;
	}
	bool CopareNodes(Node* _first, Node* _second)
	{
		return _first->GetF() > _second->GetF();
	}

public:
	vector<Coords> FindPath()
	{
		priority_queue<Node*, vector<Node*>, function<bool(Node*, Node*)>> _openList(CopareNodes);
		//unordered_map<>
	}
};

