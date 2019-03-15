#ifndef ASTARCLASS_H
#define ASTARCLASS_H
#include "GridClass.h"
#include <list>
using namespace std;
//Included for rich text box
using namespace System;
using namespace System::Windows::Forms;

//***Structure for lists***//
struct ListStruct
{
    int X;
    int Y;
    ListStruct* Parent;
    int Score;
    int Cost;
    int Heristic;
};


//***Structure for the finishlist***//
struct AStarFinishList
{
    int X;
    int Y;
};

//***A* class***//
class AStar
{
public:
    bool PathFind( Grid &MAP, System::Windows::Forms::RichTextBox^ RTB );
    ~AStar();
};

//***Compare function to order the openlist***//
bool AStarCompareFunc( const ListStruct* FirstValue, const ListStruct* SecondValue )
{
    if ( FirstValue->Score < SecondValue->Score ) { return true; }
    else if ( FirstValue->Score > SecondValue->Score ) { return false; }
    return false;
}


//*** A* Algarithem.**(//
bool AStar::PathFind( Grid &MAP, System::Windows::Forms::RichTextBox^ RTB )
{
    /***Verable declratins***/
    bool onList = false;
    bool Wall = false;
    AStarFinishList* FListC = new ( AStarFinishList );
    list<AStarFinishList*> FList;
    list<AStarFinishList*>::iterator q;
    ListStruct* tmp = new ( ListStruct );
    ListStruct* current = new ( ListStruct );
    

    //***Creating the start node***/
    tmp->X = MAP.StartX;
    tmp->Y = MAP.StartY;
    tmp->Parent = 0;
    tmp->Cost = 0;
    tmp->Heristic = MAP.DistanceHeristic(MAP.StartX, MAP.StartY);
    tmp->Score = 0;

    //1)Create OpenList and ClosedList 
    list<ListStruct*> OpenList;
    list<ListStruct*> CloseList;
    //2)Push the initial state (start) on to OpenList, set its parent to 0, 
    //set its cost to 0 and calculate its score using the heuristic value.

    OpenList.push_back( tmp );
    tmp = 0;
    list<ListStruct*>::iterator i;
    list<ListStruct*>::iterator p;  
    
    do
    {
       //3) A)Remove (pop) the first element from OpenList and call it 'current'.
       if ( current == 0 ) { current = new ( ListStruct ); }
       if ( tmp == 0 ) { tmp = new ( ListStruct ); }
       if ( !OpenList.empty() )
       {
           current = OpenList.front();
       }
       //3) B) If OpenList was empty, return failure and quit.
       else if ( OpenList.empty() )
       {
           delete( current );
           delete( tmp );
           return false; 
       }

       //3) C) If 'current' is the goal state, return success, construct the path and quit
       if ( ( current->X == MAP.EndX ) && ( current->Y == MAP.EndY ) )// do this bit
       {
           RTB->Text += "\nGoal Found!\n";
           if ( FListC == 0 ) { FListC = new ( AStarFinishList ); }
           FListC->X = MAP.EndX;
           FListC->Y = MAP.EndY;
           FList.push_back( FListC );
           FListC = 0;
           bool FoundStart = false;
           bool FoundNext = false;
           ListStruct* B = new ( ListStruct );  
           B = current->Parent;
           do
           {
               if ( FListC == 0 ) { FListC = new ( AStarFinishList ); }
               for ( i = OpenList.begin(); i != OpenList.end(); i++)
               {
                    FoundNext = false;
                    if ( FoundNext ) {  break; }
                    if ( (*i) == B )
                    {
                        FoundNext = true;
                        FListC->X = (*i)->X;
                        FListC->Y = (*i)->Y;
                        B = (*i)->Parent;
                        FList.push_back( FListC );
                    }
               }
               for ( p = CloseList.begin(); p != CloseList.end(); p++)
               {
                    FoundNext = false;
                    if ( FoundNext ) { break; }
                    if ( (*p) == B )
                    {
                        FoundNext = true;
                        FListC->X = (*p)->X;
                        FListC->Y = (*p)->Y;
                        B = (*p)->Parent;
                        FList.push_back( FListC );
                    }
               }
               FListC = 0;
               if ( B == 0 ) { FoundStart = true; }
               
           }
           while (!FoundStart );

           int a = 0;
           MAP.ClearPathArray();
           for ( q = FList.begin(); q != FList.end(); q++)
           {
               a++;
               RTB->Text += a + ") X: " + (*q)->X.ToString() + " Y: " + (*q)->Y.ToString() + "\n"; 
               MAP.Path[(*q)->X][(*q)->Y] = true;
           }
           //dealocate memory here and at end
           delete( current );
           delete( tmp );
           return true;
       }
       

       //3)  d) For each rule that can match 'current' do:
       //    i) Apply the rule to generate a new state and call it 'n'
       //    ii) The cost of the new state is the cost of 'current' added to the cost of moving from 'current' to 'n':
	   //        newcost = current.cost + cost(current, n)
       //    iii) If 'n' is on OpenList or on ClosedList and newcost >= existing_n.cost then skip the rest of the loop and go back to (d)
       //    iv) If 'n' is on OpenList or on ClosedList then let 'n' now refer to existing_n.
       //    v) Set the parent of 'n' to 'current'. Calculate the heuristic value. Set the score of 'n' to newcost + heuristic value. Set the cost of 'n' to newcost.
       //    vi) If 'n' was on ClosedList then remove it from ClosedList and push it onto OpenList.
       //    vii) If 'n' was not on OpenList or on ClosedList then push 'n' on to OpenList.
       //    viii) Reorder OpenList by score (since either the cost of 'n' has been updated or 'n' has been pushed onto OpenList).



       /***Generate successers of current***/

       //Generate North of the current node
       if ( ( MAP.Cost[current->X][current->Y + 1] == 0 ) || ( ( current->Y + 1 ) > 9 )  )
       { 
           Wall = true; 
       } 
       else 
       { 
           Wall = false; 
       }

       if ( !Wall )
       {
           
           tmp->X = current->X;
           tmp->Y = current->Y + 1;
           tmp->Parent = current; 
           tmp->Cost = ( current->Cost + MAP.Cost[current->X][current->Y] );
           tmp->Heristic = MAP.DistanceHeristic(tmp->X, tmp->Y);
           tmp->Score = ( tmp->Cost + tmp->Heristic );
           

           for ( i = OpenList.begin(); i != OpenList.end(); i++)
           {
               if ( onList ){ break; }
               if ( ( ( (*i)->X == tmp->X ) && ( (*i)->Y == tmp->Y ) ) ){ onList = true; }
               if ( onList && ( tmp->Cost < (*i)->Cost ) )
               {
                   (*i) = tmp;
               }
           }
           for ( p = CloseList.begin(); p != CloseList.end(); p++)
           {
               if ( onList ){ break; }
               if ( ( ( (*p)->X == tmp->X ) && ( (*p)->Y == tmp->Y ) ) ){ onList = true; }
               if ( onList && ( tmp->Cost < (*p)->Cost ) )
               {
                   OpenList.push_back( tmp );
                   p = CloseList.erase( p );
               }
           }
           if ( !onList )
           {
               OpenList.push_back( tmp );
               tmp = 0;
           }
       }
       if ( tmp == 0 ) { tmp = new ( ListStruct ); }
       onList = false;

       //Generate East of the current node
       if ( ( MAP.Cost[current->X + 1][current->Y ] == 0 ) || ( ( current->X + 1 ) > 9 )  )
       { 
           Wall = true; 
       } 
       else 
       { 
           Wall = false; 
       }

       if ( !Wall )
       {
           
           tmp->X = current->X + 1;
           tmp->Y = current->Y;
           tmp->Parent = current; 
           tmp->Cost = ( current->Cost + MAP.Cost[current->X][current->Y] );
           tmp->Heristic = MAP.DistanceHeristic(tmp->X, tmp->Y);
           tmp->Score = ( tmp->Cost + tmp->Heristic );
           

           for ( i = OpenList.begin(); i != OpenList.end(); i++)
           {
               if ( onList ){ break; }
               if ( ( ( (*i)->X == tmp->X ) && ( (*i)->Y == tmp->Y ) ) ){ onList = true; }
               if ( onList && ( tmp->Cost < (*i)->Cost ) )
               {
                   (*i) = tmp;
               }
           }
           for ( p = CloseList.begin(); p != CloseList.end(); p++)
           {
               if ( onList ){ break; }
               if ( ( ( (*p)->X == tmp->X ) && ( (*p)->Y == tmp->Y ) ) ){ onList = true; }
               if ( onList && ( tmp->Cost < (*p)->Cost ) )
               {
                   OpenList.push_back( tmp );
                   p = CloseList.erase( p );
               }
           }
           if ( !onList )
           {
               OpenList.push_back( tmp );
               tmp = 0;
           }
       }
       if ( tmp == 0 ) { tmp = new ( ListStruct ); }
       onList = false;

       //Generate South of the current node
       if ( ( MAP.Cost[current->X][current->Y - 1] == 0 ) || ( ( current->Y - 1 ) > 9 )  )
       { 
           Wall = true; 
       } 
       else 
       { 
           Wall = false; 
       }

       if ( !Wall )
       {
           
           tmp->X = current->X;
           tmp->Y = current->Y - 1;
           tmp->Parent = current; 
           tmp->Cost = ( current->Cost + MAP.Cost[current->X][current->Y] );
           tmp->Heristic = MAP.DistanceHeristic(tmp->X, tmp->Y);
           tmp->Score = ( tmp->Cost + tmp->Heristic );
           

           for ( i = OpenList.begin(); i != OpenList.end(); i++)
           {
               if ( onList ){ break; }
               if ( ( ( (*i)->X == tmp->X ) && ( (*i)->Y == tmp->Y ) ) ){ onList = true; }
               if ( onList && ( tmp->Cost < (*i)->Cost ) )
               {
                   (*i) = tmp;
               }
           }
           for ( p = CloseList.begin(); p != CloseList.end(); p++)
           {
               if ( onList ){ break; }
               if ( ( ( (*p)->X == tmp->X ) && ( (*p)->Y == tmp->Y ) ) ){ onList = true; }
               if ( onList && ( tmp->Cost < (*p)->Cost ) )
               {
                   OpenList.push_back( tmp );
                   p = CloseList.erase( p );
               }
           }
           if ( !onList )
           {
               OpenList.push_back( tmp );
               tmp = 0;
           }
       }
       if ( tmp == 0 ) { tmp = new ( ListStruct ); }
       onList = false;

       //Generate West of the current node
       if ( ( MAP.Cost[current->X - 1][current->Y] == 0 ) || ( ( current->X - 1 ) > 9 )  )
       { 
           Wall = true; 
       } 
       else 
       { 
           Wall = false; 
       }

       if ( !Wall )
       {
           
           tmp->X = current->X - 1;
           tmp->Y = current->Y;
           tmp->Parent = current; 
           tmp->Cost = ( current->Cost + MAP.Cost[current->X][current->Y] );
           tmp->Heristic = MAP.DistanceHeristic(tmp->X, tmp->Y);
           tmp->Score = ( tmp->Cost + tmp->Heristic );
           

           for ( i = OpenList.begin(); i != OpenList.end(); i++)
           {
               if ( onList ){ break; }
               if ( ( ( (*i)->X == tmp->X ) && ( (*i)->Y == tmp->Y ) ) ){ onList = true; }
               if ( onList && ( tmp->Cost < (*i)->Cost ) )
               {
                   (*i) = tmp;
               }
           }
           for ( p = CloseList.begin(); p != CloseList.end(); p++)
           {
               if ( onList ){ break; }
               if ( ( ( (*p)->X == tmp->X ) && ( (*p)->Y == tmp->Y ) ) ){ onList = true; }
               if ( onList && ( tmp->Cost < (*p)->Cost ) )
               {
                   OpenList.push_back( tmp );
                   p = CloseList.erase( p );
               }
           }
           if ( !onList )
           {
               OpenList.push_back( tmp );
               tmp = 0;
           }
       }
       if ( tmp == 0 ) { tmp = new ( ListStruct ); }
       onList = false;

       //3) E) Push 'current' on to ClosedList.
       CloseList.push_back( current );
              
       //Add Text to the rich text box on the form
       RTB->Text += "Open List: \n";
       
       for ( i = OpenList.begin(); i != OpenList.end(); i++)
       {
           RTB->Text += (*i)->X + ", " + (*i)->Y + "\n";
       }

       RTB->Text += "Close List: \n";
       
       for ( p = CloseList.begin(); p != CloseList.end(); p++)
       {
           RTB->Text += (*p)->X + ", " + (*p)->Y + "\n";
       }
       
       //Reorders the open list based on cost and sets 
       //structures to 0 so that new structures can be generated 
       //the begining of the loop.
       OpenList.pop_front();
       OpenList.sort( AStarCompareFunc );
       current = 0;
       tmp = 0;


    }
    while( !OpenList.empty() ); 

    delete( current );
    delete( tmp );
    return false;
    
}


AStar::~AStar(){}
#endif