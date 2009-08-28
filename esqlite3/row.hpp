///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                                                           //
// Copyright (c) 2009, Vinzenz Feenstra  All rights reserved.                //
//                                                                           //
//                                                                           //
// Redistribution and use in source and binary forms, with or without        //
// modification, are permitted provided that the following conditions are    //
// met:                                                                      //
//                                                                           //
// * Redistributions of source code must retain the above copyright notice,  //
//   this list of conditions and the following disclaimer.                   //
//                                                                           //
// * Redistributions in binary form must reproduce the above copyright       //
//   notice, this list of conditions and the following disclaimer in the     //
//   documentation and/or other materials provided with the distribution.    //
//                                                                           //
// * Neither the name of the Vinzenz Feenstra nor the names of its           //
//   contributors may be used to endorse or promote products derived from    //
//   this software without specific prior written permission.                //
//                                                                           //
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS       //
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT         //
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR     //
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT      //
// HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,    //
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED  //
// TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR    //
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF    //
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING      //
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS        //
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.              //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
#ifndef GUARD_ESQLITE3_ROW_HPP_INCLUDED
#define GUARD_ESQLITE3_ROW_HPP_INCLUDED

#include <sqlite3.h>
#include <boost/lexical_cast.hpp>
#include <boost/tuple/tuple.hpp>

namespace esqlite3
{
    struct statement;
    struct row
    {
        row(statement & stmt);

        template<typename T>
        T get(int idx, T const t = T())
        {        
            return boost::lexical_cast<T>( get( idx ) );
        }

        char const * get(int idx);
        int columns() const;

        template<typename P0>
        boost::tuple<P0> as_tuple(int idx0)
        {
            return boost::make_tuple( get( idx0, P0() ) );
        }

        template<typename P0>
        boost::tuple<P0> as_tuple()
        {
            return as_tuple<P0>(0);
        }

        template<typename P0, typename P1>
        boost::tuple<P0, P1> as_tuple(int idx0, int idx1)
        {
            return boost::make_tuple( get( idx0, P0() ), get( idx1, P1() ) );
        }

        template<typename P0, typename P1>
        boost::tuple<P0, P1> as_tuple()
        {
            return as_tuple<P0, P1>(0, 1);
        }

        template<typename P0, typename P1, typename P2>
        boost::tuple<P0, P1, P2> as_tuple(int idx0, int idx1, int idx2)
        {
            return boost::make_tuple( get( idx0, P0() ), get( idx1, P1() ), get( idx2, P2() ));
        }

        template<typename P0, typename P1, typename P2>
        boost::tuple<P0, P1, P2> as_tuple()
        {
            return as_tuple<P0, P1, P2>(0, 1, 2);
        }

        template<typename P0, typename P1, typename P2, typename P3>
        boost::tuple<P0, P1, P2, P3> as_tuple(int idx0, int idx1, int idx2, int idx3)
        {
            return boost::make_tuple( get( idx0, P0() ), get( idx1, P1() ), get( idx2, P2() ), get( idx3, P3() ) );
        }

        template<typename P0, typename P1, typename P2, typename P3>
        boost::tuple<P0, P1, P2, P3> as_tuple()
        {
            return as_tuple<P0, P1, P2, P3>(0, 1, 2, 3);
        }

        template<typename P0, typename P1, typename P2, typename P3, typename P4>
        boost::tuple<P0, P1, P2, P3, P4> as_tuple(int idx0, int idx1, int idx2, int idx3, int idx4)
        {
            return boost::make_tuple( get( idx0, P0() ), get( idx1, P1() ), get( idx2, P2() ), get( idx3, P3() ), get( idx4, P4() ) );
        }

        template<typename P0, typename P1, typename P2, typename P3, typename P4>
        boost::tuple<P0, P1, P2, P3, P4> as_tuple()
        {
            return as_tuple<P0, P1, P2, P3, P4>(0, 1, 2, 3, 4);
        }

    protected:
        friend struct cursor;    
        void next(bool end = false);

    protected:
        statement & stmt_;
        int columns_;
    };
}

#endif //GUARD_ESQLITE3_ROW_HPP_INCLUDED

