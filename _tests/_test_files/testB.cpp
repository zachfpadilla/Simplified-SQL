#include "gtest/gtest.h"
#include <iostream>
#include <iomanip>
#include "../../includes/parser/parser.h"
#include "../../includes/table/table.h"

using namespace std;

bool test_table_ctr(bool debug = false)
{
    vectorstr fields={"fname", "lname", "age"};

    Table t("student", fields);
    vectorstr row;
    row = {"Joe", "Gomez", "20"};
    t.insert_into(row);
    row = {"Karen", "Orozco", "21"};
    t.insert_into(row);
    row = {"Flo", "Yao", "29"};
    t.insert_into(row);
    row = {"Jack", "Yao", "19"};
    t.insert_into(row);
    row = {"Flo", "Jackson", "20"};
    t.insert_into(row);
    row = {"Flo", "Gomez", "20"};
    t.insert_into(row);
    row = {"Karen", "Jackson", "15"};
    t.insert_into(row);

    cout<< "Here is table t: " << endl << t << endl;

    Table t2("student");
    cout << "Copied table t: " << endl << t2 << endl;

    cout << "select_all() for t2: " << endl << t2.select_all();

    cout << "select_all() again for t2: " << endl << t2.select_all();
    return true;
}

bool test_shunting_yard(bool debug = false)
{
    vectorstr prefix({"Last", ">=", "Baker", "and", "Last", "<=", "Torres", "or", "state", "=", "ca", "and", "age", "<", "30"});
    cout << "prefix:\n";
    for (const auto &i : prefix)
        cout << i << ' ';
    cout << endl << "postfix:\n";
    Queue<Token*> postfix = ShuntingYard::sy(prefix);
    for (auto i : postfix) {
        cout << i->get_tk() << ' ';
    } cout << "\n\n";

    prefix = {"last", "=", "yao", "or", "first", "=", "flo", "and", "age", ">", "21"};
    cout << "prefix:\n";
    for (const auto &i : prefix)
        cout << i << ' ';
    cout << endl << "postfix:\n";
    postfix = ShuntingYard::sy(prefix);
    for (auto i : postfix) {
        cout << i->get_tk() << ' ';
    } cout << "\n\n";

    prefix = {"(", "age", "<", "17", "or", "age", ">", "20", ")", "and", "lname", "=", "Jackson"};
    cout << "prefix:\n";
    for (const auto &i : prefix)
        cout << i << ' ';
    cout << endl << "postfix:\n";
    postfix = ShuntingYard::sy(prefix);
    for (auto i : postfix) {
        cout << i->get_tk() << ' ';
    } cout << "\n\n";

    prefix = {"lname", "=", "Yang", "or", "major", "=", "CS", "and", "age", "<", "23", "or", "lname", "=", "Jackson"};
    cout << "prefix:\n";
    for (const auto &i : prefix)
        cout << i << ' ';
    cout << endl << "postfix:\n";
    postfix = ShuntingYard::sy(prefix);
    for (auto i : postfix) {
        cout << i->get_tk() << ' ';
    } cout << "\n\n";

    return true;
}

bool test_compound_conditions(bool debug = false) {
    vectorstr fields={"fname", "lname", "age", "state"};

    Table t("employees", fields);
    vectorstr row;
    row = {"Joe", "Gomez", "20", "CA"};
    t.insert_into(row);
    row = {"Karen", "Orozco", "21", "CA"};
    t.insert_into(row);
    row = {"Flo", "Yao", "29", "CA"};
    t.insert_into(row);
    row = {"Jack", "Yao", "19", "CA"};
    t.insert_into(row);
    row = {"Flo", "Jackson", "20", "CA"};
    t.insert_into(row);
    row = {"Flo", "Gomez", "20", "CA"};
    t.insert_into(row);
    row = {"Karen", "Jackson", "15", "CA"};
    t.insert_into(row);

    cout << "employees table:\n";
    cout << t;

    cout << "Records where lname >= Gomez && lname <= Yao || state = CA && age < 30:\n";
    cout << t.select(fields, {"lname", ">=", "Gomez", "and", "lname", "<=", "Yao", "or", "state", "=", "CA", "and", "age", "<", "30"});
    cout << "Records where lname == Yao || fname == flo && age > 21\n";
    cout << t.select({"fname", "lname", "age"}, {"lname", "=", "Yao", "or", "fname", "=", "Flo", "and", "age", ">", "21"});
    cout << "Records where (age < 17 or age > 20) && lname = Jackson:\n";
    cout << t.select({"fname", "lname", "age"}, {"(", "age", "<", "17", "or", "age", ">", "20", ")", "and", "lname", "=", "Jackson"});
    cout << "Records where lname == Yao || state == CA && age < 23 || lname == Jackson:\n";
    vectorstr test = {"lname", "=", "Yao", "or", "state", "=", "CA", "and", "age", "<", "23", "or", "lname", "=", "Jackson"};
    cout << t.select(fields, test);

    return true;
}

