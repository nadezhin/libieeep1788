//
//                              libieeep1788
//
//   An implementation of the preliminary IEEE P1788 standard for
//   interval arithmetic
//
//
//   Copyright 2013 - 2015
//
//   Marco Nehmeier (nehmeier@informatik.uni-wuerzburg.de)
//   Department of Computer Science,
//   University of Wuerzburg, Germany
//
//   Licensed under the Apache License, Version 2.0 (the "License");
//   you may not use this file except in compliance with the License.
//   You may obtain a copy of the License at
//
//       http://www.apache.org/licenses/LICENSE-2.0
//
//   Unless required by applicable law or agreed to in writing, software
//   distributed under the License is distributed on an "AS IS" BASIS,
//   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//   See the License for the specific language governing permissions and
//   limitations under the License.

#define BOOST_TEST_MODULE "Integration: Boolean functions of intervals [infsup/interval, infsup/decorated_interval, p1788/flavor/infsup/setbased/mpfr_bin_ieee754_flavor]"
#include "test/util/boost_test_wrapper.hpp"


#include <limits>

#include "p1788/p1788.hpp"

template<typename T>
using I = p1788::infsup::interval<T, p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor>;
template<typename T>
using DI = p1788::infsup::decorated_interval<T, p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor>;



BOOST_AUTO_TEST_CASE(integration_is_empty_test)
{
    BOOST_CHECK(is_empty(I<double>::empty()));
    BOOST_CHECK(!is_empty(I<double>::entire()));
    BOOST_CHECK(I<double>::is_empty(I<double>::empty()));
    BOOST_CHECK(!I<double>::is_empty(I<double>::entire()));

    BOOST_CHECK(is_empty(DI<double>::empty()));
    BOOST_CHECK(!is_empty(DI<double>::entire()));
    BOOST_CHECK(DI<double>::is_empty(DI<double>::empty()));
    BOOST_CHECK(!DI<double>::is_empty(DI<double>::entire()));
}

BOOST_AUTO_TEST_CASE(integration_is_entire_test)
{
    BOOST_CHECK(!is_entire(I<double>::empty()));
    BOOST_CHECK(is_entire(I<double>::entire()));
    BOOST_CHECK(!I<double>::is_entire(I<double>::empty()));
    BOOST_CHECK(I<double>::is_entire(I<double>::entire()));

    BOOST_CHECK(!is_entire(DI<double>::empty()));
    BOOST_CHECK(is_entire(DI<double>::entire()));
    BOOST_CHECK(!DI<double>::is_entire(DI<double>::empty()));
    BOOST_CHECK(DI<double>::is_entire(DI<double>::entire()));
}

BOOST_AUTO_TEST_CASE(integration_is_nai_test)
{
    BOOST_CHECK(!is_nai(DI<double>::empty()));
    BOOST_CHECK(!is_nai(DI<double>::entire()));
    BOOST_CHECK(is_nai(DI<double>::nai()));
    BOOST_CHECK(!DI<double>::is_nai(DI<double>::empty()));
    BOOST_CHECK(!DI<double>::is_nai(DI<double>::entire()));
    BOOST_CHECK(DI<double>::is_nai(DI<double>::nai()));
}


