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
#include <esqlite3/database.hpp>

namespace esqlite3
{
    database::database(char const * db_path)
    : db_(0)
    {
        open( db_path );
    }
    
    database::~database()
    {
        close();
    }

    void database::ensure( int res )
    {
        if(res != SQLITE_OK)
        {
            throw db_error( db() ); 
        }        
    }

    database::statement_ptr database::statement(char const * sql)
    {
        sqlite3_stmt * stmt = 0;
        ensure( sqlite3_prepare_v2( db(), sql, -1, &stmt, 0) );
        return statement_ptr( new esqlite3::statement( stmt ) );
    }

    sqlite3 * database::db()
    {
        return db_;
    }

    void database::open(char const * path)
    {
        ensure
        (
            sqlite3_open_v2
            (
                path, 
                &db_, 
                SQLITE_OPEN_FULLMUTEX | SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, 
                0
            )
        );
    }

    void database::close()
    {
        if(db_)
        {
            sqlite3_close(db_);
        }
    }
}

