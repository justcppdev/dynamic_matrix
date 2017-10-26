#include <catch.hpp>
#include "matrix.hpp"

TEST_CASE("add", "")
{
    unsigned int const lhs_rows = 3;
    unsigned int const lhs_columns = 3;
    auto lhs_elements = create( lhs_rows, lhs_columns, 1.0f );

    unsigned int const rhs_rows = 3;
    unsigned int const rhs_columns = 3;
    auto rhs_elements = create( rhs_rows, rhs_columns, 2.0f );
    
    unsigned int const expected_rows = 3;
    unsigned int const expected_columns = 3;
    auto expected_elements = create( rhs_rows, rhs_columns, 3.0f );

    unsigned int result_rows = 0;
    unsigned int result_columns = 0;
    float ** result_elements = nullptr;

    bool success = add( lhs_elements, lhs_rows, lhs_columns, rhs_elements, rhs_rows, rhs_columns, result_elements, result_rows, result_columns );
    REQUIRE( success );
    REQUIRE( equal( result_elements, result_rows, result_columns, expected_elements, expected_rows, expected_columns ) );

    destroy( result_elements, result_rows );
}