BOOST_AUTO_TEST_CASE(integration_equal_test)
{
    BOOST_CHECK(equal(I<double>::empty(), I<double>::empty()));
    BOOST_CHECK(equal(I<double>::empty(), I<float>::empty()));
    BOOST_CHECK(!equal(I<double>::entire(), I<double>::empty()));
    BOOST_CHECK(!equal(I<double>::entire(), I<float>::empty()));
    BOOST_CHECK(equal(I<double>::entire(), I<double>::entire()));
    BOOST_CHECK(equal(I<double>::entire(), I<float>::entire()));
    BOOST_CHECK( I<double>::entire() != I<double>::empty() );
    BOOST_CHECK( I<double>::entire() != I<float>::empty() );
    BOOST_CHECK( I<double>::entire() == I<double>::entire() );
    BOOST_CHECK( I<double>::entire() == I<float>::entire() );
    BOOST_CHECK(I<double>::equal(I<double>::empty(), I<double>::empty()));
    BOOST_CHECK(I<double>::equal(I<double>::empty(), I<float>::empty()));
    BOOST_CHECK(!I<double>::equal(I<double>::entire(), I<double>::empty()));
    BOOST_CHECK(!I<double>::equal(I<double>::entire(), I<float>::empty()));
    BOOST_CHECK(I<double>::equal(I<double>::entire(), I<double>::entire()));
    BOOST_CHECK(I<double>::equal(I<double>::entire(), I<float>::entire()));

    BOOST_CHECK(equal(DI<double>::empty(), DI<double>::empty()));
    BOOST_CHECK(equal(DI<double>::empty(), DI<float>::empty()));
    BOOST_CHECK(!equal(DI<double>::entire(), DI<double>::empty()));
    BOOST_CHECK(!equal(DI<double>::entire(), DI<float>::empty()));
    BOOST_CHECK(equal(DI<double>::entire(), DI<double>::entire()));
    BOOST_CHECK(equal(DI<double>::entire(), DI<float>::entire()));
    BOOST_CHECK( DI<double>::entire() != DI<double>::empty() );
    BOOST_CHECK( DI<double>::entire() != DI<float>::empty() );
    BOOST_CHECK( DI<double>::entire() == DI<double>::entire() );
    BOOST_CHECK( DI<double>::entire() == DI<float>::entire() );
    BOOST_CHECK(DI<double>::equal(DI<double>::empty(), DI<double>::empty()));
    BOOST_CHECK(DI<double>::equal(DI<double>::empty(), DI<float>::empty()));
    BOOST_CHECK(!DI<double>::equal(DI<double>::entire(), DI<double>::empty()));
    BOOST_CHECK(!DI<double>::equal(DI<double>::entire(), DI<float>::empty()));
    BOOST_CHECK(DI<double>::equal(DI<double>::entire(), DI<double>::entire()));
    BOOST_CHECK(DI<double>::equal(DI<double>::entire(), DI<float>::entire()));
}

BOOST_AUTO_TEST_CASE(integration_subset_test)
{
    BOOST_CHECK(subset(I<double>(2.0,3.0), I<double>(1.0,3.0)));
    BOOST_CHECK(subset(I<double>(2.0,3.0), I<float>(1.0f,3.0f)));
    BOOST_CHECK(!subset(I<double>(-1.0,3.0), I<double>(2.0,3.0)));
    BOOST_CHECK(!subset(I<double>(-1.0,3.0), I<float>(2.0f,3.0f)));
    BOOST_CHECK(I<double>::subset(I<double>(2.0,3.0), I<double>(1.0,3.0)));
    BOOST_CHECK(I<double>::subset(I<double>(2.0,3.0), I<float>(1.0f,3.0f)));
    BOOST_CHECK(!I<double>::subset(I<double>(-1.0,3.0), I<double>(2.0,3.0)));
    BOOST_CHECK(!I<double>::subset(I<double>(-1.0,3.0), I<float>(2.0f,3.0f)));

    BOOST_CHECK(subset(DI<double>(2.0,3.0), DI<double>(1.0,3.0)));
    BOOST_CHECK(subset(DI<double>(2.0,3.0), DI<float>(1.0f,3.0f)));
    BOOST_CHECK(!subset(DI<double>(-1.0,3.0), DI<double>(2.0,3.0)));
    BOOST_CHECK(!subset(DI<double>(-1.0,3.0), DI<float>(2.0f,3.0f)));
    BOOST_CHECK(DI<double>::subset(DI<double>(2.0,3.0), DI<double>(1.0,3.0)));
    BOOST_CHECK(DI<double>::subset(DI<double>(2.0,3.0), DI<float>(1.0f,3.0f)));
    BOOST_CHECK(!DI<double>::subset(DI<double>(-1.0,3.0), DI<double>(2.0,3.0)));
    BOOST_CHECK(!DI<double>::subset(DI<double>(-1.0,3.0), DI<float>(2.0f,3.0f)));
}

