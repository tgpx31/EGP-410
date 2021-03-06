#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include "GridVisualizer.h"
#include "GraphicsSystem.h"
#include "GraphicsBuffer.h"
#include "Grid.h"
#include "Vector2D.h"

#include "Game.h"

GridVisualizer::GridVisualizer( Grid* pGrid )
:mpGrid(pGrid)
,mDirty(true)
{
}

GridVisualizer::~GridVisualizer()
{
}

void GridVisualizer::refresh()
{
	const ALLEGRO_COLOR& color = BLACK_COLOR; 
	if( mDirty )
	{
		//remove old entries first
		removeAllEntriesOfColor( color );

		int size = mpGrid->getGridWidth() * mpGrid->getGridHeight();
		//get any non-zero squares and send them to the visualizer
		for( int i=0; i<size; i++ )
		{
			if( mpGrid->getValueAtIndex(i) != 0 )
			{
				addColor( i, color );
			}
		}
	}
	mDirty = false;
}

void GridVisualizer::addColor( int index, const ALLEGRO_COLOR& color )
{
	//set dirty flag
	mDirty = true;

	//find the existing entry in the map (if it exists)
	std::map< ALLEGRO_COLOR, std::vector<int>, AllegroColorCompare >::iterator iter = mColormap.find( color );

	if( iter != mColormap.end() )//found the existing entry
	{
		iter->second.push_back( index );
	}
	else
	{
		//create a vector to put in the map
		std::vector<int> colorVector;
		colorVector.push_back( index );

		//put the vector into the map
		mColormap[color] = colorVector;
	}
}

void GridVisualizer::removeAllEntriesOfColor( const ALLEGRO_COLOR& color )
{
	//find the existing entry in the map (if it exists)
	std::map< ALLEGRO_COLOR, std::vector<int>, AllegroColorCompare >::iterator iter = mColormap.find( color );
	
	if( iter != mColormap.end() )
	{
		mColormap.erase( iter );
	}
}

void GridVisualizer::draw( GraphicsBuffer& dest )
{
	if( mDirty )
	{
		refresh();
	}

	ALLEGRO_BITMAP* pOldTarget = GraphicsSystem::switchTargetBitmap( dest.getBitmap() );

	int gridHeight = mpGrid->getGridHeight();
	int gridWidth = mpGrid->getGridWidth();
	int numSquares = gridWidth * gridHeight;
	int squareSize = mpGrid->getSquareSize();

	std::map< ALLEGRO_COLOR, std::vector<int>, AllegroColorCompare >::iterator iter;
	for( iter = mColormap.begin(); iter != mColormap.end(); ++iter )
	{
		std::vector<int> theIndices = iter->second;

		for( unsigned int i=0; i<theIndices.size(); i++ )
		{
			Vector2D ulPos = mpGrid->getULCornerOfSquare( theIndices[i] );
			al_draw_filled_rectangle( ulPos.getX(), ulPos.getY(), ulPos.getX() + squareSize, ulPos.getY() + squareSize, iter->first );

			const ALLEGRO_COLOR startColor = al_map_rgb(1, 255, 128);
			const ALLEGRO_COLOR stopColor = al_map_rgb(1, 128, 255);

			// This should only happen on the start node and end node
			// checking this way becaus ethe AllegroColorCompare operator() does not want to work
			if (iter->first.r == startColor.r &&
				iter->first.g == startColor.g &&
				iter->first.b == startColor.b)
			{
				al_draw_text(gpGame->getFont(), al_map_rgb(255, 255, 255), ulPos.getX() + squareSize / 4, ulPos.getY() + squareSize / 4, ALLEGRO_ALIGN_LEFT, "S");
			}
				

			if (iter->first.r == stopColor.r &&
				iter->first.g == stopColor.g &&
				iter->first.b == stopColor.b)
			{
				al_draw_text(gpGame->getFont(), al_map_rgb(255, 255, 255), ulPos.getX() + squareSize / 4, ulPos.getY() + squareSize / 4, ALLEGRO_ALIGN_LEFT, "G");
			}
				
			//mpBuffer->fillRegion( ulPos, Vector2D( ulPos.getX() + squareSize, ulPos.getY() + squareSize ), iter->first );
		}
	}

	GraphicsSystem::switchTargetBitmap( pOldTarget );
}

void GridVisualizer::clear()
{
	mColormap.clear();
}