bool parser_basic(bool debug = false){

    cout<<"\n\n\n------------------------\n\n"<<endl;
    string str;
    char s[300];
    str = "make table student fields last, first, age, major, class";
    strcpy(s, str.c_str());
    Parser parser(s);
    mmap_ss ptree;
    ptree= parser.parse_tree();
    cout<<"input: ["<<s<<"]"<<endl<<endl;
    ptree.print_lookup();   //multimap function to print mmap as a table
    cout << endl<<endl;

    str = "insert into student values Jones,\"Sue Ellen\", 20, CS, Fr ";
    strcpy(s, str.c_str());
    parser.set_string(s);
    ptree= parser.parse_tree();
    cout<<"input: ["<<s<<"]"<<endl<<endl;
    ptree.print_lookup();
    cout << endl<<endl;

    str = "select * from student";
    strcpy(s, str.c_str());
    parser.set_string(s);
    ptree= parser.parse_tree();
    cout<<"input: ["<<s<<"]"<<endl<<endl;
    ptree.print_lookup();
    cout << endl<<endl;

    str = "select lname, fname from student where lname = \"Yao\" and fname = \"Flo\"";
    strcpy(s, str.c_str());
    parser.set_string(s);
    ptree= parser.parse_tree();
    cout<<"input: ["<<s<<"]"<<endl<<endl;
    ptree.print_lookup();
    cout << endl<<endl;

    str = "select age, lname, fname from student where fname = \"Mary Ann\" and lname = Yao";
    strcpy(s, str.c_str());
    parser.set_string(s);
    ptree= parser.parse_tree();
    cout<<"input: ["<<s<<"]"<<endl<<endl;
    ptree.print_lookup();
    cout << endl<<endl;

    str = "select * from student where (age>=25 or lname = Yao) and (fname = \"Teresa Mae\" or Major = CS)";
    strcpy(s, str.c_str());
    parser.set_string(s);
    ptree= parser.parse_tree();
    cout<<"input: ["<<s<<"]"<<endl<<endl;
    ptree.print_lookup();
    cout << endl<< endl;

    cout << "\n\n\n----- DONE -------------\n\n"
         << endl;
    return true;
}

bool basic_one_arg(bool debug = false)
{
    string command = "make table student fields last, first, age, major, class";
    Parser p(command);
    p.parse_tree().print_lookup();
    cout << "\n\n";

    command = "select * from student where (age>=25 or lname = Yao) and (fname = Teresa or Major = CS)";
    p.set_string(command);
    p.parse_tree().print_lookup();
    cout << "\n\n";

    command = "insert into student values Jones, Sue, 20, CS, Fr";
    p.set_string(command);
    p.parse_tree().print_lookup();
    return true;
}

TEST(TEST_TABLE_CTR, TestTableCTR) {
    EXPECT_EQ(1, test_table_ctr());
}

TEST(TEST_SHUNTING_YARD, TestShuntingYard) {
    EXPECT_EQ(1, test_shunting_yard());
}

TEST(TEST_COMPOUND_CONDITIONS, TestCompoundConditions) {
    EXPECT_EQ(1, test_compound_conditions());
}

TEST(TEST_TEMPLATE, TestTemplate) {
    EXPECT_EQ(1, parser_basic());
}

TEST(BASIC_ONE_ARG, BasicOneArg) {
    EXPECT_EQ(1, basic_one_arg(false));
}



int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    std::cout<<"\n\n----------running testB.cpp---------\n\n"<<std::endl;
    return RUN_ALL_TESTS();
}