BOOST_AUTO_TEST_CASE(integration_superset_test)
{
    BOOST_CHECK(!superset(I<double>(2.0,3.0), I<double>(1.0,3.0)));
    BOOST_CHECK(!superset(I<double>(2.0,3.0), I<float>(1.0f,3.0f)));
    BOOST_CHECK(superset(I<double>(-1.0,3.0), I<double>(2.0,3.0)));
    BOOST_CHECK(superset(I<double>(-1.0,3.0), I<float>(2.0f,3.0f)));
    BOOST_CHECK(!I<double>::superset(I<double>(2.0,3.0), I<double>(1.0,3.0)));
    BOOST_CHECK(!I<double>::superset(I<double>(2.0,3.0), I<float>(1.0f,3.0f)));
    BOOST_CHECK(I<double>::superset(I<double>(-1.0,3.0), I<double>(2.0,3.0)));
    BOOST_CHECK(I<double>::superset(I<double>(-1.0,3.0), I<float>(2.0f,3.0f)));

    BOOST_CHECK(!superset(DI<double>(2.0,3.0), DI<double>(1.0,3.0)));
    BOOST_CHECK(!superset(DI<double>(2.0,3.0), DI<float>(1.0f,3.0f)));
    BOOST_CHECK(superset(DI<double>(-1.0,3.0), DI<double>(2.0,3.0)));
    BOOST_CHECK(superset(DI<double>(-1.0,3.0), DI<float>(2.0f,3.0f)));
    BOOST_CHECK(!DI<double>::superset(DI<double>(2.0,3.0), DI<double>(1.0,3.0)));
    BOOST_CHECK(!DI<double>::superset(DI<double>(2.0,3.0), DI<float>(1.0f,3.0f)));
    BOOST_CHECK(DI<double>::superset(DI<double>(-1.0,3.0), DI<double>(2.0,3.0)));
    BOOST_CHECK(DI<double>::superset(DI<double>(-1.0,3.0), DI<float>(2.0f,3.0f)));
}

BOOST_AUTO_TEST_CASE(integration_less_test)
{
    BOOST_CHECK(less(I<double>(2.0,4.5), I<double>(4.0,5.0)));
    BOOST_CHECK(less(I<double>(2.0,4.5), I<float>(4.0f,5.0f)));
    BOOST_CHECK(!less(I<double>(-1.0,3.0), I<double>(-5.0,-3.0)));
    BOOST_CHECK(!less(I<double>(-1.0,3.0), I<float>(-5.0f,-3.0f)));
    BOOST_CHECK(I<double>::less(I<double>(2.0,4.5), I<double>(4.0,5.0)));
    BOOST_CHECK(I<double>::less(I<double>(2.0,4.5), I<float>(4.0f,5.0f)));
    BOOST_CHECK(!I<double>::less(I<double>(-1.0,3.0), I<double>(-5.0,-3.0)));
    BOOST_CHECK(!I<double>::less(I<double>(-1.0,3.0), I<float>(-5.0f,-3.0f)));

    BOOST_CHECK(less(DI<double>(2.0,4.5), DI<double>(4.0,5.0)));
    BOOST_CHECK(less(DI<double>(2.0,4.5), DI<float>(4.0f,5.0f)));
    BOOST_CHECK(!less(DI<double>(-1.0,3.0), DI<double>(-5.0,-3.0)));
    BOOST_CHECK(!less(DI<double>(-1.0,3.0), DI<float>(-5.0f,-3.0f)));
    BOOST_CHECK(DI<double>::less(DI<double>(2.0,4.5), DI<double>(4.0,5.0)));
    BOOST_CHECK(DI<double>::less(DI<double>(2.0,4.5), DI<float>(4.0f,5.0f)));
    BOOST_CHECK(!DI<double>::less(DI<double>(-1.0,3.0), DI<double>(-5.0,-3.0)));
    BOOST_CHECK(!DI<double>::less(DI<double>(-1.0,3.0), DI<float>(-5.0f,-3.0f)));
}

