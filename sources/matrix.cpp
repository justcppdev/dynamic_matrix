#include <iostream>
#include "matrix.hpp"

bool equal( float ** lhs_elements,
            unsigned int lhs_rows,
            unsigned int lhs_columns,
            float ** rhs_elements,
            unsigned int rhs_rows,
            unsigned int rhs_columns )
{
    if( lhs_rows != rhs_rows || lhs_columns != rhs_columns ) {
        return false;
    }

    for( unsigned int i = 0; i < lhs_rows; ++ i ) {
        for( unsigned int j = 0; j < lhs_columns; ++j ) {
            if( lhs_elements[ i ][ j ] != rhs_elements[ i ][ j ] ) {
                return false;
            }
        }
    }

    return true;
}

bool add( float ** lhs_elements,
          unsigned int lhs_rows,
          unsigned int lhs_columns,
          float ** rhs_elements,
          unsigned int rhs_rows,
          unsigned int rhs_columns,
          float ** & result_elements,
          unsigned int & result_rows,
          unsigned int & result_columns )
{
    if( lhs_rows != rhs_rows || lhs_columns != rhs_columns ) {
        return false;
    }
    
    auto rows = lhs_rows;
    auto columns = lhs_columns;
    
    auto elements = new float *[ rows ];
    for( unsigned int i = 0; i < rows; ++i ) {
        elements[ i ] = new float[ columns ];
        for( unsigned int j = 0; j < columns; ++j ) {
            elements[ i ][ j ] = lhs_elements[ i ][ j ] + rhs_elements[ i ][ j ];
        }
    }
    
    result_elements = elements;
    result_rows = rows;
    result_columns = columns;
    
    return true;
}

bool sub( float ** lhs_elements,
          unsigned int lhs_rows,
          unsigned int lhs_columns,
          float ** rhs_elements,
          unsigned int rhs_rows,
          unsigned int rhs_columns,
          float ** & result_elements,
          unsigned int & result_rows,
          unsigned int & result_columns )
{
    if( lhs_rows != rhs_rows || lhs_columns != rhs_columns ) {
        return false;
    }
    
    auto rows = lhs_rows;
    auto columns = lhs_columns;
    
    auto elements = new float *[ rows ];
    for( unsigned int i = 0; i < rows; ++i ) {
        elements[ i ] = new float[ columns ];
        for( unsigned int j = 0; j < columns; ++j ) {
            elements[ i ][ j ] = lhs_elements[ i ][ j ] - rhs_elements[ i ][ j ];
        }
    }
    
    result_elements = elements;
    result_rows = rows;
    result_columns = columns;
    
    return true;
}

bool multiply( float ** lhs_elements,
               unsigned int lhs_rows,
               unsigned int lhs_columns,
               float ** rhs_elements,
               unsigned int rhs_rows,
               unsigned int rhs_columns,
               float ** & result_elements,
               unsigned int & result_rows,
               unsigned int & result_columns )
{
    if(  lhs_columns != rhs_rows ) {
        return false;
    }
    
    auto rows = lhs_rows;
    auto columns = rhs_columns;
    
    auto elements = new float *[ rows ];
    for( unsigned int i = 0; i < rows; ++i ) {
        elements[ i ] = new float[ columns ];
        for( unsigned int j = 0; j < columns; ++j ) {
            auto element = 0.0f;
            for( unsigned int k = 0; k < lhs_columns; ++k ) {
                element += lhs_elements[ i ][ k ] * rhs_elements[ k ][ j ];
            }
            elements[ i ][ j ] = element;
        }
    }
    
    result_elements = elements;
    result_rows = rows;
    result_columns = columns;
    
    return true;
}

auto input( std::istream & stream, float ** & result_elements, unsigned int & result_rows, unsigned int & result_columns ) -> std::istream &
{
    float ** elements = nullptr;
    unsigned int rows = 0;
    unsigned int columns = 0;
    
    bool success = true;
    char symbol;
    if( stream >> rows &&
        stream >> symbol && symbol == ',' &&
        stream >> columns ) {
        
        elements = new float *[ rows ];
        for( unsigned int i = 0; i < rows && success; ++i ) {
            elements[ i ] = new float[ columns ];
            for( unsigned int j = 0; j < columns; ++j ) {
                if( !( stream >> elements[ i ][ j ] ) ) {
                    success = false;
                    break;
                }
            }
        }
    }
    else {
        success = false;
    }
    
    if( success ) {
        result_elements = elements;
        result_rows = rows;
        result_columns = columns;
    }
    else {
        stream.setstate( std::ios::failbit );
    }
    
    return stream;
}

