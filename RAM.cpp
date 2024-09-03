#include <iostream>
#include <fstream>
#include <cstring>
#include "registers.h"
#include "instructions.h"
#include "linked_lists.h"
#include "modes.h"

using namespace std;

bool instr_analyze( instr_nodes*, char* );
void operand_analyze( instr_nodes*, char* );
void execute( unsigned int&, instr_nodes*, registers*, registers* );

int main()
{
    ifstream file_program;
    ifstream file_input;
    ofstream file_output;
    file_output.open( "output.txt" );
    const int max_length = 20;
    char reply;
    char program_name[ max_length ];
    registers *pRAM = 0;
    registers *pI = 0;
    

    cout << "Enter the full name of a .txt file in this folder containing a RAM program to execute: ";
    cin >> program_name;
    file_program.open( program_name );
    

    cout << "Does the RAM program have input parameter(s), stored in the file 'input.txt'? (Y/N) ";
    cin >> reply;
    
    if ( reply == 'y' || reply == 'Y' ) //If the program comes with an input file
    {
         const char* const input_name = "input.txt";
         file_input.open( input_name );
         linked_lists_int input;
         int *value = 0;
         list_nodes_int* node = 0;
         
         while ( file_input.peek() != EOF )
         {
               value = new int;
               file_input >> *value;
               
               node = new list_nodes_int( value );
               input.insert_nodes_int( node );
               
               node = 0;
               value = 0;
         }
         
         
         unsigned int input_size = input.list_size_int();
         int* input_array[ input_size ];
         
         input.transfer_int( input_array );
         
         pI = new registers( input_size, input_array );
    }
    
    
    linked_lists_instr instr_list;
    char auxiliary[ max_length ];
    instr_nodes* value = 0;
    list_nodes_instr* node = 0;
    bool no_operand = true;
    
    while ( file_program.peek() != EOF )
    {
          value = new instr_nodes;
          file_program >> auxiliary;
          no_operand = instr_analyze( value, auxiliary );
          
          if ( !no_operand )
          {
               file_program >> auxiliary;
               operand_analyze( value, auxiliary );
          }
          
          node = new list_nodes_instr( value );
          instr_list.insert_nodes_instr( node );
          value = 0;
          node = 0;
    }
    
    
    
    unsigned int program_size = instr_list.list_size_instr();
    instr_nodes* program_array[ program_size + 1 ];
    
    program_array[ 0 ] = 0;
    instr_list.transfer_instr( &program_array[ 1 ] );
    
    /*
    for ( int k = 1; k <= program_size; k++ )
        file_output << k
                    << '\t'
                    << program_array[ k ] -> instr
                    << ", "
                    << program_array[ k ] -> operand
                    << " ( "
                    << program_array[ k ] -> add_mode
                    << " )"
                    << endl;
    */
    
    
    
    unsigned int kappa = 1;
    
    pRAM = new registers( 2 );
    
    while ( kappa > 0 )
          execute( kappa, program_array[ kappa ], pRAM, pI );
    
    file_output << pRAM -> read_element( 0 );
    
    file_program.close();
    file_input.close();
    file_output.close();
    
    //system( "pause" );
    return 0;
}

bool instr_analyze( instr_nodes* val, char* aux )
{
     if ( strcmp( "READ", aux ) == 0 )
     {
          val -> instr = READ;
          return false;
     }
     else if ( strcmp( "STORE", aux ) == 0 )
     {
          val -> instr = STORE;
          return false;
     }
     else if ( strcmp( "LOAD", aux ) == 0 )
     {
          val -> instr = LOAD;
          return false;
     }
     else if ( strcmp( "ADD", aux ) == 0 )
     {
          val -> instr = ADD;
          return false;
     }
     else if ( strcmp( "SUB", aux ) == 0 )
     {
          val -> instr = SUB;
          return false;
     }
     else if ( strcmp( "HALF", aux ) == 0 )
     {
          val -> instr = HALF;
          return true;
     }
     else if ( strcmp( "JUMP", aux ) == 0 )
     {
          val -> instr = JUMP;
          return false;
     }
     else if ( strcmp( "JPOS", aux ) == 0 )
     {
          val -> instr = JPOS;
          return false;
     }
     else if ( strcmp( "JZERO", aux ) == 0 )
     {
          val -> instr = JZERO;
          return false;
     }
     else if ( strcmp( "JNEG", aux ) == 0 )
     {
          val -> instr = JNEG;
          return false;
     }
     else if ( strcmp( "HALT", aux ) == 0 )
     {
          val -> instr = HALT;
          return true;
     }
     else
         exit( 1 );
}

