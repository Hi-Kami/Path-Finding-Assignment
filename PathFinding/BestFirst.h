#ifndef BESTFIRSTCLASS_H
#define BESTFIRSTCLASS_H
#include "GridClass.h"
#include <list>
using namespace std;
//Included for rich text box
using namespace System;
using namespace System::Windows::Forms;

//***Structure for openlist***//
struct OpenListStruct
{
    int X;
    int Y;
    OpenListStruct* Parent;
    int Heristic;
};


//***Structure for closelist***//
struct CloseListStruct
{
    int X;
    int Y;
    int PX;
    int PY;
};

//***Structure for the finishlist***//
struct FinishList
{
    int X;
    int Y;
};

//***BestFirst class***//
class BestFirst
{
public:
    bool PathFind( Grid &MAP, System::Windows::Forms::RichTextBox^ RTB );
    ~BestFirst();
};

//***Compare function to order the openlist***//
bool CompareFunc( const OpenListStruct* FirstValue, const OpenListStruct* SecondValue )
{
    if ( FirstValue->Heristic < SecondValue->Heristic ) { return true; }
    else if ( FirstValue->Heristic > SecondValue->Heristic ) { return false; }
    return false;
}


//***BestFirst Algarithem.**(//
bool BestFirst::PathFind( Grid &MAP, System::Windows::Forms::RichTextBox^ RTB )
{
    /***Verable declratins***/
    bool onList = false;
    bool Wall = false;
    FinishList* FListC = new ( FinishList );
    list<FinishList*> FList;
    list<FinishList*>::iterator q;
    OpenListStruct* tmp = new ( OpenListStruct );
    CloseListStruct* Ctmp = new ( CloseListStruct );
    OpenListStruct* current = new ( OpenListStruct );
    

    //***Creating the start node***/
    tmp->X = MAP.StartX;
    tmp->Y = MAP.StartY;
    tmp->Parent = 0;
    tmp->Heristic = MAP.DistanceHeristic(MAP.StartX, MAP.StartY);

    //1)Create OpenList and ClosedList 
    list<OpenListStruct*> OpenList;
    list<CloseListStruct*> CloseList;
    //2)Push the initial state (start) on to OpenList, 
    //set its parent to 0 and calculate its score using the heuristic value.
    OpenList.push_back( tmp );
    tmp = 0;
    list<OpenListStruct*>::iterator i;
    list<CloseListStruct*>::iterator p;  
    
    do
    {
       //3) A)Pop the first (best) element from OpenList and call it 'current'.
       if ( current == 0 ) { current = new ( OpenListStruct ); }
       if ( tmp == 0 ) { tmp = new ( OpenListStruct ); }
       if ( Ctmp == 0 ) { Ctmp = new ( CloseListStruct ); }
       if ( !OpenList.empty() )
       {
           current = OpenList.front();
       }
       //3) B) If OpenList was empty, return failure and quit.
       else if ( OpenList.empty() )
       {
           delete( current );
           delete( tmp );
           delete( Ctmp );
           return false; 
       }

       //3) C) If 'current' is the goal state, return success, construct the path and quit
       if ( ( current->X == MAP.EndX ) && ( current->Y == MAP.EndY ) )
       {
           RTB->Text += "\nGoal Found!\n";
           FListC = new ( FinishList );
           FListC->X = MAP.EndX;
           FListC->Y = MAP.EndY;
           FList.push_back( FListC );
           FListC = 0;
           bool FoundStart = false;
           bool FoundNext = false;
           int AX = current->Parent->X; 
           int AY = current->Parent->Y;
           do
           {
               if ( FListC == 0 ) { FListC = new ( FinishList ); }
               for ( p = CloseList.begin(); p != CloseList.end(); p++)
               {
                    if ( FoundNext ) { break; }
                    if ( ( (*p)->X == AX ) && ( (*p)->Y == AY ) )
                    {
                        FoundNext = true;
                        FListC->X = AX;
                        FListC->Y = AY; 
                        AX = (*p)->PX;
                        AY = (*p)->PY;
                        FList.push_back( FListC );
                    }
            
               }
               for ( i = OpenList.begin(); i != OpenList.end(); i++)
               {
                    if ( FoundNext ) {  break; }
                    if ( ( (*i)->X == AX ) && ( (*i)->Y == AY) )
                    {
                        FoundNext = true;
                        FListC->X = AX;
                        FListC->Y = AY;
                        AX = (*i)->Parent->X;
                        AY = (*i)->Parent->Y;
                        FList.push_back( FListC );
                    }
            
               }
               FListC = 0;
               if ( ( AX == 0 ) && ( AY == 0 ) ) { FoundStart = true; }
               FoundNext = false;
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
           delete( Ctmp );
           return true;
       }
       

       //3)  D) For each rule that can match 'current' do:
       //    i) Apply the rule to generate a new state and calculate its heuristic value.
       //   ii) If the new state has not already been visited, set its parent to 'current' 
       //       and push the new state on to OpenList (using the heuristic value to order the list)


       /***Generate successers of current***/

       //Generate North of the current node
       if ( ( MAP.Cost[current->X][current->Y + 1] == 0 ) || ( ( current->Y + 1 ) > 9 )  )
       { 
           Wall = true; 
       } 
       else 
       { 
           Wall = false; 
           for ( p = CloseList.begin(); p != CloseList.end(); p++)
           {
                if ( onList ) {  break; }
                if ( ( (*p)->X == current->X ) && ( (*p)->Y == ( current->Y + 1 ) ) )
                {
                    onList = true;
                }
            
           }
           for ( i = OpenList.begin(); i != OpenList.end(); i++)
           {
                if ( onList ) {  break; }
                if ( ( (*i)->X == current->X ) && ( (*i)->Y == ( current->Y + 1 ) ) )
                {
                    onList = true;
                }
            
           }
       }

       if ( !Wall && !onList )
       {
           
           tmp->X = current->X;
           tmp->Y = current->Y + 1;
           tmp->Parent = current;
           tmp->Heristic = MAP.DistanceHeristic(tmp->X, tmp->Y);
           OpenList.push_back( tmp );
           tmp = 0;
       }
       if ( tmp == 0 ) { tmp = new ( OpenListStruct ); }
       onList = false;

       //Generate East of the current node
       if ( ( MAP.Cost[current->X + 1][current->Y] == 0 ) || ( ( current->X + 1) > 9 ) ) 
       { 
           Wall = true; 
       } 
       else 
       { 
           Wall = false; 
           for ( p = CloseList.begin(); p != CloseList.end(); p++)
           {
               if ( onList ){ break; }
               if ( ( (*p)->X == current->X + 1 ) && ( (*p)->Y == ( current->Y ) ) )
               {
                   onList = true;
               }
               
           }
           for ( i = OpenList.begin(); i != OpenList.end(); i++)
           {
               if ( onList ){ break; }
               if ( ( (*i)->X == current->X + 1 ) && ( (*i)->Y == ( current->Y ) ) )
               {
                   onList = true;
               }
               
           }
       }

       if ( !Wall && !onList )
       {
           
           tmp->X = current->X + 1;
           tmp->Y = current->Y;
           tmp->Parent = current;
           tmp->Heristic = MAP.DistanceHeristic(tmp->X, tmp->Y);
           OpenList.push_back( tmp );
           tmp = 0;
       }
       if ( tmp == 0 ) { tmp = new ( OpenListStruct ); }
       onList = false;

       //Generate South of the current node
       if ( ( MAP.Cost[current->X][current->Y - 1] == 0 ) || ( ( current->Y - 1) < 0 ) )
       { 
           Wall = true; 
       } 
       else 
       { 
           Wall = false; 
           for ( p = CloseList.begin(); p != CloseList.end(); p++)
           {
                if ( onList ){ break; }
                if ( ( (*p)->X == current->X ) && ( (*p)->Y == ( current->Y - 1 ) ) )
                {
                    onList = true;
                }
                
           }
           for ( i = OpenList.begin(); i != OpenList.end(); i++)
           {
                if ( onList ){ break; }
                if ( ( (*i)->X == current->X ) && ( (*i)->Y == ( current->Y - 1 ) ) )
                {
                    onList = true;
                }
                
           }
       }

       if ( !Wall && !onList )
       {
            
           tmp->X = current->X;
           tmp->Y = current->Y - 1;
           tmp->Parent = current;
           tmp->Heristic = MAP.DistanceHeristic(tmp->X, tmp->Y);
           OpenList.push_back( tmp );
           tmp = 0;
       }
       if ( tmp == 0 ) { tmp = new ( OpenListStruct ); }
       onList = false;

       //Generate West of the current node
       if ( ( MAP.Cost[current->X - 1][current->Y] == 0 ) || ( ( current->X - 1 ) < 0 ) ) 
       { 
           Wall = true; 
       } 
       else 
       { 
           Wall = false; 
           for ( p = CloseList.begin(); p != CloseList.end(); p++)
           {
                if ( onList ){ break; }
                if ( ( (*p)->X == current->X - 1 ) && ( (*p)->Y == ( current->Y ) ) )
                {
                   onList = true;
                }
                
           }
           for ( i = OpenList.begin(); i != OpenList.end(); i++)
           {
                if ( onList ){ break; }
                if ( ( (*i)->X == current->X - 1 ) && ( (*i)->Y == ( current->Y ) ) )
                {
                   onList = true;
                }
                
           }
       }
       if ( !Wall && !onList )
       {
           
           tmp->X = current->X - 1;
           tmp->Y = current->Y;
           tmp->Parent = current;
           tmp->Heristic = MAP.DistanceHeristic(tmp->X, tmp->Y);
           OpenList.push_back( tmp );
           tmp = 0;
       }
       if ( tmp == 0 ) { tmp = new ( OpenListStruct ); }
       onList = false;

       //3) E) Add 'current' to ClosedList
       Ctmp->X = current->X;
       Ctmp->Y = current->Y;
       if(current->Parent != 0)
       {
           Ctmp->PX = current->Parent->X;
           Ctmp->PY = current->Parent->Y;
       }
       else
       {
           Ctmp->PX = 0;
           Ctmp->PY = 0;
       }
       CloseList.push_back( Ctmp );
              
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
       
       //Reorders the open list based on heristic and sets 
       //structures to 0 so that new structures can be generated 
       //the begining of the loop.
       OpenList.pop_front();
       OpenList.sort( CompareFunc );
       current = 0;
       tmp = 0;
       Ctmp = 0;


    }
    while( !OpenList.empty() ); 

    delete( current );
    delete( tmp );
    delete( Ctmp );
    return false;
    
}


BestFirst::~BestFirst(){}
#endif