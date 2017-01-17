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

#ifndef LIBIEEEP1788_P1788_FLAVOR_INFSUP_SETBASED_MPFR_BIN_IEEE754_FLAVOR_BOOL_FUNC_IMPL_HPP
#define LIBIEEEP1788_P1788_FLAVOR_INFSUP_SETBASED_MPFR_BIN_IEEE754_FLAVOR_BOOL_FUNC_IMPL_HPP


namespace p1788
{

namespace flavor
{

namespace infsup
{

namespace setbased
{

// is_empty ( bare interval )
template<typename T>
bool
mpfr_bin_ieee754_flavor<T>::is_empty(mpfr_bin_ieee754_flavor<T>::representation const& x)
{
    if (!is_valid(x))
        return false;

    return std::isnan(x.first) && std::isnan(x.second);
}

// is_empty ( decorated interval )
template<typename T>
bool
mpfr_bin_ieee754_flavor<T>::is_empty(mpfr_bin_ieee754_flavor<T>::representation_dec const& x)
{
    if (!is_valid(x) || is_nai(x))
        return false;

    // call bare version if not ill
    return is_empty(x.first);
}



// is_entire ( bare interval )
template<typename T>
bool
mpfr_bin_ieee754_flavor<T>::is_entire(mpfr_bin_ieee754_flavor<T>::representation const& x)
{
    if (!is_valid(x))
        return false;

    return x.first == -std::numeric_limits<T>::infinity()
           && x.second == std::numeric_limits<T>::infinity();
}

// is_entire ( decorated interval )
template<typename T>
bool
mpfr_bin_ieee754_flavor<T>::is_entire(mpfr_bin_ieee754_flavor<T>::representation_dec const& x)
{
    if (!is_valid(x) || is_nai(x))
        return false;

    // call bare version
    return is_entire(x.first);
}



// is_nai ( decorated interval )
template<typename T>
bool
mpfr_bin_ieee754_flavor<T>::is_nai(mpfr_bin_ieee754_flavor<T>::representation_dec const& x)
{
    if (!is_valid(x))
        return false;

    return std::isnan(x.first.first) && std::isnan(x.first.second) && x.second == p1788::decoration::decoration::ill;
}



// equal ( bare interval, bare interval )
template<typename T>
bool
mpfr_bin_ieee754_flavor<T>::equal(mpfr_bin_ieee754_flavor<T>::representation const& x,
                                     mpfr_bin_ieee754_flavor<T>::representation const& y)
{
    if (!is_valid(x) || !is_valid(y))
        return false;

    // call bare mixed type version
    return equal<T>(x,y);
}

// equal ( decorated interval, decorated interval )
template<typename T>
bool
mpfr_bin_ieee754_flavor<T>::equal(mpfr_bin_ieee754_flavor<T>::representation_dec const& x,
                                     mpfr_bin_ieee754_flavor<T>::representation_dec const& y)
{
    if (!is_valid(x) || !is_valid(y) || is_nai(x) || is_nai(y))
        return false;

    // call bare mixed type version if not NaI
    return equal<T>(x.first, y.first);
}

// equal ( bare interval, bare interval ) mixed type
template<typename T>
template<typename T_>
bool
mpfr_bin_ieee754_flavor<T>::equal(mpfr_bin_ieee754_flavor<T>::representation const& x,
                                     mpfr_bin_ieee754_flavor<T>::representation_type<T_> const& y)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!is_valid(x) || !mpfr_bin_ieee754_flavor<T_>::is_valid(y))
        return false;

    return (is_empty(x) && mpfr_bin_ieee754_flavor<T_>::is_empty(y))
           || (x.first == y.first && x.second == y.second);
}

// equal ( decorated interval, decorated interval ) mixed type
template<typename T>
template<typename T_>
bool
mpfr_bin_ieee754_flavor<T>::equal(mpfr_bin_ieee754_flavor<T>::representation_dec const& x,
                                     mpfr_bin_ieee754_flavor<T>::representation_dec_type<T_> const& y)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!is_valid(x) || !mpfr_bin_ieee754_flavor<T_>::is_valid(y) || is_nai(x) || mpfr_bin_ieee754_flavor<T_>::is_nai(y))
        return false;

