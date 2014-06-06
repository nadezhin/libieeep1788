//
//                              libieeep1788
//
//   An implementation of the preliminary IEEE P1788 standard for
//   interval arithmetic
//
//
//   Copyright 2013
//
//   Marco Nehmeier (nehmeier@informatik.uni-wuerzburg.de)
//   Institute of Computer Science,
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

#define BOOST_TEST_MODULE "Recommended div to pair function [inf-sup-interval, mpfr_flavor]"
#include "test/util/boost_test_wrapper.hpp"

#include <limits>
#include "p1788/p1788.hpp"

template<typename T>
using flavor = p1788::flavor::infsup::mpfr_flavor<T, p1788::flavor::infsup::subnormalize::yes>;

template<typename T>
using I = p1788::infsup::interval<T, flavor>;

const double INF = std::numeric_limits<double>::infinity();

BOOST_AUTO_TEST_CASE(minimal_div_to_pair_test)
{
    BOOST_CHECK_EQUAL( div_to_pair(I<double>::empty(), I<double>::empty()).first, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>::empty(), I<double>::empty()).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-1.0,1.0), I<double>::empty()).first, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-1.0,1.0), I<double>::empty()).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>::empty(), I<double>(-1.0,1.0)).first, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>::empty(), I<double>(-1.0,1.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>::empty(), I<double>(0.1,1.0)).first, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>::empty(), I<double>(0.1,1.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>::empty(), I<double>(-1.0,-0.1)).first, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>::empty(), I<double>(-1.0,-0.1)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>::empty(), I<double>::entire()).first, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>::empty(), I<double>::entire()).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>::entire(), I<double>::empty()).first, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>::entire(), I<double>::empty()).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(0.0), I<double>::empty()).first, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(0.0), I<double>::empty()).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>::empty(), I<double>(0.0)).first, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>::empty(), I<double>(0.0)).second, I<double>::empty() );

    BOOST_CHECK_EQUAL( div_to_pair(I<double>::entire(), I<double>(-5.0, -3.0)).first, I<double>::entire() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>::entire(), I<double>(-5.0, -3.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>::entire(), I<double>(3.0, 5.0)).first, I<double>::entire() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>::entire(), I<double>(3.0, 5.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>::entire(), I<double>(-INF, -3.0)).first, I<double>::entire() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>::entire(), I<double>(-INF, -3.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>::entire(), I<double>(3.0,INF)).first, I<double>::entire() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>::entire(), I<double>(3.0,INF)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>::entire(), I<double>(0.0)).first, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>::entire(), I<double>(0.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>::entire(), I<double>(-3.0, 0.0)).first, I<double>::entire() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>::entire(), I<double>(-3.0, 0.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>::entire(), I<double>(-3.0, 3.0)).first, I<double>::entire() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>::entire(), I<double>(-3.0, 3.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>::entire(), I<double>(0.0, 3.0)).first, I<double>::entire() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>::entire(), I<double>(0.0, 3.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>::entire(), I<double>(-INF, 0.0)).first, I<double>::entire() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>::entire(), I<double>(-INF, 0.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>::entire(), I<double>(-INF, 3.0)).first, I<double>::entire() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>::entire(), I<double>(-INF, 3.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>::entire(), I<double>(-3.0, INF)).first, I<double>::entire() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>::entire(), I<double>(-3.0, INF)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>::entire(), I<double>(0.0, INF)).first, I<double>::entire() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>::entire(), I<double>(0.0, INF)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>::entire(), I<double>::entire()).first, I<double>::entire() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>::entire(), I<double>::entire()).second, I<double>::empty() );

    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-30.0,-15.0), I<double>(-5.0, -3.0)).first, I<double>(3.0,10.0) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-30.0,-15.0), I<double>(-5.0, -3.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-30.0,-15.0), I<double>(3.0, 5.0)).first, I<double>(-10.0,-3.0) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-30.0,-15.0), I<double>(3.0, 5.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-30.0,-15.0), I<double>(-INF, -3.0)).first, I<double>(0.0,10.0) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-30.0,-15.0), I<double>(-INF, -3.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-30.0,-15.0), I<double>(3.0,INF)).first, I<double>(-10.0,0.0) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-30.0,-15.0), I<double>(3.0,INF)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-30.0,-15.0), I<double>(0.0)).first, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-30.0,-15.0), I<double>(0.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-30.0,-15.0), I<double>(-3.0, 0.0)).first, I<double>(5.0,INF) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-30.0,-15.0), I<double>(-3.0, 0.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-30.0,-15.0), I<double>(-3.0, 3.0)).first, I<double>(-INF,-5.0) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-30.0,-15.0), I<double>(-3.0, 3.0)).second, I<double>(5.0,INF) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-30.0,-15.0), I<double>(0.0, 3.0)).first, I<double>(-INF,-5.0) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-30.0,-15.0), I<double>(0.0, 3.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-30.0,-15.0), I<double>(-INF, 0.0)).first, I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-30.0,-15.0), I<double>(-INF, 0.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-30.0,-15.0), I<double>(-INF, 3.0)).first, I<double>(-INF,-5.0) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-30.0,-15.0), I<double>(-INF, 3.0)).second, I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-30.0,-15.0), I<double>(-3.0, INF)).first, I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-30.0,-15.0), I<double>(-3.0, INF)).second, I<double>(5.0,INF) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-30.0,-15.0), I<double>(0.0, INF)).first, I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-30.0,-15.0), I<double>(0.0, INF)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-30.0,-15.0), I<double>::entire()).first, I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-30.0,-15.0), I<double>::entire()).second, I<double>(0.0,INF) );

    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-30.0,15.0), I<double>(-5.0, -3.0)).first, I<double>(-5.0,10.0) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-30.0,15.0), I<double>(-5.0, -3.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-30.0,15.0), I<double>(3.0, 5.0)).first, I<double>(-10.0,5.0) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-30.0,15.0), I<double>(3.0, 5.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-30.0,15.0), I<double>(-INF, -3.0)).first, I<double>(-5.0,10.0) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-30.0,15.0), I<double>(-INF, -3.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-30.0,15.0), I<double>(3.0,INF)).first, I<double>(-10.0,5.0) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-30.0,15.0), I<double>(3.0,INF)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-30.0,15.0), I<double>(0.0)).first, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-30.0,15.0), I<double>(0.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-30.0,15.0), I<double>(-3.0, 0.0)).first, I<double>::entire() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-30.0,15.0), I<double>(-3.0, 0.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-30.0,15.0), I<double>(-3.0, 3.0)).first, I<double>::entire() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-30.0,15.0), I<double>(-3.0, 3.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-30.0,15.0), I<double>(0.0, 3.0)).first, I<double>::entire() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-30.0,15.0), I<double>(0.0, 3.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-30.0,15.0), I<double>(-INF, 0.0)).first, I<double>::entire() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-30.0,15.0), I<double>(-INF, 0.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-30.0,15.0), I<double>(-INF, 3.0)).first, I<double>::entire() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-30.0,15.0), I<double>(-INF, 3.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-30.0,15.0), I<double>(-3.0, INF)).first, I<double>::entire() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-30.0,15.0), I<double>(-3.0, INF)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-30.0,15.0), I<double>(0.0, INF)).first, I<double>::entire() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-30.0,15.0), I<double>(0.0, INF)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-30.0,15.0), I<double>::entire()).first, I<double>::entire() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-30.0,15.0), I<double>::entire()).second, I<double>::empty() );

    BOOST_CHECK_EQUAL( div_to_pair(I<double>(15.0,30.0), I<double>(-5.0, -3.0)).first, I<double>(-10.0,-3.0) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(15.0,30.0), I<double>(-5.0, -3.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(15.0,30.0), I<double>(3.0, 5.0)).first, I<double>(3.0,10.0) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(15.0,30.0), I<double>(3.0, 5.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(15.0,30.0), I<double>(-INF, -3.0)).first, I<double>(-10.0,0.0) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(15.0,30.0), I<double>(-INF, -3.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(15.0,30.0), I<double>(3.0,INF)).first, I<double>(0.0,10.0) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(15.0,30.0), I<double>(3.0,INF)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(15.0,30.0), I<double>(0.0)).first, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(15.0,30.0), I<double>(0.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(15.0,30.0), I<double>(-3.0, 0.0)).first, I<double>(-INF,-5.0) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(15.0,30.0), I<double>(-3.0, 0.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(15.0,30.0), I<double>(-3.0, 3.0)).first, I<double>(-INF,-5.0) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(15.0,30.0), I<double>(-3.0, 3.0)).second, I<double>(5.0,INF) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(15.0,30.0), I<double>(0.0, 3.0)).first, I<double>(5.0,INF) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(15.0,30.0), I<double>(0.0, 3.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(15.0,30.0), I<double>(-INF, 0.0)).first, I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(15.0,30.0), I<double>(-INF, 0.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(15.0,30.0), I<double>(-INF, 3.0)).first, I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(15.0,30.0), I<double>(-INF, 3.0)).second, I<double>(5.0,INF) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(15.0,30.0), I<double>(-3.0, INF)).first, I<double>(-INF,-5.0) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(15.0,30.0), I<double>(-3.0, INF)).second, I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(15.0,30.0), I<double>(0.0, INF)).first, I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(15.0,30.0), I<double>(0.0, INF)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(15.0,30.0), I<double>::entire()).first, I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(15.0,30.0), I<double>::entire()).second, I<double>(0.0,INF) );

    BOOST_CHECK_EQUAL( div_to_pair(I<double>(0.0), I<double>(-5.0, -3.0)).first, I<double>(0.0) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(0.0), I<double>(-5.0, -3.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(0.0), I<double>(3.0, 5.0)).first, I<double>(0.0) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(0.0), I<double>(3.0, 5.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(0.0), I<double>(-INF, -3.0)).first, I<double>(0.0) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(0.0), I<double>(-INF, -3.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(0.0), I<double>(3.0,INF)).first, I<double>(0.0) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(0.0), I<double>(3.0,INF)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(0.0), I<double>(0.0)).first, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(0.0), I<double>(0.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(0.0), I<double>(-3.0, 0.0)).first, I<double>(0.0) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(0.0), I<double>(-3.0, 0.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(0.0), I<double>(-3.0, 3.0)).first, I<double>(0.0) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(0.0), I<double>(-3.0, 3.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(0.0), I<double>(0.0, 3.0)).first, I<double>(0.0) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(0.0), I<double>(0.0, 3.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(0.0), I<double>(-INF, 0.0)).first, I<double>(0.0) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(0.0), I<double>(-INF, 0.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(0.0), I<double>(-INF, 3.0)).first, I<double>(0.0) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(0.0), I<double>(-INF, 3.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(0.0), I<double>(-3.0, INF)).first, I<double>(0.0) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(0.0), I<double>(-3.0, INF)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(0.0), I<double>(0.0, INF)).first, I<double>(0.0) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(0.0), I<double>(0.0, INF)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(0.0), I<double>::entire()).first, I<double>(0.0) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(0.0), I<double>::entire()).second, I<double>::empty() );

    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-INF,-15.0), I<double>(-5.0, -3.0)).first, I<double>(3.0,INF) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-INF,-15.0), I<double>(-5.0, -3.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-INF,-15.0), I<double>(3.0, 5.0)).first, I<double>(-INF,-3.0) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-INF,-15.0), I<double>(3.0, 5.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-INF,-15.0), I<double>(-INF, -3.0)).first, I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-INF,-15.0), I<double>(-INF, -3.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-INF,-15.0), I<double>(3.0,INF)).first, I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-INF,-15.0), I<double>(3.0,INF)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-INF,-15.0), I<double>(0.0)).first, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-INF,-15.0), I<double>(0.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-INF,-15.0), I<double>(-3.0, 0.0)).first, I<double>(5.0,INF) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-INF,-15.0), I<double>(-3.0, 0.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-INF,-15.0), I<double>(-3.0, 3.0)).first, I<double>(-INF,-5.0) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-INF,-15.0), I<double>(-3.0, 3.0)).second, I<double>(5.0,INF) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-INF,-15.0), I<double>(0.0, 3.0)).first, I<double>(-INF,-5.0) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-INF,-15.0), I<double>(0.0, 3.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-INF,-15.0), I<double>(-INF, 0.0)).first, I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-INF,-15.0), I<double>(-INF, 0.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-INF,-15.0), I<double>(-INF, 3.0)).first, I<double>(-INF,-5.0) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-INF,-15.0), I<double>(-INF, 3.0)).second, I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-INF,-15.0), I<double>(-3.0, INF)).first, I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-INF,-15.0), I<double>(-3.0, INF)).second, I<double>(5.0,INF) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-INF,-15.0), I<double>(0.0, INF)).first, I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-INF,-15.0), I<double>(0.0, INF)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-INF,-15.0), I<double>::entire()).first, I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-INF,-15.0), I<double>::entire()).second, I<double>(0.0,INF) );

    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-INF,15.0), I<double>(-5.0, -3.0)).first, I<double>(-5.0,INF) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-INF,15.0), I<double>(-5.0, -3.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-INF,15.0), I<double>(3.0, 5.0)).first, I<double>(-INF,5.0) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-INF,15.0), I<double>(3.0, 5.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-INF,15.0), I<double>(-INF, -3.0)).first, I<double>(-5.0,INF) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-INF,15.0), I<double>(-INF, -3.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-INF,15.0), I<double>(3.0,INF)).first, I<double>(-INF,5.0) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-INF,15.0), I<double>(3.0,INF)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-INF,15.0), I<double>(0.0)).first, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-INF,15.0), I<double>(0.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-INF,15.0), I<double>(-3.0, 0.0)).first, I<double>::entire() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-INF,15.0), I<double>(-3.0, 0.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-INF,15.0), I<double>(-3.0, 3.0)).first, I<double>::entire() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-INF,15.0), I<double>(-3.0, 3.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-INF,15.0), I<double>(0.0, 3.0)).first, I<double>::entire() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-INF,15.0), I<double>(0.0, 3.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-INF,15.0), I<double>(-INF, 0.0)).first, I<double>::entire() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-INF,15.0), I<double>(-INF, 0.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-INF,15.0), I<double>(-INF, 3.0)).first, I<double>::entire() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-INF,15.0), I<double>(-INF, 3.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-INF,15.0), I<double>(-3.0, INF)).first, I<double>::entire() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-INF,15.0), I<double>(-3.0, INF)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-INF,15.0), I<double>(0.0, INF)).first, I<double>::entire() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-INF,15.0), I<double>(0.0, INF)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-INF,15.0), I<double>::entire()).first, I<double>::entire() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-INF,15.0), I<double>::entire()).second, I<double>::empty() );

    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-15.0,INF), I<double>(-5.0, -3.0)).first, I<double>(-INF,5.0) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-15.0,INF), I<double>(-5.0, -3.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-15.0,INF), I<double>(3.0, 5.0)).first, I<double>(-5.0,INF) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-15.0,INF), I<double>(3.0, 5.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-15.0,INF), I<double>(-INF, -3.0)).first, I<double>(-INF,5.0) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-15.0,INF), I<double>(-INF, -3.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-15.0,INF), I<double>(3.0,INF)).first, I<double>(-5.0,INF) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-15.0,INF), I<double>(3.0,INF)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-15.0,INF), I<double>(0.0)).first, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-15.0,INF), I<double>(0.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-15.0,INF), I<double>(-3.0, 0.0)).first, I<double>::entire() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-15.0,INF), I<double>(-3.0, 0.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-15.0,INF), I<double>(-3.0, 3.0)).first, I<double>::entire() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-15.0,INF), I<double>(-3.0, 3.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-15.0,INF), I<double>(0.0, 3.0)).first, I<double>::entire() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-15.0,INF), I<double>(0.0, 3.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-15.0,INF), I<double>(-INF, 0.0)).first, I<double>::entire() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-15.0,INF), I<double>(-INF, 0.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-15.0,INF), I<double>(-INF, 3.0)).first, I<double>::entire() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-15.0,INF), I<double>(-INF, 3.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-15.0,INF), I<double>(-3.0, INF)).first, I<double>::entire() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-15.0,INF), I<double>(-3.0, INF)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-15.0,INF), I<double>(0.0, INF)).first, I<double>::entire() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-15.0,INF), I<double>(0.0, INF)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-15.0,INF), I<double>::entire()).first, I<double>::entire() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-15.0,INF), I<double>::entire()).second, I<double>::empty() );

    BOOST_CHECK_EQUAL( div_to_pair(I<double>(15.0,INF), I<double>(-5.0, -3.0)).first, I<double>(-INF,-3.0) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(15.0,INF), I<double>(-5.0, -3.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(15.0,INF), I<double>(3.0, 5.0)).first, I<double>(3.0,INF) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(15.0,INF), I<double>(3.0, 5.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(15.0,INF), I<double>(-INF, -3.0)).first, I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(15.0,INF), I<double>(-INF, -3.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(15.0,INF), I<double>(3.0,INF)).first, I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(15.0,INF), I<double>(3.0,INF)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(15.0,INF), I<double>(0.0)).first, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(15.0,INF), I<double>(0.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(15.0,INF), I<double>(-3.0, 0.0)).first, I<double>(-INF,-5.0) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(15.0,INF), I<double>(-3.0, 0.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(15.0,INF), I<double>(-3.0, 3.0)).first, I<double>(-INF,-5.0)  );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(15.0,INF), I<double>(-3.0, 3.0)).second, I<double>(5.0,INF) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(15.0,INF), I<double>(0.0, 3.0)).first, I<double>(5.0,INF) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(15.0,INF), I<double>(0.0, 3.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(15.0,INF), I<double>(-INF, 0.0)).first, I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(15.0,INF), I<double>(-INF, 0.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(15.0,INF), I<double>(-INF, 3.0)).first, I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(15.0,INF), I<double>(-INF, 3.0)).second, I<double>(5.0,INF) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(15.0,INF), I<double>(-3.0, INF)).first, I<double>(-INF,-5.0) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(15.0,INF), I<double>(-3.0, INF)).second, I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(15.0,INF), I<double>(0.0, INF)).first, I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(15.0,INF), I<double>(0.0, INF)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(15.0,INF), I<double>::entire()).first, I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(15.0,INF), I<double>::entire()).second, I<double>(0.0,INF) );


    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-30.0,0.0), I<double>(-5.0, -3.0)).first, I<double>(0.0,10.0) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-30.0,0.0), I<double>(-5.0, -3.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-30.0,0.0), I<double>(3.0, 5.0)).first, I<double>(-10.0,0.0) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-30.0,0.0), I<double>(3.0, 5.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-30.0,0.0), I<double>(-INF, -3.0)).first, I<double>(0.0,10.0) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-30.0,0.0), I<double>(-INF, -3.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-30.0,0.0), I<double>(3.0,INF)).first, I<double>(-10.0,0.0) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-30.0,0.0), I<double>(3.0,INF)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-30.0,0.0), I<double>(0.0)).first, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-30.0,0.0), I<double>(0.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-30.0,0.0), I<double>(-3.0, 0.0)).first, I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-30.0,0.0), I<double>(-3.0, 0.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-30.0,0.0), I<double>(-3.0, 3.0)).first, I<double>::entire() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-30.0,0.0), I<double>(-3.0, 3.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-30.0,0.0), I<double>(0.0, 3.0)).first, I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-30.0,0.0), I<double>(0.0, 3.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-30.0,0.0), I<double>(-INF, 0.0)).first, I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-30.0,0.0), I<double>(-INF, 0.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-30.0,0.0), I<double>(-INF, 3.0)).first, I<double>::entire() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-30.0,0.0), I<double>(-INF, 3.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-30.0,0.0), I<double>(-3.0, INF)).first, I<double>::entire() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-30.0,0.0), I<double>(-3.0, INF)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-30.0,0.0), I<double>(0.0, INF)).first, I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-30.0,0.0), I<double>(0.0, INF)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-30.0,0.0), I<double>::entire()).first, I<double>::entire() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-30.0,0.0), I<double>::entire()).second, I<double>::empty() );

    BOOST_CHECK_EQUAL( div_to_pair(I<double>(0.0,30.0), I<double>(-5.0, -3.0)).first, I<double>(-10.0,0.0) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(0.0,30.0), I<double>(-5.0, -3.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(0.0,30.0), I<double>(3.0, 5.0)).first, I<double>(0.0,10.0) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(0.0,30.0), I<double>(3.0, 5.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(0.0,30.0), I<double>(-INF, -3.0)).first, I<double>(-10.0,0.0) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(0.0,30.0), I<double>(-INF, -3.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(0.0,30.0), I<double>(3.0,INF)).first, I<double>(0.0,10.0) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(0.0,30.0), I<double>(3.0,INF)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(0.0,30.0), I<double>(0.0)).first, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(0.0,30.0), I<double>(0.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(0.0,30.0), I<double>(-3.0, 0.0)).first, I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(0.0,30.0), I<double>(-3.0, 0.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(0.0,30.0), I<double>(-3.0, 3.0)).first, I<double>::entire() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(0.0,30.0), I<double>(-3.0, 3.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(0.0,30.0), I<double>(0.0, 3.0)).first, I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(0.0,30.0), I<double>(0.0, 3.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(0.0,30.0), I<double>(-INF, 0.0)).first, I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(0.0,30.0), I<double>(-INF, 0.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(0.0,30.0), I<double>(-INF, 3.0)).first, I<double>::entire() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(0.0,30.0), I<double>(-INF, 3.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(0.0,30.0), I<double>(-3.0, INF)).first, I<double>::entire() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(0.0,30.0), I<double>(-3.0, INF)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(0.0,30.0), I<double>(0.0, INF)).first, I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(0.0,30.0), I<double>(0.0, INF)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(0.0,30.0), I<double>::entire()).first, I<double>::entire() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(0.0,30.0), I<double>::entire()).second, I<double>::empty() );

    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-INF,0.0), I<double>(-5.0, -3.0)).first, I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-INF,0.0), I<double>(-5.0, -3.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-INF,0.0), I<double>(3.0, 5.0)).first, I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-INF,0.0), I<double>(3.0, 5.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-INF,0.0), I<double>(-INF, -3.0)).first, I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-INF,0.0), I<double>(-INF, -3.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-INF,0.0), I<double>(3.0,INF)).first, I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-INF,0.0), I<double>(3.0,INF)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-INF,0.0), I<double>(0.0)).first, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-INF,0.0), I<double>(0.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-INF,0.0), I<double>(-3.0, 0.0)).first, I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-INF,0.0), I<double>(-3.0, 0.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-INF,0.0), I<double>(-3.0, 3.0)).first, I<double>::entire() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-INF,0.0), I<double>(-3.0, 3.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-INF,0.0), I<double>(0.0, 3.0)).first, I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-INF,0.0), I<double>(0.0, 3.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-INF,0.0), I<double>(-INF, 0.0)).first, I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-INF,0.0), I<double>(-INF, 0.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-INF,0.0), I<double>(-INF, 3.0)).first, I<double>::entire() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-INF,0.0), I<double>(-INF, 3.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-INF,0.0), I<double>(-3.0, INF)).first, I<double>::entire() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-INF,0.0), I<double>(-3.0, INF)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-INF,0.0), I<double>(0.0, INF)).first, I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-INF,0.0), I<double>(0.0, INF)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-INF,0.0), I<double>::entire()).first, I<double>::entire() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-INF,0.0), I<double>::entire()).second, I<double>::empty() );

    BOOST_CHECK_EQUAL( div_to_pair(I<double>(0.0,INF), I<double>(-5.0, -3.0)).first, I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(0.0,INF), I<double>(-5.0, -3.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(0.0,INF), I<double>(3.0, 5.0)).first, I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(0.0,INF), I<double>(3.0, 5.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(0.0,INF), I<double>(-INF, -3.0)).first, I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(0.0,INF), I<double>(-INF, -3.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(0.0,INF), I<double>(3.0,INF)).first, I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(0.0,INF), I<double>(3.0,INF)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(0.0,INF), I<double>(0.0)).first, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(0.0,INF), I<double>(0.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(0.0,INF), I<double>(-3.0, 0.0)).first, I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(0.0,INF), I<double>(-3.0, 0.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(0.0,INF), I<double>(-3.0, 3.0)).first, I<double>::entire()  );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(0.0,INF), I<double>(-3.0, 3.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(0.0,INF), I<double>(0.0, 3.0)).first, I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(0.0,INF), I<double>(0.0, 3.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(0.0,INF), I<double>(-INF, 0.0)).first, I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(0.0,INF), I<double>(-INF, 0.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(0.0,INF), I<double>(-INF, 3.0)).first, I<double>::entire() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(0.0,INF), I<double>(-INF, 3.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(0.0,INF), I<double>(-3.0, INF)).first, I<double>::entire() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(0.0,INF), I<double>(-3.0, INF)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(0.0,INF), I<double>(0.0, INF)).first, I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(0.0,INF), I<double>(0.0, INF)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(0.0,INF), I<double>::entire()).first, I<double>::entire() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(0.0,INF), I<double>::entire()).second, I<double>::empty() );


    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-2.0,-1.0), I<double>(-10.0, -3.0)).first, I<double>(0X1.9999999999999P-4,0X1.5555555555556P-1) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-2.0,-1.0), I<double>(-10.0, -3.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-2.0,-1.0), I<double>(0.0, 10.0)).first, I<double>(-INF,-0X1.9999999999999P-4) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-2.0,-1.0), I<double>(0.0, 10.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-1.0,2.0), I<double>(10.0,INF)).first, I<double>(-0X1.999999999999AP-4,0X1.999999999999AP-3) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-1.0,2.0), I<double>(10.0,INF)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(1.0,3.0), I<double>(-INF, -10.0)).first, I<double>(-0X1.3333333333334P-2,0.0) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(1.0,3.0), I<double>(-INF, -10.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-INF,-1.0), I<double>(1.0, 3.0)).first, I<double>(-INF,-0X1.5555555555555P-2) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-INF,-1.0), I<double>(1.0, 3.0)).second, I<double>::empty() );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-30.0,-1.0), I<double>(-INF, 10.0)).first, I<double>(-INF,-0X1.9999999999999P-4) );
    BOOST_CHECK_EQUAL( div_to_pair(I<double>(-30.0,-1.0), I<double>(-INF, 10.0)).second, I<double>(0.0,INF) );
}
