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
#include <esqlite3/row.hpp>
#include <esqlite3/statement.hpp>
#include <esqlite3/database_error.hpp>

namespace esqlite3
{
    row::row(statement & stmt)
    : stmt_(stmt)
    , columns_(0)
    {}

	char const * row::get(int idx)
    {        
        if(idx < 0 || idx >= columns())
        {
            throw std::out_of_range("Database column index out of range");
        }
        char const * result = reinterpret_cast<char const * >(sqlite3_column_text( stmt_.get(), idx ));
        return result ? result : "NULL";
    }
    
    int row::columns() const
    {
        return columns_;
    }

    void row::next(bool end)
    {
        columns_ = end ? 0 : sqlite3_column_count( stmt_.get() );
    }
}