    // call bare mixed type version if not NaI
    return equal(x.first, y.first);
}



// subset ( bare interval, bare interval )
template<typename T>
bool
mpfr_bin_ieee754_flavor<T>::subset(mpfr_bin_ieee754_flavor<T>::representation const& x,
                                   mpfr_bin_ieee754_flavor<T>::representation const& y)
{
    if (!is_valid(x) || !is_valid(y))
        return false;

    // call bare mixed type version
    return subset<T>(x,y);
}

// subset ( decorated interval, decorated interval )
template<typename T>
bool
mpfr_bin_ieee754_flavor<T>::subset(mpfr_bin_ieee754_flavor<T>::representation_dec const& x,
                                   mpfr_bin_ieee754_flavor<T>::representation_dec const& y)
{
    if (!is_valid(x) || !is_valid(y) || is_nai(x) || is_nai(y))
        return false;

    // call bare mixed type version if not NaI
    return subset<T>(x.first, y.first);
}

// subset ( bare interval, bare interval ) mixed type
template<typename T>
template<typename T_>
bool
mpfr_bin_ieee754_flavor<T>::subset(mpfr_bin_ieee754_flavor<T>::representation const& x,
                                   mpfr_bin_ieee754_flavor<T>::representation_type<T_> const& y)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!is_valid(x) || !mpfr_bin_ieee754_flavor<T_>::is_valid(y))
        return false;

    return is_empty(x) || (y.first <= x.first && x.second <= y.second);
}

// subset ( decorated interval, decorated interval ) mixed type
template<typename T>
template<typename T_>
bool
mpfr_bin_ieee754_flavor<T>::subset(mpfr_bin_ieee754_flavor<T>::representation_dec const& x,
                                   mpfr_bin_ieee754_flavor<T>::representation_dec_type<T_> const& y)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!is_valid(x) || !mpfr_bin_ieee754_flavor<T_>::is_valid(y)
            || is_nai(x) || mpfr_bin_ieee754_flavor<T_>::is_nai(y))
        return false;

    // call bare mixed type version if not NaI
    return subset(x.first, y.first);
}



// less ( bare interval, bare interval )
template<typename T>
bool
mpfr_bin_ieee754_flavor<T>::less(mpfr_bin_ieee754_flavor<T>::representation const& x,
                                 mpfr_bin_ieee754_flavor<T>::representation const& y)
{
    if (!is_valid(x) || !is_valid(y))
        return false;

    // call bare mixed type version
    return less<T>(x,y);
}

// less ( decorated interval, decorated interval )
template<typename T>
bool
mpfr_bin_ieee754_flavor<T>::less(mpfr_bin_ieee754_flavor<T>::representation_dec const& x,
                                 mpfr_bin_ieee754_flavor<T>::representation_dec const& y)
{
    if (!is_valid(x) || !is_valid(y) || is_nai(x) || is_nai(y))
        return false;

    // call bare mixed type version if not NaI
    return less<T>(x.first, y.first);
}

// less ( bare interval, bare interval ) mixed type
template<typename T>
template<typename T_>
bool
mpfr_bin_ieee754_flavor<T>::less(mpfr_bin_ieee754_flavor<T>::representation const& x,
                                 mpfr_bin_ieee754_flavor<T>::representation_type<T_> const& y)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!is_valid(x) || !mpfr_bin_ieee754_flavor<T_>::is_valid(y))
        return false;

    return (is_empty(x) && mpfr_bin_ieee754_flavor<T_>::is_empty(y))
           || (x.first <= y.first && x.second <= y.second);
}