BOOST_AUTO_TEST_CASE(integration_greater_test)
{
    BOOST_CHECK(!greater(I<double>(2.0,3.0), I<double>(4.0,5.0)));
    BOOST_CHECK(!greater(I<double>(2.0,3.0), I<float>(4.0f,5.0f)));
    BOOST_CHECK(greater(I<double>(-1.0,3.0), I<double>(-5.0,-3.0)));
    BOOST_CHECK(greater(I<double>(-1.0,3.0), I<float>(-5.0f,-3.0f)));
    BOOST_CHECK(!I<double>::greater(I<double>(2.0,3.0), I<double>(4.0,5.0)));
    BOOST_CHECK(!I<double>::greater(I<double>(2.0,3.0), I<float>(4.0f,5.0f)));
    BOOST_CHECK(I<double>::greater(I<double>(-1.0,3.0), I<double>(-5.0,-3.0)));
    BOOST_CHECK(I<double>::greater(I<double>(-1.0,3.0), I<float>(-5.0f,-3.0f)));

    BOOST_CHECK(!greater(DI<double>(2.0,3.0), DI<double>(4.0,5.0)));
    BOOST_CHECK(!greater(DI<double>(2.0,3.0), DI<float>(4.0f,5.0f)));
    BOOST_CHECK(greater(DI<double>(-1.0,3.0), DI<double>(-5.0,-3.0)));
    BOOST_CHECK(greater(DI<double>(-1.0,3.0), DI<float>(-5.0f,-3.0f)));
    BOOST_CHECK(!DI<double>::greater(DI<double>(2.0,3.0), DI<double>(4.0,5.0)));
    BOOST_CHECK(!DI<double>::greater(DI<double>(2.0,3.0), DI<float>(4.0f,5.0f)));
    BOOST_CHECK(DI<double>::greater(DI<double>(-1.0,3.0), DI<double>(-5.0,-3.0)));
    BOOST_CHECK(DI<double>::greater(DI<double>(-1.0,3.0), DI<float>(-5.0f,-3.0f)));
}

BOOST_AUTO_TEST_CASE(integration_precedes_test)
{
    BOOST_CHECK(precedes(I<double>(2.0,4.0), I<double>(4.0,5.0)));
    BOOST_CHECK(precedes(I<double>(2.0,4.0), I<float>(4.0f,5.0f)));
    BOOST_CHECK(!precedes(I<double>(-1.0,3.0), I<double>(-5.0,-3.0)));
    BOOST_CHECK(!precedes(I<double>(-1.0,3.0), I<float>(-5.0f,-3.0f)));
    BOOST_CHECK(I<double>::precedes(I<double>(2.0,4.0), I<double>(4.0,5.0)));
    BOOST_CHECK(I<double>::precedes(I<double>(2.0,4.0), I<float>(4.0f,5.0f)));
    BOOST_CHECK(!I<double>::precedes(I<double>(-1.0,3.0), I<double>(-5.0,-3.0)));
    BOOST_CHECK(!I<double>::precedes(I<double>(-1.0,3.0), I<float>(-5.0f,-3.0f)));

    BOOST_CHECK(precedes(DI<double>(2.0,4.0), DI<double>(4.0,5.0)));
    BOOST_CHECK(precedes(DI<double>(2.0,4.0), DI<float>(4.0f,5.0f)));
    BOOST_CHECK(!precedes(DI<double>(-1.0,3.0), DI<double>(-5.0,-3.0)));
    BOOST_CHECK(!precedes(DI<double>(-1.0,3.0), DI<float>(-5.0f,-3.0f)));
    BOOST_CHECK(DI<double>::precedes(DI<double>(2.0,4.0), DI<double>(4.0,5.0)));
    BOOST_CHECK(DI<double>::precedes(DI<double>(2.0,4.0), DI<float>(4.0f,5.0f)));
    BOOST_CHECK(!DI<double>::precedes(DI<double>(-1.0,3.0), DI<double>(-5.0,-3.0)));
    BOOST_CHECK(!DI<double>::precedes(DI<double>(-1.0,3.0), DI<float>(-5.0f,-3.0f)));
}

