#ifndef DIJKSTRACLASS_H
#define DIJKSTRACLASS_H
#include "GridClass.h"
#include <list>
using namespace std;
//Included for rich text box
using namespace System;
using namespace System::Windows::Forms;

//***Structure for openlist***//
struct DijkstraOpenListStruct
{
    int X;
    int Y;
    DijkstraOpenListStruct* Parent;
    int Cost;
};



//***Structure for the finishlist***//
struct DijkstraFinishList
{
    int X;
    int Y;
};

//***Dijkstra class***//
class Dijkstra
{
public:
    bool PathFind( Grid &MAP, System::Windows::Forms::RichTextBox^ RTB );
    ~Dijkstra();
};

//***Compare function to order the openlist***//
bool DijkstraCompareFunc( const DijkstraOpenListStruct* FirstValue, const DijkstraOpenListStruct* SecondValue )
{
    if ( FirstValue->Cost < SecondValue->Cost ) { return true; }
    else if ( FirstValue->Cost > SecondValue->Cost ) { return false; }
    return false;
}


//***Dijkstra Algarithem.**(//
bool Dijkstra::PathFind( Grid &MAP, System::Windows::Forms::RichTextBox^ RTB )//find and replace heristic to cost
{
    /***Verable declratins***/
    bool onList = false;
    bool Wall = false;
    DijkstraFinishList* FListC = new ( DijkstraFinishList );
    list<DijkstraFinishList*> FList;
    list<DijkstraFinishList*>::iterator z;
    DijkstraOpenListStruct* tmp = new ( DijkstraOpenListStruct );
    DijkstraOpenListStruct* current = new ( DijkstraOpenListStruct );
    
    //***Creating the start node***/
    tmp->X = MAP.StartX;
    tmp->Y = MAP.StartY;
    tmp->Parent = 0;
    tmp->Cost = 0;
    

    //1)Create OpenList and visited list
    list<DijkstraOpenListStruct*> OpenList;
    list<DijkstraOpenListStruct*>::iterator i;
    list<DijkstraOpenListStruct*> VisitedOpenList;
    list<DijkstraOpenListStruct*>::iterator Z;

     
    //2)Push the initial state (start) on to OpenList, 
    //set its cost to 0 and set its parent to 0.
    OpenList.push_back( tmp );
    tmp = 0;
    
    do
    {
       //3) A)Pop the first (best) element from OpenList and call it 'current'.
       if ( current == 0 ) { current = new ( DijkstraOpenListStruct ); }
       if ( tmp == 0 ) { tmp = new ( DijkstraOpenListStruct ); }
       onList = false;
       if ( !OpenList.empty() )
       {
           current = OpenList.front();
           VisitedOpenList.push_back( current );
           OpenList.pop_front();
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
           if ( FListC == 0 ) { FListC = new ( DijkstraFinishList ); }
           FListC->X = MAP.EndX;
           FListC->Y = MAP.EndY;
           FList.push_back( FListC );
           FListC = 0;
           bool FoundStart = false;
           bool FoundNext = false;
           DijkstraOpenListStruct* A = new ( DijkstraOpenListStruct );  
           A = current->Parent;
           do
           {
               if ( FListC == 0 ) { FListC = new ( DijkstraFinishList ); }
               for ( i = OpenList.begin(); i != OpenList.end(); i++)
               {
                    FoundNext = false;
                    if ( FoundNext ) {  break; }
                    if ( (*i) == A )
                    {
                        FoundNext = true;
                        FListC->X = (*i)->X;
                        FListC->Y = (*i)->Y;
                        A = (*i)->Parent;
                        FList.push_back( FListC );
                    }
               }
               for ( Z = VisitedOpenList.begin(); Z != VisitedOpenList.end(); Z++)
               {
                    FoundNext = false;
                    if ( FoundNext ) { break; }
                    if ( (*Z) == A )
                    {
                        FoundNext = true;
                        FListC->X = (*Z)->X;
                        FListC->Y = (*Z)->Y;
                        A = (*Z)->Parent;
                        FList.push_back( FListC );
                    }
               }
               FListC = 0;
               if ( A == 0 ) { FoundStart = true; }
               
           }
           while (!FoundStart );

           int a = 0;
           MAP.ClearPathArray();
           for ( z = FList.begin(); z != FList.end(); z++)
           {
               a++;
               RTB->Text += a + ") X: " + (*z)->X.ToString() + " Y: " + (*z)->Y.ToString() + "\n"; 
               MAP.Path[(*z)->X][(*z)->Y] = true;
           }
           //dealocate memory here and at end
           delete( current );
           delete( tmp );
           return true;
       }
       

       /***Generate successers of current***/

       //d) For each rule that can match 'current' do:
       //   i)  Apply the rule to generate a new state and call it 'n'
       //   ii) The cost of the new state is the cost of 'current' added to the cost 
       //       of moving from 'current' to 'n': newcost = current.cost + cost(current, n)
       //   iii)If 'n' is on OpenList and newcost >= existing_n.cost then skip the rest of 
       //       the loop and go back to (d)
       //   iv) If 'n' is on OpenList then let 'n' now refer to existing_n.
       //   v) Set the parent of 'n' to 'current'. Set the cost of 'n' to newcost.
       //   vi) If 'n' was not on OpenList then push 'n' on to OpenList.
       //   vii) Reorder OpenList by cost (since either the cost of 'n' has been updated or 
       //        'n' has been pushed onto OpenList).

       //Generate North of the current node 
       Wall = false;
       if ( ( MAP.Cost[current->X][current->Y + 1] == 0 ) || ( ( current->Y + 1) > 9 )  )
       { 
           Wall = true; 
       } 
       if ( !Wall  )
       {
           onList = false;
           tmp->X = current->X;
           tmp->Y = current->Y + 1;
           tmp->Parent = current;
           tmp->Cost = ( current->Cost + MAP.Cost[current->X][current->Y] );

           for ( i = OpenList.begin(); i != OpenList.end(); i++)
           {
               if (onList){ break; }
               if ( ( ( (*i)->X == tmp->X ) && ( (*i)->Y == tmp->Y ) ) ){ onList = true; }
               if ( onList && ( tmp->Cost < (*i)->Cost ) )
               {
                   (*i) = tmp;
               }
           }
           for ( Z = VisitedOpenList.begin(); Z != VisitedOpenList.end(); Z++)
           {
               if (onList){ break; }
               if ( ( ( (*Z)->X == tmp->X ) && ( (*Z)->Y == tmp->Y ) ) ){ onList = true; }
               if ( onList && ( tmp->Cost < (*Z)->Cost ) )
               {
                   (*Z) = tmp;
               }
              
           }
           if (!onList)
           {
               OpenList.push_back( tmp ); 
           }
           tmp = 0;
           
       }
       if ( tmp == 0 ) { tmp = new ( DijkstraOpenListStruct ); }
       
       //Generate East of the current node
       Wall = false;
       if ( ( MAP.Cost[current->X + 1][current->Y ] == 0 ) || ( ( current->X + 1) > 9 )  )
       { 
           Wall = true; 
       } 
       
       if ( !Wall  )
       {
           onList = false;
           tmp->X = current->X + 1;
           tmp->Y = current->Y;
           tmp->Parent = current;
           tmp->Cost = ( current->Cost + MAP.Cost[current->X][current->Y] );
           for ( i = OpenList.begin(); i != OpenList.end(); i++)
           {
               if (onList){ break; }
               if ( ( ( (*i)->X == tmp->X ) && ( (*i)->Y == tmp->Y ) ) ){ onList = true; }
               if ( onList && ( tmp->Cost < (*i)->Cost ) )
               {
                   (*i) = tmp;
               }
           }
           for ( Z = VisitedOpenList.begin(); Z != VisitedOpenList.end(); Z++)
           {
               if (onList){ break; }
               if ( ( ( (*Z)->X == tmp->X ) && ( (*Z)->Y == tmp->Y ) ) ){ onList = true; }
               if ( onList && ( tmp->Cost < (*Z)->Cost ) )
               {
                   (*Z) = tmp;
               }
              
           }
           if (!onList)
           {
               OpenList.push_back( tmp ); 
           }
           tmp = 0;
           
       }
       if ( tmp == 0 ) { tmp = new ( DijkstraOpenListStruct ); }

       //Generate South of the current node
       Wall = false;
       if ( ( MAP.Cost[current->X][current->Y - 1] == 0 ) || ( ( current->Y - 1) < 0 )  )
       { 
           Wall = true; 
       } 
       
       if ( !Wall  )
       {
           onList = false;
           tmp->X = current->X;
           tmp->Y = current->Y - 1;
           tmp->Parent = current;
           tmp->Cost = ( current->Cost + MAP.Cost[current->X][current->Y] );
           for ( i = OpenList.begin(); i != OpenList.end(); i++)
           {
               if (onList){ break; }
               if ( ( ( (*i)->X == tmp->X ) && ( (*i)->Y == tmp->Y ) ) ){ onList = true; }
               if ( onList && ( tmp->Cost < (*i)->Cost ) )
               {
                   (*i) = tmp;
               }
           }
           for ( Z = VisitedOpenList.begin(); Z != VisitedOpenList.end(); Z++)
           {
               if (onList){ break; }
               if ( ( ( (*Z)->X == tmp->X ) && ( (*Z)->Y == tmp->Y ) ) ){ onList = true; }
               if ( onList && ( tmp->Cost < (*Z)->Cost ) )
               {
                   (*Z) = tmp;
               }
              
           }
           if (!onList)
           {
               OpenList.push_back( tmp ); 
           }
           tmp = 0;
           
       }
       if ( tmp == 0 ) { tmp = new ( DijkstraOpenListStruct ); }

       //Generate West of the current node
       Wall = false;
       if ( ( MAP.Cost[current->X - 1][current->Y] == 0 ) || ( ( current->X - 1) < 0 )  )
       { 
           Wall = true; 
       } 
       
       if ( !Wall  )
       {
           onList = false;
           tmp->X = current->X - 1;
           tmp->Y = current->Y;
           tmp->Parent = current;
           tmp->Cost = ( current->Cost + MAP.Cost[current->X][current->Y] );
           for ( i = OpenList.begin(); i != OpenList.end(); i++)
           {
               if (onList){ break; }
               if ( ( ( (*i)->X == tmp->X ) && ( (*i)->Y == tmp->Y ) ) ){ onList = true; }
               if ( onList && ( tmp->Cost < (*i)->Cost ) )
               {
                   (*i) = tmp;
               }
           }
           for ( Z = VisitedOpenList.begin(); Z != VisitedOpenList.end(); Z++)
           {
               if (onList){ break; }
               if ( ( ( (*Z)->X == tmp->X ) && ( (*Z)->Y == tmp->Y ) ) ){ onList = true; }
               if ( onList && ( tmp->Cost < (*Z)->Cost ) )
               {
                   (*Z) = tmp;
               }
              
           }
           if (!onList)
           {
               OpenList.push_back( tmp ); 
           }
           tmp = 0;
           
       }
       if ( tmp == 0 ) { tmp = new ( DijkstraOpenListStruct ); }

       //Add Text to the rich text box on the form
       RTB->Text += "Open List: \n";
       //Reorders the open list based on Cost 
       OpenList.sort( DijkstraCompareFunc );
       for ( i = OpenList.begin(); i != OpenList.end(); i++)
       {
           RTB->Text += (*i)->X + ", " + (*i)->Y + " Cost: " + (*i)->Cost + " \n";
       }
       //sets structures to 0 so that new structures can be generated 
       //the begining of the loop.
       
       current = 0;
       tmp = 0;
    }
    while( !OpenList.empty() ); 

    delete( current );
    delete( tmp );
    return false;
    
}

Dijkstra::~Dijkstra(){}
#endif