// less ( decorated interval, decorated interval ) mixed type
template<typename T>
template<typename T_>
bool
mpfr_bin_ieee754_flavor<T>::less(mpfr_bin_ieee754_flavor<T>::representation_dec const& x,
                                 mpfr_bin_ieee754_flavor<T>::representation_dec_type<T_> const& y)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!is_valid(x) || !mpfr_bin_ieee754_flavor<T_>::is_valid(y)
            || is_nai(x) || mpfr_bin_ieee754_flavor<T_>::is_nai(y))
        return false;

    // call bare mixed type version if not NaI
    return less(x.first, y.first);
}



// precedes ( bare interval, bare interval )
template<typename T>
bool
mpfr_bin_ieee754_flavor<T>::precedes(mpfr_bin_ieee754_flavor<T>::representation const& x,
                                     mpfr_bin_ieee754_flavor<T>::representation const& y)
{
    if (!is_valid(x) || !is_valid(y))
        return false;

    // call bare mixed type version
    return precedes<T>(x,y);
}

// precedes ( decorated interval, decorated interval )
template<typename T>
bool
mpfr_bin_ieee754_flavor<T>::precedes(mpfr_bin_ieee754_flavor<T>::representation_dec const& x,
                                     mpfr_bin_ieee754_flavor<T>::representation_dec const& y)
{
    if (!is_valid(x) || !is_valid(y) || is_nai(x) || is_nai(y) )
        return false;

    // call bare mixed type version if not NaI
    return precedes<T>(x.first, y.first);
}

// precedes ( bare interval, bare interval ) mixed type
template<typename T>
template<typename T_>
bool
mpfr_bin_ieee754_flavor<T>::precedes(mpfr_bin_ieee754_flavor<T>::representation const& x,
                                     mpfr_bin_ieee754_flavor<T>::representation_type<T_> const& y)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!is_valid(x) || !mpfr_bin_ieee754_flavor<T_>::is_valid(y))
        return false;

    return is_empty(x) || mpfr_bin_ieee754_flavor<T_>::is_empty(y) || x.second <= y.first;
}

// precedes ( decorated interval, decorated interval ) mixed type
template<typename T>
template<typename T_>
bool
mpfr_bin_ieee754_flavor<T>::precedes(mpfr_bin_ieee754_flavor<T>::representation_dec const& x,
                                     mpfr_bin_ieee754_flavor<T>::representation_dec_type<T_> const& y)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!is_valid(x) || !mpfr_bin_ieee754_flavor<T_>::is_valid(y)
            || is_nai(x) || mpfr_bin_ieee754_flavor<T_>::is_nai(y))
        return false;

    // call bare mixed type version if not NaI
    return precedes(x.first, y.first);
}



// interior ( bare interval, bare interval )
template<typename T>
bool
mpfr_bin_ieee754_flavor<T>::interior(mpfr_bin_ieee754_flavor<T>::representation const& x,
                                        mpfr_bin_ieee754_flavor<T>::representation const& y)
{
    if (!is_valid(x) || !is_valid(y))
        return false;

    // call bare mixed type version
    return interior<T>(x,y);
}

// interior ( decorated interval, decorated interval )
template<typename T>
bool
mpfr_bin_ieee754_flavor<T>::interior(mpfr_bin_ieee754_flavor<T>::representation_dec const& x,
                                        mpfr_bin_ieee754_flavor<T>::representation_dec const& y)
{
    if (!is_valid(x) || !is_valid(y) || is_nai(x) || is_nai(y))
        return false;

    // call bare mixed type version if not NaI
    return interior<T>(x.first, y.first);
}

// interior ( bare interval, bare interval ) mixed type
template<typename T>
template<typename T_>
bool
mpfr_bin_ieee754_flavor<T>::interior(mpfr_bin_ieee754_flavor<T>::representation const& x,
                                        mpfr_bin_ieee754_flavor<T>::representation_type<T_>  const& y)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!is_valid(x) || !mpfr_bin_ieee754_flavor<T_>::is_valid(y))
        return false;

    return is_empty(x)
           || ((y.first < x.first
                || (y.first == -std::numeric_limits<T_>::infinity()
                    && x.first == -std::numeric_limits<T>::infinity()))
               && (x.second < y.second
                   || (x.second == std::numeric_limits<T>::infinity()
                       && y.second == std::numeric_limits<T_>::infinity())));
}

