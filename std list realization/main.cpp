//
//  main.cpp
//  std list realization
//
//  Created by Эльдар Дамиров on 14.02.2018.
//  Copyright © 2018 Эльдар Дамиров. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <sys/types.h>
#include <unistd.h>
#include <math.h>

#include <time.h>


// FAST - default, SECURE0, SECURE1, DEBUG;

#define listUnit element <typeOfData>

#define DEBUG 


//// ------------------------------------------------------------------------------------------------
const int poisonInt = 12345678;
const double poisonDouble = NAN;
const float poisonFloat = NAN;
const char poisonChar = '~';
//// ------------------------------------------------------------------------------------------------




template <typename typeOfData> struct element
    {
    typeOfData value = NULL;
    

    listUnit* previous = nullptr;
    listUnit* next     = nullptr;
    };


template <typename typeOfData> class List
    {
    public:
        
        List()
            {
            
            tail = new listUnit;
            head = new listUnit;
            
            
            #if defined ( DEBUG ) || defined ( SECURE0 ) || defined ( SECURE1 )
            setPoisonValue();
            #endif
            
            init();
            
            
            }
            
        ~List()
            {
            
            }
    
    
        
        ///-----------------------------------------------------------------------------------------------------------------------------------------------------------------
        void printItAll()
            {
            listUnit* currentCell = tail;
            
            for ( int i = 0; i < listSize; i++ )
                {
                printf ( "%d ", currentCell->value );
                
                currentCell = currentCell->next;
                }
                
            printf ( "\n" );    
            
            
            }
        
        ///-----------------------------------------------------------------------------------------------------------------------------------------------------------------
    
    
    
        typeOfData top()
            {
            return head->value;
            }
            
        typeOfData front()
            {
            return tail->value;
            }
            
            
        listUnit* push_back ( int valueToPush )
            {
            listUnit* temp = new listUnit;
            
            temp->value    = valueToPush;
            
            temp->previous = head;
            head->next     = temp;
            
            head = temp;
            
            return temp;
            }
            
            
        listUnit* push_front ( int valueToPush )
            {
            listUnit* temp = new listUnit;
            
            temp->value = valueToPush;
            
            temp->next = tail;
            tail->previoud = temp;
            
            return temp;
            }
        
        
    
    
    
        listUnit* insert ( int idToInsertAfter, typeOfData valueToInsert )
            {
            listUnit* temp = new listUnit;
            
            listUnit* pointerToCurrentCell = tail;
            
            for ( int currentCellId = 0; currentCellId < idToInsertAfter; currentCellId++ )
                {
                #if defined ( DEBUG ) || defined ( SECURE1 )
                if ( currentCellId == listSize )
                    {
                    log = log + "Runned out of list. Check id to insert after.\n";
                    return nullptr;
                    }
                #endif
                
                
                pointerToCurrentCell = pointerToCurrentCell->next;
                }
                
            
            temp->value    = valueToInsert;
            
            temp->previous = pointerToCurrentCell;
            temp->next     = pointerToCurrentCell->next;
            
            
            pointerToCurrentCell->next = temp;
            ( temp->next )->previous = temp; 
                
            listSize++;
            
            return temp;
            }
            
            
    
    
        
        
    
    
    
    private:
        int listSize = 0;
    
        listUnit* tail = nullptr;
        listUnit* head = nullptr;
        
        
        #if defined ( DEBUG ) || defined ( SECURE0 ) || defined ( SECURE1 )
        typeOfData poisonValue = NULL;
        #endif
        
        
        #ifdef DEBUG
        std::string log = "";
        #endif
    
    
        void init()
            {
            listSize = 2;
            
            
            #if defined ( DEBUG ) || defined ( SECURE0 ) || defined ( SECURE1 )
            tail->value = poisonValue;
            head->value = poisonValue;
            #endif
            
            tail->next     = head;
            head->previous = tail;
            
            tail->previous = tail;
            head->next     = head;

            }

    
    
        int setPoisonValue()
            {
            if ( typeid ( typeOfData ).name() == typeid ( int ).name() )
                {
                poisonValue = poisonInt;
                return 0;
                }
            else if ( typeid ( typeOfData ).name() == typeid ( double ).name() )
                {
                poisonValue = poisonDouble;
                return 0;
                }
            else if ( typeid ( typeOfData ).name() == typeid ( float ).name() )
                {
                poisonValue = poisonFloat;
                return 0;
                }
            else if ( typeid ( typeOfData ).name() == typeid ( char ).name() )
                {
                poisonValue = poisonChar;
                return 0;
                }
            
            return 0;
            }
    
    
    };




int main()
    {
    List <int> myList;
    
    myList.insert ( 1, 5 );
    myList.insert ( 1, 5 );
    myList.insert ( 1, 5 );
    
    myList.printItAll();
    
    return 0;
    }
