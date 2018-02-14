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
            printf ( "SIZE: %d\n", listSize );
            
            listUnit* currentCell = tail;
            
            for ( int i = 0; i < listSize; i++ )
                {
                printf ( "%f ", currentCell->value );
                
                currentCell = currentCell->next;
                }
                
            printf ( "\n" );    
            
            
            }
        
        ///-----------------------------------------------------------------------------------------------------------------------------------------------------------------
    
        typeOfData& operator[] ( const typeOfData index )  
            {
            listUnit* pointerToCurrentCell = tail;
            
            
            for ( int currentCellId = 0; currentCellId <= index; currentCellId++ )
                {
                #if defined ( DEBUG ) || defined ( SECURE1 )
                if ( currentCellId == listSize )
                    {
                    log = log + "Runned out of list. Check id to insert after.\n";
                    return nullReference;
                    }
                #endif
                
                
                pointerToCurrentCell = pointerToCurrentCell->next;
                }
                
            return pointerToCurrentCell->value;
            }
    
    
        int size()
            {
            return ( listSize - 2 );
            }
            
        bool isEmpty()
            {
            return ( listSize == 2 );
            }
    
    
        typeOfData top()
            {
            return head->previous->value;
            }
            
        typeOfData front()
            {
            return tail->next->value;
            }
            
            
        listUnit* push_back ( typeOfData valueToPush )
            {
            listUnit* temp = new listUnit;

            head->value    = valueToPush;
            
            head->next     = temp;
            temp->previous = head;
            
            head = temp;
            
            #ifdef DEBUG
            head->value = poisonValue;
            #endif
            
            listSize++;
            
            return temp;
            }
            
            
        listUnit* push_front ( typeOfData valueToPush )
            {
            listUnit* temp = new listUnit;
        
            tail->value    = valueToPush;
            
            tail->previous = temp;
            temp->next     = tail;
            
            tail = temp;
            
            #ifdef DEBUG
            tail->value = poisonValue;
            #endif
            
            listSize++;
            
            return temp;
            }
            
            
        
        void pop_back()
            {
            #if defined ( DEBUG ) || defined ( SECURE1 ) || defined ( SECURE0 )
            if ( listSize <= 2 )
                {
                log = log + "Unable to pop_back. List is at its minimum size!\n";
                
                return;
                }
            #endif
            
            head = head->previous;
            
            #ifdef DEBUG
            head->value = poisonValue;
            #endif
            
            listSize--;
            delete head->next;
            }
            
        void pop_front()
            {
            #if defined ( DEBUG ) || defined ( SECURE1 ) || defined ( SECURE0 )
            if ( listSize <= 2 )
                {
                log = log + "Unable to pop_front. List is at its minimum size!\n";
                
                return;
                }
            #endif
            
            tail = tail->next;
            
            #ifdef DEBUG
            tail->value = poisonValue;
            #endif
            
            listSize--;
            delete tail->previous;
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
            
        
        void erase ( int idToErase )
            {
            listUnit* pointerToCurrentCell = tail;
            
            for ( int currentCellId = 0; currentCellId <= idToErase; currentCellId++ )
                {
                #if defined ( DEBUG ) || defined ( SECURE1 )
                if ( currentCellId == listSize )
                    {
                    log = log + "Runned out of list. Check id to insert after.\n";
                    return;
                    }
                #endif
                
                
                pointerToCurrentCell = pointerToCurrentCell->next;
                }
            
            pointerToCurrentCell->previous->next = pointerToCurrentCell->next;
            pointerToCurrentCell->next->previous = pointerToCurrentCell->previous;
            
            listSize--;
            delete pointerToCurrentCell;
            }
            
            
    
    
        
        
    
    
    
    private:
        int listSize = 0;
    
        listUnit* tail = nullptr;
        listUnit* head = nullptr;
        
        
        #if defined ( DEBUG ) || defined ( SECURE0 ) || defined ( SECURE1 )
        typeOfData poisonValue = NULL;
        typeOfData& nullReference = poisonValue;
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
    List <double> myList;
    
    
    for ( int i = 0; i < 10; i++ )
        {
        myList.push_back ( 2.58 );
        }
   
    myList [ 5 ] = 89.69;
    
//    std::cout << "DEBUG: "<< myList [ 5 ];
    printf ( "HEY%fHEY", myList [ 5 ] );
    
    std::cout << "DEBUG: " << myList.front() << "\n";
    
    myList.printItAll();
    
    return 0;
    }
