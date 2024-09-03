#include "registers.h"

registers::registers( unsigned int default_size )
{
    size = default_size;
    pArray = new int[ size ];
    
    int index = 0;
    
    for ( index = 0; index < size; index++ )
        pArray[ index ] = 0;
}

registers::registers( unsigned int default_size, int* input_array[] )
{
    size = default_size;
    pArray = new int[ size ];
    
    int index = 0;
    
    for ( index = 0; index < size; index++ )
        pArray[ index ] = *input_array[ index ];
}

int registers::read_element( unsigned int index )
{
    if ( index >= size )
         remedy( index );
    
    return pArray[ index ];
}

void registers::write_element( unsigned int index, int value )
{
     if ( index >= size )
          remedy( index );
     
     pArray[ index ] = value;
}

void registers::enlarge()
{
     int *pAuxiliary;
     pAuxiliary = pArray;
     
     int enlarged_size = size * 2;
     
     pArray = 0;
     pArray = new int[ enlarged_size ];
     
     int index = 0;
     
     for ( index = 0; index < enlarged_size; index++ )
         if ( index < size )
             pArray[ index ] = pAuxiliary[ index ];
         else
             pArray[ index ] = 0;
     
     delete[] pAuxiliary;
     
     size = enlarged_size;
}

void registers::remedy( unsigned int index )
{
     while ( index >= size )
           enlarge();
}
