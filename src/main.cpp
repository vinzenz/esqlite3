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
#include <iostream>
#include <esqlite3/database.hpp>

using namespace esqlite3;

void print_tuple(cursor & c)
{
    boost::tuple<std::string, std::string, std::string, std::string> values;
    values = c.row().as_tuple<std::string, std::string, std::string, std::string>();
    std::cout << "Print as_tuple:  \n"
              << "User:  " << boost::get<0>(values) << "\n"
              << "Name:  " << boost::get<1>(values) << "\n"
              << "Value: " << boost::get<2>(values) << "\n"
              << "ROWID: " << boost::get<3>(values) << "\n"
              << "--------------------------------------------\n";
}

void print_tied(cursor & c)
{
    std::string col1, col2, col3, col4;
    boost::tie(col1, col2, col3, col4) = c.row().as_tuple<std::string, std::string, std::string, std::string>();
    std::cout << "Print tied:  \n"
              << "User:  " << col1 << "\n"
              << "Name:  " << col2 << "\n"
              << "Value: " << col3 << "\n"
              << "ROWID: " << col4 << "\n"
              << "--------------------------------------------\n";
}

void print_tied_reverse(cursor & c)
{
    std::string col1, col2, col3, col4;
    boost::tie(col4, col3, col2, col1) = c.row().as_tuple<std::string, std::string, std::string, std::string>(3, 2, 1, 0);
    std::cout << "Print tied reverse:  \n"
              << "User:  " << col1 << "\n"
              << "Name:  " << col2 << "\n"
              << "Value: " << col3 << "\n"
              << "ROWID: " << col4 << "\n"
              << "--------------------------------------------\n";
}

void print(database::statement_ptr & stmt)
{
    cursor & c = stmt->cursor();
    while(c.fetch())
    {
        print_tuple(c);
        print_tied(c);
        print_tied_reverse(c);
    }
}

void select_test(database & db)
{
    database::statement_ptr stmt = db.statement("SELECT User,Name,Value,ROWID FROM settings WHERE ROWID = ?");
    for(int i = 0; i < 10; ++i)
    {
        stmt->bind(i+1);
        print(stmt);
        stmt->clear();
    }
}

void insert_test(database & db)
{
    database::statement_ptr stmt = db.statement("INSERT INTO settings VALUES(?,?,?)");
    for(int i = 0; i < 10; ++i)
    {
        stmt->bind(i+1)
             .bind("name")
             .bind("value");
        stmt->execute();
        stmt->clear();
    }
}
void insert_test_fail(database & db)
{
    try
    {
        insert_test(db);
        std::cout << "Insert failure test FAILED!" << std::endl;
    }
    catch(db_error const &)
    {
        std::cout << "Insert failure test successful!" << std::endl;
    }
}

int main()
{
    database db("test.db");    
    try{ db.statement("DROP TABLE settings")->execute(); }catch(...){}
    db.statement("CREATE TABLE IF NOT EXISTS settings(User, Name, Value, UNIQUE(User, Name))")->execute();    
    insert_test(db);
    select_test(db);
    insert_test_fail(db);
}