// interior ( decorated interval, decorated interval ) mixed type
template<typename T>
template<typename T_>
bool
mpfr_bin_ieee754_flavor<T>::interior(mpfr_bin_ieee754_flavor<T>::representation_dec const& x,
                                        mpfr_bin_ieee754_flavor<T>::representation_dec_type<T_>  const& y)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!is_valid(x) || !mpfr_bin_ieee754_flavor<T_>::is_valid(y)
            || is_nai(x) || mpfr_bin_ieee754_flavor<T_>::is_nai(y))
        return false;

    // call bare mixed type version if not NaI
    return interior(x.first, y.first);
}



// strict_less ( bare interval, bare interval )
template<typename T>
bool
mpfr_bin_ieee754_flavor<T>::strict_less(mpfr_bin_ieee754_flavor<T>::representation const& x,
        mpfr_bin_ieee754_flavor<T>::representation const& y)
{
    if (!is_valid(x) || !is_valid(y))
        return false;


    // call bare mixed type version
    return strict_less<T>(x,y);
}

// strict_less ( decorated interval, decorated interval )
template<typename T>
bool
mpfr_bin_ieee754_flavor<T>::strict_less(mpfr_bin_ieee754_flavor<T>::representation_dec const& x,
        mpfr_bin_ieee754_flavor<T>::representation_dec const& y)
{
    if (!is_valid(x) || !is_valid(y) || is_nai(x) || is_nai(y))
        return false;

    // call bare mixed type version if not NaI
    return strict_less<T>(x.first, y.first);
}

// strict_less ( bare interval, bare interval ) mixed type
template<typename T>
template<typename T_>
bool
mpfr_bin_ieee754_flavor<T>::strict_less(mpfr_bin_ieee754_flavor<T>::representation const& x,
        mpfr_bin_ieee754_flavor<T>::representation_type<T_> const& y)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!is_valid(x) || !mpfr_bin_ieee754_flavor<T_>::is_valid(y))
        return false;

    return (is_empty(x) && mpfr_bin_ieee754_flavor<T_>::is_empty(y))
           || ((x.first < y.first
                || (x.first == -std::numeric_limits<T>::infinity()
                    && y.first == -std::numeric_limits<T_>::infinity()))
               && (x.second < y.second
                   || (x.second == std::numeric_limits<T>::infinity()
                       && y.second == std::numeric_limits<T_>::infinity())));
}

// strict_less ( decorated interval, decorated interval ) mixed type
template<typename T>
template<typename T_>
bool
mpfr_bin_ieee754_flavor<T>::strict_less(mpfr_bin_ieee754_flavor<T>::representation_dec const& x,
        mpfr_bin_ieee754_flavor<T>::representation_dec_type<T_> const& y)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!is_valid(x) || !mpfr_bin_ieee754_flavor<T_>::is_valid(y)
            || is_nai(x) || mpfr_bin_ieee754_flavor<T_>::is_nai(y))
        return false;

    // call bare mixed type version if not NaI
    return strict_less(x.first, y.first);
}



// strict_precedes ( bare interval, bare interval )
template<typename T>
bool
mpfr_bin_ieee754_flavor<T>::strict_precedes(mpfr_bin_ieee754_flavor<T>::representation const& x,
        mpfr_bin_ieee754_flavor<T>::representation const& y)
{
    if (!is_valid(x) || !is_valid(y))
        return false;

    // call bare mixed type version
    return strict_precedes<T>(x,y);
}

