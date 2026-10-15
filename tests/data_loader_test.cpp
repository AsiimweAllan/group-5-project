 #include "../include/data_loader.hpp"

#include <cassert>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
using projectname::load_csv_data;

namespace {

using Grid = vector<vector<string>>;

string write_temp_file(const string& name, const string& contents) {
    ofstream out(name, ios::binary);
    out << contents;
    return name;
}

Grid load_from_text(const string& name, const string& contents) {
    write_temp_file(name, contents);
    Grid result = load_csv_data(name);
    remove(name.c_str());
    return result;
}

}  // namespace

int main() {
    {
        ostringstream captured;
        streambuf* old_buf = cerr.rdbuf(captured.rdbuf());
        const Grid missing = load_csv_data("this_file_does_not_exist.csv");
        cerr.rdbuf(old_buf);

        assert(missing.empty());
        assert(captured.str().find("Could not open") != string::npos);
    }

    const Grid empty_file = load_from_text("tmp_empty.csv", "");
    assert(empty_file.empty());

    const Grid simple = load_from_text("tmp_simple.csv", "a,b,c\n1,2,3\n");
    assert(simple.size() == 2);
    assert(simple[0] == (vector<string>{"a", "b", "c"}));
    assert(simple[1] == (vector<string>{"1", "2", "3"}));

    const Grid no_trailing_newline = load_from_text("tmp_no_newline.csv", "x,y\n7,8");
    assert(no_trailing_newline.size() == 2);
    assert(no_trailing_newline[1] == (vector<string>{"7", "8"}));

    const Grid single_column = load_from_text("tmp_single_col.csv", "one\ntwo\nthree\n");
    assert(single_column.size() == 3);
    assert(single_column[0] == vector<string>{"one"});
    assert(single_column[2] == vector<string>{"three"});

    const Grid empty_field = load_from_text("tmp_empty_field.csv", "a,,c\n");
    assert(empty_field.size() == 1);
    assert(empty_field[0] == (vector<string>{"a", "", "c"}));

    const Grid blank_line = load_from_text("tmp_blank_line.csv", "a,b\n\nc,d\n");
    assert(blank_line.size() == 3);
    assert(blank_line[1].empty());
    assert(blank_line[2] == (vector<string>{"c", "d"}));

    const Grid ragged = load_from_text("tmp_ragged.csv", "a,b,c\nd\ne,f\n");
    assert(ragged.size() == 3);
    assert(ragged[0].size() == 3);
    assert(ragged[1].size() == 1);
    assert(ragged[2].size() == 2);

    const Grid spaces = load_from_text("tmp_spaces.csv", " a , b \n");
    assert(spaces[0] == (vector<string>{" a ", " b "}));

    // Current behavior: trailing comma adds no empty field.
    const Grid trailing_comma = load_from_text("tmp_trailing_comma.csv", "a,b,\n");
    assert(trailing_comma.size() == 1);
    assert(trailing_comma[0] == (vector<string>{"a", "b"}));

    // Current limitation: quoted fields are not supported.
    const Grid quoted = load_from_text("tmp_quoted.csv", "\"a,b\",c\n");
    assert(quoted[0].size() == 3);
    assert(quoted[0][0] == "\"a");
    assert(quoted[0][1] == "b\"");

    // Current behavior: CRLF leaves '\r' on the last field.
    const Grid crlf = load_from_text("tmp_crlf.csv", "a,b\r\nc,d\r\n");
    assert(crlf.size() == 2);
    assert(crlf[0][1] == "b\r");

    return 0;
}