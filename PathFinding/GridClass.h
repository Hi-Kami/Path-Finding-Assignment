#ifndef GRIDCLASS_H
#define GRIDCLASS_H
//Used for creating the map using bitmaps
using namespace System;
using namespace System::Drawing;

//Creates Grid class, used to store map data, start and end coords and the final path.
//There is also functions to add map data, the coords and to work out Heristics.
//Theres a function to create and clear the map as a bitmap to be desplayed in a picture box.
class Grid
{
public:  
    int Cost[10][10]; 
    bool Path[10][10];
    int StartX;
    int StartY;
    int EndX;
    int EndY;
    void AddMapData( wchar_t, int, int );
    void AddStartCordz( wchar_t, wchar_t ); 
    void AddEndCordz( wchar_t, wchar_t );
    int DistanceHeristic( int, int );
    void ClearPathArray();
    Bitmap^ CreateGrid();
    Bitmap^ CreateBlank();
};

void Grid::AddMapData( wchar_t Data, int X, int Y)
{
    Cost[X][Y] = ( Data - 48 );
}

void Grid::AddStartCordz( wchar_t SX, wchar_t SY )
{
    StartX = ( SX - 48 );
    StartY = ( SY - 48 );
}
void Grid::AddEndCordz( wchar_t EX, wchar_t EY )
{
    EndX = ( EX - 48 );
    EndY = ( EY - 48 );
}


int Grid::DistanceHeristic( int X, int Y )
{
    int NewX = ( EndX - X );
    int NewY = ( EndY - Y );
    if ( NewX < 0 ) { NewX *= -1; }
    if ( NewY < 0 ) { NewY *= -1; }
    int DHeristic = ( NewX + NewY );
    return DHeristic;
}

void Grid::ClearPathArray()
{
    for ( int i = 0; i < 10; i++ ) 
    {
        for ( int j = 0; j < 10; j++ ) 
        {
            Path[i][j] = false;
        }
    }
}
Bitmap^ Grid::CreateGrid()
{
    Bitmap^ MapImage = gcnew Bitmap(600, 600); 
    int SixtyCountX = 60;
    int SixtyCountY = 0;
    int CountX = 600;
    int CountY = 600;
     
    int const Wall = 0;
    int const Clear = 1;
    int const Wood = 2;
    int const Water = 3;

    bool Start;
    bool End;
    bool PathSwitch = true;

    for ( int x = 0; x < 600; x++ )
    {
        for ( int y = 0; y < 600; y++ )
        {
           int cX = (int)( ( x / 60) + 0.5f );
           int cY = (int)( ( CountY / 60) + 0.5f );
           
           
           if ( ( StartX == cX ) && ( StartY == cY ) )
           {
                Start = true;
           }
           else 
           {
                Start = false;
           }

           if ( ( EndX == cX ) && ( EndY == cY ) )
           {
                End = true;
           }
           else 
           {
                End = false;
           }

           int Square = Cost[cX][cY];

           if ( SixtyCountX == 60 || SixtyCountY == 60) 
           { 
               MapImage->SetPixel( x, y, Color::Black );
           }

           else if ( Start )
           {
               MapImage->SetPixel( x, y, Color::LightSalmon );
           }
           else if ( End )
           {
               MapImage->SetPixel( x, y, Color::Yellow );
           }
           else if ( Square == Wall  )
           {
               MapImage->SetPixel( x, y, Color::Black );
           }
           else if ( Square == Clear )
           {
               MapImage->SetPixel( x, y, Color::White );
           }
           else if ( Square == Wood )
           {
               MapImage->SetPixel( x, y, Color::Green );
           }
           else if ( Square == Water )
           {
               MapImage->SetPixel( x, y, Color::Blue);
           }
           
           if ( Path[cX][cY] )
           {
               if ( PathSwitch )
               { 
                   MapImage->SetPixel( x, y, Color::Red ); 
                   PathSwitch = false;
               }
               else if ( !PathSwitch ) { PathSwitch = true; }
           }

           if ( SixtyCountY == 60 ){ SixtyCountY = 0; }
           CountY--;
           SixtyCountY++;
        }
         if ( PathSwitch ){ PathSwitch = false;}
         else if ( !PathSwitch ) { PathSwitch = true; }
        CountY = 600;
        if ( SixtyCountX == 60 ){ SixtyCountX = 0; }
        SixtyCountX++;
            

    }

    return MapImage;
}

Bitmap^ Grid::CreateBlank()
{
    Bitmap^ MapImage = gcnew Bitmap(600, 600); 
    for ( int x = 0; x < 600; x++ )
    {
        for ( int y = 0; y < 600; y++ )
        {
          MapImage->SetPixel( x, y, Color::White );
        }
    }
    return MapImage;
}
#endif