bool transpose( float ** lhs_elements,
                unsigned int lhs_rows,
                unsigned int lhs_columns,
                float ** & result_elements,
                unsigned int & result_rows,
                unsigned int & result_columns )
{
    auto rows = lhs_columns;
    auto columns = lhs_rows;
    
    auto elements = new float *[ rows ];
    for( unsigned int i = 0; i < rows; ++i ) {
        elements[ i ] = new float[ columns ];
        for( unsigned int j = 0; j < columns; ++j ) {
            elements[ i ][ j ] = lhs_elements[ j ][ i ];
        }
    }
    
    result_elements = elements;
    result_rows = rows;
    result_columns = columns;
    
    return true;
}

void destroy( float ** elements,
              unsigned int rows )
{
    for( unsigned int i = 0; i < rows; ++i ) {
        delete [] elements[ i ];
    }
    delete [] elements;
}

auto create( unsigned int rows,
             unsigned int columns,
             float filler ) -> float **
{
    auto elements = new float *[ rows ];
    for( unsigned int i = 0; i < rows; ++i ) {
        elements[ i ] = new float[ columns ];
        for( unsigned int j = 0; j < columns; ++j ) {
            elements[ i ][ j ] = filler;
        }
    }
    
    return elements;
}

bool truncate( float ** lhs_elements,
               unsigned int lhs_rows,
               unsigned int lhs_columns,
               unsigned int new_rows,
               unsigned int new_columns,
               unsigned int start_row_index,
               unsigned int start_colmn_index,
               float ** & result_elements,
               unsigned int & result_rows,
               unsigned int & result_columns )
{
    if( lhs_rows < start_row_index + new_rows || lhs_columns < start_colmn_index + new_columns ) {
        return false;
    }
    
    auto rows = new_rows;
    auto columns = new_columns;
    
    auto elements = new float *[ rows ];
    for( unsigned int i = 0; i < rows; ++i ) {
        elements[ i ] = new float[ columns ];
        for( unsigned int j = 0; j < columns; ++j ) {
            elements[ i ][ j ] = lhs_elements[ i + start_row_index ][ j + start_colmn_index ];
        }
    }
    
    result_elements = elements;
    result_rows = rows;
    result_columns = columns;
    
    return true;
}

auto output( std::ostream & stream, float ** elements, unsigned int rows, unsigned int columns ) -> std::ostream &
{
    bool success = true;
    for( unsigned int i = 0; i < rows && success; ++i ) {
        for( unsigned int j = 0; j < columns; ++j ) {
            stream.width( 4 );
            if( !( stream << elements[ i ][ j ] << '\t' ) ) {
                success = false;
                break;
            }
        }
        stream << '\n';
    }
        
    return stream;
}

bool reverse( float ** lhs_elements,
              unsigned int lhs_rows,
              unsigned int lhs_columns,
              float ** & result_elements,
              unsigned int & result_rows,
              unsigned int & result_columns )
{
    if( lhs_rows != lhs_columns ) {
        return false;
    }
    
    auto rows = lhs_rows;
    auto columns = lhs_columns * 2;
    auto elements = new float *[ rows ];
    for( unsigned int i = 0; i < rows; ++i ) {
        elements[ i ] = new float[ columns ];
        for( unsigned int j = 0; j < columns; ++j ) {
            if( j < lhs_columns ) {
                elements[ i ][ j ] = lhs_elements[ i ][ j ];
            }
            else {
                elements[ i ][ j ] = i == j - lhs_columns ? 1 : 0;
            }
        }
    }
    
    bool reversible = true;
    for( unsigned int j = 0; j < lhs_columns && !reversible; ++j ) {
        for( unsigned int i = 0; i < rows; ++i ) {
            auto expected = i == j ? 1.0f : 0.0f;
            auto element = elements[ i ][ j ];
            
            if( element != expected ) {
                if( ( expected == 1.0f && element == 0.0f ) || expected == 0.0f ) {
                    bool found = false;
                    float multiplier = 0.0f;
                    unsigned int k = 0;
                    for( ; k < rows; ++k) {
                        if(  k != i && elements[ k ][ j ] != 0.0f ) {
                            multiplier = ( expected - element ) / elements[ k ][ j ];
                            found = true;
                            break;
                        }
                    }
                    if( found ) {
                        for( int l = 0; l < columns; ++l ) {
                            elements[ i ][ l ] += elements[ k ][ l ] * multiplier;
                        }
                    }
                    else {
                        reversible = false;
                        break;
                    }
                }
                else if ( expected == 1.0f && element != 0.0f ) {
                    auto multiplier = expected / element;
                    for( int l = 0; l < columns; ++l ) {
                        elements[ i ][ l ] *= multiplier;
                    }
                }
            }
        }
    }
    
    bool success = reversible;
    if( reversible ) {
        success = truncate( elements, rows, columns, rows, lhs_columns, 0, lhs_columns, result_elements, result_rows, result_columns );
    }
    
    destroy( elements, rows );
    
    return success;
}
