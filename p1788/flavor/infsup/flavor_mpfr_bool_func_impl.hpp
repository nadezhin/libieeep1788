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

#ifndef LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_MPFR_BOOL_FUNC_IMPL_HPP
#define LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_MPFR_BOOL_FUNC_IMPL_HPP

#include <cmath>

namespace p1788
{

namespace flavor
{

namespace infsup
{

template<typename T>
bool
mpfr_flavor<T>::is_empty(mpfr_flavor<T>::representation const& x)
{
    return std::isnan(x.first) && std::isnan(x.second);
}

template<typename T>
bool
mpfr_flavor<T>::is_entire(mpfr_flavor<T>::representation const& x)
{
    return std::isinf(x.first) && std::isinf(x.second) && (x.first < x.second);
}

template<typename T>
bool
mpfr_flavor<T>::is_equal(mpfr_flavor<T>::representation const& x,
                         mpfr_flavor<T>::representation const& y)
{
    return (is_empty(x) && is_empty(y))
           || (x.first == y.first && x.second == y.second);
}

template<typename T>
bool
mpfr_flavor<T>::contained_in(mpfr_flavor<T>::representation const& x,
                             mpfr_flavor<T>::representation const& y)
{
    return is_empty(x) || (y.first <= x.first && x.second <= y.second);
}

template<typename T>
bool
mpfr_flavor<T>::precedes(mpfr_flavor<T>::representation const&,
                         mpfr_flavor<T>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return false;
}

template<typename T>
bool
mpfr_flavor<T>::is_enterior(mpfr_flavor<T>::representation const&,
                            mpfr_flavor<T>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return false;
}

template<typename T>
bool
mpfr_flavor<T>::strictly_less(mpfr_flavor<T>::representation const&,
                              mpfr_flavor<T>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return false;
}

template<typename T>
bool
mpfr_flavor<T>::strictly_precedes(mpfr_flavor<T>::representation const&,
                                  mpfr_flavor<T>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return false;
}

template<typename T>
bool
mpfr_flavor<T>::are_disjoint(mpfr_flavor<T>::representation const&,
                             mpfr_flavor<T>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return false;
}

} // namespace infsup

} // namespace flavor

} // namespace p1788


#endif // LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_MPFR_BOOL_FUNC_IMPL_HPP