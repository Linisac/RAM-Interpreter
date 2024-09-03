#include "modes.h"
#include "instructions.h"
#include "linked_lists.h"

list_nodes_int::list_nodes_int( int* content )
{
     pContent = content;
     next = 0;
}


linked_lists_int::linked_lists_int()
{
     head = 0;
     tail = 0;
     size = 0;
}


void linked_lists_int::insert_nodes_int( list_nodes_int* new_node )
{
     if ( size == 0 ) //Inserting node for the first time
     {
        head = new_node;
        tail = new_node;
     }
     else
     {
         tail -> next = new_node;
         tail = new_node;
     }
     
     size++;
}


unsigned int linked_lists_int::list_size_int()
{
     return size;
}


void linked_lists_int::transfer_int( int* target_array[] )
{
     int index = 0;
     list_nodes_int* traverse = head;
     
     while ( traverse != 0 )
     {
         target_array[ index ] = traverse -> pContent;
         traverse -> pContent = 0;
         traverse = traverse -> next;
         index++;
     }
}


linked_lists_int::~linked_lists_int()
{
     list_nodes_int* traverse = 0;
     
     while ( head != 0 )
     {
           traverse = head;
           head = head -> next;
           
           if ( traverse -> pContent != 0 )
              delete traverse -> pContent;
              
           delete traverse;
     }
}




list_nodes_instr::list_nodes_instr( instr_nodes* content )
{
     pContent = content;
     next = 0;
}


linked_lists_instr::linked_lists_instr()
{
     head = 0;
     tail = 0;
     size = 0;
}


void linked_lists_instr::insert_nodes_instr( list_nodes_instr* new_node )
{
     if ( size == 0 ) //Inserting node for the first time
     {
          head = new_node;
          tail = new_node;
     }
     else
     {
         tail -> next = new_node;
         tail = new_node;
     }
     
     size++;
}


unsigned int linked_lists_instr::list_size_instr()
{
     return size;
}


void linked_lists_instr::transfer_instr( instr_nodes* target_array[] )
{
     int index = 0;
     list_nodes_instr* traverse = head;
     
     while ( traverse != 0 )
     {
         target_array[ index ] = traverse -> pContent;
         traverse -> pContent = 0;
         traverse = traverse -> next;
         index++;
     }
}


linked_lists_instr::~linked_lists_instr()
{
     list_nodes_instr* traverse = 0;
     
     while ( head != 0 )
     {
           traverse = head;
           head = head -> next;
           
           if ( traverse -> pContent != 0 )
              delete traverse -> pContent;
              
           delete traverse;
     }
}