BOOST_AUTO_TEST_CASE(integration_succeeds_test)
{
    BOOST_CHECK(!succeeds(I<double>(2.0,3.0), I<double>(4.0,5.0)));
    BOOST_CHECK(!succeeds(I<double>(2.0,3.0), I<float>(4.0f,5.0f)));
    BOOST_CHECK(succeeds(I<double>(-1.0,3.0), I<double>(-5.0,-1.0)));
    BOOST_CHECK(succeeds(I<double>(-1.0,3.0), I<float>(-5.0f,-1.0f)));
    BOOST_CHECK(!I<double>::succeeds(I<double>(2.0,3.0), I<double>(4.0,5.0)));
    BOOST_CHECK(!I<double>::succeeds(I<double>(2.0,3.0), I<float>(4.0f,5.0f)));
    BOOST_CHECK(I<double>::succeeds(I<double>(-1.0,3.0), I<double>(-5.0,-1.0)));
    BOOST_CHECK(I<double>::succeeds(I<double>(-1.0,3.0), I<float>(-5.0f,-1.0f)));

    BOOST_CHECK(!succeeds(DI<double>(2.0,3.0), DI<double>(4.0,5.0)));
    BOOST_CHECK(!succeeds(DI<double>(2.0,3.0), DI<float>(4.0f,5.0f)));
    BOOST_CHECK(succeeds(DI<double>(-1.0,3.0), DI<double>(-5.0,-1.0)));
    BOOST_CHECK(succeeds(DI<double>(-1.0,3.0), DI<float>(-5.0f,-1.0f)));
    BOOST_CHECK(!DI<double>::succeeds(DI<double>(2.0,3.0), DI<double>(4.0,5.0)));
    BOOST_CHECK(!DI<double>::succeeds(DI<double>(2.0,3.0), DI<float>(4.0f,5.0f)));
    BOOST_CHECK(DI<double>::succeeds(DI<double>(-1.0,3.0), DI<double>(-5.0,-1.0)));
    BOOST_CHECK(DI<double>::succeeds(DI<double>(-1.0,3.0), DI<float>(-5.0f,-1.0f)));
}

BOOST_AUTO_TEST_CASE(integration_interior_test)
{
    BOOST_CHECK(interior(I<double>(2.0,3.0), I<double>(0.0,5.0)));
    BOOST_CHECK(interior(I<double>(2.0,3.0), I<float>(0.0f,5.0f)));
    BOOST_CHECK(!interior(I<double>(-1.0,3.0), I<double>(-5.0,-3.0)));
    BOOST_CHECK(!interior(I<double>(-1.0,3.0), I<float>(-5.0f,-3.0f)));
    BOOST_CHECK(I<double>::interior(I<double>(2.0,3.0), I<double>(0.0,5.0)));
    BOOST_CHECK(I<double>::interior(I<double>(2.0,3.0), I<float>(0.0f,5.0f)));
    BOOST_CHECK(!I<double>::interior(I<double>(-1.0,3.0), I<double>(-5.0,-3.0)));
    BOOST_CHECK(!I<double>::interior(I<double>(-1.0,3.0), I<float>(-5.0f,-3.0f)));

    BOOST_CHECK(interior(DI<double>(2.0,3.0), DI<double>(0.0,5.0)));
    BOOST_CHECK(interior(DI<double>(2.0,3.0), DI<float>(0.0f,5.0f)));
    BOOST_CHECK(!interior(DI<double>(-1.0,3.0), DI<double>(-5.0,-3.0)));
    BOOST_CHECK(!interior(DI<double>(-1.0,3.0), DI<float>(-5.0f,-3.0f)));
    BOOST_CHECK(DI<double>::interior(DI<double>(2.0,3.0), DI<double>(0.0,5.0)));
    BOOST_CHECK(DI<double>::interior(DI<double>(2.0,3.0), DI<float>(0.0f,5.0f)));
    BOOST_CHECK(!DI<double>::interior(DI<double>(-1.0,3.0), DI<double>(-5.0,-3.0)));
    BOOST_CHECK(!DI<double>::interior(DI<double>(-1.0,3.0), DI<float>(-5.0f,-3.0f)));
}

