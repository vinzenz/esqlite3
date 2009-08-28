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
#include <esqlite3/statement.hpp>
#include <esqlite3/database_error.hpp>

#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable:4355)// We know what we're doing 
#endif

namespace esqlite3
{
    statement::statement(sqlite3_stmt * stmt)
    : stmt_(stmt)
    , sql_(sqlite3_sql(stmt))
    , bind_(0)
    , cursor_(*this)
    {
        if(!stmt)
        {
            throw db_error("Invalid statement pointer");
        }
    }
   
    statement::~statement()
    {
        finalize();
    }
 
    void statement::throw_error()
    {
        throw db_error( sqlite3_db_handle( get() ) );
    }    

    void statement::ensure(int result)
    {
        if(result != SQLITE_OK)
        {
            throw_error();
        }
    }

    void statement::execute()
    {
        if(sqlite3_step( get() ) != SQLITE_DONE)
        {
            throw_error();
        }
    }

    esqlite3::cursor & statement::cursor()
    {
        return cursor_;
    }

    statement & statement::bind(std::string const & value)
    {
        return bind( value.c_str() );
    }

    statement & statement::bind(char const * value)
    { 
        ensure
        (
            sqlite3_bind_text
            (
                get(), 
                ++bind_, 
                value, 
                -1, 
                SQLITE_TRANSIENT
            ) 
        ); 
        return *this;
    }

    sqlite3 * statement::db()
    {
        return ::sqlite3_db_handle( get() );
    }

    sqlite3_stmt * statement::get()
    {
        return stmt_;
    }

    void statement::finalize()
    {
        ::sqlite3_finalize( get() );
        stmt_ = 0;
    }

    void statement::clear()
    {        
        ::sqlite3_reset( get() );
        ::sqlite3_clear_bindings( get() );
        cursor_.clear();
        bind_ = 0;
    }
}

#if defined(_MSC_VER)
#	pragma warning(pop)
#endif
