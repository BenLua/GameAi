#include "SceneData.h"

int SceneData::GetObjectCount() const
{
	return m_objectCount;
}

void SceneData::SetObjectCount(const int objectCount)
{
	m_objectCount = objectCount;
}

int SceneData::GetFishCount() const
{
	return m_fishCount;
}

void SceneData::SetFishCount(const int fishCount)
{
	m_fishCount = fishCount;
}

int SceneData::GetPaperCount() const
{
	return m_papercount;
}

void SceneData::SetPaperCount(const int papercount)
{
	m_papercount = papercount;
}

int SceneData::GetRockCount() const
{
	return m_rockcount;
}

void SceneData::SetRockCount(const int rockcount)
{
	m_rockcount = rockcount;
}

int SceneData::GetScissorsCount() const
{
	return m_scissorscount;
}

void SceneData::SetScissorsCount(const int scissorscount)
{
	m_scissorscount = scissorscount;
}

SceneData::SceneData()
{
}

SceneData::~SceneData()
{
}

int SceneData::GetNumGrid() const
{
	return m_noGrid;
}

void SceneData::SetNumGrid(const int numGrid)
{
	m_noGrid = numGrid;
}

float SceneData::GetGridSize() const
{
	return m_gridSize;
}

void SceneData::SetGridSize(const float gridSize)
{
	m_gridSize = gridSize;
}

float SceneData::GetGridOffset() const
{
	return m_gridOffset;
}

void SceneData::SetGridOffset(const float gridOffset)
{
	m_gridOffset = gridOffset;
}