BOOST_AUTO_TEST_CASE(integration_contains_interior_test)
{
    BOOST_CHECK(contains_interior(I<double>(-2.0,13.0), I<double>(0.0,5.0)));
    BOOST_CHECK(contains_interior(I<double>(-2.0,13.0), I<float>(0.0f,5.0f)));
    BOOST_CHECK(!contains_interior(I<double>(-1.0,3.0), I<double>(-5.0,-3.0)));
    BOOST_CHECK(!contains_interior(I<double>(-1.0,3.0), I<float>(-5.0f,-3.0f)));
    BOOST_CHECK(I<double>::contains_interior(I<double>(-2.0,13.0), I<double>(0.0,5.0)));
    BOOST_CHECK(I<double>::contains_interior(I<double>(-2.0,13.0), I<float>(0.0f,5.0f)));
    BOOST_CHECK(!I<double>::contains_interior(I<double>(-1.0,3.0), I<double>(-5.0,-3.0)));
    BOOST_CHECK(!I<double>::contains_interior(I<double>(-1.0,3.0), I<float>(-5.0f,-3.0f)));

    BOOST_CHECK(contains_interior(DI<double>(-2.0,13.0), DI<double>(0.0,5.0)));
    BOOST_CHECK(contains_interior(DI<double>(-2.0,13.0), DI<float>(0.0f,5.0f)));
    BOOST_CHECK(!contains_interior(DI<double>(-1.0,3.0), DI<double>(-5.0,-3.0)));
    BOOST_CHECK(!contains_interior(DI<double>(-1.0,3.0), DI<float>(-5.0f,-3.0f)));
    BOOST_CHECK(DI<double>::contains_interior(DI<double>(-2.0,13.0), DI<double>(0.0,5.0)));
    BOOST_CHECK(DI<double>::contains_interior(DI<double>(-2.0,13.0), DI<float>(0.0f,5.0f)));
    BOOST_CHECK(!DI<double>::contains_interior(DI<double>(-1.0,3.0), DI<double>(-5.0,-3.0)));
    BOOST_CHECK(!DI<double>::contains_interior(DI<double>(-1.0,3.0), DI<float>(-5.0f,-3.0f)));
}

BOOST_AUTO_TEST_CASE(integration_strict_less_test)
{
    BOOST_CHECK(strict_less(I<double>(2.0,3.0), I<double>(4.0,5.0)));
    BOOST_CHECK(strict_less(I<double>(2.0,3.0), I<float>(4.0f,5.0f)));
    BOOST_CHECK(!strict_less(I<double>(-1.0,3.0), I<double>(-5.0,-3.0)));
    BOOST_CHECK(!strict_less(I<double>(-1.0,3.0), I<float>(-5.0f,-3.0f)));
    BOOST_CHECK(I<double>::strict_less(I<double>(2.0,3.0), I<double>(4.0,5.0)));
    BOOST_CHECK(I<double>::strict_less(I<double>(2.0,3.0), I<float>(4.0f,5.0f)));
    BOOST_CHECK(!I<double>::strict_less(I<double>(-1.0,3.0), I<double>(-5.0,-3.0)));
    BOOST_CHECK(!I<double>::strict_less(I<double>(-1.0,3.0), I<float>(-5.0f,-3.0f)));

    BOOST_CHECK(strict_less(DI<double>(2.0,3.0), DI<double>(4.0,5.0)));
    BOOST_CHECK(strict_less(DI<double>(2.0,3.0), DI<float>(4.0f,5.0f)));
    BOOST_CHECK(!strict_less(DI<double>(-1.0,3.0), DI<double>(-5.0,-3.0)));
    BOOST_CHECK(!strict_less(DI<double>(-1.0,3.0), DI<float>(-5.0f,-3.0f)));
    BOOST_CHECK(DI<double>::strict_less(DI<double>(2.0,3.0), DI<double>(4.0,5.0)));
    BOOST_CHECK(DI<double>::strict_less(DI<double>(2.0,3.0), DI<float>(4.0f,5.0f)));
    BOOST_CHECK(!DI<double>::strict_less(DI<double>(-1.0,3.0), DI<double>(-5.0,-3.0)));
    BOOST_CHECK(!DI<double>::strict_less(DI<double>(-1.0,3.0), DI<float>(-5.0f,-3.0f)));
}

