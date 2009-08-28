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
#ifndef GUARD_ESQLITE3_STATEMENT_HPP_INCLUDED
#define GUARD_ESQLITE3_STATEMENT_HPP_INCLUDED

#include <sqlite3.h>
#include <esqlite3/cursor.hpp>
#include <boost/lexical_cast.hpp>
#include <string>

namespace esqlite3
{
    struct statement 
    {
        statement(sqlite3_stmt * stmt);
        ~statement();
        
        void throw_error();
        void ensure(int result);
        void execute();
        esqlite3::cursor & cursor();
        template<typename T>
        statement & bind( T const & t )
        {
            return bind
            (
                boost::lexical_cast<std::string>( t ) 
            );
        }

        statement & bind(std::string const & value);
        statement & bind(char const * value);

        void clear();

        sqlite3 * db();
        sqlite3_stmt * get();        

    protected:
        void finalize();

    protected:
        sqlite3_stmt * stmt_;
        char const * sql_;
        int bind_;
        esqlite3::cursor cursor_;
    };
}

#endif //GUARD_ESQLITE3_STATEMENT_HPP_INCLUDED

