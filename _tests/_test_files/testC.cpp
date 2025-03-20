

#include "gtest/gtest.h"
#include <cmath>
#include <iostream>
#include <iomanip>
#include <set>
#include <vector>

//------------------------------------------------------------------------------------------
//Files we are testing:
#include "../../includes/sql/sql.h"


//------------------------------------------------------------------------------------------

using namespace std;

const vector<string> command_list_1 = {
/*00*/     "make table employee fields  Name,  Age,  Gende,  City,       Country",
/*01*/     "insert into employee values Alice   25      Female   \"New York\"    USA",
/*02*/     "insert into employee values Bob     30    Male     London      UK",
/*03*/     "insert into employee values Charlie   35   Male     Paris         France",
/*04*/     "insert into employee values David   20    Male  Beijing     China",
/*05*/     "insert into employee values Eva     28    Female   Madrid        Spain",
/*06*/     "insert into employee values Frank    32    Male      Berlin      Germany",
/*07*/     "insert into employee values Grace   24    Female   Sydney   Australia",
/*08*/     "insert into employee values Henry   40    Male   Tokyo       Japan",
/*09*/     "insert into employee values Isabella   29   Female   Rome      Italy",
/*10*/     "insert into employee values Jack    27    Male    Toronto     Canada",
/*11*/     "insert into employee values AKate      26    Female   Moscow      Russia",
/*12*/     "insert into employee values Luke    23      Male     Seoul       \"South Korea\"",
/*13*/     "insert into employee values Nick    22    Male     \"Mexico City\"   Mexico",
/*14*/     "insert into employee values Olivia   33   Female   \"Cape_Town\"   \"South Africa\"",
/*15*/     "insert into employee values Peter    36  \t Male       \"Sao Paulo\"   Brazil",
/*16*/     "insert into employee values Qin     38    Female   Shanghai    China",
/*17*/     "insert into employee values Robert   42   Male     \"New Delhiv\"   India",
/*18*/     "insert into employee values Sophie   21      Female   \"Buenos Aires\"   Argentina",
/*19*/     "insert into employee values Tom     39    Male     Sydney      Australia",

};

const vector<string> command_list_2 ={
/*0*/     "select * from employee where Name > J",
/*1*/     "select * from employee where Country > I",
/*2*/     "select Name, Age, Year from employee where age > 15",
/*3*/     "select Name, Age, Country from employee where Age < 30",
/*4*/     "select * from employee where Gende = Male"
};

const vector<string> command_list_3 ={
/*0*/     "select Name, Age, Country from employee where Name > J or Age < 30",
/*1*/     "select Name, Years, City, Town from employee where Name > J or Country > I",
/*2*/     "select * from employee where Name > J and Age < 30 or Gende = Male and Country > I",
/*3*/     "select * from employee where Name > J or Age < 30 or Gende = Male and Country > I",
};

const vector<string> command_list_4 = {
/*1*/     "select * from employee where (Name > J and Age < 30 or Gende = Male) and Country > I",
/*2*/     "select * from employee where Name > J and (Age < 30 or (Gende = Male and Country > I))",
/*3*/     "select * from employee where (Name > J or Age < 30) and (Gende = Male\t or Country > I)",
/*7*/     "select Name,  Age,  Gende,  \"City23\",   Name,   Country from employee where City = Moscow or Age < 30 and (Gende = Male and age > 20)  "
};

bool sql_basic(bool debug = false)
{
    SQL sql;
    Table t;
    cout << endl
         << endl;
    for (int i = 0; i < command_list_1.size(); i++)
    {
        t = sql.command(command_list_1[i]);
    }
    cout << t << endl;
    cout << "----- END TEST --------" << endl;
    return true;
}

bool sql_relational(bool debug = false)
{
    SQL sql;

    cout << endl
         << endl;
    for (int i = 0; i < command_list_2.size(); i++)
    {
        sql.command(command_list_2[i]);
        cout << "basic_test: records selected: "<<sql.select_recnos() << endl <<  endl << endl << endl;
    }

    cout << "----- END TEST --------" << endl;
    return true;
}

bool sql_logical(bool debug = false)
{
    SQL sql;

    cout << endl
         << endl;
    for (int i = 0; i < command_list_3.size(); i++)
    {
        sql.command(command_list_3[i]);
        cout << "basic_test: records selected: "<<sql.select_recnos() << endl <<  endl << endl << endl;
    }

    cout << "----- END TEST --------" << endl;
    return true;
}

bool sql_paren(bool debug = false)
{
    SQL sql;

    cout << endl
         << endl;
    for (int i = 0; i < command_list_4.size(); i++)
    {
        sql.command(command_list_4[i]);
        cout << "basic_test: records selected: "<<sql.select_recnos() << endl << endl << endl << endl;
    }

    cout << "----- END TEST --------" << endl;
    return true;
}

// ==============================
// global BAD!
bool debug = false;
// ==============================

