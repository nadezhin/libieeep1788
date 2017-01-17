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
//   UnF<double>::less required by applicable law or agreed to in writing, software
//   distributed under the License is distributed on an "AS IS" BASIS,
//   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//   See the License for the specific language governing permissions and
//   limitations under the License.

#define BOOST_TEST_MODULE "Flavor: Boolean functions of intervals [p1788/flavor/infsup/setbased/mpfr_bin_ieee754_flavor]"
#include "test/util/boost_test_wrapper.hpp"

#include "p1788/exception/exception.hpp"
#include "p1788/decoration/decoration.hpp"
#include "p1788/flavor/infsup/setbased/mpfr_bin_ieee754_flavor.hpp"
#include "test/util/mpfr_bin_ieee754_flavor_io_test_util.hpp"

#include <limits>

template<typename T>
using F = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>;

template<typename T>
using REP = typename F<T>::representation;

template<typename T>
using REP_DEC = typename F<T>::representation_dec;

typedef p1788::decoration::decoration DEC;

const double INF_D = std::numeric_limits<double>::infinity();
const double NaN_D = std::numeric_limits<double>::quiet_NaN();
const float INF_F = std::numeric_limits<float>::infinity();
const float NaN_F = std::numeric_limits<float>::quiet_NaN();

BOOST_AUTO_TEST_CASE(minimal_is_empty_test)
{
    p1788::exception::clear();

    BOOST_CHECK( F<double>::is_empty(REP<double>(NaN_D,NaN_D)) );
    BOOST_CHECK( !F<double>::is_empty(REP<double>(-INF_D,+INF_D)) );
    BOOST_CHECK( !F<double>::is_empty(REP<double>(1.0,2.0)) );
    BOOST_CHECK( !F<double>::is_empty(REP<double>(-1.0,2.0)) );
    BOOST_CHECK( !F<double>::is_empty(REP<double>(-3.0,-2.0)) );
    BOOST_CHECK( !F<double>::is_empty(REP<double>(-INF_D,2.0)) );
    BOOST_CHECK( !F<double>::is_empty(REP<double>(-INF_D,0.0)) );
    BOOST_CHECK( !F<double>::is_empty(REP<double>(-INF_D,-0.0)) );
    BOOST_CHECK( !F<double>::is_empty(REP<double>(0.0,INF_D)) );
    BOOST_CHECK( !F<double>::is_empty(REP<double>(-0.0,INF_D)) );
    BOOST_CHECK( !F<double>::is_empty(REP<double>(-0.0,0.0)) );
    BOOST_CHECK( !F<double>::is_empty(REP<double>(0.0,-0.0)) );
    BOOST_CHECK( !F<double>::is_empty(REP<double>(0.0,0.0)) );
    BOOST_CHECK( !F<double>::is_empty(REP<double>(-0.0,-0.0)) );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK( !F<double>::is_empty(REP<double>(1.0,-2.0)) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::is_empty(REP<double>(1.0,-2.0)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}

BOOST_AUTO_TEST_CASE(minimal_is_empty_dec_test)
{
    p1788::exception::clear();

    BOOST_CHECK( !F<double>::is_empty(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill)) );
    BOOST_CHECK( F<double>::is_empty(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv)) );
    BOOST_CHECK( !F<double>::is_empty(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::def)) );
    BOOST_CHECK( !F<double>::is_empty(REP_DEC<double>(REP<double>(1.0,2.0), DEC::com)) );
    BOOST_CHECK( !F<double>::is_empty(REP_DEC<double>(REP<double>(-1.0,2.0), DEC::trv)) );
    BOOST_CHECK( !F<double>::is_empty(REP_DEC<double>(REP<double>(-3.0,-2.0), DEC::dac)) );
    BOOST_CHECK( !F<double>::is_empty(REP_DEC<double>(REP<double>(-INF_D,2.0), DEC::trv)) );
    BOOST_CHECK( !F<double>::is_empty(REP_DEC<double>(REP<double>(-INF_D,0.0), DEC::trv)) );
    BOOST_CHECK( !F<double>::is_empty(REP_DEC<double>(REP<double>(-INF_D,-0.0), DEC::trv)) );
    BOOST_CHECK( !F<double>::is_empty(REP_DEC<double>(REP<double>(0.0,INF_D), DEC::def)) );
    BOOST_CHECK( !F<double>::is_empty(REP_DEC<double>(REP<double>(-0.0,INF_D), DEC::trv)) );
    BOOST_CHECK( !F<double>::is_empty(REP_DEC<double>(REP<double>(-0.0,0.0), DEC::com)) );
    BOOST_CHECK( !F<double>::is_empty(REP_DEC<double>(REP<double>(0.0,-0.0), DEC::trv)) );
    BOOST_CHECK( !F<double>::is_empty(REP_DEC<double>(REP<double>(0.0,0.0), DEC::trv)) );
    BOOST_CHECK( !F<double>::is_empty(REP_DEC<double>(REP<double>(-0.0,-0.0), DEC::trv)) );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK( !F<double>::is_empty(REP_DEC<double>(REP<double>(1.0,-2.0), DEC::com)) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::is_empty(REP_DEC<double>(REP<double>(1.0,-2.0), DEC::com)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}

BOOST_AUTO_TEST_CASE(minimal_is_entire_test)
{
    p1788::exception::clear();

    BOOST_CHECK( !F<double>::is_entire(REP<double>(NaN_D,NaN_D)) );
    BOOST_CHECK( F<double>::is_entire(REP<double>(-INF_D,+INF_D)) );
    BOOST_CHECK( !F<double>::is_entire(REP<double>(1.0,2.0)) );
    BOOST_CHECK( !F<double>::is_entire(REP<double>(-1.0,2.0)) );
    BOOST_CHECK( !F<double>::is_entire(REP<double>(-3.0,-2.0)) );
    BOOST_CHECK( !F<double>::is_entire(REP<double>(-INF_D,2.0)) );
    BOOST_CHECK( !F<double>::is_entire(REP<double>(-INF_D,0.0)) );
    BOOST_CHECK( !F<double>::is_entire(REP<double>(-INF_D,-0.0)) );
    BOOST_CHECK( !F<double>::is_entire(REP<double>(0.0,INF_D)) );
    BOOST_CHECK( !F<double>::is_entire(REP<double>(-0.0,INF_D)) );
    BOOST_CHECK( !F<double>::is_entire(REP<double>(-0.0,0.0)) );
    BOOST_CHECK( !F<double>::is_entire(REP<double>(0.0,-0.0)) );
    BOOST_CHECK( !F<double>::is_entire(REP<double>(0.0,0.0)) );
    BOOST_CHECK( !F<double>::is_entire(REP<double>(-0.0,-0.0)) );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK( !F<double>::is_entire(REP<double>(-1.0,-2.0)) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::is_entire(REP<double>(-1.0,-2.0)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}

BOOST_AUTO_TEST_CASE(minimal_is_entire_dec_test)
{
    p1788::exception::clear();

    BOOST_CHECK( !F<double>::is_entire(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill)) );
    BOOST_CHECK( !F<double>::is_entire(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv)) );
    BOOST_CHECK( F<double>::is_entire(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::trv)) );
    BOOST_CHECK( F<double>::is_entire(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::def)) );
    BOOST_CHECK( F<double>::is_entire(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::dac)) );
    BOOST_CHECK( !F<double>::is_entire(REP_DEC<double>(REP<double>(1.0,2.0), DEC::com)) );
    BOOST_CHECK( !F<double>::is_entire(REP_DEC<double>(REP<double>(-1.0,2.0), DEC::trv)) );
    BOOST_CHECK( !F<double>::is_entire(REP_DEC<double>(REP<double>(-3.0,-2.0), DEC::dac)) );
    BOOST_CHECK( !F<double>::is_entire(REP_DEC<double>(REP<double>(-INF_D,2.0), DEC::trv)) );
    BOOST_CHECK( !F<double>::is_entire(REP_DEC<double>(REP<double>(-INF_D,0.0), DEC::trv)) );
    BOOST_CHECK( !F<double>::is_entire(REP_DEC<double>(REP<double>(-INF_D,-0.0), DEC::trv)) );
    BOOST_CHECK( !F<double>::is_entire(REP_DEC<double>(REP<double>(0.0,INF_D), DEC::def)) );
    BOOST_CHECK( !F<double>::is_entire(REP_DEC<double>(REP<double>(-0.0,INF_D), DEC::trv)) );
    BOOST_CHECK( !F<double>::is_entire(REP_DEC<double>(REP<double>(-0.0,0.0), DEC::com)) );
    BOOST_CHECK( !F<double>::is_entire(REP_DEC<double>(REP<double>(0.0,-0.0), DEC::trv)) );
    BOOST_CHECK( !F<double>::is_entire(REP_DEC<double>(REP<double>(0.0,0.0), DEC::trv)) );
    BOOST_CHECK( !F<double>::is_entire(REP_DEC<double>(REP<double>(-0.0,-0.0), DEC::trv)) );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK( !F<double>::is_entire(REP_DEC<double>(REP<double>(1.0,-2.0), DEC::com)) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::is_entire(REP_DEC<double>(REP<double>(1.0,-2.0), DEC::com)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}

BOOST_AUTO_TEST_CASE(minimal_is_nai_dec_test)
{
    p1788::exception::clear();

    BOOST_CHECK( F<double>::is_nai(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill)) );
    BOOST_CHECK( !F<double>::is_nai(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv)) );
    BOOST_CHECK( !F<double>::is_nai(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::trv)) );
    BOOST_CHECK( !F<double>::is_nai(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::def)) );
    BOOST_CHECK( !F<double>::is_nai(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::dac)) );
    BOOST_CHECK( !F<double>::is_nai(REP_DEC<double>(REP<double>(1.0,2.0), DEC::com)) );
    BOOST_CHECK( !F<double>::is_nai(REP_DEC<double>(REP<double>(-1.0,2.0), DEC::trv)) );
    BOOST_CHECK( !F<double>::is_nai(REP_DEC<double>(REP<double>(-3.0,-2.0), DEC::dac)) );
    BOOST_CHECK( !F<double>::is_nai(REP_DEC<double>(REP<double>(-INF_D,2.0), DEC::trv)) );
    BOOST_CHECK( !F<double>::is_nai(REP_DEC<double>(REP<double>(-INF_D,0.0), DEC::trv)) );
    BOOST_CHECK( !F<double>::is_nai(REP_DEC<double>(REP<double>(-INF_D,-0.0), DEC::trv)) );
    BOOST_CHECK( !F<double>::is_nai(REP_DEC<double>(REP<double>(0.0,INF_D), DEC::def)) );
    BOOST_CHECK( !F<double>::is_nai(REP_DEC<double>(REP<double>(-0.0,INF_D), DEC::trv)) );
    BOOST_CHECK( !F<double>::is_nai(REP_DEC<double>(REP<double>(-0.0,0.0), DEC::com)) );
    BOOST_CHECK( !F<double>::is_nai(REP_DEC<double>(REP<double>(0.0,-0.0), DEC::trv)) );
    BOOST_CHECK( !F<double>::is_nai(REP_DEC<double>(REP<double>(0.0,0.0), DEC::trv)) );
    BOOST_CHECK( !F<double>::is_nai(REP_DEC<double>(REP<double>(-0.0,-0.0), DEC::trv)) );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK( !F<double>::is_nai(REP_DEC<double>(REP<double>(-1.0,-2.0), DEC::trv)) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::is_nai(REP_DEC<double>(REP<double>(-1.0,-2.0), DEC::trv)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}

BOOST_AUTO_TEST_CASE(minimal_equal_test)
{
    p1788::exception::clear();

    BOOST_CHECK( F<double>::equal(REP<double>(1.0,2.0), REP<double>(1.0,2.0)) );
    BOOST_CHECK( !F<double>::equal(REP<double>(1.0,2.1), REP<double>(1.0,2.0)) );
    BOOST_CHECK( F<double>::equal(REP<double>(NaN_D,NaN_D), REP<double>(NaN_D,NaN_D)) );
    BOOST_CHECK( !F<double>::equal(REP<double>(NaN_D,NaN_D), REP<double>(1.0,2.0)) );
    BOOST_CHECK( F<double>::equal(REP<double>(-INF_D,+INF_D), REP<double>(-INF_D,+INF_D)) );
    BOOST_CHECK( !F<double>::equal(REP<double>(1.0,2.4), REP<double>(-INF_D,+INF_D)) );
    BOOST_CHECK( F<double>::equal(REP<double>(1.0,INF_D), REP<double>(1.0,INF_D)) );
    BOOST_CHECK( !F<double>::equal(REP<double>(1.0,2.4), REP<double>(1.0,INF_D)) );
    BOOST_CHECK( F<double>::equal(REP<double>(-INF_D,2.0), REP<double>(-INF_D,2.0)) );
    BOOST_CHECK( !F<double>::equal(REP<double>(-INF_D,2.4), REP<double>(-INF_D,2.0)) );
    BOOST_CHECK( F<double>::equal(REP<double>(-2.0,0.0), REP<double>(-2.0,0.0)) );
    BOOST_CHECK( F<double>::equal(REP<double>(-0.0,2.0), REP<double>(0.0,2.0)) );
    BOOST_CHECK( F<double>::equal(REP<double>(-0.0,-0.0), REP<double>(0.0,0.0)) );
    BOOST_CHECK( F<double>::equal(REP<double>(-0.0,0.0), REP<double>(0.0,0.0)) );
    BOOST_CHECK( F<double>::equal(REP<double>(0.0,-0.0), REP<double>(0.0,0.0)) );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK( !F<double>::equal(REP<double>(1.0,-2.4), REP<double>(-INF_D,+INF_D)) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::equal(REP<double>(1.0,2.4), REP<double>(-INF_D,-INF_D)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}

BOOST_AUTO_TEST_CASE(minimal_equal_mixedtype_test)
{
    p1788::exception::clear();

    BOOST_CHECK( F<double>::equal(REP<double>(1.0,2.0), REP<float>(1.0f,2.0f)) );
    BOOST_CHECK( !F<double>::equal(REP<double>(1.0,2.1), REP<float>(1.0f,2.0f)) );
    BOOST_CHECK( F<double>::equal(REP<double>(NaN_D,NaN_D), REP<float>(NaN_F,NaN_F)) );
    BOOST_CHECK( !F<double>::equal(REP<double>(NaN_D,NaN_D), REP<float>(1.0f,2.0f)) );
    BOOST_CHECK( F<double>::equal(REP<double>(-INF_D,+INF_D), REP<float>(-INF_F,+INF_F)) );
    BOOST_CHECK( !F<double>::equal(REP<double>(1.0,2.4), REP<float>(-INF_F,+INF_F)) );
    BOOST_CHECK( F<double>::equal(REP<double>(1.0,INF_D), REP<float>(1.0f,INF_F)) );
    BOOST_CHECK( !F<double>::equal(REP<double>(1.0,2.4), REP<float>(1.0f,INF_F)) );
    BOOST_CHECK( F<double>::equal(REP<double>(-INF_D,2.0), REP<float>(-INF_F,2.0f)) );
    BOOST_CHECK( !F<double>::equal(REP<double>(-INF_D,2.4), REP<float>(-INF_F,2.0f)) );
    BOOST_CHECK( F<double>::equal(REP<double>(-2.0,0.0), REP<float>(-2.0f,0.0f)) );
    BOOST_CHECK( F<double>::equal(REP<double>(-0.0,2.0), REP<float>(0.0f,2.0f)) );
    BOOST_CHECK( F<double>::equal(REP<double>(-0.0,-0.0), REP<float>(0.0f,0.0f)) );
    BOOST_CHECK( F<double>::equal(REP<double>(-0.0,0.0), REP<float>(0.0f,0.0f)) );
    BOOST_CHECK( F<double>::equal(REP<double>(0.0,-0.0), REP<float>(0.0f,0.0f)) );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK( !F<double>::equal(REP<double>(1.0,-2.4), REP<float>(-INF_F,+INF_F)) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::equal(REP<double>(1.0,2.4), REP<float>(+INF_F,+INF_F)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);

    BOOST_CHECK( F<float>::equal(REP<float>(1.0f,2.0f), REP<double>(1.0,2.0)) );
    BOOST_CHECK( !F<float>::equal(REP<float>(1.0f,2.1f), REP<double>(1.0,2.0)) );
    BOOST_CHECK( F<float>::equal(REP<float>(NaN_F,NaN_F), REP<double>(NaN_D,NaN_D)) );
    BOOST_CHECK( !F<float>::equal(REP<float>(NaN_F,NaN_F), REP<double>(1.0,2.0)) );
    BOOST_CHECK( F<float>::equal(REP<float>(-INF_F,+INF_F), REP<double>(-INF_D,+INF_D)) );
    BOOST_CHECK( !F<float>::equal(REP<float>(1.0f,2.4f), REP<double>(-INF_D,+INF_D)) );
    BOOST_CHECK( F<float>::equal(REP<float>(1.0f,INF_F), REP<double>(1.0,INF_D)) );
    BOOST_CHECK( !F<float>::equal(REP<float>(1.0f,2.4f), REP<double>(1.0,INF_D)) );
    BOOST_CHECK( F<float>::equal(REP<float>(-INF_F,2.0f), REP<double>(-INF_D,2.0)) );
    BOOST_CHECK( !F<float>::equal(REP<float>(-INF_F,2.4f), REP<double>(-INF_D,2.0)) );
    BOOST_CHECK( F<float>::equal(REP<float>(-2.0f,0.0f), REP<double>(-2.0,0.0)) );
    BOOST_CHECK( F<float>::equal(REP<float>(-0.0f,2.0f), REP<double>(0.0,2.0)) );
    BOOST_CHECK( F<float>::equal(REP<float>(-0.0f,-0.0f), REP<double>(0.0,0.0)) );
    BOOST_CHECK( F<float>::equal(REP<float>(-0.0f,0.0f), REP<double>(0.0,0.0)) );
    BOOST_CHECK( F<float>::equal(REP<float>(0.0f,-0.0f), REP<double>(0.0,0.0)) );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK( !F<float>::equal(REP<float>(+INF_F,-2.4f), REP<double>(-INF_D,2.0)) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<float>::equal(REP<float>(-INF_F,2.4f), REP<double>(+INF_D,2.0)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}

BOOST_AUTO_TEST_CASE(minimal_equal_dec_test)
{
    p1788::exception::clear();

    BOOST_CHECK( F<double>::equal(REP_DEC<double>(REP<double>(1.0,2.0),DEC::def), REP_DEC<double>(REP<double>(1.0,2.0),DEC::trv)) );
    BOOST_CHECK( !F<double>::equal(REP_DEC<double>(REP<double>(1.0,2.1),DEC::trv), REP_DEC<double>(REP<double>(1.0,2.0),DEC::trv)) );
    BOOST_CHECK( F<double>::equal(REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );
    BOOST_CHECK( !F<double>::equal(REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );
    BOOST_CHECK( !F<double>::equal(REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );
    BOOST_CHECK( !F<double>::equal(REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );
    BOOST_CHECK( !F<double>::equal(REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv), REP_DEC<double>(REP<double>(1.0,2.0),DEC::trv)) );
    BOOST_CHECK( !F<double>::equal(REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill), REP_DEC<double>(REP<double>(1.0,2.0),DEC::trv)) );
    BOOST_CHECK( F<double>::equal(REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::def), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );
    BOOST_CHECK( !F<double>::equal(REP_DEC<double>(REP<double>(1.0,2.4),DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );
    BOOST_CHECK( F<double>::equal(REP_DEC<double>(REP<double>(1.0,INF_D),DEC::trv), REP_DEC<double>(REP<double>(1.0,INF_D),DEC::trv)) );
    BOOST_CHECK( !F<double>::equal(REP_DEC<double>(REP<double>(1.0,2.4),DEC::def), REP_DEC<double>(REP<double>(1.0,INF_D),DEC::trv)) );
    BOOST_CHECK( F<double>::equal(REP_DEC<double>(REP<double>(-INF_D,2.0),DEC::trv), REP_DEC<double>(REP<double>(-INF_D,2.0),DEC::trv)) );
    BOOST_CHECK( !F<double>::equal(REP_DEC<double>(REP<double>(-INF_D,2.4),DEC::def), REP_DEC<double>(REP<double>(-INF_D,2.0),DEC::trv)) );
    BOOST_CHECK( F<double>::equal(REP_DEC<double>(REP<double>(-2.0,0.0),DEC::trv), REP_DEC<double>(REP<double>(-2.0,0.0),DEC::trv)) );
    BOOST_CHECK( F<double>::equal(REP_DEC<double>(REP<double>(-0.0,2.0),DEC::def), REP_DEC<double>(REP<double>(0.0,2.0),DEC::trv)) );
    BOOST_CHECK( F<double>::equal(REP_DEC<double>(REP<double>(-0.0,-0.0),DEC::trv), REP_DEC<double>(REP<double>(0.0,0.0),DEC::trv)) );
    BOOST_CHECK( F<double>::equal(REP_DEC<double>(REP<double>(-0.0,0.0),DEC::def), REP_DEC<double>(REP<double>(0.0,0.0),DEC::trv)) );
    BOOST_CHECK( F<double>::equal(REP_DEC<double>(REP<double>(0.0,-0.0),DEC::trv), REP_DEC<double>(REP<double>(0.0,0.0),DEC::trv)) );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK( !F<double>::equal(REP_DEC<double>(REP<double>(-INF_D,2.4),DEC::def), REP_DEC<double>(REP<double>(+INF_D,2.0),DEC::trv)) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::equal(REP_DEC<double>(REP<double>(+INF_D,2.4),DEC::def), REP_DEC<double>(REP<double>(-INF_D,2.0),DEC::trv)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}

BOOST_AUTO_TEST_CASE(minimal_equal_dec_mixedtype_test)
{
    p1788::exception::clear();

    BOOST_CHECK( F<double>::equal(REP_DEC<double>(REP<double>(1.0,2.0),DEC::com), REP_DEC<float>(REP<float>(1.0f,2.0f),DEC::trv)) );
    BOOST_CHECK( !F<double>::equal(REP_DEC<double>(REP<double>(1.0,2.1),DEC::trv), REP_DEC<float>(REP<float>(1.0f,2.0f),DEC::trv)) );
    BOOST_CHECK( F<double>::equal(REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv), REP_DEC<float>(REP<float>(NaN_F,NaN_F),DEC::trv)) );
    BOOST_CHECK( !F<double>::equal(REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv), REP_DEC<float>(REP<float>(NaN_F,NaN_F),DEC::ill)) );
    BOOST_CHECK( !F<double>::equal(REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill), REP_DEC<float>(REP<float>(NaN_F,NaN_F),DEC::trv)) );
    BOOST_CHECK( !F<double>::equal(REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill), REP_DEC<float>(REP<float>(NaN_F,NaN_F),DEC::ill)) );
    BOOST_CHECK( !F<double>::equal(REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv), REP_DEC<float>(REP<float>(1.0f,2.0f),DEC::trv)) );
    BOOST_CHECK( !F<double>::equal(REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill), REP_DEC<float>(REP<float>(1.0f,2.0f),DEC::trv)) );
    BOOST_CHECK( F<double>::equal(REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv), REP_DEC<float>(REP<float>(-INF_F,+INF_F),DEC::def)) );
    BOOST_CHECK( !F<double>::equal(REP_DEC<double>(REP<double>(1.0,2.4),DEC::def), REP_DEC<float>(REP<float>(-INF_F,+INF_F),DEC::trv)) );
    BOOST_CHECK( F<double>::equal(REP_DEC<double>(REP<double>(1.0,INF_D),DEC::trv), REP_DEC<float>(REP<float>(1.0f,INF_F),DEC::trv)) );
    BOOST_CHECK( !F<double>::equal(REP_DEC<double>(REP<double>(1.0,2.4),DEC::trv), REP_DEC<float>(REP<float>(1.0f,INF_F),DEC::trv)) );
    BOOST_CHECK( F<double>::equal(REP_DEC<double>(REP<double>(-INF_D,2.0),DEC::trv), REP_DEC<float>(REP<float>(-INF_F,2.0f),DEC::trv)) );
    BOOST_CHECK( !F<double>::equal(REP_DEC<double>(REP<double>(-INF_D,2.4),DEC::trv), REP_DEC<float>(REP<float>(-INF_F,2.0f),DEC::trv)) );
    BOOST_CHECK( F<double>::equal(REP_DEC<double>(REP<double>(-2.0,0.0),DEC::trv), REP_DEC<float>(REP<float>(-2.0f,0.0f),DEC::trv)) );
    BOOST_CHECK( F<double>::equal(REP_DEC<double>(REP<double>(-0.0,2.0),DEC::trv), REP_DEC<float>(REP<float>(0.0f,2.0f),DEC::trv)) );
    BOOST_CHECK( F<double>::equal(REP_DEC<double>(REP<double>(-0.0,-0.0),DEC::def), REP_DEC<float>(REP<float>(0.0f,0.0f),DEC::trv)) );
    BOOST_CHECK( F<double>::equal(REP_DEC<double>(REP<double>(-0.0,0.0),DEC::trv), REP_DEC<float>(REP<float>(0.0f,0.0f),DEC::dac)) );
    BOOST_CHECK( F<double>::equal(REP_DEC<double>(REP<double>(0.0,-0.0),DEC::com), REP_DEC<float>(REP<float>(0.0f,0.0f),DEC::def)) );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK( !F<double>::equal(REP_DEC<double>(REP<double>(+INF_D,2.4),DEC::trv), REP_DEC<float>(REP<float>(-INF_F,2.0f),DEC::trv)) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::equal(REP_DEC<double>(REP<double>(-INF_D,2.4),DEC::trv), REP_DEC<float>(REP<float>(+INF_F,2.0f),DEC::trv)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);

    BOOST_CHECK( F<float>::equal(REP_DEC<float>(REP<float>(1.0f,2.0f),DEC::com), REP_DEC<double>(REP<double>(1.0,2.0),DEC::trv)) );
    BOOST_CHECK( !F<float>::equal(REP_DEC<float>(REP<float>(1.0f,2.1f),DEC::trv), REP_DEC<double>(REP<double>(1.0,2.0),DEC::trv)) );
    BOOST_CHECK( F<float>::equal(REP_DEC<float>(REP<float>(NaN_F,NaN_F),DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );
    BOOST_CHECK( !F<float>::equal(REP_DEC<float>(REP<float>(NaN_F,NaN_F),DEC::ill), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );
    BOOST_CHECK( !F<float>::equal(REP_DEC<float>(REP<float>(NaN_F,NaN_F),DEC::ill), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );
    BOOST_CHECK( !F<float>::equal(REP_DEC<float>(REP<float>(NaN_F,NaN_F),DEC::ill), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );
    BOOST_CHECK( !F<float>::equal(REP_DEC<float>(REP<float>(NaN_F,NaN_F),DEC::trv), REP_DEC<double>(REP<double>(1.0,2.0),DEC::trv)) );
    BOOST_CHECK( F<float>::equal(REP_DEC<float>(REP<float>(-INF_F,+INF_F),DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::def)) );
    BOOST_CHECK( !F<float>::equal(REP_DEC<float>(REP<float>(1.0f,2.4f),DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );
    BOOST_CHECK( F<float>::equal(REP_DEC<float>(REP<float>(1.0f,INF_F),DEC::dac), REP_DEC<double>(REP<double>(1.0,INF_D),DEC::trv)) );
    BOOST_CHECK( !F<float>::equal(REP_DEC<float>(REP<float>(1.0f,2.4f),DEC::trv), REP_DEC<double>(REP<double>(1.0,INF_D),DEC::trv)) );
    BOOST_CHECK( F<float>::equal(REP_DEC<float>(REP<float>(-INF_F,2.0f),DEC::trv), REP_DEC<double>(REP<double>(-INF_D,2.0),DEC::trv)) );
    BOOST_CHECK( !F<float>::equal(REP_DEC<float>(REP<float>(-INF_F,2.4f),DEC::def), REP_DEC<double>(REP<double>(-INF_D,2.0),DEC::trv)) );
    BOOST_CHECK( F<float>::equal(REP_DEC<float>(REP<float>(-2.0f,0.0f),DEC::trv), REP_DEC<double>(REP<double>(-2.0,0.0),DEC::trv)) );
    BOOST_CHECK( F<float>::equal(REP_DEC<float>(REP<float>(-0.0f,2.0f),DEC::trv), REP_DEC<double>(REP<double>(0.0,2.0),DEC::trv)) );
    BOOST_CHECK( F<float>::equal(REP_DEC<float>(REP<float>(-0.0f,-0.0f),DEC::trv), REP_DEC<double>(REP<double>(0.0,0.0),DEC::trv)) );
    BOOST_CHECK( F<float>::equal(REP_DEC<float>(REP<float>(-0.0f,0.0f),DEC::com), REP_DEC<double>(REP<double>(0.0,0.0),DEC::def)) );
    BOOST_CHECK( F<float>::equal(REP_DEC<float>(REP<float>(0.0f,-0.0f),DEC::trv), REP_DEC<double>(REP<double>(0.0,0.0),DEC::trv)) );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK( !F<float>::equal(REP_DEC<float>(REP<float>(1.0f,-2.4f),DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<float>::equal(REP_DEC<float>(REP<float>(1.0f,2.4f),DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::com)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}


BOOST_AUTO_TEST_CASE(minimal_subset_test)
{
    p1788::exception::clear();

    BOOST_CHECK( F<double>::subset(REP<double>(NaN_D,NaN_D), REP<double>(NaN_D,NaN_D)) );
    BOOST_CHECK( F<double>::subset(REP<double>(NaN_D,NaN_D), REP<double>(0.0,4.0)) );
    BOOST_CHECK( F<double>::subset(REP<double>(NaN_D,NaN_D), REP<double>(-0.0,4.0)) );
    BOOST_CHECK( F<double>::subset(REP<double>(NaN_D,NaN_D), REP<double>(-0.1,1.0)) );
    BOOST_CHECK( F<double>::subset(REP<double>(NaN_D,NaN_D), REP<double>(-0.1,0.0)) );
    BOOST_CHECK( F<double>::subset(REP<double>(NaN_D,NaN_D), REP<double>(-0.1,-0.0)) );
    BOOST_CHECK( F<double>::subset(REP<double>(NaN_D,NaN_D), REP<double>(-INF_D,+INF_D)) );

    BOOST_CHECK( !F<double>::subset(REP<double>(0.0,4.0), REP<double>(NaN_D,NaN_D)) );
    BOOST_CHECK( !F<double>::subset(REP<double>(-0.0,4.0), REP<double>(NaN_D,NaN_D)) );
    BOOST_CHECK( !F<double>::subset(REP<double>(-0.1,1.0), REP<double>(NaN_D,NaN_D)) );
    BOOST_CHECK( !F<double>::subset(REP<double>(-INF_D,+INF_D), REP<double>(NaN_D,NaN_D)) );

    BOOST_CHECK( F<double>::subset(REP<double>(0.0,4.0), REP<double>(-INF_D,+INF_D)) );
    BOOST_CHECK( F<double>::subset(REP<double>(-0.0,4.0), REP<double>(-INF_D,+INF_D)) );
    BOOST_CHECK( F<double>::subset(REP<double>(-0.1,1.0), REP<double>(-INF_D,+INF_D)) );
    BOOST_CHECK( F<double>::subset(REP<double>(-INF_D,+INF_D), REP<double>(-INF_D,+INF_D)) );

    BOOST_CHECK( F<double>::subset(REP<double>(1.0,2.0), REP<double>(1.0,2.0)) );
    BOOST_CHECK( F<double>::subset(REP<double>(1.0,2.0), REP<double>(0.0,4.0)) );
    BOOST_CHECK( F<double>::subset(REP<double>(1.0,2.0), REP<double>(-0.0,4.0)) );
    BOOST_CHECK( F<double>::subset(REP<double>(0.1,0.2), REP<double>(0.0,4.0)) );
    BOOST_CHECK( F<double>::subset(REP<double>(0.1,0.2), REP<double>(-0.0,4.0)) );
    BOOST_CHECK( F<double>::subset(REP<double>(-0.1,-0.1), REP<double>(-4.0, 3.4)) );

    BOOST_CHECK( F<double>::subset(REP<double>(0.0,0.0), REP<double>(-0.0,-0.0)) );
    BOOST_CHECK( F<double>::subset(REP<double>(-0.0,-0.0), REP<double>(0.0,0.0)) );
    BOOST_CHECK( F<double>::subset(REP<double>(-0.0,0.0), REP<double>(0.0,0.0)) );
    BOOST_CHECK( F<double>::subset(REP<double>(-0.0,0.0), REP<double>(0.0,-0.0)) );
    BOOST_CHECK( F<double>::subset(REP<double>(0.0,-0.0), REP<double>(0.0,0.0)) );
    BOOST_CHECK( F<double>::subset(REP<double>(0.0,-0.0), REP<double>(-0.0,0.0)) );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK( !F<double>::subset(REP<double>(1.0,-2.0), REP<double>(-0.0,4.0)) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::subset(REP<double>(1.0,2.0), REP<double>(-0.0,-4.0)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}


BOOST_AUTO_TEST_CASE(minimal_subset_mixedtype_test)
{
    p1788::exception::clear();

    BOOST_CHECK( F<double>::subset(REP<double>(NaN_D,NaN_D), REP<float>(NaN_F,NaN_F)) );
    BOOST_CHECK( F<double>::subset(REP<double>(NaN_D,NaN_D), REP<float>(0.0f,4.0f)) );
    BOOST_CHECK( F<double>::subset(REP<double>(NaN_D,NaN_D), REP<float>(-0.0f,4.0f)) );
    BOOST_CHECK( F<double>::subset(REP<double>(NaN_D,NaN_D), REP<float>(-0.1f,1.0f)) );
    BOOST_CHECK( F<double>::subset(REP<double>(NaN_D,NaN_D), REP<float>(-0.1f,0.0f)) );
    BOOST_CHECK( F<double>::subset(REP<double>(NaN_D,NaN_D), REP<float>(-0.1f,-0.0f)) );
    BOOST_CHECK( F<double>::subset(REP<double>(NaN_D,NaN_D), REP<float>(-INF_F,+INF_F)) );

    BOOST_CHECK( !F<double>::subset(REP<double>(0.0,4.0), REP<float>(NaN_F,NaN_F)) );
    BOOST_CHECK( !F<double>::subset(REP<double>(-0.0,4.0), REP<float>(NaN_F,NaN_F)) );
    BOOST_CHECK( !F<double>::subset(REP<double>(-0.1,1.0), REP<float>(NaN_F,NaN_F)) );
    BOOST_CHECK( !F<double>::subset(REP<double>(-INF_D,+INF_D), REP<float>(NaN_F,NaN_F)) );

    BOOST_CHECK( F<double>::subset(REP<double>(0.0,4.0), REP<float>(-INF_F,+INF_F)) );
    BOOST_CHECK( F<double>::subset(REP<double>(-0.0,4.0), REP<float>(-INF_F,+INF_F)) );
    BOOST_CHECK( F<double>::subset(REP<double>(-0.1,1.0), REP<float>(-INF_F,+INF_F)) );
    BOOST_CHECK( F<double>::subset(REP<double>(-INF_D,+INF_D), REP<float>(-INF_F,+INF_F)) );

    BOOST_CHECK( F<double>::subset(REP<double>(1.0,2.0), REP<float>(1.0f,2.0f)) );
    BOOST_CHECK( F<double>::subset(REP<double>(1.0,2.0), REP<float>(0.0f,4.0f)) );
    BOOST_CHECK( F<double>::subset(REP<double>(1.0,2.0), REP<float>(-0.0f,4.0f)) );
    BOOST_CHECK( F<double>::subset(REP<double>(0.1,0.2), REP<float>(0.0f,4.0f)) );
    BOOST_CHECK( F<double>::subset(REP<double>(0.1,0.2), REP<float>(-0.0f,4.0f)) );
    BOOST_CHECK( F<double>::subset(REP<double>(-0.1,-0.1), REP<float>(-4.0f, 3.4f)) );

    BOOST_CHECK( F<double>::subset(REP<double>(0.0,0.0), REP<float>(-0.0f,-0.0f)) );
    BOOST_CHECK( F<double>::subset(REP<double>(-0.0,-0.0), REP<float>(0.0f,0.0f)) );
    BOOST_CHECK( F<double>::subset(REP<double>(-0.0,0.0), REP<float>(0.0f,0.0f)) );
    BOOST_CHECK( F<double>::subset(REP<double>(-0.0,0.0), REP<float>(0.0f,-0.0f)) );
    BOOST_CHECK( F<double>::subset(REP<double>(0.0,-0.0), REP<float>(0.0f,0.0f)) );
    BOOST_CHECK( F<double>::subset(REP<double>(0.0,-0.0), REP<float>(-0.0f,0.0f)) );


    BOOST_CHECK( F<float>::subset(REP<float>(NaN_F,NaN_F), REP<double>(NaN_D,NaN_D)) );
    BOOST_CHECK( F<float>::subset(REP<float>(NaN_F,NaN_F), REP<double>(0.0,4.0)) );
    BOOST_CHECK( F<float>::subset(REP<float>(NaN_F,NaN_F), REP<double>(-0.0,4.0)) );
    BOOST_CHECK( F<float>::subset(REP<float>(NaN_F,NaN_F), REP<double>(-0.1,1.0)) );
    BOOST_CHECK( F<float>::subset(REP<float>(NaN_F,NaN_F), REP<double>(-0.1,0.0)) );
    BOOST_CHECK( F<float>::subset(REP<float>(NaN_F,NaN_F), REP<double>(-0.1,-0.0)) );
    BOOST_CHECK( F<float>::subset(REP<float>(NaN_F,NaN_F), REP<double>(-INF_D,+INF_D)) );

    BOOST_CHECK( !F<float>::subset(REP<float>(0.0f,4.0f), REP<double>(NaN_D,NaN_D)) );
    BOOST_CHECK( !F<float>::subset(REP<float>(-0.0f,4.0f), REP<double>(NaN_D,NaN_D)) );
    BOOST_CHECK( !F<float>::subset(REP<float>(-0.1f,1.0f), REP<double>(NaN_D,NaN_D)) );
    BOOST_CHECK( !F<float>::subset(REP<float>(-INF_F,+INF_F), REP<double>(NaN_D,NaN_D)) );

    BOOST_CHECK( F<float>::subset(REP<float>(0.0f,4.0f), REP<double>(-INF_D,+INF_D)) );
    BOOST_CHECK( F<float>::subset(REP<float>(-0.0f,4.0f), REP<double>(-INF_D,+INF_D)) );
    BOOST_CHECK( F<float>::subset(REP<float>(-0.1f,1.0f), REP<double>(-INF_D,+INF_D)) );
    BOOST_CHECK( F<float>::subset(REP<float>(-INF_F,+INF_F), REP<double>(-INF_D,+INF_D)) );

    BOOST_CHECK( F<float>::subset(REP<float>(1.0f,2.0f), REP<double>(1.0,2.0)) );
    BOOST_CHECK( F<float>::subset(REP<float>(1.0f,2.0f), REP<double>(0.0,4.0)) );
    BOOST_CHECK( F<float>::subset(REP<float>(1.0f,2.0f), REP<double>(-0.0,4.0)) );
    BOOST_CHECK( F<float>::subset(REP<float>(0.1f,0.2f), REP<double>(0.0,4.0)) );
    BOOST_CHECK( F<float>::subset(REP<float>(0.1f,0.2f), REP<double>(-0.0,4.0)) );
    BOOST_CHECK( F<float>::subset(REP<float>(-0.1f,-0.1f), REP<double>(-4.0, 3.4)) );

    BOOST_CHECK( F<float>::subset(REP<float>(0.0f,0.0f), REP<double>(-0.0,-0.0)) );
    BOOST_CHECK( F<float>::subset(REP<float>(-0.0f,-0.0f), REP<double>(0.0,0.0)) );
    BOOST_CHECK( F<float>::subset(REP<float>(-0.0f,0.0f), REP<double>(0.0,0.0)) );
    BOOST_CHECK( F<float>::subset(REP<float>(-0.0f,0.0f), REP<double>(0.0,-0.0)) );
    BOOST_CHECK( F<float>::subset(REP<float>(0.0f,-0.0f), REP<double>(0.0,0.0)) );
    BOOST_CHECK( F<float>::subset(REP<float>(0.0f,-0.0f), REP<double>(-0.0,0.0)) );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK( !F<float>::subset(REP<float>(1.0f,-2.0f), REP<double>(0.0,4.0)) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<float>::subset(REP<float>(1.0f,2.0f), REP<double>(0.0,-4.0)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}


BOOST_AUTO_TEST_CASE(minimal_subset_dec_test)
{
    p1788::exception::clear();

    BOOST_CHECK( !F<double>::subset(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );
    BOOST_CHECK( !F<double>::subset(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );
    BOOST_CHECK( !F<double>::subset(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill), REP_DEC<double>(REP<double>(0.0,4.0),DEC::trv)) );

    BOOST_CHECK( F<double>::subset(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );
    BOOST_CHECK( F<double>::subset(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<double>(REP<double>(0.0,4.0),DEC::trv)) );
    BOOST_CHECK( F<double>::subset(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<double>(REP<double>(-0.0,4.0),DEC::def)) );
    BOOST_CHECK( F<double>::subset(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<double>(REP<double>(-0.1,1.0),DEC::trv)) );
    BOOST_CHECK( F<double>::subset(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<double>(REP<double>(-0.1,0.0),DEC::trv)) );
    BOOST_CHECK( F<double>::subset(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<double>(REP<double>(-0.1,-0.0),DEC::trv)) );
    BOOST_CHECK( F<double>::subset(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );

    BOOST_CHECK( !F<double>::subset(REP_DEC<double>(REP<double>(0.0,4.0), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );
    BOOST_CHECK( !F<double>::subset(REP_DEC<double>(REP<double>(-0.0,4.0), DEC::def), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );
    BOOST_CHECK( !F<double>::subset(REP_DEC<double>(REP<double>(-0.1,1.0), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );
    BOOST_CHECK( !F<double>::subset(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );

    BOOST_CHECK( F<double>::subset(REP_DEC<double>(REP<double>(0.0,4.0), DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );
    BOOST_CHECK( F<double>::subset(REP_DEC<double>(REP<double>(-0.0,4.0), DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );
    BOOST_CHECK( F<double>::subset(REP_DEC<double>(REP<double>(-0.1,1.0), DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );
    BOOST_CHECK( F<double>::subset(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );

    BOOST_CHECK( F<double>::subset(REP_DEC<double>(REP<double>(1.0,2.0), DEC::trv), REP_DEC<double>(REP<double>(1.0,2.0),DEC::trv)) );
    BOOST_CHECK( F<double>::subset(REP_DEC<double>(REP<double>(1.0,2.0), DEC::trv), REP_DEC<double>(REP<double>(0.0,4.0),DEC::trv)) );
    BOOST_CHECK( F<double>::subset(REP_DEC<double>(REP<double>(1.0,2.0), DEC::def), REP_DEC<double>(REP<double>(-0.0,4.0),DEC::def)) );
    BOOST_CHECK( F<double>::subset(REP_DEC<double>(REP<double>(0.1,0.2), DEC::trv), REP_DEC<double>(REP<double>(0.0,4.0),DEC::trv)) );
    BOOST_CHECK( F<double>::subset(REP_DEC<double>(REP<double>(0.1,0.2), DEC::trv), REP_DEC<double>(REP<double>(-0.0,4.0),DEC::def)) );
    BOOST_CHECK( F<double>::subset(REP_DEC<double>(REP<double>(-0.1,-0.1), DEC::trv), REP_DEC<double>(REP<double>(-4.0, 3.4),DEC::trv)) );

    BOOST_CHECK( F<double>::subset(REP_DEC<double>(REP<double>(0.0,0.0), DEC::trv), REP_DEC<double>(REP<double>(-0.0,-0.0),DEC::trv)) );
    BOOST_CHECK( F<double>::subset(REP_DEC<double>(REP<double>(-0.0,-0.0), DEC::trv), REP_DEC<double>(REP<double>(0.0,0.0),DEC::def)) );
    BOOST_CHECK( F<double>::subset(REP_DEC<double>(REP<double>(-0.0,0.0), DEC::trv), REP_DEC<double>(REP<double>(0.0,0.0),DEC::trv)) );
    BOOST_CHECK( F<double>::subset(REP_DEC<double>(REP<double>(-0.0,0.0), DEC::trv), REP_DEC<double>(REP<double>(0.0,-0.0),DEC::trv)) );
    BOOST_CHECK( F<double>::subset(REP_DEC<double>(REP<double>(0.0,-0.0), DEC::def), REP_DEC<double>(REP<double>(0.0,0.0),DEC::trv)) );
    BOOST_CHECK( F<double>::subset(REP_DEC<double>(REP<double>(0.0,-0.0), DEC::trv), REP_DEC<double>(REP<double>(-0.0,0.0),DEC::trv)) );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK( !F<double>::subset(REP_DEC<double>(REP<double>(1.0,-2.0), DEC::trv), REP_DEC<double>(REP<double>(1.0,2.0),DEC::trv)) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::subset(REP_DEC<double>(REP<double>(1.0,2.0), DEC::trv), REP_DEC<double>(REP<double>(1.0,2.0),DEC::ill)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}


BOOST_AUTO_TEST_CASE(minimal_subset_dec_mixedtype_test)
{
    p1788::exception::clear();

    BOOST_CHECK( !F<double>::subset(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill), REP_DEC<float>(REP<float>(NaN_F,NaN_F),DEC::ill)) );
    BOOST_CHECK( !F<double>::subset(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill), REP_DEC<float>(REP<float>(NaN_F,NaN_F),DEC::trv)) );
    BOOST_CHECK( !F<double>::subset(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill), REP_DEC<float>(REP<float>(0.0f,4.0f),DEC::trv)) );

    BOOST_CHECK( F<double>::subset(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<float>(REP<float>(NaN_F,NaN_F),DEC::trv)) );
    BOOST_CHECK( F<double>::subset(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<float>(REP<float>(0.0f,4.0f),DEC::trv)) );
    BOOST_CHECK( F<double>::subset(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<float>(REP<float>(-0.0f,4.0f),DEC::def)) );
    BOOST_CHECK( F<double>::subset(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<float>(REP<float>(-0.1f,1.0f),DEC::trv)) );
    BOOST_CHECK( F<double>::subset(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<float>(REP<float>(-0.1f,0.0f),DEC::trv)) );
    BOOST_CHECK( F<double>::subset(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<float>(REP<float>(-0.1f,-0.0f),DEC::trv)) );
    BOOST_CHECK( F<double>::subset(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<float>(REP<float>(-INF_F,+INF_F),DEC::trv)) );

    BOOST_CHECK( !F<double>::subset(REP_DEC<double>(REP<double>(0.0,4.0), DEC::trv), REP_DEC<float>(REP<float>(NaN_F,NaN_F),DEC::trv)) );
    BOOST_CHECK( !F<double>::subset(REP_DEC<double>(REP<double>(-0.0,4.0), DEC::def), REP_DEC<float>(REP<float>(NaN_F,NaN_F),DEC::trv)) );
    BOOST_CHECK( !F<double>::subset(REP_DEC<double>(REP<double>(-0.1,1.0), DEC::trv), REP_DEC<float>(REP<float>(NaN_F,NaN_F),DEC::trv)) );
    BOOST_CHECK( !F<double>::subset(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::trv), REP_DEC<float>(REP<float>(NaN_F,NaN_F),DEC::trv)) );

    BOOST_CHECK( F<double>::subset(REP_DEC<double>(REP<double>(0.0,4.0), DEC::trv), REP_DEC<float>(REP<float>(-INF_F,+INF_F),DEC::trv)) );
    BOOST_CHECK( F<double>::subset(REP_DEC<double>(REP<double>(-0.0,4.0), DEC::trv), REP_DEC<float>(REP<float>(-INF_F,+INF_F),DEC::trv)) );
    BOOST_CHECK( F<double>::subset(REP_DEC<double>(REP<double>(-0.1,1.0), DEC::trv), REP_DEC<float>(REP<float>(-INF_F,+INF_F),DEC::trv)) );
    BOOST_CHECK( F<double>::subset(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::trv), REP_DEC<float>(REP<float>(-INF_F,+INF_F),DEC::trv)) );

    BOOST_CHECK( F<double>::subset(REP_DEC<double>(REP<double>(1.0,2.0), DEC::trv), REP_DEC<float>(REP<float>(1.0f,2.0f),DEC::trv)) );
    BOOST_CHECK( F<double>::subset(REP_DEC<double>(REP<double>(1.0,2.0), DEC::trv), REP_DEC<float>(REP<float>(0.0f,4.0f),DEC::trv)) );
    BOOST_CHECK( F<double>::subset(REP_DEC<double>(REP<double>(1.0,2.0), DEC::def), REP_DEC<float>(REP<float>(-0.0f,4.0f),DEC::def)) );
    BOOST_CHECK( F<double>::subset(REP_DEC<double>(REP<double>(0.1,0.2), DEC::trv), REP_DEC<float>(REP<float>(0.0f,4.0f),DEC::trv)) );
    BOOST_CHECK( F<double>::subset(REP_DEC<double>(REP<double>(0.1,0.2), DEC::trv), REP_DEC<float>(REP<float>(-0.0f,4.0f),DEC::def)) );
    BOOST_CHECK( F<double>::subset(REP_DEC<double>(REP<double>(-0.1,-0.1), DEC::trv), REP_DEC<float>(REP<float>(-4.0f, 3.4f),DEC::trv)) );

    BOOST_CHECK( F<double>::subset(REP_DEC<double>(REP<double>(0.0,0.0), DEC::trv), REP_DEC<float>(REP<float>(-0.0f,-0.0f),DEC::trv)) );
    BOOST_CHECK( F<double>::subset(REP_DEC<double>(REP<double>(-0.0,-0.0), DEC::trv), REP_DEC<float>(REP<float>(0.0f,0.0f),DEC::trv)) );
    BOOST_CHECK( F<double>::subset(REP_DEC<double>(REP<double>(-0.0,0.0), DEC::def), REP_DEC<float>(REP<float>(0.0f,0.0f),DEC::trv)) );
    BOOST_CHECK( F<double>::subset(REP_DEC<double>(REP<double>(-0.0,0.0), DEC::trv), REP_DEC<float>(REP<float>(0.0f,-0.0f),DEC::trv)) );
    BOOST_CHECK( F<double>::subset(REP_DEC<double>(REP<double>(0.0,-0.0), DEC::trv), REP_DEC<float>(REP<float>(0.0f,0.0f),DEC::def)) );
    BOOST_CHECK( F<double>::subset(REP_DEC<double>(REP<double>(0.0,-0.0), DEC::trv), REP_DEC<float>(REP<float>(-0.0f,0.0f),DEC::trv)) );

    BOOST_CHECK( !F<float>::subset(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::ill), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );
    BOOST_CHECK( !F<float>::subset(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::ill), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );
    BOOST_CHECK( !F<float>::subset(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::ill), REP_DEC<double>(REP<double>(0.0,4.0),DEC::trv)) );

    BOOST_CHECK( F<float>::subset(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );
    BOOST_CHECK( F<float>::subset(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::trv), REP_DEC<double>(REP<double>(0.0,4.0),DEC::trv)) );
    BOOST_CHECK( F<float>::subset(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::trv), REP_DEC<double>(REP<double>(-0.0,4.0),DEC::trv)) );
    BOOST_CHECK( F<float>::subset(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::trv), REP_DEC<double>(REP<double>(-0.1,1.0),DEC::def)) );
    BOOST_CHECK( F<float>::subset(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::trv), REP_DEC<double>(REP<double>(-0.1,0.0),DEC::trv)) );
    BOOST_CHECK( F<float>::subset(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::trv), REP_DEC<double>(REP<double>(-0.1,-0.0),DEC::trv)) );
    BOOST_CHECK( F<float>::subset(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );

    BOOST_CHECK( !F<float>::subset(REP_DEC<float>(REP<float>(0.0f,4.0f), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );
    BOOST_CHECK( !F<float>::subset(REP_DEC<float>(REP<float>(-0.0f,4.0f), DEC::def), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );
    BOOST_CHECK( !F<float>::subset(REP_DEC<float>(REP<float>(-0.1f,1.0f), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );
    BOOST_CHECK( !F<float>::subset(REP_DEC<float>(REP<float>(-INF_F,+INF_F), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );

    BOOST_CHECK( F<float>::subset(REP_DEC<float>(REP<float>(0.0f,4.0f), DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );
    BOOST_CHECK( F<float>::subset(REP_DEC<float>(REP<float>(-0.0f,4.0f), DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );
    BOOST_CHECK( F<float>::subset(REP_DEC<float>(REP<float>(-0.1f,1.0f), DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );
    BOOST_CHECK( F<float>::subset(REP_DEC<float>(REP<float>(-INF_F,+INF_F), DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );

    BOOST_CHECK( F<float>::subset(REP_DEC<float>(REP<float>(1.0f,2.0f), DEC::trv), REP_DEC<double>(REP<double>(1.0,2.0),DEC::trv)) );
    BOOST_CHECK( F<float>::subset(REP_DEC<float>(REP<float>(1.0f,2.0f), DEC::trv), REP_DEC<double>(REP<double>(0.0,4.0),DEC::trv)) );
    BOOST_CHECK( F<float>::subset(REP_DEC<float>(REP<float>(1.0f,2.0f), DEC::def), REP_DEC<double>(REP<double>(-0.0,4.0),DEC::trv)) );
    BOOST_CHECK( F<float>::subset(REP_DEC<float>(REP<float>(0.1f,0.2f), DEC::trv), REP_DEC<double>(REP<double>(0.0,4.0),DEC::trv)) );
    BOOST_CHECK( F<float>::subset(REP_DEC<float>(REP<float>(0.1f,0.2f), DEC::trv), REP_DEC<double>(REP<double>(-0.0,4.0),DEC::def)) );
    BOOST_CHECK( F<float>::subset(REP_DEC<float>(REP<float>(-0.1f,-0.1f), DEC::trv), REP_DEC<double>(REP<double>(-4.0, 3.4),DEC::trv)) );

    BOOST_CHECK( F<float>::subset(REP_DEC<float>(REP<float>(0.0f,0.0f), DEC::trv), REP_DEC<double>(REP<double>(-0.0,-0.0),DEC::trv)) );
    BOOST_CHECK( F<float>::subset(REP_DEC<float>(REP<float>(-0.0f,-0.0f), DEC::trv), REP_DEC<double>(REP<double>(0.0,0.0),DEC::trv)) );
    BOOST_CHECK( F<float>::subset(REP_DEC<float>(REP<float>(-0.0f,0.0f), DEC::trv), REP_DEC<double>(REP<double>(0.0,0.0),DEC::trv)) );
    BOOST_CHECK( F<float>::subset(REP_DEC<float>(REP<float>(-0.0f,0.0f), DEC::trv), REP_DEC<double>(REP<double>(0.0,-0.0),DEC::def)) );
    BOOST_CHECK( F<float>::subset(REP_DEC<float>(REP<float>(0.0f,-0.0f), DEC::trv), REP_DEC<double>(REP<double>(0.0,0.0),DEC::trv)) );
    BOOST_CHECK( F<float>::subset(REP_DEC<float>(REP<float>(0.0f,-0.0f), DEC::trv), REP_DEC<double>(REP<double>(-0.0,0.0),DEC::trv)) );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK( !F<float>::subset(REP_DEC<float>(REP<float>(0.0f,4.0f), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::def)) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<float>::subset(REP_DEC<float>(REP<float>(0.0f,4.0f), DEC::ill), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}


BOOST_AUTO_TEST_CASE(minimal_less_test)
{
    p1788::exception::clear();

    BOOST_CHECK( F<double>::less(REP<double>(NaN_D,NaN_D), REP<double>(NaN_D,NaN_D)) );
    BOOST_CHECK( !F<double>::less(REP<double>(1.0,2.0), REP<double>(NaN_D,NaN_D)) );
    BOOST_CHECK( !F<double>::less(REP<double>(NaN_D,NaN_D), REP<double>(1.0,2.0)) );

    BOOST_CHECK( F<double>::less(REP<double>(-INF_D,+INF_D), REP<double>(-INF_D,+INF_D)) );
    BOOST_CHECK( !F<double>::less(REP<double>(1.0,2.0), REP<double>(-INF_D,+INF_D)) );
    BOOST_CHECK( !F<double>::less(REP<double>(0.0,2.0), REP<double>(-INF_D,+INF_D)) );
    BOOST_CHECK( !F<double>::less(REP<double>(-0.0,2.0), REP<double>(-INF_D,+INF_D)) );
    BOOST_CHECK( !F<double>::less(REP<double>(-INF_D,+INF_D), REP<double>(1.0,2.0)) );
    BOOST_CHECK( !F<double>::less(REP<double>(-INF_D,+INF_D), REP<double>(0.0,2.0)) );
    BOOST_CHECK( !F<double>::less(REP<double>(-INF_D,+INF_D), REP<double>(-0.0,2.0)) );

    BOOST_CHECK( F<double>::less(REP<double>(0.0,2.0), REP<double>(0.0,2.0)) );
    BOOST_CHECK( F<double>::less(REP<double>(0.0,2.0), REP<double>(-0.0,2.0)) );
    BOOST_CHECK( F<double>::less(REP<double>(0.0,2.0), REP<double>(1.0,2.0)) );
    BOOST_CHECK( F<double>::less(REP<double>(-0.0,2.0), REP<double>(1.0,2.0)) );
    BOOST_CHECK( F<double>::less(REP<double>(1.0,2.0), REP<double>(1.0,2.0)) );
    BOOST_CHECK( F<double>::less(REP<double>(1.0,2.0), REP<double>(3.0,4.0)) );
    BOOST_CHECK( F<double>::less(REP<double>(1.0,3.5), REP<double>(3.0,4.0)) );
    BOOST_CHECK( F<double>::less(REP<double>(1.0,4.0), REP<double>(3.0,4.0)) );

    BOOST_CHECK( F<double>::less(REP<double>(-2.0,-1.0), REP<double>(-2.0,-1.0)) );
    BOOST_CHECK( F<double>::less(REP<double>(-3.0,-1.5), REP<double>(-2.0,-1.0)) );

    BOOST_CHECK( F<double>::less(REP<double>(0.0,0.0), REP<double>(-0.0,-0.0)) );
    BOOST_CHECK( F<double>::less(REP<double>(-0.0,-0.0), REP<double>(0.0,0.0)) );
    BOOST_CHECK( F<double>::less(REP<double>(-0.0,0.0), REP<double>(0.0,0.0)) );
    BOOST_CHECK( F<double>::less(REP<double>(-0.0,0.0), REP<double>(0.0,-0.0)) );
    BOOST_CHECK( F<double>::less(REP<double>(0.0,-0.0), REP<double>(0.0,0.0)) );
    BOOST_CHECK( F<double>::less(REP<double>(0.0,-0.0), REP<double>(-0.0,0.0)) );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK( !F<double>::less(REP<double>(0.0,2.0), REP<double>(1.0,-2.0)) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::less(REP<double>(0.0,NaN_D), REP<double>(1.0,2.0)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}


BOOST_AUTO_TEST_CASE(minimal_less_mixedtype_test)
{
    p1788::exception::clear();

    BOOST_CHECK( F<double>::less(REP<double>(NaN_D,NaN_D), REP<float>(NaN_F,NaN_F)) );
    BOOST_CHECK( !F<double>::less(REP<double>(1.0,2.0), REP<float>(NaN_F,NaN_F)) );
    BOOST_CHECK( !F<double>::less(REP<double>(NaN_D,NaN_D), REP<float>(1.0f,2.0f)) );

    BOOST_CHECK( F<double>::less(REP<double>(-INF_D,+INF_D), REP<float>(-INF_F,+INF_F)) );
    BOOST_CHECK( !F<double>::less(REP<double>(1.0,2.0), REP<float>(-INF_F,+INF_F)) );
    BOOST_CHECK( !F<double>::less(REP<double>(0.0,2.0), REP<float>(-INF_F,+INF_F)) );
    BOOST_CHECK( !F<double>::less(REP<double>(-0.0,2.0), REP<float>(-INF_F,+INF_F)) );
    BOOST_CHECK( !F<double>::less(REP<double>(-INF_D,+INF_D), REP<float>(1.0f,2.0f)) );
    BOOST_CHECK( !F<double>::less(REP<double>(-INF_D,+INF_D), REP<float>(0.0f,2.0f)) );
    BOOST_CHECK( !F<double>::less(REP<double>(-INF_D,+INF_D), REP<float>(-0.0f,2.0f)) );

    BOOST_CHECK( F<double>::less(REP<double>(0.0,2.0), REP<float>(0.0f,2.0f)) );
    BOOST_CHECK( F<double>::less(REP<double>(0.0,2.0), REP<float>(-0.0f,2.0f)) );
    BOOST_CHECK( F<double>::less(REP<double>(0.0,2.0), REP<float>(1.0f,2.0f)) );
    BOOST_CHECK( F<double>::less(REP<double>(-0.0,2.0), REP<float>(1.0f,2.0f)) );
    BOOST_CHECK( F<double>::less(REP<double>(1.0,2.0), REP<float>(1.0f,2.0f)) );
    BOOST_CHECK( F<double>::less(REP<double>(1.0,2.0), REP<float>(3.0f,4.0f)) );
    BOOST_CHECK( F<double>::less(REP<double>(1.0,3.5), REP<float>(3.0f,4.0f)) );
    BOOST_CHECK( F<double>::less(REP<double>(1.0,4.0), REP<float>(3.0f,4.0f)) );

    BOOST_CHECK( F<double>::less(REP<double>(-2.0,-1.0), REP<float>(-2.0f,-1.0f)) );
    BOOST_CHECK( F<double>::less(REP<double>(-3.0,-1.5), REP<float>(-2.0f,-1.0f)) );

    BOOST_CHECK( F<double>::less(REP<double>(0.0,0.0), REP<float>(-0.0f,-0.0f)) );
    BOOST_CHECK( F<double>::less(REP<double>(-0.0,-0.0), REP<float>(0.0f,0.0f)) );
    BOOST_CHECK( F<double>::less(REP<double>(-0.0,0.0), REP<float>(0.0f,0.0f)) );
    BOOST_CHECK( F<double>::less(REP<double>(-0.0,0.0), REP<float>(0.0f,-0.0f)) );
    BOOST_CHECK( F<double>::less(REP<double>(0.0,-0.0), REP<float>(0.0f,0.0f)) );
    BOOST_CHECK( F<double>::less(REP<double>(0.0,-0.0), REP<float>(-0.0f,0.0f)) );


    BOOST_CHECK( F<float>::less(REP<float>(NaN_F,NaN_F), REP<double>(NaN_D,NaN_D)) );
    BOOST_CHECK( !F<float>::less(REP<float>(1.0f,2.0f), REP<double>(NaN_D,NaN_D)) );
    BOOST_CHECK( !F<float>::less(REP<float>(NaN_F,NaN_F), REP<double>(1.0,2.0)) );

    BOOST_CHECK( F<float>::less(REP<float>(-INF_F,+INF_F), REP<double>(-INF_D,+INF_D)) );
    BOOST_CHECK( !F<float>::less(REP<float>(1.0f,2.0f), REP<double>(-INF_D,+INF_D)) );
    BOOST_CHECK( !F<float>::less(REP<float>(0.0f,2.0f), REP<double>(-INF_D,+INF_D)) );
    BOOST_CHECK( !F<float>::less(REP<float>(-0.0f,2.0f), REP<double>(-INF_D,+INF_D)) );
    BOOST_CHECK( !F<float>::less(REP<float>(-INF_F,+INF_F), REP<double>(1.0,2.0)) );
    BOOST_CHECK( !F<float>::less(REP<float>(-INF_F,+INF_F), REP<double>(0.0,2.0)) );
    BOOST_CHECK( !F<float>::less(REP<float>(-INF_F,+INF_F), REP<double>(-0.0,2.0)) );

    BOOST_CHECK( F<float>::less(REP<float>(0.0f,2.0f), REP<double>(0.0,2.0)) );
    BOOST_CHECK( F<float>::less(REP<float>(0.0f,2.0f), REP<double>(-0.0,2.0)) );
    BOOST_CHECK( F<float>::less(REP<float>(0.0f,2.0f), REP<double>(1.0,2.0)) );
    BOOST_CHECK( F<float>::less(REP<float>(-0.0f,2.0f), REP<double>(1.0,2.0)) );
    BOOST_CHECK( F<float>::less(REP<float>(1.0f,2.0f), REP<double>(1.0,2.0)) );
    BOOST_CHECK( F<float>::less(REP<float>(1.0f,2.0f), REP<double>(3.0,4.0)) );
    BOOST_CHECK( F<float>::less(REP<float>(1.0f,3.5f), REP<double>(3.0,4.0)) );
    BOOST_CHECK( F<float>::less(REP<float>(1.0f,4.0f), REP<double>(3.0,4.0)) );

    BOOST_CHECK( F<float>::less(REP<float>(-2.0f,-1.0f), REP<double>(-2.0,-1.0)) );
    BOOST_CHECK( F<float>::less(REP<float>(-3.0f,-1.5f), REP<double>(-2.0,-1.0)) );

    BOOST_CHECK( F<float>::less(REP<float>(0.0f,0.0f), REP<double>(-0.0,-0.0)) );
    BOOST_CHECK( F<float>::less(REP<float>(-0.0f,-0.0f), REP<double>(0.0,0.0)) );
    BOOST_CHECK( F<float>::less(REP<float>(-0.0f,0.0f), REP<double>(0.0,0.0)) );
    BOOST_CHECK( F<float>::less(REP<float>(-0.0f,0.0f), REP<double>(0.0,-0.0)) );
    BOOST_CHECK( F<float>::less(REP<float>(0.0f,-0.0f), REP<double>(0.0,0.0)) );
    BOOST_CHECK( F<float>::less(REP<float>(0.0f,-0.0f), REP<double>(-0.0,0.0)) );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK( !F<double>::less(REP<double>(1.0,2.0), REP<float>(1.0f,-2.0f)) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::less(REP<double>(1.0,-2.0), REP<float>(1.0f,2.0f)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}

BOOST_AUTO_TEST_CASE(minimal_less_dec_test)
{
    p1788::exception::clear();

    BOOST_CHECK( !F<double>::less(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );
    BOOST_CHECK( !F<double>::less(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );
    BOOST_CHECK( !F<double>::less(REP_DEC<double>(REP<double>(1.0,2.0), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );
    BOOST_CHECK( !F<double>::less(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill), REP_DEC<double>(REP<double>(1.0,2.0),DEC::def)) );

    BOOST_CHECK( F<double>::less(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );
    BOOST_CHECK( !F<double>::less(REP_DEC<double>(REP<double>(1.0,2.0), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );
    BOOST_CHECK( !F<double>::less(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<double>(REP<double>(1.0,2.0),DEC::trv)) );

    BOOST_CHECK( F<double>::less(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );
    BOOST_CHECK( !F<double>::less(REP_DEC<double>(REP<double>(1.0,2.0), DEC::def), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );
    BOOST_CHECK( !F<double>::less(REP_DEC<double>(REP<double>(0.0,2.0), DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );
    BOOST_CHECK( !F<double>::less(REP_DEC<double>(REP<double>(-0.0,2.0), DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );
    BOOST_CHECK( !F<double>::less(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::trv), REP_DEC<double>(REP<double>(1.0,2.0),DEC::trv)) );
    BOOST_CHECK( !F<double>::less(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::trv), REP_DEC<double>(REP<double>(0.0,2.0),DEC::def)) );
    BOOST_CHECK( !F<double>::less(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::trv), REP_DEC<double>(REP<double>(-0.0,2.0),DEC::trv)) );

    BOOST_CHECK( F<double>::less(REP_DEC<double>(REP<double>(0.0,2.0), DEC::trv), REP_DEC<double>(REP<double>(0.0,2.0),DEC::trv)) );
    BOOST_CHECK( F<double>::less(REP_DEC<double>(REP<double>(0.0,2.0), DEC::trv), REP_DEC<double>(REP<double>(-0.0,2.0),DEC::trv)) );
    BOOST_CHECK( F<double>::less(REP_DEC<double>(REP<double>(0.0,2.0), DEC::def), REP_DEC<double>(REP<double>(1.0,2.0),DEC::def)) );
    BOOST_CHECK( F<double>::less(REP_DEC<double>(REP<double>(-0.0,2.0), DEC::trv), REP_DEC<double>(REP<double>(1.0,2.0),DEC::trv)) );
    BOOST_CHECK( F<double>::less(REP_DEC<double>(REP<double>(1.0,2.0), DEC::trv), REP_DEC<double>(REP<double>(1.0,2.0),DEC::trv)) );
    BOOST_CHECK( F<double>::less(REP_DEC<double>(REP<double>(1.0,2.0), DEC::trv), REP_DEC<double>(REP<double>(3.0,4.0),DEC::def)) );
    BOOST_CHECK( F<double>::less(REP_DEC<double>(REP<double>(1.0,3.5), DEC::trv), REP_DEC<double>(REP<double>(3.0,4.0),DEC::trv)) );
    BOOST_CHECK( F<double>::less(REP_DEC<double>(REP<double>(1.0,4.0), DEC::trv), REP_DEC<double>(REP<double>(3.0,4.0),DEC::trv)) );

    BOOST_CHECK( F<double>::less(REP_DEC<double>(REP<double>(-2.0,-1.0), DEC::trv), REP_DEC<double>(REP<double>(-2.0,-1.0),DEC::trv)) );
    BOOST_CHECK( F<double>::less(REP_DEC<double>(REP<double>(-3.0,-1.5), DEC::trv), REP_DEC<double>(REP<double>(-2.0,-1.0),DEC::trv)) );

    BOOST_CHECK( F<double>::less(REP_DEC<double>(REP<double>(0.0,0.0), DEC::trv), REP_DEC<double>(REP<double>(-0.0,-0.0),DEC::trv)) );
    BOOST_CHECK( F<double>::less(REP_DEC<double>(REP<double>(-0.0,-0.0), DEC::trv), REP_DEC<double>(REP<double>(0.0,0.0),DEC::def)) );
    BOOST_CHECK( F<double>::less(REP_DEC<double>(REP<double>(-0.0,0.0), DEC::trv), REP_DEC<double>(REP<double>(0.0,0.0),DEC::trv)) );
    BOOST_CHECK( F<double>::less(REP_DEC<double>(REP<double>(-0.0,0.0), DEC::trv), REP_DEC<double>(REP<double>(0.0,-0.0),DEC::trv)) );
    BOOST_CHECK( F<double>::less(REP_DEC<double>(REP<double>(0.0,-0.0), DEC::def), REP_DEC<double>(REP<double>(0.0,0.0),DEC::trv)) );
    BOOST_CHECK( F<double>::less(REP_DEC<double>(REP<double>(0.0,-0.0), DEC::trv), REP_DEC<double>(REP<double>(-0.0,0.0),DEC::trv)) );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK( !F<double>::less(REP_DEC<double>(REP<double>(1.0,-2.0), DEC::trv), REP_DEC<double>(REP<double>(3.0,4.0),DEC::def)) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::less(REP_DEC<double>(REP<double>(1.0,2.0), DEC::trv), REP_DEC<double>(REP<double>(3.0,-4.0),DEC::def)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}


BOOST_AUTO_TEST_CASE(minimal_less_dec_mixedtype_test)
{
    p1788::exception::clear();

    BOOST_CHECK( !F<double>::less(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill), REP_DEC<float>(REP<float>(NaN_F,NaN_F),DEC::ill)) );
    BOOST_CHECK( !F<double>::less(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<float>(REP<float>(NaN_F,NaN_F),DEC::ill)) );
    BOOST_CHECK( !F<double>::less(REP_DEC<double>(REP<double>(1.0,2.0), DEC::trv), REP_DEC<float>(REP<float>(NaN_F,NaN_F),DEC::ill)) );
    BOOST_CHECK( !F<double>::less(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill), REP_DEC<float>(REP<float>(1.0f,2.0f),DEC::trv)) );

    BOOST_CHECK( F<double>::less(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<float>(REP<float>(NaN_F,NaN_F),DEC::trv)) );
    BOOST_CHECK( !F<double>::less(REP_DEC<double>(REP<double>(1.0,2.0), DEC::trv), REP_DEC<float>(REP<float>(NaN_F,NaN_F),DEC::trv)) );
    BOOST_CHECK( !F<double>::less(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<float>(REP<float>(1.0f,2.0f),DEC::trv)) );

    BOOST_CHECK( F<double>::less(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::trv), REP_DEC<float>(REP<float>(-INF_F,+INF_F),DEC::def)) );
    BOOST_CHECK( !F<double>::less(REP_DEC<double>(REP<double>(1.0,2.0), DEC::trv), REP_DEC<float>(REP<float>(-INF_F,+INF_F),DEC::trv)) );
    BOOST_CHECK( !F<double>::less(REP_DEC<double>(REP<double>(0.0,2.0), DEC::def), REP_DEC<float>(REP<float>(-INF_F,+INF_F),DEC::trv)) );
    BOOST_CHECK( !F<double>::less(REP_DEC<double>(REP<double>(-0.0,2.0), DEC::trv), REP_DEC<float>(REP<float>(-INF_F,+INF_F),DEC::trv)) );
    BOOST_CHECK( !F<double>::less(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::trv), REP_DEC<float>(REP<float>(1.0f,2.0f),DEC::trv)) );
    BOOST_CHECK( !F<double>::less(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::trv), REP_DEC<float>(REP<float>(0.0f,2.0f),DEC::def)) );
    BOOST_CHECK( !F<double>::less(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::trv), REP_DEC<float>(REP<float>(-0.0f,2.0f),DEC::trv)) );

    BOOST_CHECK( F<double>::less(REP_DEC<double>(REP<double>(0.0,2.0), DEC::trv), REP_DEC<float>(REP<float>(0.0f,2.0f),DEC::trv)) );
    BOOST_CHECK( F<double>::less(REP_DEC<double>(REP<double>(0.0,2.0), DEC::trv), REP_DEC<float>(REP<float>(-0.0f,2.0f),DEC::trv)) );
    BOOST_CHECK( F<double>::less(REP_DEC<double>(REP<double>(0.0,2.0), DEC::def), REP_DEC<float>(REP<float>(1.0f,2.0f),DEC::def)) );
    BOOST_CHECK( F<double>::less(REP_DEC<double>(REP<double>(-0.0,2.0), DEC::trv), REP_DEC<float>(REP<float>(1.0f,2.0f),DEC::trv)) );
    BOOST_CHECK( F<double>::less(REP_DEC<double>(REP<double>(1.0,2.0), DEC::trv), REP_DEC<float>(REP<float>(1.0f,2.0f),DEC::trv)) );
    BOOST_CHECK( F<double>::less(REP_DEC<double>(REP<double>(1.0,2.0), DEC::trv), REP_DEC<float>(REP<float>(3.0f,4.0f),DEC::def)) );
    BOOST_CHECK( F<double>::less(REP_DEC<double>(REP<double>(1.0,3.5), DEC::trv), REP_DEC<float>(REP<float>(3.0f,4.0f),DEC::trv)) );
    BOOST_CHECK( F<double>::less(REP_DEC<double>(REP<double>(1.0,4.0), DEC::trv), REP_DEC<float>(REP<float>(3.0f,4.0f),DEC::trv)) );

    BOOST_CHECK( F<double>::less(REP_DEC<double>(REP<double>(-2.0,-1.0), DEC::trv), REP_DEC<float>(REP<float>(-2.0f,-1.0f),DEC::trv)) );
    BOOST_CHECK( F<double>::less(REP_DEC<double>(REP<double>(-3.0,-1.5), DEC::trv), REP_DEC<float>(REP<float>(-2.0f,-1.0f),DEC::trv)) );

    BOOST_CHECK( F<double>::less(REP_DEC<double>(REP<double>(0.0,0.0), DEC::trv), REP_DEC<float>(REP<float>(-0.0f,-0.0f),DEC::trv)) );
    BOOST_CHECK( F<double>::less(REP_DEC<double>(REP<double>(-0.0,-0.0), DEC::trv), REP_DEC<float>(REP<float>(0.0f,0.0f),DEC::trv)) );
    BOOST_CHECK( F<double>::less(REP_DEC<double>(REP<double>(-0.0,0.0), DEC::def), REP_DEC<float>(REP<float>(0.0f,0.0f),DEC::trv)) );
    BOOST_CHECK( F<double>::less(REP_DEC<double>(REP<double>(-0.0,0.0), DEC::trv), REP_DEC<float>(REP<float>(0.0f,-0.0f),DEC::def)) );
    BOOST_CHECK( F<double>::less(REP_DEC<double>(REP<double>(0.0,-0.0), DEC::trv), REP_DEC<float>(REP<float>(0.0f,0.0f),DEC::trv)) );
    BOOST_CHECK( F<double>::less(REP_DEC<double>(REP<double>(0.0,-0.0), DEC::trv), REP_DEC<float>(REP<float>(-0.0f,0.0f),DEC::trv)) );


    BOOST_CHECK( !F<float>::less(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::ill), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );
    BOOST_CHECK( !F<float>::less(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );
    BOOST_CHECK( !F<float>::less(REP_DEC<float>(REP<float>(1.0f,2.0f), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );
    BOOST_CHECK( !F<float>::less(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::ill), REP_DEC<double>(REP<double>(1.0,2.0),DEC::trv)) );

    BOOST_CHECK( F<float>::less(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );
    BOOST_CHECK( !F<float>::less(REP_DEC<float>(REP<float>(1.0f,2.0f), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );
    BOOST_CHECK( !F<float>::less(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::trv), REP_DEC<double>(REP<double>(1.0,2.0),DEC::trv)) );

    BOOST_CHECK( F<float>::less(REP_DEC<float>(REP<float>(-INF_F,+INF_F), DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );
    BOOST_CHECK( !F<float>::less(REP_DEC<float>(REP<float>(1.0f,2.0f), DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );
    BOOST_CHECK( !F<float>::less(REP_DEC<float>(REP<float>(0.0f,2.0f), DEC::def), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );
    BOOST_CHECK( !F<float>::less(REP_DEC<float>(REP<float>(-0.0f,2.0f), DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );
    BOOST_CHECK( !F<float>::less(REP_DEC<float>(REP<float>(-INF_F,+INF_F), DEC::trv), REP_DEC<double>(REP<double>(1.0,2.0),DEC::trv)) );
    BOOST_CHECK( !F<float>::less(REP_DEC<float>(REP<float>(-INF_F,+INF_F), DEC::trv), REP_DEC<double>(REP<double>(0.0,2.0),DEC::def)) );
    BOOST_CHECK( !F<float>::less(REP_DEC<float>(REP<float>(-INF_F,+INF_F), DEC::trv), REP_DEC<double>(REP<double>(-0.0,2.0),DEC::trv)) );

    BOOST_CHECK( F<float>::less(REP_DEC<float>(REP<float>(0.0f,2.0f), DEC::trv), REP_DEC<double>(REP<double>(0.0,2.0),DEC::trv)) );
    BOOST_CHECK( F<float>::less(REP_DEC<float>(REP<float>(0.0f,2.0f), DEC::trv), REP_DEC<double>(REP<double>(-0.0,2.0),DEC::trv)) );
    BOOST_CHECK( F<float>::less(REP_DEC<float>(REP<float>(0.0f,2.0f), DEC::trv), REP_DEC<double>(REP<double>(1.0,2.0),DEC::trv)) );
    BOOST_CHECK( F<float>::less(REP_DEC<float>(REP<float>(-0.0f,2.0f), DEC::def), REP_DEC<double>(REP<double>(1.0,2.0),DEC::def)) );
    BOOST_CHECK( F<float>::less(REP_DEC<float>(REP<float>(1.0f,2.0f), DEC::trv), REP_DEC<double>(REP<double>(1.0,2.0),DEC::trv)) );
    BOOST_CHECK( F<float>::less(REP_DEC<float>(REP<float>(1.0f,2.0f), DEC::trv), REP_DEC<double>(REP<double>(3.0,4.0),DEC::trv)) );
    BOOST_CHECK( F<float>::less(REP_DEC<float>(REP<float>(1.0f,3.5f), DEC::trv), REP_DEC<double>(REP<double>(3.0,4.0),DEC::def)) );
    BOOST_CHECK( F<float>::less(REP_DEC<float>(REP<float>(1.0f,4.0f), DEC::trv), REP_DEC<double>(REP<double>(3.0,4.0),DEC::trv)) );

    BOOST_CHECK( F<float>::less(REP_DEC<float>(REP<float>(-2.0f,-1.0f), DEC::trv), REP_DEC<double>(REP<double>(-2.0,-1.0),DEC::trv)) );
    BOOST_CHECK( F<float>::less(REP_DEC<float>(REP<float>(-3.0f,-1.5f), DEC::trv), REP_DEC<double>(REP<double>(-2.0,-1.0),DEC::trv)) );

    BOOST_CHECK( F<float>::less(REP_DEC<float>(REP<float>(0.0f,0.0f), DEC::trv), REP_DEC<double>(REP<double>(-0.0,-0.0),DEC::trv)) );
    BOOST_CHECK( F<float>::less(REP_DEC<float>(REP<float>(-0.0f,-0.0f), DEC::trv), REP_DEC<double>(REP<double>(0.0,0.0),DEC::trv)) );
    BOOST_CHECK( F<float>::less(REP_DEC<float>(REP<float>(-0.0f,0.0f), DEC::trv), REP_DEC<double>(REP<double>(0.0,0.0),DEC::def)) );
    BOOST_CHECK( F<float>::less(REP_DEC<float>(REP<float>(-0.0f,0.0f), DEC::trv), REP_DEC<double>(REP<double>(0.0,-0.0),DEC::trv)) );
    BOOST_CHECK( F<float>::less(REP_DEC<float>(REP<float>(0.0f,-0.0f), DEC::def), REP_DEC<double>(REP<double>(0.0,0.0),DEC::trv)) );
    BOOST_CHECK( F<float>::less(REP_DEC<float>(REP<float>(0.0f,-0.0f), DEC::trv), REP_DEC<double>(REP<double>(-0.0,0.0),DEC::trv)) );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK( !F<double>::less(REP_DEC<double>(REP<double>(1.0,-2.0), DEC::trv), REP_DEC<float>(REP<float>(1.0f,2.0f),DEC::trv)) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::less(REP_DEC<double>(REP<double>(1.0,2.0), DEC::trv), REP_DEC<float>(REP<float>(-1.0f,-2.0f),DEC::trv)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}


BOOST_AUTO_TEST_CASE(minimal_precedes_test)
{
    p1788::exception::clear();

    BOOST_CHECK( F<double>::precedes(REP<double>(NaN_D,NaN_D), REP<double>(3.0,4.0)) );
    BOOST_CHECK( F<double>::precedes(REP<double>(3.0,4.0), REP<double>(NaN_D,NaN_D)) );
    BOOST_CHECK( F<double>::precedes(REP<double>(NaN_D,NaN_D), REP<double>(NaN_D,NaN_D)) );


    BOOST_CHECK( !F<double>::precedes(REP<double>(1.0,2.0), REP<double>(-INF_D,+INF_D)) );
    BOOST_CHECK( !F<double>::precedes(REP<double>(0.0,2.0), REP<double>(-INF_D,+INF_D)) );
    BOOST_CHECK( !F<double>::precedes(REP<double>(-0.0,2.0), REP<double>(-INF_D,+INF_D)) );
    BOOST_CHECK( !F<double>::precedes(REP<double>(-INF_D,+INF_D), REP<double>(1.0,2.0)) );
    BOOST_CHECK( !F<double>::precedes(REP<double>(-INF_D,+INF_D), REP<double>(-INF_D,+INF_D)) );

    BOOST_CHECK( F<double>::precedes(REP<double>(1.0,2.0), REP<double>(3.0,4.0)) );
    BOOST_CHECK( F<double>::precedes(REP<double>(1.0,3.0), REP<double>(3.0,4.0)) );
    BOOST_CHECK( F<double>::precedes(REP<double>(-3.0, -1.0), REP<double>(-1.0,0.0)) );
    BOOST_CHECK( F<double>::precedes(REP<double>(-3.0, -1.0), REP<double>(-1.0,-0.0)) );

    BOOST_CHECK( !F<double>::precedes(REP<double>(1.0,3.5), REP<double>(3.0,4.0)) );
    BOOST_CHECK( !F<double>::precedes(REP<double>(1.0,4.0), REP<double>(3.0,4.0)) );
    BOOST_CHECK( !F<double>::precedes(REP<double>(-3.0, -0.1), REP<double>(-1.0,0.0)) );

    BOOST_CHECK( F<double>::precedes(REP<double>(0.0,0.0), REP<double>(-0.0,-0.0)) );
    BOOST_CHECK( F<double>::precedes(REP<double>(-0.0,-0.0), REP<double>(0.0,0.0)) );
    BOOST_CHECK( F<double>::precedes(REP<double>(-0.0,0.0), REP<double>(0.0,0.0)) );
    BOOST_CHECK( F<double>::precedes(REP<double>(-0.0,0.0), REP<double>(0.0,-0.0)) );
    BOOST_CHECK( F<double>::precedes(REP<double>(0.0,-0.0), REP<double>(0.0,0.0)) );
    BOOST_CHECK( F<double>::precedes(REP<double>(0.0,-0.0), REP<double>(-0.0,0.0)) );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK( !F<double>::precedes(REP<double>(-3.0, -1.0), REP<double>(1.0,0.0)) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::precedes(REP<double>(3.0, -1.0), REP<double>(-1.0,0.0)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}

BOOST_AUTO_TEST_CASE(minimal_precedes_mixedtype_test)
{
    p1788::exception::clear();

    BOOST_CHECK( F<double>::precedes(REP<double>(NaN_D,NaN_D), REP<float>(3.0f,4.0f)) );
    BOOST_CHECK( F<double>::precedes(REP<double>(3.0,4.0), REP<float>(NaN_F,NaN_F)) );
    BOOST_CHECK( F<double>::precedes(REP<double>(NaN_D,NaN_D), REP<float>(NaN_F,NaN_F)) );

    BOOST_CHECK( !F<double>::precedes(REP<double>(1.0,2.0), REP<float>(-INF_F,+INF_F)) );
    BOOST_CHECK( !F<double>::precedes(REP<double>(0.0,2.0), REP<float>(-INF_F,+INF_F)) );
    BOOST_CHECK( !F<double>::precedes(REP<double>(-0.0,2.0), REP<float>(-INF_F,+INF_F)) );
    BOOST_CHECK( !F<double>::precedes(REP<double>(-INF_D,+INF_D), REP<float>(1.0f,2.0f)) );
    BOOST_CHECK( !F<double>::precedes(REP<double>(-INF_D,+INF_D), REP<float>(-INF_F,+INF_F)) );

    BOOST_CHECK( F<double>::precedes(REP<double>(1.0,2.0), REP<float>(3.0f,4.0f)) );
    BOOST_CHECK( F<double>::precedes(REP<double>(1.0,3.0), REP<float>(3.0f,4.0f)) );
    BOOST_CHECK( F<double>::precedes(REP<double>(-3.0, -1.0), REP<float>(-1.0f,0.0f)) );
    BOOST_CHECK( F<double>::precedes(REP<double>(-3.0, -1.0), REP<float>(-1.0f,-0.0f)) );

    BOOST_CHECK( !F<double>::precedes(REP<double>(1.0,3.5), REP<float>(3.0f,4.0f)) );
    BOOST_CHECK( !F<double>::precedes(REP<double>(1.0,4.0), REP<float>(3.0f,4.0f)) );
    BOOST_CHECK( !F<double>::precedes(REP<double>(-3.0, -0.1), REP<float>(-1.0f,0.0f)) );

    BOOST_CHECK( F<double>::precedes(REP<double>(0.0,0.0), REP<float>(-0.0f,-0.0f)) );
    BOOST_CHECK( F<double>::precedes(REP<double>(-0.0,-0.0), REP<float>(0.0f,0.0f)) );
    BOOST_CHECK( F<double>::precedes(REP<double>(-0.0,0.0), REP<float>(0.0f,0.0f)) );
    BOOST_CHECK( F<double>::precedes(REP<double>(-0.0,0.0), REP<float>(0.0f,-0.0f)) );
    BOOST_CHECK( F<double>::precedes(REP<double>(0.0,-0.0), REP<float>(0.0f,0.0f)) );
    BOOST_CHECK( F<double>::precedes(REP<double>(0.0,-0.0), REP<float>(-0.0f,0.0f)) );

    BOOST_CHECK( F<float>::precedes(REP<float>(NaN_F,NaN_F), REP<double>(3.0,4.0)) );
    BOOST_CHECK( F<float>::precedes(REP<float>(3.0f,4.0f), REP<double>(NaN_D,NaN_D)) );
    BOOST_CHECK( F<float>::precedes(REP<float>(NaN_F,NaN_F), REP<double>(NaN_D,NaN_D)) );

    BOOST_CHECK( !F<float>::precedes(REP<float>(1.0f,2.0f), REP<double>(-INF_D,+INF_D)) );
    BOOST_CHECK( !F<float>::precedes(REP<float>(0.0f,2.0f), REP<double>(-INF_D,+INF_D)) );
    BOOST_CHECK( !F<float>::precedes(REP<float>(-0.0f,2.0f), REP<double>(-INF_D,+INF_D)) );
    BOOST_CHECK( !F<float>::precedes(REP<float>(-INF_F,+INF_F), REP<double>(1.0,2.0)) );
    BOOST_CHECK( !F<float>::precedes(REP<float>(-INF_F,+INF_F), REP<double>(-INF_D,+INF_D)) );

    BOOST_CHECK( F<float>::precedes(REP<float>(1.0f,2.0f), REP<double>(3.0,4.0)) );
    BOOST_CHECK( F<float>::precedes(REP<float>(1.0f,3.0f), REP<double>(3.0,4.0)) );
    BOOST_CHECK( F<float>::precedes(REP<float>(-3.0f, -1.0f), REP<double>(-1.0,0.0)) );
    BOOST_CHECK( F<float>::precedes(REP<float>(-3.0f, -1.0f), REP<double>(-1.0,-0.0)) );

    BOOST_CHECK( !F<float>::precedes(REP<float>(1.0f,3.5f), REP<double>(3.0,4.0)) );
    BOOST_CHECK( !F<float>::precedes(REP<float>(1.0f,4.0f), REP<double>(3.0,4.0)) );
    BOOST_CHECK( !F<float>::precedes(REP<float>(-3.0f, -0.1f), REP<double>(-1.0,0.0)) );

    BOOST_CHECK( F<float>::precedes(REP<float>(0.0f,0.0f), REP<double>(-0.0,-0.0)) );
    BOOST_CHECK( F<float>::precedes(REP<float>(-0.0f,-0.0f), REP<double>(0.0,0.0)) );
    BOOST_CHECK( F<float>::precedes(REP<float>(-0.0f,0.0f), REP<double>(0.0,0.0)) );
    BOOST_CHECK( F<float>::precedes(REP<float>(-0.0f,0.0f), REP<double>(0.0,-0.0)) );
    BOOST_CHECK( F<float>::precedes(REP<float>(0.0f,-0.0f), REP<double>(0.0,0.0)) );
    BOOST_CHECK( F<float>::precedes(REP<float>(0.0f,-0.0f), REP<double>(-0.0,0.0)) );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK( !F<double>::precedes(REP<double>(1.0,3.5), REP<float>(3.0f,-4.0f)) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW(!F<double>::precedes(REP<double>(1.0,-3.5), REP<float>(3.0f,4.0f)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}


BOOST_AUTO_TEST_CASE(minimal_precedes_dec_test)
{
    p1788::exception::clear();

    BOOST_CHECK( !F<double>::precedes(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill), REP_DEC<double>(REP<double>(3.0,4.0),DEC::def)) );
    BOOST_CHECK( !F<double>::precedes(REP_DEC<double>(REP<double>(3.0,4.0), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );
    BOOST_CHECK( !F<double>::precedes(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );
    BOOST_CHECK( !F<double>::precedes(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );

    BOOST_CHECK( F<double>::precedes(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<double>(REP<double>(3.0,4.0),DEC::trv)) );
    BOOST_CHECK( F<double>::precedes(REP_DEC<double>(REP<double>(3.0,4.0), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );
    BOOST_CHECK( F<double>::precedes(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );


    BOOST_CHECK( !F<double>::precedes(REP_DEC<double>(REP<double>(1.0,2.0), DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );
    BOOST_CHECK( !F<double>::precedes(REP_DEC<double>(REP<double>(0.0,2.0), DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );
    BOOST_CHECK( !F<double>::precedes(REP_DEC<double>(REP<double>(-0.0,2.0), DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );
    BOOST_CHECK( !F<double>::precedes(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::trv), REP_DEC<double>(REP<double>(1.0,2.0),DEC::trv)) );
    BOOST_CHECK( !F<double>::precedes(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );

    BOOST_CHECK( F<double>::precedes(REP_DEC<double>(REP<double>(1.0,2.0), DEC::trv), REP_DEC<double>(REP<double>(3.0,4.0),DEC::trv)) );
    BOOST_CHECK( F<double>::precedes(REP_DEC<double>(REP<double>(1.0,3.0), DEC::trv), REP_DEC<double>(REP<double>(3.0,4.0),DEC::def)) );
    BOOST_CHECK( F<double>::precedes(REP_DEC<double>(REP<double>(-3.0, -1.0), DEC::def), REP_DEC<double>(REP<double>(-1.0,0.0),DEC::trv)) );
    BOOST_CHECK( F<double>::precedes(REP_DEC<double>(REP<double>(-3.0, -1.0), DEC::trv), REP_DEC<double>(REP<double>(-1.0,-0.0),DEC::trv)) );

    BOOST_CHECK( !F<double>::precedes(REP_DEC<double>(REP<double>(1.0,3.5), DEC::trv), REP_DEC<double>(REP<double>(3.0,4.0),DEC::trv)) );
    BOOST_CHECK( !F<double>::precedes(REP_DEC<double>(REP<double>(1.0,4.0), DEC::trv), REP_DEC<double>(REP<double>(3.0,4.0),DEC::trv)) );
    BOOST_CHECK( !F<double>::precedes(REP_DEC<double>(REP<double>(-3.0, -0.1), DEC::trv), REP_DEC<double>(REP<double>(-1.0,0.0),DEC::trv)) );

    BOOST_CHECK( F<double>::precedes(REP_DEC<double>(REP<double>(0.0,0.0), DEC::trv), REP_DEC<double>(REP<double>(-0.0,-0.0),DEC::trv)) );
    BOOST_CHECK( F<double>::precedes(REP_DEC<double>(REP<double>(-0.0,-0.0), DEC::trv), REP_DEC<double>(REP<double>(0.0,0.0),DEC::def)) );
    BOOST_CHECK( F<double>::precedes(REP_DEC<double>(REP<double>(-0.0,0.0), DEC::trv), REP_DEC<double>(REP<double>(0.0,0.0),DEC::trv)) );
    BOOST_CHECK( F<double>::precedes(REP_DEC<double>(REP<double>(-0.0,0.0), DEC::def), REP_DEC<double>(REP<double>(0.0,-0.0),DEC::trv)) );
    BOOST_CHECK( F<double>::precedes(REP_DEC<double>(REP<double>(0.0,-0.0), DEC::trv), REP_DEC<double>(REP<double>(0.0,0.0),DEC::trv)) );
    BOOST_CHECK( F<double>::precedes(REP_DEC<double>(REP<double>(0.0,-0.0), DEC::trv), REP_DEC<double>(REP<double>(-0.0,0.0),DEC::trv)) );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK( !F<double>::precedes(REP_DEC<double>(REP<double>(1.0,3.5), DEC::ill), REP_DEC<double>(REP<double>(3.0,4.0),DEC::trv)) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::precedes(REP_DEC<double>(REP<double>(1.0,3.5), DEC::trv), REP_DEC<double>(REP<double>(3.0,-4.0),DEC::trv)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}

BOOST_AUTO_TEST_CASE(minimal_precedes_dec_mixedtype_test)
{
    p1788::exception::clear();

    BOOST_CHECK( !F<double>::precedes(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill), REP_DEC<float>(REP<float>(3.0f,4.0f),DEC::trv)) );
    BOOST_CHECK( !F<double>::precedes(REP_DEC<double>(REP<double>(3.0,4.0), DEC::trv), REP_DEC<float>(REP<float>(NaN_F,NaN_F),DEC::ill)) );
    BOOST_CHECK( !F<double>::precedes(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<float>(REP<float>(NaN_F,NaN_F),DEC::ill)) );
    BOOST_CHECK( !F<double>::precedes(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill), REP_DEC<float>(REP<float>(NaN_F,NaN_F),DEC::ill)) );

    BOOST_CHECK( F<double>::precedes(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<float>(REP<float>(3.0f,4.0f),DEC::trv)) );
    BOOST_CHECK( F<double>::precedes(REP_DEC<double>(REP<double>(3.0,4.0), DEC::trv), REP_DEC<float>(REP<float>(NaN_F,NaN_F),DEC::trv)) );
    BOOST_CHECK( F<double>::precedes(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<float>(REP<float>(NaN_F,NaN_F),DEC::trv)) );

    BOOST_CHECK( !F<double>::precedes(REP_DEC<double>(REP<double>(1.0,2.0), DEC::trv), REP_DEC<float>(REP<float>(-INF_F,+INF_F),DEC::trv)) );
    BOOST_CHECK( !F<double>::precedes(REP_DEC<double>(REP<double>(0.0,2.0), DEC::def), REP_DEC<float>(REP<float>(-INF_F,+INF_F),DEC::trv)) );
    BOOST_CHECK( !F<double>::precedes(REP_DEC<double>(REP<double>(-0.0,2.0), DEC::trv), REP_DEC<float>(REP<float>(-INF_F,+INF_F),DEC::trv)) );
    BOOST_CHECK( !F<double>::precedes(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::trv), REP_DEC<float>(REP<float>(1.0f,2.0f),DEC::trv)) );
    BOOST_CHECK( !F<double>::precedes(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::trv), REP_DEC<float>(REP<float>(-INF_F,+INF_F),DEC::trv)) );

    BOOST_CHECK( F<double>::precedes(REP_DEC<double>(REP<double>(1.0,2.0), DEC::trv), REP_DEC<float>(REP<float>(3.0f,4.0f),DEC::trv)) );
    BOOST_CHECK( F<double>::precedes(REP_DEC<double>(REP<double>(1.0,3.0), DEC::trv), REP_DEC<float>(REP<float>(3.0f,4.0f),DEC::trv)) );
    BOOST_CHECK( F<double>::precedes(REP_DEC<double>(REP<double>(-3.0, -1.0), DEC::trv), REP_DEC<float>(REP<float>(-1.0f,0.0f),DEC::def)) );
    BOOST_CHECK( F<double>::precedes(REP_DEC<double>(REP<double>(-3.0, -1.0), DEC::trv), REP_DEC<float>(REP<float>(-1.0f,-0.0f),DEC::trv)) );

    BOOST_CHECK( !F<double>::precedes(REP_DEC<double>(REP<double>(1.0,3.5), DEC::trv), REP_DEC<float>(REP<float>(3.0f,4.0f),DEC::trv)) );
    BOOST_CHECK( !F<double>::precedes(REP_DEC<double>(REP<double>(1.0,4.0), DEC::def), REP_DEC<float>(REP<float>(3.0f,4.0f),DEC::trv)) );
    BOOST_CHECK( !F<double>::precedes(REP_DEC<double>(REP<double>(-3.0, -0.1), DEC::trv), REP_DEC<float>(REP<float>(-1.0f,0.0f),DEC::trv)) );

    BOOST_CHECK( F<double>::precedes(REP_DEC<double>(REP<double>(0.0,0.0), DEC::trv), REP_DEC<float>(REP<float>(-0.0f,-0.0f),DEC::trv)) );
    BOOST_CHECK( F<double>::precedes(REP_DEC<double>(REP<double>(-0.0,-0.0), DEC::trv), REP_DEC<float>(REP<float>(0.0f,0.0f),DEC::trv)) );
    BOOST_CHECK( F<double>::precedes(REP_DEC<double>(REP<double>(-0.0,0.0), DEC::def), REP_DEC<float>(REP<float>(0.0f,0.0f),DEC::def)) );
    BOOST_CHECK( F<double>::precedes(REP_DEC<double>(REP<double>(-0.0,0.0), DEC::trv), REP_DEC<float>(REP<float>(0.0f,-0.0f),DEC::trv)) );
    BOOST_CHECK( F<double>::precedes(REP_DEC<double>(REP<double>(0.0,-0.0), DEC::trv), REP_DEC<float>(REP<float>(0.0f,0.0f),DEC::trv)) );
    BOOST_CHECK( F<double>::precedes(REP_DEC<double>(REP<double>(0.0,-0.0), DEC::trv), REP_DEC<float>(REP<float>(-0.0f,0.0f),DEC::trv)) );

    BOOST_CHECK( !F<float>::precedes(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::ill), REP_DEC<double>(REP<double>(3.0,4.0),DEC::trv)) );
    BOOST_CHECK( !F<float>::precedes(REP_DEC<float>(REP<float>(3.0f,4.0f), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );
    BOOST_CHECK( !F<float>::precedes(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );
    BOOST_CHECK( !F<float>::precedes(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::ill), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );

    BOOST_CHECK( F<float>::precedes(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::trv), REP_DEC<double>(REP<double>(3.0,4.0),DEC::trv)) );
    BOOST_CHECK( F<float>::precedes(REP_DEC<float>(REP<float>(3.0f,4.0f), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );
    BOOST_CHECK( F<float>::precedes(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );

    BOOST_CHECK( !F<float>::precedes(REP_DEC<float>(REP<float>(1.0f,2.0f), DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );
    BOOST_CHECK( !F<float>::precedes(REP_DEC<float>(REP<float>(0.0f,2.0f), DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );
    BOOST_CHECK( !F<float>::precedes(REP_DEC<float>(REP<float>(-0.0f,2.0f), DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );
    BOOST_CHECK( !F<float>::precedes(REP_DEC<float>(REP<float>(-INF_F,+INF_F), DEC::trv), REP_DEC<double>(REP<double>(1.0,2.0),DEC::trv)) );
    BOOST_CHECK( !F<float>::precedes(REP_DEC<float>(REP<float>(-INF_F,+INF_F), DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );

    BOOST_CHECK( F<float>::precedes(REP_DEC<float>(REP<float>(1.0f,2.0f), DEC::trv), REP_DEC<double>(REP<double>(3.0,4.0),DEC::trv)) );
    BOOST_CHECK( F<float>::precedes(REP_DEC<float>(REP<float>(1.0f,3.0f), DEC::trv), REP_DEC<double>(REP<double>(3.0,4.0),DEC::def)) );
    BOOST_CHECK( F<float>::precedes(REP_DEC<float>(REP<float>(-3.0f, -1.0f), DEC::def), REP_DEC<double>(REP<double>(-1.0,0.0),DEC::trv)) );
    BOOST_CHECK( F<float>::precedes(REP_DEC<float>(REP<float>(-3.0f, -1.0f), DEC::def), REP_DEC<double>(REP<double>(-1.0,-0.0),DEC::def)) );

    BOOST_CHECK( !F<float>::precedes(REP_DEC<float>(REP<float>(1.0f,3.5f), DEC::trv), REP_DEC<double>(REP<double>(3.0,4.0),DEC::trv)) );
    BOOST_CHECK( !F<float>::precedes(REP_DEC<float>(REP<float>(1.0f,4.0f), DEC::trv), REP_DEC<double>(REP<double>(3.0,4.0),DEC::trv)) );
    BOOST_CHECK( !F<float>::precedes(REP_DEC<float>(REP<float>(-3.0f, -0.1f), DEC::trv), REP_DEC<double>(REP<double>(-1.0,0.0),DEC::trv)) );

    BOOST_CHECK( F<float>::precedes(REP_DEC<float>(REP<float>(0.0f,0.0f), DEC::trv), REP_DEC<double>(REP<double>(-0.0,-0.0),DEC::trv)) );
    BOOST_CHECK( F<float>::precedes(REP_DEC<float>(REP<float>(-0.0f,-0.0f), DEC::def), REP_DEC<double>(REP<double>(0.0,0.0),DEC::def)) );
    BOOST_CHECK( F<float>::precedes(REP_DEC<float>(REP<float>(-0.0f,0.0f), DEC::trv), REP_DEC<double>(REP<double>(0.0,0.0),DEC::def)) );
    BOOST_CHECK( F<float>::precedes(REP_DEC<float>(REP<float>(-0.0f,0.0f), DEC::trv), REP_DEC<double>(REP<double>(0.0,-0.0),DEC::trv)) );
    BOOST_CHECK( F<float>::precedes(REP_DEC<float>(REP<float>(0.0f,-0.0f), DEC::trv), REP_DEC<double>(REP<double>(0.0,0.0),DEC::trv)) );
    BOOST_CHECK( F<float>::precedes(REP_DEC<float>(REP<float>(0.0f,-0.0f), DEC::trv), REP_DEC<double>(REP<double>(-0.0,0.0),DEC::trv)) );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK( !F<double>::precedes(REP_DEC<double>(REP<double>(1.0,-4.0), DEC::def), REP_DEC<float>(REP<float>(3.0f,4.0f),DEC::trv)) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::precedes(REP_DEC<double>(REP<double>(1.0,4.0), DEC::def), REP_DEC<float>(REP<float>(3.0f,-4.0f),DEC::trv)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}


BOOST_AUTO_TEST_CASE(minimal_interior_test)
{
    p1788::exception::clear();

    BOOST_CHECK( F<double>::interior(REP<double>(NaN_D,NaN_D), REP<double>(NaN_D,NaN_D)) );
    BOOST_CHECK( F<double>::interior(REP<double>(NaN_D,NaN_D), REP<double>(0.0,4.0)) );
    BOOST_CHECK( !F<double>::interior(REP<double>(0.0,4.0), REP<double>(NaN_D,NaN_D)) );

    BOOST_CHECK( F<double>::interior(REP<double>(-INF_D,+INF_D), REP<double>(-INF_D,+INF_D)) );
    BOOST_CHECK( F<double>::interior(REP<double>(0.0,4.0), REP<double>(-INF_D,+INF_D)) );
    BOOST_CHECK( F<double>::interior(REP<double>(NaN_D,NaN_D), REP<double>(-INF_D,+INF_D)) );
    BOOST_CHECK( !F<double>::interior(REP<double>(-INF_D,+INF_D), REP<double>(0.0,4.0)) );

    BOOST_CHECK( !F<double>::interior(REP<double>(0.0,4.0), REP<double>(0.0,4.0)) );
    BOOST_CHECK( F<double>::interior(REP<double>(1.0,2.0), REP<double>(0.0,4.0)) );
    BOOST_CHECK( !F<double>::interior(REP<double>(-2.0,2.0), REP<double>(-2.0,4.0)) );
    BOOST_CHECK( F<double>::interior(REP<double>(-0.0,-0.0), REP<double>(-2.0,4.0)) );
    BOOST_CHECK( F<double>::interior(REP<double>(0.0,0.0), REP<double>(-2.0,4.0)) );
    BOOST_CHECK( !F<double>::interior(REP<double>(0.0,0.0), REP<double>(-0.0,-0.0)) );

    BOOST_CHECK( !F<double>::interior(REP<double>(0.0,4.4), REP<double>(0.0,4.0)) );
    BOOST_CHECK( !F<double>::interior(REP<double>(-1.0,-1.0), REP<double>(0.0,4.0)) );
    BOOST_CHECK( !F<double>::interior(REP<double>(2.0,2.0), REP<double>(-2.0,-1.0)) );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK( !F<double>::interior(REP<double>(-0.0,-1.0), REP<double>(-2.0,4.0)) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::interior(REP<double>(-0.0,-0.0), REP<double>(-2.0,-4.0)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}

BOOST_AUTO_TEST_CASE(minimal_interior_mixedtype_test)
{
    p1788::exception::clear();

    BOOST_CHECK( F<double>::interior(REP<double>(NaN_D,NaN_D), REP<float>(NaN_F,NaN_F)) );
    BOOST_CHECK( F<double>::interior(REP<double>(NaN_D,NaN_D), REP<float>(0.0f,4.0f)) );
    BOOST_CHECK( !F<double>::interior(REP<double>(0.0,4.0), REP<float>(NaN_F,NaN_F)) );

    BOOST_CHECK( F<double>::interior(REP<double>(-INF_D,+INF_D), REP<float>(-INF_F,+INF_F)) );
    BOOST_CHECK( F<double>::interior(REP<double>(0.0,4.0), REP<float>(-INF_F,+INF_F)) );
    BOOST_CHECK( F<double>::interior(REP<double>(NaN_D,NaN_D), REP<float>(-INF_F,+INF_F)) );
    BOOST_CHECK( !F<double>::interior(REP<double>(-INF_D,+INF_D), REP<float>(0.0f,4.0f)) );

    BOOST_CHECK( !F<double>::interior(REP<double>(0.0,4.0), REP<float>(0.0f,4.0f)) );
    BOOST_CHECK( F<double>::interior(REP<double>(1.0,2.0), REP<float>(0.0f,4.0f)) );
    BOOST_CHECK( !F<double>::interior(REP<double>(-2.0,2.0), REP<float>(-2.0f,4.0f)) );
    BOOST_CHECK( F<double>::interior(REP<double>(-0.0,-0.0), REP<float>(-2.0f,4.0f)) );
    BOOST_CHECK( F<double>::interior(REP<double>(0.0,0.0), REP<float>(-2.0f,4.0f)) );
    BOOST_CHECK( !F<double>::interior(REP<double>(0.0,0.0), REP<float>(-0.0f,-0.0f)) );

    BOOST_CHECK( !F<double>::interior(REP<double>(0.0,4.4), REP<float>(0.0f,4.0f)) );
    BOOST_CHECK( !F<double>::interior(REP<double>(-1.0,-1.0), REP<float>(0.0f,4.0f)) );
    BOOST_CHECK( !F<double>::interior(REP<double>(2.0,2.0), REP<float>(-2.0f,-1.0f)) );

    BOOST_CHECK( F<float>::interior(REP<float>(NaN_F,NaN_F), REP<double>(NaN_D,NaN_D)) );
    BOOST_CHECK( F<float>::interior(REP<float>(NaN_F,NaN_F), REP<double>(0.0,4.0)) );
    BOOST_CHECK( !F<float>::interior(REP<float>(0.0f,4.0f), REP<double>(NaN_D,NaN_D)) );

    BOOST_CHECK( F<float>::interior(REP<float>(-INF_F,+INF_F), REP<double>(-INF_D,+INF_D)) );
    BOOST_CHECK( F<float>::interior(REP<float>(0.0f,4.0f), REP<double>(-INF_D,+INF_D)) );
    BOOST_CHECK( F<float>::interior(REP<float>(NaN_F,NaN_F), REP<double>(-INF_D,+INF_D)) );
    BOOST_CHECK( !F<float>::interior(REP<float>(-INF_F,+INF_F), REP<double>(0.0,4.0)) );

    BOOST_CHECK( !F<float>::interior(REP<float>(0.0f,4.0f), REP<double>(0.0,4.0)) );
    BOOST_CHECK( F<float>::interior(REP<float>(1.0f,2.0f), REP<double>(0.0,4.0)) );
    BOOST_CHECK( !F<float>::interior(REP<float>(-2.0f,2.0f), REP<double>(-2.0,4.0)) );
    BOOST_CHECK( F<float>::interior(REP<float>(-0.0f,-0.0f), REP<double>(-2.0,4.0)) );
    BOOST_CHECK( F<float>::interior(REP<float>(0.0f,0.0f), REP<double>(-2.0,4.0)) );
    BOOST_CHECK( !F<float>::interior(REP<float>(0.0f,0.0f), REP<double>(-0.0,-0.0)) );

    BOOST_CHECK( !F<float>::interior(REP<float>(0.0f,4.4f), REP<double>(0.0,4.0)) );
    BOOST_CHECK( !F<float>::interior(REP<float>(-1.0f,-1.0f), REP<double>(0.0,4.0)) );
    BOOST_CHECK( !F<float>::interior(REP<float>(2.0f,2.0f), REP<double>(-2.0,-1.0)) );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK( !F<double>::interior(REP<double>(1.0,-1.0), REP<float>(0.0f,4.0f)) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::interior(REP<double>(-1.0,-1.0), REP<float>(10.0f,4.0f)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}


BOOST_AUTO_TEST_CASE(minimal_interior_dec_test)
{
    p1788::exception::clear();

    BOOST_CHECK( !F<double>::interior(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );
    BOOST_CHECK( !F<double>::interior(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );
    BOOST_CHECK( !F<double>::interior(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill), REP_DEC<double>(REP<double>(0.0,4.0),DEC::trv)) );
    BOOST_CHECK( !F<double>::interior(REP_DEC<double>(REP<double>(0.0,4.0), DEC::def), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );

    BOOST_CHECK( F<double>::interior(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );
    BOOST_CHECK( F<double>::interior(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<double>(REP<double>(0.0,4.0),DEC::trv)) );
    BOOST_CHECK( !F<double>::interior(REP_DEC<double>(REP<double>(0.0,4.0), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );

    BOOST_CHECK( F<double>::interior(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );
    BOOST_CHECK( F<double>::interior(REP_DEC<double>(REP<double>(0.0,4.0), DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );
    BOOST_CHECK( F<double>::interior(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );
    BOOST_CHECK( !F<double>::interior(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::trv), REP_DEC<double>(REP<double>(0.0,4.0),DEC::trv)) );

    BOOST_CHECK( !F<double>::interior(REP_DEC<double>(REP<double>(0.0,4.0), DEC::trv), REP_DEC<double>(REP<double>(0.0,4.0),DEC::trv)) );
    BOOST_CHECK( F<double>::interior(REP_DEC<double>(REP<double>(1.0,2.0), DEC::def), REP_DEC<double>(REP<double>(0.0,4.0),DEC::trv)) );
    BOOST_CHECK( !F<double>::interior(REP_DEC<double>(REP<double>(-2.0,2.0), DEC::trv), REP_DEC<double>(REP<double>(-2.0,4.0),DEC::def)) );
    BOOST_CHECK( F<double>::interior(REP_DEC<double>(REP<double>(-0.0,-0.0), DEC::trv), REP_DEC<double>(REP<double>(-2.0,4.0),DEC::trv)) );
    BOOST_CHECK( F<double>::interior(REP_DEC<double>(REP<double>(0.0,0.0), DEC::def), REP_DEC<double>(REP<double>(-2.0,4.0),DEC::trv)) );
    BOOST_CHECK( !F<double>::interior(REP_DEC<double>(REP<double>(0.0,0.0), DEC::trv), REP_DEC<double>(REP<double>(-0.0,-0.0),DEC::trv)) );

    BOOST_CHECK( !F<double>::interior(REP_DEC<double>(REP<double>(0.0,4.4), DEC::trv), REP_DEC<double>(REP<double>(0.0,4.0),DEC::trv)) );
    BOOST_CHECK( !F<double>::interior(REP_DEC<double>(REP<double>(-1.0,-1.0), DEC::trv), REP_DEC<double>(REP<double>(0.0,4.0),DEC::def)) );
    BOOST_CHECK( !F<double>::interior(REP_DEC<double>(REP<double>(2.0,2.0), DEC::def), REP_DEC<double>(REP<double>(-2.0,-1.0),DEC::trv)) );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK( !F<double>::interior(REP_DEC<double>(REP<double>(-2.0,-14.0), DEC::trv), REP_DEC<double>(REP<double>(-2.0,4.0),DEC::def)) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::interior(REP_DEC<double>(REP<double>(-2.0,14.0), DEC::trv), REP_DEC<double>(REP<double>(-2.0,4.0),DEC::ill)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}

BOOST_AUTO_TEST_CASE(minimal_interior_dec_mixedtype_test)
{
    p1788::exception::clear();

    BOOST_CHECK( !F<double>::interior(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill), REP_DEC<float>(REP<float>(NaN_F,NaN_F),DEC::ill)) );
    BOOST_CHECK( !F<double>::interior(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<float>(REP<float>(NaN_F,NaN_F),DEC::ill)) );
    BOOST_CHECK( !F<double>::interior(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill), REP_DEC<float>(REP<float>(0.0f,4.0f),DEC::trv)) );
    BOOST_CHECK( !F<double>::interior(REP_DEC<double>(REP<double>(0.0,4.0), DEC::trv), REP_DEC<float>(REP<float>(NaN_F,NaN_F),DEC::ill)) );

    BOOST_CHECK( F<double>::interior(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<float>(REP<float>(NaN_F,NaN_F),DEC::trv)) );
    BOOST_CHECK( F<double>::interior(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<float>(REP<float>(0.0f,4.0f),DEC::trv)) );
    BOOST_CHECK( !F<double>::interior(REP_DEC<double>(REP<double>(0.0,4.0), DEC::trv), REP_DEC<float>(REP<float>(NaN_F,NaN_F),DEC::trv)) );

    BOOST_CHECK( F<double>::interior(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::trv), REP_DEC<float>(REP<float>(-INF_F,+INF_F),DEC::trv)) );
    BOOST_CHECK( F<double>::interior(REP_DEC<double>(REP<double>(0.0,4.0), DEC::trv), REP_DEC<float>(REP<float>(-INF_F,+INF_F),DEC::trv)) );
    BOOST_CHECK( F<double>::interior(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<float>(REP<float>(-INF_F,+INF_F),DEC::trv)) );
    BOOST_CHECK( !F<double>::interior(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::trv), REP_DEC<float>(REP<float>(0.0f,4.0f),DEC::trv)) );

    BOOST_CHECK( !F<double>::interior(REP_DEC<double>(REP<double>(0.0,4.0), DEC::trv), REP_DEC<float>(REP<float>(0.0f,4.0f),DEC::trv)) );
    BOOST_CHECK( F<double>::interior(REP_DEC<double>(REP<double>(1.0,2.0), DEC::def), REP_DEC<float>(REP<float>(0.0f,4.0f),DEC::trv)) );
    BOOST_CHECK( !F<double>::interior(REP_DEC<double>(REP<double>(-2.0,2.0), DEC::trv), REP_DEC<float>(REP<float>(-2.0f,4.0f),DEC::def)) );
    BOOST_CHECK( F<double>::interior(REP_DEC<double>(REP<double>(-0.0,-0.0), DEC::trv), REP_DEC<float>(REP<float>(-2.0f,4.0f),DEC::trv)) );
    BOOST_CHECK( F<double>::interior(REP_DEC<double>(REP<double>(0.0,0.0), DEC::def), REP_DEC<float>(REP<float>(-2.0f,4.0f),DEC::trv)) );
    BOOST_CHECK( !F<double>::interior(REP_DEC<double>(REP<double>(0.0,0.0), DEC::trv), REP_DEC<float>(REP<float>(-0.0f,-0.0f),DEC::trv)) );

    BOOST_CHECK( !F<double>::interior(REP_DEC<double>(REP<double>(0.0,4.4), DEC::trv), REP_DEC<float>(REP<float>(0.0f,4.0f),DEC::trv)) );
    BOOST_CHECK( !F<double>::interior(REP_DEC<double>(REP<double>(-1.0,-1.0), DEC::def), REP_DEC<float>(REP<float>(0.0f,4.0f),DEC::def)) );
    BOOST_CHECK( !F<double>::interior(REP_DEC<double>(REP<double>(2.0,2.0), DEC::trv), REP_DEC<float>(REP<float>(-2.0f,-1.0f),DEC::trv)) );

    BOOST_CHECK( !F<float>::interior(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::ill), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );
    BOOST_CHECK( !F<float>::interior(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::ill), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );
    BOOST_CHECK( !F<float>::interior(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::ill), REP_DEC<double>(REP<double>(0.0,4.0),DEC::trv)) );
    BOOST_CHECK( !F<float>::interior(REP_DEC<float>(REP<float>(0.0f,4.0f), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );

    BOOST_CHECK( F<float>::interior(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );
    BOOST_CHECK( F<float>::interior(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::trv), REP_DEC<double>(REP<double>(0.0,4.0),DEC::trv)) );
    BOOST_CHECK( !F<float>::interior(REP_DEC<float>(REP<float>(0.0f,4.0f), DEC::def), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );

    BOOST_CHECK( F<float>::interior(REP_DEC<float>(REP<float>(-INF_F,+INF_F), DEC::trv), REP_DEC<double>(REP<double>(-INF_F,+INF_F),DEC::trv)) );
    BOOST_CHECK( F<float>::interior(REP_DEC<float>(REP<float>(0.0f,4.0f), DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );
    BOOST_CHECK( F<float>::interior(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::trv), REP_DEC<double>(REP<double>(-INF_F,+INF_F),DEC::trv)) );
    BOOST_CHECK( !F<float>::interior(REP_DEC<float>(REP<float>(-INF_F,+INF_F), DEC::trv), REP_DEC<double>(REP<double>(0.0,4.0),DEC::trv)) );

    BOOST_CHECK( !F<float>::interior(REP_DEC<float>(REP<float>(0.0f,4.0f), DEC::trv), REP_DEC<double>(REP<double>(0.0,4.0),DEC::trv)) );
    BOOST_CHECK( F<float>::interior(REP_DEC<float>(REP<float>(1.0f,2.0f), DEC::def), REP_DEC<double>(REP<double>(0.0,4.0),DEC::def)) );
    BOOST_CHECK( !F<float>::interior(REP_DEC<float>(REP<float>(-2.0f,2.0f), DEC::trv), REP_DEC<double>(REP<double>(-2.0,4.0),DEC::def)) );
    BOOST_CHECK( F<float>::interior(REP_DEC<float>(REP<float>(-0.0f,-0.0f), DEC::trv), REP_DEC<double>(REP<double>(-2.0,4.0),DEC::trv)) );
    BOOST_CHECK( F<float>::interior(REP_DEC<float>(REP<float>(0.0f,0.0f), DEC::trv), REP_DEC<double>(REP<double>(-2.0,4.0),DEC::trv)) );
    BOOST_CHECK( !F<float>::interior(REP_DEC<float>(REP<float>(0.0f,0.0f), DEC::trv), REP_DEC<double>(REP<double>(-0.0,-0.0),DEC::trv)) );

    BOOST_CHECK( !F<float>::interior(REP_DEC<float>(REP<float>(0.0f,4.4f), DEC::trv), REP_DEC<double>(REP<double>(0.0,4.0),DEC::trv)) );
    BOOST_CHECK( !F<float>::interior(REP_DEC<float>(REP<float>(-1.0f,-1.0f), DEC::trv), REP_DEC<double>(REP<double>(0.0,4.0),DEC::trv)) );
    BOOST_CHECK( !F<float>::interior(REP_DEC<float>(REP<float>(2.0f,2.0f), DEC::trv), REP_DEC<double>(REP<double>(-2.0,-1.0),DEC::trv)) );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK( !F<float>::interior(REP_DEC<float>(REP<float>(0.0f,4.0f), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::com)) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<float>::interior(REP_DEC<float>(REP<float>(0.0f,-4.0f), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}


BOOST_AUTO_TEST_CASE(minimal_strict_less_test)
{
    p1788::exception::clear();

    BOOST_CHECK( F<double>::strict_less(REP<double>(NaN_D,NaN_D), REP<double>(NaN_D,NaN_D)) );
    BOOST_CHECK( !F<double>::strict_less(REP<double>(1.0,2.0), REP<double>(NaN_D,NaN_D)) );
    BOOST_CHECK( !F<double>::strict_less(REP<double>(NaN_D,NaN_D), REP<double>(1.0,2.0)) );

    BOOST_CHECK( F<double>::strict_less(REP<double>(-INF_D,+INF_D), REP<double>(-INF_D,+INF_D)) );
    BOOST_CHECK( !F<double>::strict_less(REP<double>(1.0,2.0), REP<double>(-INF_D,+INF_D)) );
    BOOST_CHECK( !F<double>::strict_less(REP<double>(-INF_D,+INF_D), REP<double>(1.0,2.0)) );

    BOOST_CHECK( !F<double>::strict_less(REP<double>(1.0,2.0), REP<double>(1.0,2.0)) );
    BOOST_CHECK( F<double>::strict_less(REP<double>(1.0,2.0), REP<double>(3.0,4.0)) );
    BOOST_CHECK( F<double>::strict_less(REP<double>(1.0,3.5), REP<double>(3.0,4.0)) );
    BOOST_CHECK( !F<double>::strict_less(REP<double>(1.0,4.0), REP<double>(3.0,4.0)) );
    BOOST_CHECK( !F<double>::strict_less(REP<double>(0.0,4.0), REP<double>(0.0,4.0)) );
    BOOST_CHECK( !F<double>::strict_less(REP<double>(-0.0,4.0), REP<double>(0.0,4.0)) );

    BOOST_CHECK( !F<double>::strict_less(REP<double>(-2.0,-1.0), REP<double>(-2.0,-1.0)) );
    BOOST_CHECK( F<double>::strict_less(REP<double>(-3.0,-1.5), REP<double>(-2.0,-1.0)) );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK( !F<double>::strict_less(REP<double>(1.0,4.0), REP<double>(3.0,-4.0)) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::strict_less(REP<double>(10.0,4.0), REP<double>(3.0,4.0)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}

BOOST_AUTO_TEST_CASE(minimal_strict_less_mixedtype_test)
{
    p1788::exception::clear();

    BOOST_CHECK( F<double>::strict_less(REP<double>(NaN_F,NaN_F), REP<float>(NaN_D,NaN_D)) );
    BOOST_CHECK( !F<double>::strict_less(REP<double>(1.0f,2.0f), REP<float>(NaN_D,NaN_D)) );
    BOOST_CHECK( !F<double>::strict_less(REP<double>(NaN_F,NaN_F), REP<float>(1.0,2.0)) );

    BOOST_CHECK( F<double>::strict_less(REP<double>(-INF_F,+INF_F), REP<float>(-INF_D,+INF_D)) );
    BOOST_CHECK( !F<double>::strict_less(REP<double>(1.0f,2.0f), REP<float>(-INF_D,+INF_D)) );
    BOOST_CHECK( !F<double>::strict_less(REP<double>(-INF_F,+INF_F), REP<float>(1.0,2.0)) );

    BOOST_CHECK( !F<double>::strict_less(REP<double>(1.0f,2.0f), REP<float>(1.0,2.0)) );
    BOOST_CHECK( F<double>::strict_less(REP<double>(1.0f,2.0f), REP<float>(3.0,4.0)) );
    BOOST_CHECK( F<double>::strict_less(REP<double>(1.0f,3.5f), REP<float>(3.0,4.0)) );
    BOOST_CHECK( !F<double>::strict_less(REP<double>(1.0f,4.0f), REP<float>(3.0,4.0)) );
    BOOST_CHECK( !F<double>::strict_less(REP<double>(0.0f,4.0f), REP<float>(0.0,4.0)) );
    BOOST_CHECK( !F<double>::strict_less(REP<double>(-0.0f,4.0f), REP<float>(0.0,4.0)) );

    BOOST_CHECK( !F<double>::strict_less(REP<double>(-2.0f,-1.0f), REP<float>(-2.0,-1.0)) );
    BOOST_CHECK( F<double>::strict_less(REP<double>(-3.0f,-1.5f), REP<float>(-2.0,-1.0)) );

    BOOST_CHECK( F<float>::strict_less(REP<float>(NaN_F,NaN_F), REP<double>(NaN_D,NaN_D)) );
    BOOST_CHECK( !F<float>::strict_less(REP<float>(1.0f,2.0f), REP<double>(NaN_D,NaN_D)) );
    BOOST_CHECK( !F<float>::strict_less(REP<float>(NaN_F,NaN_F), REP<double>(1.0,2.0)) );

    BOOST_CHECK( F<float>::strict_less(REP<float>(-INF_F,+INF_F), REP<double>(-INF_D,+INF_D)) );
    BOOST_CHECK( !F<float>::strict_less(REP<float>(1.0f,2.0f), REP<double>(-INF_D,+INF_D)) );
    BOOST_CHECK( !F<float>::strict_less(REP<float>(-INF_F,+INF_F), REP<double>(1.0,2.0)) );

    BOOST_CHECK( !F<float>::strict_less(REP<float>(1.0f,2.0f), REP<double>(1.0,2.0)) );
    BOOST_CHECK( F<float>::strict_less(REP<float>(1.0f,2.0f), REP<double>(3.0,4.0)) );
    BOOST_CHECK( F<float>::strict_less(REP<float>(1.0f,3.5f), REP<double>(3.0,4.0)) );
    BOOST_CHECK( !F<float>::strict_less(REP<float>(1.0f,4.0f), REP<double>(3.0,4.0)) );
    BOOST_CHECK( !F<float>::strict_less(REP<float>(0.0f,4.0f), REP<double>(0.0,4.0)) );
    BOOST_CHECK( !F<float>::strict_less(REP<float>(-0.0f,4.0f), REP<double>(0.0,4.0)) );

    BOOST_CHECK( !F<float>::strict_less(REP<float>(-2.0f,-1.0f), REP<double>(-2.0,-1.0)) );
    BOOST_CHECK( F<float>::strict_less(REP<float>(-3.0f,-1.5f), REP<double>(-2.0,-1.0)) );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK( !F<double>::strict_less(REP<double>(1.0,3.5), REP<float>(3.0f,-4.0f)) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::strict_less(REP<double>(1.0,-3.5), REP<float>(3.0f,4.0f)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}


BOOST_AUTO_TEST_CASE(minimal_strict_less_dec_test)
{
    p1788::exception::clear();

    BOOST_CHECK( !F<double>::strict_less(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );
    BOOST_CHECK( !F<double>::strict_less(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );
    BOOST_CHECK( !F<double>::strict_less(REP_DEC<double>(REP<double>(1.0,2.0), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );
    BOOST_CHECK( !F<double>::strict_less(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill), REP_DEC<double>(REP<double>(1.0,2.0),DEC::def)) );

    BOOST_CHECK( F<double>::strict_less(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );
    BOOST_CHECK( !F<double>::strict_less(REP_DEC<double>(REP<double>(1.0,2.0), DEC::def), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );
    BOOST_CHECK( !F<double>::strict_less(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<double>(REP<double>(1.0,2.0),DEC::def)) );

    BOOST_CHECK( F<double>::strict_less(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );
    BOOST_CHECK( !F<double>::strict_less(REP_DEC<double>(REP<double>(1.0,2.0), DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );
    BOOST_CHECK( !F<double>::strict_less(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::trv), REP_DEC<double>(REP<double>(1.0,2.0),DEC::trv)) );

    BOOST_CHECK( !F<double>::strict_less(REP_DEC<double>(REP<double>(1.0,2.0), DEC::trv), REP_DEC<double>(REP<double>(1.0,2.0),DEC::trv)) );
    BOOST_CHECK( F<double>::strict_less(REP_DEC<double>(REP<double>(1.0,2.0), DEC::trv), REP_DEC<double>(REP<double>(3.0,4.0),DEC::trv)) );
    BOOST_CHECK( F<double>::strict_less(REP_DEC<double>(REP<double>(1.0,3.5), DEC::def), REP_DEC<double>(REP<double>(3.0,4.0),DEC::trv)) );
    BOOST_CHECK( !F<double>::strict_less(REP_DEC<double>(REP<double>(1.0,4.0), DEC::trv), REP_DEC<double>(REP<double>(3.0,4.0),DEC::def)) );
    BOOST_CHECK( !F<double>::strict_less(REP_DEC<double>(REP<double>(0.0,4.0), DEC::trv), REP_DEC<double>(REP<double>(0.0,4.0),DEC::def)) );
    BOOST_CHECK( !F<double>::strict_less(REP_DEC<double>(REP<double>(-0.0,4.0), DEC::def), REP_DEC<double>(REP<double>(0.0,4.0),DEC::trv)) );

    BOOST_CHECK( !F<double>::strict_less(REP_DEC<double>(REP<double>(-2.0,-1.0), DEC::def), REP_DEC<double>(REP<double>(-2.0,-1.0),DEC::def)) );
    BOOST_CHECK( F<double>::strict_less(REP_DEC<double>(REP<double>(-3.0,-1.5), DEC::trv), REP_DEC<double>(REP<double>(-2.0,-1.0),DEC::trv)) );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK( !F<double>::strict_less(REP_DEC<double>(REP<double>(1.0,2.0), DEC::trv), REP_DEC<double>(REP<double>(3.0,-4.0),DEC::trv)) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::strict_less(REP_DEC<double>(REP<double>(1.0,-2.0), DEC::trv), REP_DEC<double>(REP<double>(3.0,4.0),DEC::trv)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}

BOOST_AUTO_TEST_CASE(minimal_strict_less_dec_mixedtype_test)
{
    p1788::exception::clear();

    BOOST_CHECK( !F<double>::strict_less(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill), REP_DEC<float>(REP<float>(NaN_F,NaN_F),DEC::ill)) );
    BOOST_CHECK( !F<double>::strict_less(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill), REP_DEC<float>(REP<float>(NaN_F,NaN_F),DEC::trv)) );
    BOOST_CHECK( !F<double>::strict_less(REP_DEC<double>(REP<double>(1.0,2.0), DEC::trv), REP_DEC<float>(REP<float>(NaN_F,NaN_F),DEC::ill)) );
    BOOST_CHECK( !F<double>::strict_less(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill), REP_DEC<float>(REP<float>(1.0f,2.0f),DEC::trv)) );

    BOOST_CHECK( F<double>::strict_less(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<float>(REP<float>(NaN_F,NaN_F),DEC::trv)) );
    BOOST_CHECK( !F<double>::strict_less(REP_DEC<double>(REP<double>(1.0,2.0), DEC::trv), REP_DEC<float>(REP<float>(NaN_F,NaN_F),DEC::trv)) );
    BOOST_CHECK( !F<double>::strict_less(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<float>(REP<float>(1.0f,2.0f),DEC::def)) );

    BOOST_CHECK( F<double>::strict_less(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::trv), REP_DEC<float>(REP<float>(-INF_F,+INF_F),DEC::trv)) );
    BOOST_CHECK( !F<double>::strict_less(REP_DEC<double>(REP<double>(1.0,2.0), DEC::trv), REP_DEC<float>(REP<float>(-INF_F,+INF_F),DEC::trv)) );
    BOOST_CHECK( !F<double>::strict_less(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::trv), REP_DEC<float>(REP<float>(1.0f,2.0f),DEC::trv)) );

    BOOST_CHECK( !F<double>::strict_less(REP_DEC<double>(REP<double>(1.0,2.0), DEC::def), REP_DEC<float>(REP<float>(1.0f,2.0f),DEC::def)) );
    BOOST_CHECK( F<double>::strict_less(REP_DEC<double>(REP<double>(1.0,2.0), DEC::trv), REP_DEC<float>(REP<float>(3.0f,4.0f),DEC::trv)) );
    BOOST_CHECK( F<double>::strict_less(REP_DEC<double>(REP<double>(1.0,3.5), DEC::def), REP_DEC<float>(REP<float>(3.0f,4.0f),DEC::trv)) );
    BOOST_CHECK( !F<double>::strict_less(REP_DEC<double>(REP<double>(1.0,4.0), DEC::trv), REP_DEC<float>(REP<float>(3.0f,4.0f),DEC::trv)) );
    BOOST_CHECK( !F<double>::strict_less(REP_DEC<double>(REP<double>(0.0,4.0), DEC::trv), REP_DEC<float>(REP<float>(0.0f,4.0f),DEC::trv)) );
    BOOST_CHECK( !F<double>::strict_less(REP_DEC<double>(REP<double>(-0.0,4.0), DEC::trv), REP_DEC<float>(REP<float>(0.0f,4.0f),DEC::trv)) );

    BOOST_CHECK( !F<double>::strict_less(REP_DEC<double>(REP<double>(-2.0,-1.0), DEC::trv), REP_DEC<float>(REP<float>(-2.0f,-1.0f),DEC::trv)) );
    BOOST_CHECK( F<double>::strict_less(REP_DEC<double>(REP<double>(-3.0,-1.5), DEC::trv), REP_DEC<float>(REP<float>(-2.0f,-1.0f),DEC::trv)) );

    BOOST_CHECK( !F<float>::strict_less(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::ill), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );
    BOOST_CHECK( !F<float>::strict_less(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::ill), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );
    BOOST_CHECK( !F<float>::strict_less(REP_DEC<float>(REP<float>(1.0f,2.0f), DEC::def), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );
    BOOST_CHECK( !F<float>::strict_less(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::ill), REP_DEC<double>(REP<double>(1.0,2.0),DEC::trv)) );

    BOOST_CHECK( F<float>::strict_less(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );
    BOOST_CHECK( !F<float>::strict_less(REP_DEC<float>(REP<float>(1.0f,2.0f), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );
    BOOST_CHECK( !F<float>::strict_less(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::trv), REP_DEC<double>(REP<double>(1.0,2.0),DEC::trv)) );

    BOOST_CHECK( F<float>::strict_less(REP_DEC<float>(REP<float>(-INF_F,+INF_F), DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );
    BOOST_CHECK( !F<float>::strict_less(REP_DEC<float>(REP<float>(1.0f,2.0f), DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );
    BOOST_CHECK( !F<float>::strict_less(REP_DEC<float>(REP<float>(-INF_F,+INF_F), DEC::trv), REP_DEC<double>(REP<double>(1.0,2.0),DEC::trv)) );

    BOOST_CHECK( !F<float>::strict_less(REP_DEC<float>(REP<float>(1.0f,2.0f), DEC::trv), REP_DEC<double>(REP<double>(1.0,2.0),DEC::trv)) );
    BOOST_CHECK( F<float>::strict_less(REP_DEC<float>(REP<float>(1.0f,2.0f), DEC::def), REP_DEC<double>(REP<double>(3.0,4.0),DEC::trv)) );
    BOOST_CHECK( F<float>::strict_less(REP_DEC<float>(REP<float>(1.0f,3.5f), DEC::trv), REP_DEC<double>(REP<double>(3.0,4.0),DEC::trv)) );
    BOOST_CHECK( !F<float>::strict_less(REP_DEC<float>(REP<float>(1.0f,4.0f), DEC::trv), REP_DEC<double>(REP<double>(3.0,4.0),DEC::def)) );
    BOOST_CHECK( !F<float>::strict_less(REP_DEC<float>(REP<float>(0.0f,4.0f), DEC::trv), REP_DEC<double>(REP<double>(0.0,4.0),DEC::trv)) );
    BOOST_CHECK( !F<float>::strict_less(REP_DEC<float>(REP<float>(-0.0f,4.0f), DEC::trv), REP_DEC<double>(REP<double>(0.0,4.0),DEC::trv)) );

    BOOST_CHECK( !F<float>::strict_less(REP_DEC<float>(REP<float>(-2.0f,-1.0f), DEC::trv), REP_DEC<double>(REP<double>(-2.0,-1.0),DEC::trv)) );
    BOOST_CHECK( F<float>::strict_less(REP_DEC<float>(REP<float>(-3.0f,-1.5f), DEC::trv), REP_DEC<double>(REP<double>(-2.0,-1.0),DEC::trv)) );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK( !F<float>::strict_less(REP_DEC<float>(REP<float>(-INF_F,+INF_F), DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::com)) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<float>::strict_less(REP_DEC<float>(REP<float>(-INF_F,+INF_F), DEC::com), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}



BOOST_AUTO_TEST_CASE(minimal_strict_precedes_test)
{
    p1788::exception::clear();

    BOOST_CHECK( F<double>::strict_precedes(REP<double>(NaN_D,NaN_D), REP<double>(3.0,4.0)) );
    BOOST_CHECK( F<double>::strict_precedes(REP<double>(3.0,4.0), REP<double>(NaN_D,NaN_D)) );
    BOOST_CHECK( F<double>::strict_precedes(REP<double>(NaN_D,NaN_D), REP<double>(NaN_D,NaN_D)) );


    BOOST_CHECK( !F<double>::strict_precedes(REP<double>(1.0,2.0), REP<double>(-INF_D,+INF_D)) );
    BOOST_CHECK( !F<double>::strict_precedes(REP<double>(-INF_D,+INF_D), REP<double>(1.0,2.0)) );
    BOOST_CHECK( !F<double>::strict_precedes(REP<double>(-INF_D,+INF_D), REP<double>(-INF_D,+INF_D)) );

    BOOST_CHECK( F<double>::strict_precedes(REP<double>(1.0,2.0), REP<double>(3.0,4.0)) );
    BOOST_CHECK( !F<double>::strict_precedes(REP<double>(1.0,3.0), REP<double>(3.0,4.0)) );
    BOOST_CHECK( !F<double>::strict_precedes(REP<double>(-3.0, -1.0), REP<double>(-1.0,0.0)) );
    BOOST_CHECK( !F<double>::strict_precedes(REP<double>(-3.0, -0.0), REP<double>(0.0,1.0)) );
    BOOST_CHECK( !F<double>::strict_precedes(REP<double>(-3.0, 0.0), REP<double>(-0.0,1.0)) );

    BOOST_CHECK( !F<double>::strict_precedes(REP<double>(1.0,3.5), REP<double>(3.0,4.0)) );
    BOOST_CHECK( !F<double>::strict_precedes(REP<double>(1.0,4.0), REP<double>(3.0,4.0)) );
    BOOST_CHECK( !F<double>::strict_precedes(REP<double>(-3.0, -0.1), REP<double>(-1.0,0.0)) );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK( !F<double>::strict_precedes(REP<double>(1.0,3.0), REP<double>(3.0,-4.0)) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::strict_precedes(REP<double>(16.0,3.0), REP<double>(3.0,4.0)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}


BOOST_AUTO_TEST_CASE(minimal_strict_precedes_mixedtype_test)
{
    p1788::exception::clear();

    BOOST_CHECK( F<double>::strict_precedes(REP<double>(NaN_D,NaN_D), REP<float>(3.0f,4.0f)) );
    BOOST_CHECK( F<double>::strict_precedes(REP<double>(3.0,4.0), REP<float>(NaN_F,NaN_F)) );
    BOOST_CHECK( F<double>::strict_precedes(REP<double>(NaN_D,NaN_D), REP<float>(NaN_F,NaN_F)) );


    BOOST_CHECK( !F<double>::strict_precedes(REP<double>(1.0,2.0), REP<float>(-INF_F,+INF_F)) );
    BOOST_CHECK( !F<double>::strict_precedes(REP<double>(-INF_D,+INF_D), REP<float>(1.0f,2.0f)) );
    BOOST_CHECK( !F<double>::strict_precedes(REP<double>(-INF_D,+INF_D), REP<float>(-INF_F,+INF_F)) );

    BOOST_CHECK( F<double>::strict_precedes(REP<double>(1.0,2.0), REP<float>(3.0f,4.0f)) );
    BOOST_CHECK( !F<double>::strict_precedes(REP<double>(1.0,3.0), REP<float>(3.0f,4.0f)) );
    BOOST_CHECK( !F<double>::strict_precedes(REP<double>(-3.0, -1.0), REP<float>(-1.0f,0.0f)) );
    BOOST_CHECK( !F<double>::strict_precedes(REP<double>(-3.0, -0.0), REP<float>(0.0f,1.0f)) );
    BOOST_CHECK( !F<double>::strict_precedes(REP<double>(-3.0, 0.0), REP<float>(-0.0f,1.0f)) );

    BOOST_CHECK( !F<double>::strict_precedes(REP<double>(1.0,3.5), REP<float>(3.0f,4.0f)) );
    BOOST_CHECK( !F<double>::strict_precedes(REP<double>(1.0,4.0), REP<float>(3.0f,4.0f)) );
    BOOST_CHECK( !F<double>::strict_precedes(REP<double>(-3.0, -0.1), REP<float>(-1.0f,0.0f)) );

    BOOST_CHECK( F<float>::strict_precedes(REP<float>(NaN_F,NaN_F), REP<double>(3.0,4.0)) );
    BOOST_CHECK( F<float>::strict_precedes(REP<float>(3.0f,4.0f), REP<double>(NaN_D,NaN_D)) );
    BOOST_CHECK( F<float>::strict_precedes(REP<float>(NaN_F,NaN_F), REP<double>(NaN_D,NaN_D)) );


    BOOST_CHECK( !F<float>::strict_precedes(REP<float>(1.0f,2.0f), REP<double>(-INF_D,+INF_D)) );
    BOOST_CHECK( !F<float>::strict_precedes(REP<float>(-INF_F,+INF_F), REP<double>(1.0,2.0)) );
    BOOST_CHECK( !F<float>::strict_precedes(REP<float>(-INF_F,+INF_F), REP<double>(-INF_D,+INF_D)) );

    BOOST_CHECK( F<float>::strict_precedes(REP<float>(1.0f,2.0f), REP<double>(3.0,4.0)) );
    BOOST_CHECK( !F<float>::strict_precedes(REP<float>(1.0f,3.0f), REP<double>(3.0,4.0)) );
    BOOST_CHECK( !F<float>::strict_precedes(REP<float>(-3.0f, -1.0f), REP<double>(-1.0,0.0)) );
    BOOST_CHECK( !F<float>::strict_precedes(REP<float>(-3.0f, -0.0f), REP<double>(0.0,1.0)) );
    BOOST_CHECK( !F<float>::strict_precedes(REP<float>(-3.0f, 0.0f), REP<double>(-0.0,1.0)) );

    BOOST_CHECK( !F<float>::strict_precedes(REP<float>(1.0f,3.5f), REP<double>(3.0,4.0)) );
    BOOST_CHECK( !F<float>::strict_precedes(REP<float>(1.0f,4.0f), REP<double>(3.0,4.0)) );
    BOOST_CHECK( !F<float>::strict_precedes(REP<float>(-3.0f, -0.1f), REP<double>(-1.0,0.0)) );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK( !F<float>::strict_precedes(REP<float>(1.0f,2.0f), REP<double>(-INF_D,-INF_D)) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<float>::strict_precedes(REP<float>(1.0f,-2.0f), REP<double>(-INF_D,+INF_D)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}


BOOST_AUTO_TEST_CASE(minimal_strict_precedes_dec_test)
{
    p1788::exception::clear();

    BOOST_CHECK( !F<double>::strict_precedes(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill), REP_DEC<double>(REP<double>(3.0,4.0),DEC::trv)) );
    BOOST_CHECK( !F<double>::strict_precedes(REP_DEC<double>(REP<double>(3.0,4.0), DEC::def), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );
    BOOST_CHECK( !F<double>::strict_precedes(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );
    BOOST_CHECK( !F<double>::strict_precedes(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );

    BOOST_CHECK( F<double>::strict_precedes(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<double>(REP<double>(3.0,4.0),DEC::trv)) );
    BOOST_CHECK( F<double>::strict_precedes(REP_DEC<double>(REP<double>(3.0,4.0), DEC::def), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );
    BOOST_CHECK( F<double>::strict_precedes(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );

    BOOST_CHECK( !F<double>::strict_precedes(REP_DEC<double>(REP<double>(1.0,2.0), DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );
    BOOST_CHECK( !F<double>::strict_precedes(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::trv), REP_DEC<double>(REP<double>(1.0,2.0),DEC::trv)) );
    BOOST_CHECK( !F<double>::strict_precedes(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );

    BOOST_CHECK( F<double>::strict_precedes(REP_DEC<double>(REP<double>(1.0,2.0), DEC::trv), REP_DEC<double>(REP<double>(3.0,4.0),DEC::trv)) );
    BOOST_CHECK( !F<double>::strict_precedes(REP_DEC<double>(REP<double>(1.0,3.0), DEC::def), REP_DEC<double>(REP<double>(3.0,4.0),DEC::trv)) );
    BOOST_CHECK( !F<double>::strict_precedes(REP_DEC<double>(REP<double>(-3.0, -1.0), DEC::trv), REP_DEC<double>(REP<double>(-1.0,0.0),DEC::def)) );
    BOOST_CHECK( !F<double>::strict_precedes(REP_DEC<double>(REP<double>(-3.0, -0.0), DEC::def), REP_DEC<double>(REP<double>(0.0,1.0),DEC::trv)) );
    BOOST_CHECK( !F<double>::strict_precedes(REP_DEC<double>(REP<double>(-3.0, 0.0), DEC::trv), REP_DEC<double>(REP<double>(-0.0,1.0),DEC::trv)) );

    BOOST_CHECK( !F<double>::strict_precedes(REP_DEC<double>(REP<double>(1.0,3.5), DEC::trv), REP_DEC<double>(REP<double>(3.0,4.0),DEC::trv)) );
    BOOST_CHECK( !F<double>::strict_precedes(REP_DEC<double>(REP<double>(1.0,4.0), DEC::trv), REP_DEC<double>(REP<double>(3.0,4.0),DEC::def)) );
    BOOST_CHECK( !F<double>::strict_precedes(REP_DEC<double>(REP<double>(-3.0, -0.1), DEC::trv), REP_DEC<double>(REP<double>(-1.0,0.0),DEC::trv)) );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK( !F<double>::strict_precedes(REP_DEC<double>(REP<double>(1.0,-2.0), DEC::trv), REP_DEC<double>(REP<double>(3.0,4.0),DEC::ill)) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::strict_precedes(REP_DEC<double>(REP<double>(1.0,2.0), DEC::trv), REP_DEC<double>(REP<double>(3.0,INF_D),DEC::com)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}


BOOST_AUTO_TEST_CASE(minimal_strict_precedes_dec_mixedtype_test)
{
    p1788::exception::clear();

    BOOST_CHECK( !F<double>::strict_precedes(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill), REP_DEC<float>(REP<float>(3.0f,4.0f),DEC::trv)) );
    BOOST_CHECK( !F<double>::strict_precedes(REP_DEC<double>(REP<double>(3.0,4.0), DEC::trv), REP_DEC<float>(REP<float>(NaN_F,NaN_F),DEC::ill)) );
    BOOST_CHECK( !F<double>::strict_precedes(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill), REP_DEC<float>(REP<float>(NaN_F,NaN_F),DEC::trv)) );
    BOOST_CHECK( !F<double>::strict_precedes(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill), REP_DEC<float>(REP<float>(NaN_F,NaN_F),DEC::ill)) );

    BOOST_CHECK( F<double>::strict_precedes(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<float>(REP<float>(3.0f,4.0f),DEC::trv)) );
    BOOST_CHECK( F<double>::strict_precedes(REP_DEC<double>(REP<double>(3.0,4.0), DEC::trv), REP_DEC<float>(REP<float>(NaN_F,NaN_F),DEC::trv)) );
    BOOST_CHECK( F<double>::strict_precedes(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<float>(REP<float>(NaN_F,NaN_F),DEC::trv)) );

    BOOST_CHECK( !F<double>::strict_precedes(REP_DEC<double>(REP<double>(1.0,2.0), DEC::trv), REP_DEC<float>(REP<float>(-INF_F,+INF_F),DEC::def)) );
    BOOST_CHECK( !F<double>::strict_precedes(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::trv), REP_DEC<float>(REP<float>(1.0f,2.0f),DEC::def)) );
    BOOST_CHECK( !F<double>::strict_precedes(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::trv), REP_DEC<float>(REP<float>(-INF_F,+INF_F),DEC::trv)) );

    BOOST_CHECK( F<double>::strict_precedes(REP_DEC<double>(REP<double>(1.0,2.0), DEC::trv), REP_DEC<float>(REP<float>(3.0f,4.0f),DEC::trv)) );
    BOOST_CHECK( !F<double>::strict_precedes(REP_DEC<double>(REP<double>(1.0,3.0), DEC::trv), REP_DEC<float>(REP<float>(3.0f,4.0f),DEC::trv)) );
    BOOST_CHECK( !F<double>::strict_precedes(REP_DEC<double>(REP<double>(-3.0, -1.0), DEC::def), REP_DEC<float>(REP<float>(-1.0f,0.0f),DEC::trv)) );
    BOOST_CHECK( !F<double>::strict_precedes(REP_DEC<double>(REP<double>(-3.0, -0.0), DEC::trv), REP_DEC<float>(REP<float>(0.0f,1.0f),DEC::def)) );
    BOOST_CHECK( !F<double>::strict_precedes(REP_DEC<double>(REP<double>(-3.0, 0.0), DEC::trv), REP_DEC<float>(REP<float>(-0.0f,1.0f),DEC::trv)) );

    BOOST_CHECK( !F<double>::strict_precedes(REP_DEC<double>(REP<double>(1.0,3.5), DEC::trv), REP_DEC<float>(REP<float>(3.0f,4.0f),DEC::trv)) );
    BOOST_CHECK( !F<double>::strict_precedes(REP_DEC<double>(REP<double>(1.0,4.0), DEC::def), REP_DEC<float>(REP<float>(3.0f,4.0f),DEC::def)) );
    BOOST_CHECK( !F<double>::strict_precedes(REP_DEC<double>(REP<double>(-3.0, -0.1), DEC::trv), REP_DEC<float>(REP<float>(-1.0f,0.0f),DEC::trv)) );

    BOOST_CHECK( !F<float>::strict_precedes(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::ill), REP_DEC<double>(REP<double>(3.0,4.0),DEC::trv)) );
    BOOST_CHECK( !F<float>::strict_precedes(REP_DEC<float>(REP<float>(3.0f,4.0f), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );
    BOOST_CHECK( !F<float>::strict_precedes(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::ill), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );
    BOOST_CHECK( !F<float>::strict_precedes(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::ill), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );

    BOOST_CHECK( F<float>::strict_precedes(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::trv), REP_DEC<double>(REP<double>(3.0,4.0),DEC::trv)) );
    BOOST_CHECK( F<float>::strict_precedes(REP_DEC<float>(REP<float>(3.0f,4.0f), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );
    BOOST_CHECK( F<float>::strict_precedes(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );

    BOOST_CHECK( !F<float>::strict_precedes(REP_DEC<float>(REP<float>(1.0f,2.0f), DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );
    BOOST_CHECK( !F<float>::strict_precedes(REP_DEC<float>(REP<float>(-INF_F,+INF_F), DEC::trv), REP_DEC<double>(REP<double>(1.0,2.0),DEC::trv)) );
    BOOST_CHECK( !F<float>::strict_precedes(REP_DEC<float>(REP<float>(-INF_F,+INF_F), DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );

    BOOST_CHECK( F<float>::strict_precedes(REP_DEC<float>(REP<float>(1.0f,2.0f), DEC::trv), REP_DEC<double>(REP<double>(3.0,4.0),DEC::trv)) );
    BOOST_CHECK( !F<float>::strict_precedes(REP_DEC<float>(REP<float>(1.0f,3.0f), DEC::trv), REP_DEC<double>(REP<double>(3.0,4.0),DEC::trv)) );
    BOOST_CHECK( !F<float>::strict_precedes(REP_DEC<float>(REP<float>(-3.0f, -1.0f), DEC::def), REP_DEC<double>(REP<double>(-1.0,0.0),DEC::trv)) );
    BOOST_CHECK( !F<float>::strict_precedes(REP_DEC<float>(REP<float>(-3.0f, -0.0f), DEC::trv), REP_DEC<double>(REP<double>(0.0,1.0),DEC::def)) );
    BOOST_CHECK( !F<float>::strict_precedes(REP_DEC<float>(REP<float>(-3.0f, 0.0f), DEC::trv), REP_DEC<double>(REP<double>(-0.0,1.0),DEC::trv)) );

    BOOST_CHECK( !F<float>::strict_precedes(REP_DEC<float>(REP<float>(1.0f,3.5f), DEC::trv), REP_DEC<double>(REP<double>(3.0,4.0),DEC::trv)) );
    BOOST_CHECK( !F<float>::strict_precedes(REP_DEC<float>(REP<float>(1.0f,4.0f), DEC::trv), REP_DEC<double>(REP<double>(3.0,4.0),DEC::trv)) );
    BOOST_CHECK( !F<float>::strict_precedes(REP_DEC<float>(REP<float>(-3.0f, -0.1f), DEC::trv), REP_DEC<double>(REP<double>(-1.0,0.0),DEC::trv)) );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK( !F<double>::strict_precedes(REP_DEC<double>(REP<double>(1.0,3.5), DEC::trv), REP_DEC<float>(REP<float>(3.0f,-4.0f),DEC::trv)) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::strict_precedes(REP_DEC<double>(REP<double>(1.0,-3.5), DEC::trv), REP_DEC<float>(REP<float>(3.0f,4.0f),DEC::trv)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}


BOOST_AUTO_TEST_CASE(minimal_disjoint_test)
{
    p1788::exception::clear();

    BOOST_CHECK( F<double>::disjoint(REP<double>(NaN_D,NaN_D), REP<double>(3.0,4.0)) );
    BOOST_CHECK( F<double>::disjoint(REP<double>(3.0,4.0), REP<double>(NaN_D,NaN_D)) );
    BOOST_CHECK( F<double>::disjoint(REP<double>(NaN_D,NaN_D), REP<double>(NaN_D,NaN_D)) );

    BOOST_CHECK( F<double>::disjoint(REP<double>(3.0,4.0), REP<double>(1.0,2.0)) );

    BOOST_CHECK( !F<double>::disjoint(REP<double>(0.0,0.0), REP<double>(-0.0,-0.0)) );
    BOOST_CHECK( !F<double>::disjoint(REP<double>(0.0,-0.0), REP<double>(-0.0,0.0)) );
    BOOST_CHECK( !F<double>::disjoint(REP<double>(3.0,4.0), REP<double>(1.0,7.0)) );
    BOOST_CHECK( !F<double>::disjoint(REP<double>(3.0,4.0), REP<double>(-INF_D,+INF_D)) );
    BOOST_CHECK( !F<double>::disjoint(REP<double>(-INF_D,+INF_D), REP<double>(1.0,7.0)) );
    BOOST_CHECK( !F<double>::disjoint(REP<double>(-INF_D,+INF_D), REP<double>(-INF_D,+INF_D)) );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK( !F<double>::disjoint(REP<double>(3.0,-4.0), REP<double>(-INF_D,+INF_D)) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::disjoint(REP<double>(3.0,4.0), REP<double>(+INF_D,+INF_D)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}

BOOST_AUTO_TEST_CASE(minimal_disjoint_mixedtype_test)
{
    p1788::exception::clear();

    BOOST_CHECK( F<double>::disjoint(REP<double>(NaN_D,NaN_D), REP<float>(3.0f,4.0f)) );
    BOOST_CHECK( F<double>::disjoint(REP<double>(3.0,4.0), REP<float>(NaN_F,NaN_F)) );
    BOOST_CHECK( F<double>::disjoint(REP<double>(NaN_D,NaN_D), REP<float>(NaN_F,NaN_F)) );

    BOOST_CHECK( F<double>::disjoint(REP<double>(3.0,4.0), REP<float>(1.0f,2.0f)) );

    BOOST_CHECK( !F<double>::disjoint(REP<double>(0.0,0.0), REP<float>(-0.0f,-0.0f)) );
    BOOST_CHECK( !F<double>::disjoint(REP<double>(0.0,-0.0), REP<float>(-0.0f,0.0f)) );
    BOOST_CHECK( !F<double>::disjoint(REP<double>(3.0,4.0), REP<float>(1.0f,7.0f)) );
    BOOST_CHECK( !F<double>::disjoint(REP<double>(3.0,4.0), REP<float>(-INF_F,+INF_F)) );
    BOOST_CHECK( !F<double>::disjoint(REP<double>(-INF_D,+INF_D), REP<float>(1.0f,7.0f)) );
    BOOST_CHECK( !F<double>::disjoint(REP<double>(-INF_D,+INF_D), REP<float>(-INF_F,+INF_F)) );

    BOOST_CHECK( F<float>::disjoint(REP<float>(NaN_D,NaN_D), REP<double>(3.0,4.0)) );
    BOOST_CHECK( F<float>::disjoint(REP<float>(3.0,4.0), REP<double>(NaN_D,NaN_D)) );
    BOOST_CHECK( F<float>::disjoint(REP<float>(NaN_F,NaN_F), REP<double>(NaN_D,NaN_D)) );

    BOOST_CHECK( F<float>::disjoint(REP<float>(3.0,4.0), REP<double>(1.0,2.0)) );

    BOOST_CHECK( !F<float>::disjoint(REP<float>(0.0f,0.0f), REP<double>(-0.0,-0.0)) );
    BOOST_CHECK( !F<float>::disjoint(REP<float>(0.0,-0.0), REP<double>(-0.0,0.0)) );
    BOOST_CHECK( !F<float>::disjoint(REP<float>(3.0f,4.0f), REP<double>(1.0,7.0)) );
    BOOST_CHECK( !F<float>::disjoint(REP<float>(3.0,4.0), REP<double>(-INF_D,+INF_D)) );
    BOOST_CHECK( !F<float>::disjoint(REP<float>(-INF_F,+INF_F), REP<double>(1.0,7.0)) );
    BOOST_CHECK( !F<float>::disjoint(REP<float>(-INF_D,+INF_D), REP<double>(-INF_D,+INF_D)) );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK( !F<float>::disjoint(REP<float>(3.0f,4.0f), REP<double>(-INF_D,-INF_D)) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<float>::disjoint(REP<float>(30.0f,4.0f), REP<double>(-INF_D,+INF_D)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}


BOOST_AUTO_TEST_CASE(minimal_disjoint_dec_test)
{
    p1788::exception::clear();

    BOOST_CHECK( !F<double>::disjoint(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill), REP_DEC<double>(REP<double>(3.0,4.0),DEC::def)) );
    BOOST_CHECK( !F<double>::disjoint(REP_DEC<double>(REP<double>(3.0,4.0), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );
    BOOST_CHECK( !F<double>::disjoint(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );
    BOOST_CHECK( !F<double>::disjoint(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );

    BOOST_CHECK( F<double>::disjoint(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<double>(REP<double>(3.0,4.0),DEC::trv)) );
    BOOST_CHECK( F<double>::disjoint(REP_DEC<double>(REP<double>(3.0,4.0), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );
    BOOST_CHECK( F<double>::disjoint(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );

    BOOST_CHECK( F<double>::disjoint(REP_DEC<double>(REP<double>(3.0,4.0), DEC::trv), REP_DEC<double>(REP<double>(1.0,2.0),DEC::def)) );

    BOOST_CHECK( !F<double>::disjoint(REP_DEC<double>(REP<double>(0.0,0.0), DEC::trv), REP_DEC<double>(REP<double>(-0.0,-0.0),DEC::trv)) );
    BOOST_CHECK( !F<double>::disjoint(REP_DEC<double>(REP<double>(0.0,-0.0), DEC::trv), REP_DEC<double>(REP<double>(-0.0,0.0),DEC::trv)) );
    BOOST_CHECK( !F<double>::disjoint(REP_DEC<double>(REP<double>(3.0,4.0), DEC::def), REP_DEC<double>(REP<double>(1.0,7.0),DEC::def)) );
    BOOST_CHECK( !F<double>::disjoint(REP_DEC<double>(REP<double>(3.0,4.0), DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );
    BOOST_CHECK( !F<double>::disjoint(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::trv), REP_DEC<double>(REP<double>(1.0,7.0),DEC::trv)) );
    BOOST_CHECK( !F<double>::disjoint(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK( !F<double>::disjoint(REP_DEC<double>(REP<double>(3.0,4.0), DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::com)) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::disjoint(REP_DEC<double>(REP<double>(3.0,4.0), DEC::ill), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}

BOOST_AUTO_TEST_CASE(minimal_disjoint_dec_mixedtype_test)
{
    p1788::exception::clear();

    BOOST_CHECK( !F<double>::disjoint(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill), REP_DEC<float>(REP<float>(3.0f,4.0f),DEC::trv)) );
    BOOST_CHECK( !F<double>::disjoint(REP_DEC<double>(REP<double>(3.0,4.0), DEC::trv), REP_DEC<float>(REP<float>(NaN_F,NaN_F),DEC::ill)) );
    BOOST_CHECK( !F<double>::disjoint(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<float>(REP<float>(NaN_F,NaN_F),DEC::ill)) );
    BOOST_CHECK( !F<double>::disjoint(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill), REP_DEC<float>(REP<float>(NaN_F,NaN_F),DEC::ill)) );

    BOOST_CHECK( F<double>::disjoint(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<float>(REP<float>(3.0f,4.0f),DEC::def)) );
    BOOST_CHECK( F<double>::disjoint(REP_DEC<double>(REP<double>(3.0,4.0), DEC::trv), REP_DEC<float>(REP<float>(NaN_F,NaN_F),DEC::trv)) );
    BOOST_CHECK( F<double>::disjoint(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<float>(REP<float>(NaN_F,NaN_F),DEC::trv)) );

    BOOST_CHECK( F<double>::disjoint(REP_DEC<double>(REP<double>(3.0,4.0), DEC::trv), REP_DEC<float>(REP<float>(1.0f,2.0f),DEC::trv)) );

    BOOST_CHECK( !F<double>::disjoint(REP_DEC<double>(REP<double>(0.0,0.0), DEC::trv), REP_DEC<float>(REP<float>(-0.0f,-0.0f),DEC::trv)) );
    BOOST_CHECK( !F<double>::disjoint(REP_DEC<double>(REP<double>(0.0,-0.0), DEC::def), REP_DEC<float>(REP<float>(-0.0f,0.0f),DEC::def)) );
    BOOST_CHECK( !F<double>::disjoint(REP_DEC<double>(REP<double>(3.0,4.0), DEC::trv), REP_DEC<float>(REP<float>(1.0f,7.0f),DEC::trv)) );
    BOOST_CHECK( !F<double>::disjoint(REP_DEC<double>(REP<double>(3.0,4.0), DEC::trv), REP_DEC<float>(REP<float>(-INF_F,+INF_F),DEC::def)) );
    BOOST_CHECK( !F<double>::disjoint(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::trv), REP_DEC<float>(REP<float>(1.0f,7.0f),DEC::trv)) );
    BOOST_CHECK( !F<double>::disjoint(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::trv), REP_DEC<float>(REP<float>(-INF_F,+INF_F),DEC::trv)) );

    BOOST_CHECK( !F<float>::disjoint(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::ill), REP_DEC<double>(REP<double>(3.0,4.0),DEC::trv)) );
    BOOST_CHECK( !F<float>::disjoint(REP_DEC<float>(REP<float>(3.0f,4.0f), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );
    BOOST_CHECK( !F<float>::disjoint(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );
    BOOST_CHECK( !F<float>::disjoint(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::ill), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );

    BOOST_CHECK( F<float>::disjoint(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::trv), REP_DEC<double>(REP<double>(3.0,4.0),DEC::trv)) );
    BOOST_CHECK( F<float>::disjoint(REP_DEC<float>(REP<float>(3.0f,4.0f), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );
    BOOST_CHECK( F<float>::disjoint(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );

    BOOST_CHECK( F<float>::disjoint(REP_DEC<float>(REP<float>(3.0f,4.0f), DEC::trv), REP_DEC<double>(REP<double>(1.0,2.0),DEC::trv)) );

    BOOST_CHECK( !F<float>::disjoint(REP_DEC<float>(REP<float>(0.0f,0.0f), DEC::def), REP_DEC<double>(REP<double>(-0.0,-0.0),DEC::trv)) );
    BOOST_CHECK( !F<float>::disjoint(REP_DEC<float>(REP<float>(0.0f,-0.0f), DEC::trv), REP_DEC<double>(REP<double>(-0.0,0.0),DEC::trv)) );
    BOOST_CHECK( !F<float>::disjoint(REP_DEC<float>(REP<float>(3.0f,4.0f), DEC::trv), REP_DEC<double>(REP<double>(1.0,7.0),DEC::def)) );
    BOOST_CHECK( !F<float>::disjoint(REP_DEC<float>(REP<float>(3.0f,4.0f), DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );
    BOOST_CHECK( !F<float>::disjoint(REP_DEC<float>(REP<float>(-INF_F,+INF_F), DEC::trv), REP_DEC<double>(REP<double>(1.0,7.0),DEC::trv)) );
    BOOST_CHECK( !F<float>::disjoint(REP_DEC<float>(REP<float>(-INF_F,+INF_F), DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK( !F<float>::disjoint(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::dac), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<float>::disjoint(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::def)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}