BOOST_AUTO_TEST_CASE(integration_strict_greater_test)
{
    BOOST_CHECK(!strict_greater(I<double>(2.0,3.0), I<double>(4.0,5.0)));
    BOOST_CHECK(!strict_greater(I<double>(2.0,3.0), I<float>(4.0f,5.0f)));
    BOOST_CHECK(strict_greater(I<double>(-1.0,3.0), I<double>(-5.0,-3.0)));
    BOOST_CHECK(strict_greater(I<double>(-1.0,3.0), I<float>(-5.0f,-3.0f)));
    BOOST_CHECK(!I<double>::strict_greater(I<double>(2.0,3.0), I<double>(4.0,5.0)));
    BOOST_CHECK(!I<double>::strict_greater(I<double>(2.0,3.0), I<float>(4.0f,5.0f)));
    BOOST_CHECK(I<double>::strict_greater(I<double>(-1.0,3.0), I<double>(-5.0,-3.0)));
    BOOST_CHECK(I<double>::strict_greater(I<double>(-1.0,3.0), I<float>(-5.0f,-3.0f)));

    BOOST_CHECK(!strict_greater(DI<double>(2.0,3.0), DI<double>(4.0,5.0)));
    BOOST_CHECK(!strict_greater(DI<double>(2.0,3.0), DI<float>(4.0f,5.0f)));
    BOOST_CHECK(strict_greater(DI<double>(-1.0,3.0), DI<double>(-5.0,-3.0)));
    BOOST_CHECK(strict_greater(DI<double>(-1.0,3.0), DI<float>(-5.0f,-3.0f)));
    BOOST_CHECK(!DI<double>::strict_greater(DI<double>(2.0,3.0), DI<double>(4.0,5.0)));
    BOOST_CHECK(!DI<double>::strict_greater(DI<double>(2.0,3.0), DI<float>(4.0f,5.0f)));
    BOOST_CHECK(DI<double>::strict_greater(DI<double>(-1.0,3.0), DI<double>(-5.0,-3.0)));
    BOOST_CHECK(DI<double>::strict_greater(DI<double>(-1.0,3.0), DI<float>(-5.0f,-3.0f)));
}

BOOST_AUTO_TEST_CASE(integration_strict_precedes_test)
{
    BOOST_CHECK(strict_precedes(I<double>(2.0,3.0), I<double>(4.0,5.0)));
    BOOST_CHECK(strict_precedes(I<double>(2.0,3.0), I<float>(4.0f,5.0f)));
    BOOST_CHECK(!strict_precedes(I<double>(-1.0,3.0), I<double>(-5.0,-3.0)));
    BOOST_CHECK(!strict_precedes(I<double>(-1.0,3.0), I<float>(-5.0f,-3.0f)));
    BOOST_CHECK(I<double>::strict_precedes(I<double>(2.0,3.0), I<double>(4.0,5.0)));
    BOOST_CHECK(I<double>::strict_precedes(I<double>(2.0,3.0), I<float>(4.0f,5.0f)));
    BOOST_CHECK(!I<double>::strict_precedes(I<double>(-1.0,3.0), I<double>(-5.0,-3.0)));
    BOOST_CHECK(!I<double>::strict_precedes(I<double>(-1.0,3.0), I<float>(-5.0f,-3.0f)));

    BOOST_CHECK(strict_precedes(DI<double>(2.0,3.0), DI<double>(4.0,5.0)));
    BOOST_CHECK(strict_precedes(DI<double>(2.0,3.0), DI<float>(4.0f,5.0f)));
    BOOST_CHECK(!strict_precedes(DI<double>(-1.0,3.0), DI<double>(-5.0,-3.0)));
    BOOST_CHECK(!strict_precedes(DI<double>(-1.0,3.0), DI<float>(-5.0f,-3.0f)));
    BOOST_CHECK(DI<double>::strict_precedes(DI<double>(2.0,3.0), DI<double>(4.0,5.0)));
    BOOST_CHECK(DI<double>::strict_precedes(DI<double>(2.0,3.0), DI<float>(4.0f,5.0f)));
    BOOST_CHECK(!DI<double>::strict_precedes(DI<double>(-1.0,3.0), DI<double>(-5.0,-3.0)));
    BOOST_CHECK(!DI<double>::strict_precedes(DI<double>(-1.0,3.0), DI<float>(-5.0f,-3.0f)));
}