TEST(SQL_BASIC, SQLBasic) {
    bool success = sql_basic(debug);
    EXPECT_EQ(success, true);
}

TEST(SQL_RELATIONAL, SQLRelational) {
    bool success = sql_relational(debug);
    EXPECT_EQ(success, true);
}

TEST(SQL_LOGICAL, SQLLogical) {
    bool success = sql_logical(debug);
    EXPECT_EQ(success, true);
}

TEST(SQL_PAREN, SQLParen) {
    bool success = sql_paren(debug);
    EXPECT_EQ(success, true);
}


int main(int argc, char **argv) {
    if (argc > 1)
    {
        debug = !strcmp(argv[1], "debug");
    }

    ::testing::InitGoogleTest(&argc, argv);
    std::cout<<"\n\n----------running basic_test.cpp---------\n\n"<<std::endl;
    return RUN_ALL_TESTS();
}


/*
----------running basic_test.cpp---------


[==========] Running 4 tests from 4 test suites.
[----------] Global test environment set-up.
[----------] 1 test from SQL_BASIC
[ RUN      ] SQL_BASIC.SQLBasic



Table name: employee, records: 19
              record                Name                 Age               Gende                City             Country

                   0               Alice                  25              Female            New York                 USA
                   1                 Bob                  30                Male              London                  UK
                   2             Charlie                  35                Male               Paris              France
                   3               David                  20                Male             Beijing               China
                   4                 Eva                  28              Female              Madrid               Spain
                   5               Frank                  32                Male              Berlin             Germany
                   6               Grace                  24              Female              Sydney           Australia
                   7               Henry                  40                Male               Tokyo               Japan
                   8            Isabella                  29              Female                Rome               Italy
                   9                Jack                  27                Male             Toronto              Canada
                  10               AKate                  26              Female              Moscow              Russia
                  11                Luke                  23                Male               Seoul         South Korea
                  12                Nick                  22                Male         Mexico City              Mexico
                  13              Olivia                  33              Female           Cape_Town        South Africa
                  14               Peter                  36                Male           Sao Paulo              Brazil
                  15                 Qin                  38              Female            Shanghai               China
                  16              Robert                  42                Male          New Delhiv               India
                  17              Sophie                  21              Female        Buenos Aires           Argentina
                  18                 Tom                  39                Male              Sydney           Australia





----- END TEST --------
[       OK ] SQL_BASIC.SQLBasic (210 ms)
[----------] 1 test from SQL_BASIC (211 ms total)

[----------] 1 test from SQL_RELATIONAL
[ RUN      ] SQL_RELATIONAL.SQLRelational


here is the _condition vector string: Name > J
basic_test: records selected: 9 11 12 13 14 15 16 17 18



here is the _condition vector string: Country > I
basic_test: records selected: 0 1 4 7 8 10 11 12 13 16



basic_test: records selected:



basic_test: records selected: 0 3 4 6 8 9 10 11 12 17



here is the _condition vector string: Gende = Male
basic_test: records selected: 1 2 3 5 7 9 11 12 14 16 18



----- END TEST --------
[       OK ] SQL_RELATIONAL.SQLRelational (111 ms)
[----------] 1 test from SQL_RELATIONAL (112 ms total)

[----------] 1 test from SQL_LOGICAL
[ RUN      ] SQL_LOGICAL.SQLLogical


basic_test: records selected: 0 3 4 6 8 9 10 11 12 13 14 15 16 17 18



basic_test: records selected: 0 1 4 7 8 9 10 11 12 13 14 15 16 17 18



here is the _condition vector string: Name > J and Age < 30 or Gende = Male and Country > I
basic_test: records selected: 1 7 9 11 12 16 17



here is the _condition vector string: Name > J or Age < 30 or Gende = Male and Country > I
basic_test: records selected: 0 1 3 4 6 7 8 9 10 11 12 13 14 15 16 17 18



----- END TEST --------
[       OK ] SQL_LOGICAL.SQLLogical (78 ms)
[----------] 1 test from SQL_LOGICAL (78 ms total)

[----------] 1 test from SQL_PAREN
[ RUN      ] SQL_PAREN.SQLParen


here is the _condition vector string: ( Name > J and Age < 30 or Gende = Male ) and Country > I
basic_test: records selected: 1 7 11 12 16



here is the _condition vector string: Name > J and ( Age < 30 or ( Gende = Male and Country > I ) )
basic_test: records selected: 9 11 12 16 17



here is the _condition vector string: ( Name > J or Age < 30 ) and ( Gende = Male or Country > I )
basic_test: records selected: 0 3 4 8 9 10 11 12 13 14 16 18



basic_test: records selected: 10



----- END TEST --------
[       OK ] SQL_PAREN.SQLParen (97 ms)
[----------] 1 test from SQL_PAREN (97 ms total)

[----------] Global test environment tear-down
[==========] 4 tests from 4 test suites ran. (504 ms total)
[  PASSED  ] 4 tests.
*/