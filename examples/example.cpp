#include <iostream>
#include "matrix.hpp"

int main () {
    float ** result_elements = nullptr;
    unsigned int result_rows = 0;
    unsigned int result_columns = 0;
    
    float ** lhs_elements;
    unsigned int lhs_rows;
    unsigned int lhs_columns;
    bool success = true;
    char op;
    if( input( std::cin, lhs_elements, lhs_rows, lhs_columns ) ) {
        if( std::cin >> op ) {
            float ** rhs_elements = nullptr;
            unsigned int rhs_rows = 0;
            unsigned int rhs_columns = 0;
            
            switch( op ) {
                case 'T': {
                    if( !transpose( lhs_elements, lhs_rows, lhs_columns, result_elements, result_rows, result_columns ) ) {
                        success = false;
                    }
                    break;
                }
                case 'R': {
                    if( !reverse( lhs_elements, lhs_rows, lhs_columns, result_elements, result_rows, result_columns ) ) {
                        success = false;
                    }
                    break;
                }
                case '+': {
                    if( input( std::cin, rhs_elements, rhs_rows, rhs_columns ) ) {
                        if( !add( lhs_elements, lhs_rows, lhs_columns, rhs_elements, rhs_rows, rhs_columns, result_elements, result_rows, result_columns ) ) {
                            success = false;
                        }
                        destroy( rhs_elements, rhs_rows );
                    }
                    else {
                        success = false;
                    }
                    break;
                }
                case '-': {
                    if( input( std::cin, rhs_elements, rhs_rows, rhs_columns ) ) {
                        if( !sub( lhs_elements, lhs_rows, lhs_columns, rhs_elements, rhs_rows, rhs_columns, result_elements, result_rows, result_columns ) ) {
                            success = false;
                        }
                        destroy( rhs_elements, rhs_rows );
                    }
                    else {
                        success = false;
                    }
                    break;
                }
                case '*': {
                    if( input( std::cin, rhs_elements, rhs_rows, rhs_columns ) ) {
                        if( !multiply( lhs_elements, lhs_rows, lhs_columns, rhs_elements, rhs_rows, rhs_columns, result_elements, result_rows, result_columns ) ) {
                            success = false;
                        }
                        destroy( rhs_elements, rhs_rows );
                    }
                    else {
                        success = false;
                    }
                    break;
                }
                default: {
                    success = false;
                    break;
                }
            }
        }
        
        destroy( lhs_elements, lhs_rows );
    }
    else {
        success = false;
    }
    
    if( success ) {
        output( std::cout, result_elements, result_rows, result_columns );
        destroy( result_elements, result_rows );
    }
    
    return 0;
}