BOOST_AUTO_TEST_CASE(integration_strict_succeeds_test)
{
    BOOST_CHECK(!strict_succeeds(I<double>(2.0,3.0), I<double>(4.0,5.0)));
    BOOST_CHECK(!strict_succeeds(I<double>(2.0,3.0), I<float>(4.0f,5.0f)));
    BOOST_CHECK(strict_succeeds(I<double>(-1.0,3.0), I<double>(-5.0,-3.0)));
    BOOST_CHECK(strict_succeeds(I<double>(-1.0,3.0), I<float>(-5.0f,-3.0f)));
    BOOST_CHECK(!I<double>::strict_succeeds(I<double>(2.0,3.0), I<double>(4.0,5.0)));
    BOOST_CHECK(!I<double>::strict_succeeds(I<double>(2.0,3.0), I<float>(4.0f,5.0f)));
    BOOST_CHECK(I<double>::strict_succeeds(I<double>(-1.0,3.0), I<double>(-5.0,-3.0)));
    BOOST_CHECK(I<double>::strict_succeeds(I<double>(-1.0,3.0), I<float>(-5.0f,-3.0f)));

    BOOST_CHECK(!strict_succeeds(DI<double>(2.0,3.0), DI<double>(4.0,5.0)));
    BOOST_CHECK(!strict_succeeds(DI<double>(2.0,3.0), DI<float>(4.0f,5.0f)));
    BOOST_CHECK(strict_succeeds(DI<double>(-1.0,3.0), DI<double>(-5.0,-3.0)));
    BOOST_CHECK(strict_succeeds(DI<double>(-1.0,3.0), DI<float>(-5.0f,-3.0f)));
    BOOST_CHECK(!DI<double>::strict_succeeds(DI<double>(2.0,3.0), DI<double>(4.0,5.0)));
    BOOST_CHECK(!DI<double>::strict_succeeds(DI<double>(2.0,3.0), DI<float>(4.0f,5.0f)));
    BOOST_CHECK(DI<double>::strict_succeeds(DI<double>(-1.0,3.0), DI<double>(-5.0,-3.0)));
    BOOST_CHECK(DI<double>::strict_succeeds(DI<double>(-1.0,3.0), DI<float>(-5.0f,-3.0f)));
}

BOOST_AUTO_TEST_CASE(integration_disjoint_test)
{
    BOOST_CHECK(disjoint(I<double>(2.0,3.0), I<double>(4.0,5.0)));
    BOOST_CHECK(disjoint(I<double>(2.0,3.0), I<float>(4.0f,5.0f)));
    BOOST_CHECK(!disjoint(I<double>(-1.0,3.0), I<double>(-5.0,0.0)));
    BOOST_CHECK(!disjoint(I<double>(-1.0,3.0), I<float>(-5.0f,0.0f)));
    BOOST_CHECK(I<double>::disjoint(I<double>(2.0,3.0), I<double>(4.0,5.0)));
    BOOST_CHECK(I<double>::disjoint(I<double>(2.0,3.0), I<float>(4.0f,5.0f)));
    BOOST_CHECK(!I<double>::disjoint(I<double>(-1.0,3.0), I<double>(-5.0,0.0)));
    BOOST_CHECK(!I<double>::disjoint(I<double>(-1.0,3.0), I<float>(-5.0f,0.0f)));

    BOOST_CHECK(disjoint(DI<double>(2.0,3.0), DI<double>(4.0,5.0)));
    BOOST_CHECK(disjoint(DI<double>(2.0,3.0), DI<float>(4.0f,5.0f)));
    BOOST_CHECK(!disjoint(DI<double>(-1.0,3.0), DI<double>(-5.0,0.0)));
    BOOST_CHECK(!disjoint(DI<double>(-1.0,3.0), DI<float>(-5.0f,0.0f)));
    BOOST_CHECK(DI<double>::disjoint(DI<double>(2.0,3.0), DI<double>(4.0,5.0)));
    BOOST_CHECK(DI<double>::disjoint(DI<double>(2.0,3.0), DI<float>(4.0f,5.0f)));
    BOOST_CHECK(!DI<double>::disjoint(DI<double>(-1.0,3.0), DI<double>(-5.0,0.0)));
    BOOST_CHECK(!DI<double>::disjoint(DI<double>(-1.0,3.0), DI<float>(-5.0f,0.0f)));
}