void operand_analyze( instr_nodes* val, char* aux )
{
     if ( aux[ 0 ] == '^' )
     {
         val -> add_mode = indirect;
         val -> operand = atoi( &aux[ 1 ] );
     }
     else if ( aux[ 0 ] == '=' )
     {
         val -> add_mode = immediate;
         val -> operand = atoi( &aux[ 1 ] );
     }
     else
     {
         val -> add_mode = direct;
         val -> operand = atoi( &aux[ 0 ] );
     }         
}

void execute( unsigned int& PC, instr_nodes* ins, registers* RAM, registers* input )
{
     //default
     PC++;
     
     switch ( ins -> instr )
     {
            case READ:
                 if ( ins -> add_mode == direct )
                      RAM -> write_element( 0, input -> read_element( ins -> operand - 1 ) );
                 else //ins -> add_mode == indirect
                      RAM -> write_element( 0,
                          input -> read_element( RAM -> read_element( ins -> operand ) - 1 ) );
                 break;
            case STORE:
                 if ( ins -> add_mode == direct )
                      RAM -> write_element( ins -> operand, RAM -> read_element( 0 ) );
                 else //ins -> add_mode == indirect
                      RAM -> write_element( RAM -> read_element( ins -> operand ),
                          RAM -> read_element( 0 ) );
                 break;
            case LOAD:
                 if ( ins -> add_mode == direct )
                      RAM -> write_element( 0, RAM -> read_element( ins -> operand ) );
                 else if ( ins -> add_mode == indirect )
                      RAM -> write_element( 0,
                          RAM -> read_element( RAM -> read_element( ins -> operand ) ) );
                 else //ins -> add_mode == immediate
                      RAM -> write_element( 0, ins -> operand );
                 break;
            case ADD:
                 if ( ins -> add_mode == direct )
                      RAM -> write_element( 0,
                          RAM -> read_element( 0 ) + RAM -> read_element( ins -> operand ) );
                 else if ( ins -> add_mode == indirect )
                      RAM -> write_element( 0,
                          RAM -> read_element( 0 ) +
                             RAM -> read_element( RAM -> read_element( ins -> operand ) ) );
                 else //ins -> add_mode == immediate
                      RAM -> write_element( 0,
                          RAM -> read_element( 0 ) + ins -> operand );
                 break;
            case SUB:
                 if ( ins -> add_mode == direct )
                      RAM -> write_element( 0,
                          RAM -> read_element( 0 ) - RAM -> read_element( ins -> operand ) );
                 else if ( ins -> add_mode == indirect )
                      RAM -> write_element( 0,
                          RAM -> read_element( 0 ) -
                             RAM -> read_element( RAM -> read_element( ins -> operand ) ) );
                 else //ins -> add_mode == immediate
                      RAM -> write_element( 0,
                          RAM -> read_element( 0 ) - ins -> operand );
                 break;
            case HALF:
                 if ( RAM -> read_element( 0 ) < 0 )
                      RAM -> write_element( 0, ( RAM -> read_element( 0 ) - 1 ) / 2 );
                 else // RAM -> read_element( 0 ) >= 0
                      RAM -> write_element( 0, RAM -> read_element( 0 ) / 2 );
                 break;
            case JUMP:
                 PC = ins -> operand;
                 break;
            case JPOS:
                 if ( RAM -> read_element( 0 ) > 0 )
                    PC = ins -> operand;
                 break;
            case JZERO:
                 if ( RAM -> read_element( 0 ) == 0 )
                    PC = ins -> operand;
                 break;
            case JNEG:
                 if ( RAM -> read_element( 0 ) < 0 )
                    PC = ins -> operand;
                 break;
            case HALT:
                 PC = 0;
                 break;
            default:
                    exit( 1 );
     }
}
