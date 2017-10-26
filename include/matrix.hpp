#include <iosfwd>

bool equal( float ** lhs_elements,
            unsigned int lhs_rows,
            unsigned int lhs_columns,
            float ** rhs_elements,
            unsigned int rhs_rows,
            unsigned int rhs_columns );

bool add( float ** lhs_elements,
          unsigned int lhs_rows,
          unsigned int lhs_columns,
          float ** rhs_elements,
          unsigned int rhs_rows,
          unsigned int rhs_columns,
          float ** & result_elements,
          unsigned int & result_rows,
          unsigned int & result_columns );

bool sub( float ** lhs_elements,
          unsigned int lhs_rows,
          unsigned int lhs_columns,
          float ** rhs_elements,
          unsigned int rhs_rows,
          unsigned int rhs_columns,
          float ** & result_elements,
          unsigned int & result_rows,
          unsigned int & result_columns );

bool multiply( float ** lhs_elements,
               unsigned int lhs_rows,
               unsigned int lhs_columns,
               float ** rhs_elements,
               unsigned int rhs_rows,
               unsigned int rhs_columns,
               float ** & result_elements,
               unsigned int & result_rows,
               unsigned int & result_columns );

auto input( std::istream & stream, 
            float ** & result_elements, 
            unsigned int & result_rows, 
            unsigned int & result_columns ) -> std::istream &;

bool transpose( float ** lhs_elements,
                unsigned int lhs_rows,
                unsigned int lhs_columns,
                float ** & result_elements,
                unsigned int & result_rows,
                unsigned int & result_columns );

void destroy( float ** elements,
              unsigned int rows );

auto create( unsigned int rows,
             unsigned int columns,
             float filler = 0.0f ) -> float **;

bool truncate( float ** lhs_elements,
               unsigned int lhs_rows,
               unsigned int lhs_columns,
               unsigned int new_rows,
               unsigned int new_columns,
               unsigned int start_row_index,
               unsigned int start_colmn_index,
               float ** & result_elements,
               unsigned int & result_rows,
               unsigned int & result_columns );

auto output( std::ostream & stream, 
             float ** elements, 
             unsigned int rows, 
             unsigned int columns ) -> std::ostream &;

bool reverse( float ** lhs_elements,
              unsigned int lhs_rows,
              unsigned int lhs_columns,
              float ** & result_elements,
              unsigned int & result_rows,
              unsigned int & result_columns );
