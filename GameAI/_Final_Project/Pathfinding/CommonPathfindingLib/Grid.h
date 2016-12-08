#pragma once

#include <fstream>
#include <vector>
#include "Trackable.h"

class Vector2D;

const int CLEAR_VALUE = 0;
const int BLOCKING_VALUE = 1;

/* 
 * It hurts to do this as opposed 
 * to converting everything to an 
 * enum but the first rule of 
 * refactoring is don't do it if 
 * you you don't have to.
 */
const int ENEMY_SPAWN_VALUE = 2;
const int PLAYER_SPAWN_VALUE = 3;
const int CANDY_VALUE = 4;
const int DOOR_VALUE = 5;

class Grid:public Trackable
{
public:
	Grid( int pixelWidth, int pixelHeight, int squareSize );
	~Grid();

	int getSquareIndexFromPixelXY( int x, int y ) const;

	int getValueAtIndex( int index ) const;
	int getValueAtPixelXY( int x, int y ) const;
	void setValueAtIndex( int index, int value );
	void setValueAtPixelXY( int x, int y, int value );
	Vector2D getULCornerOfSquare( int index ) const;

	//accessors
	int getPixelWidth() const { return mPixelWidth; };
	int getPixelHeight() const { return mPixelHeight; };
	int getGridWidth() const { return mGridWidth; };
	int getGridHeight() const { return mGridHeight; };
	int getSquareSize() const { return mSquareSize; };
	int getNumValues() const { return mGridWidth * mGridHeight; };

	//get adjacent grid square indices
	std::vector<int> getAdjacentIndices( int theSquareIndex ) const;

	void save( std::ofstream& file );
	void load( std::ifstream& file );

private:
	int* mpValues;
	int mPixelWidth;
	int mPixelHeight;
	int mSquareSize;
	int mGridWidth;
	int mGridHeight;
};