// strict_precedes ( decorated interval, decorated interval )
template<typename T>
bool
mpfr_bin_ieee754_flavor<T>::strict_precedes(mpfr_bin_ieee754_flavor<T>::representation_dec const& x,
        mpfr_bin_ieee754_flavor<T>::representation_dec const& y)
{
    if (!is_valid(x) || !is_valid(y) || is_nai(x) || is_nai(y))
        return false;

    // call bare mixed type version if not NaI
    return strict_precedes<T>(x.first, y.first);
}

// strict_precedes ( bare interval, bare interval ) mixed type
template<typename T>
template<typename T_>
bool
mpfr_bin_ieee754_flavor<T>::strict_precedes(mpfr_bin_ieee754_flavor<T>::representation const& x,
        mpfr_bin_ieee754_flavor<T>::representation_type<T_> const& y)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!is_valid(x) || !mpfr_bin_ieee754_flavor<T_>::is_valid(y))
        return false;

    return is_empty(x) || mpfr_bin_ieee754_flavor<T_>::is_empty(y) || x.second < y.first;
}

// strict_precedes ( decorated interval, decorated interval ) mixed type
template<typename T>
template<typename T_>
bool
mpfr_bin_ieee754_flavor<T>::strict_precedes(mpfr_bin_ieee754_flavor<T>::representation_dec const& x,
        mpfr_bin_ieee754_flavor<T>::representation_dec_type<T_> const& y)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!is_valid(x) || !mpfr_bin_ieee754_flavor<T_>::is_valid(y)
            || is_nai(x) || mpfr_bin_ieee754_flavor<T_>::is_nai(y))
        return false;

    // call bare mixed type version if not NaI
    return strict_precedes(x.first, y.first);
}



// disjoint ( bare interval, bare interval )
template<typename T>
bool
mpfr_bin_ieee754_flavor<T>::disjoint(mpfr_bin_ieee754_flavor<T>::representation const& x,
        mpfr_bin_ieee754_flavor<T>::representation const& y)
{
    if (!is_valid(x) || !is_valid(y))
        return false;

    // call bare mixed type version
    return disjoint<T>(x,y);
}

// disjoint ( decorated interval, decorated interval )
template<typename T>
bool
mpfr_bin_ieee754_flavor<T>::disjoint(mpfr_bin_ieee754_flavor<T>::representation_dec const& x,
        mpfr_bin_ieee754_flavor<T>::representation_dec const& y)
{
    if (!is_valid(x) || !is_valid(y) || is_nai(x) || is_nai(y))
        return false;

    // call bare mixed type version if not NaI
    return disjoint<T>(x.first, y.first);
}

// disjoint ( bare interval, bare interval ) mixed type
template<typename T>
template<typename T_>
bool
mpfr_bin_ieee754_flavor<T>::disjoint(mpfr_bin_ieee754_flavor<T>::representation const& x,
        mpfr_bin_ieee754_flavor<T>::representation_type<T_> const& y)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!is_valid(x) || !mpfr_bin_ieee754_flavor<T_>::is_valid(y))
        return false;

    return is_empty(x) || mpfr_bin_ieee754_flavor<T_>::is_empty(y) || x.second < y.first || y.second < x.first;
}

// disjoint ( decorated interval, decorated interval ) mixed type
template<typename T>
template<typename T_>
bool
mpfr_bin_ieee754_flavor<T>::disjoint(mpfr_bin_ieee754_flavor<T>::representation_dec const& x,
        mpfr_bin_ieee754_flavor<T>::representation_dec_type<T_> const& y)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!is_valid(x) || !mpfr_bin_ieee754_flavor<T_>::is_valid(y)
            || is_nai(x) || mpfr_bin_ieee754_flavor<T_>::is_nai(y))
        return false;

    // call bare mixed type version if not NaI
    return disjoint(x.first, y.first);
}


} // namespace setbased

} // namespace infsup

} // namespace flavor

} // namespace p1788


#endif // LIBIEEEP1788_P1788_FLAVOR_INFSUP_SETBASED_MPFR_BIN_IEEE754_FLAVOR_BOOL_FUNC_IMPL_HPP
