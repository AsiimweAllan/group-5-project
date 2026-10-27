#include "../include/data_loader.hpp"

#include <cassert>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;

namespace {

using Grid = vector<vector<string>>;

string write_temp_file(const string& name, const string& contents) {
    ofstream out(name, ios::binary);
    out << contents;
    return name;
}

Grid load_csv_file(const string& name) {
    projectname::CsvDataLoader loader(name);
    loader.load();
    return loader.getData();
}

Grid load_from_text(const string& name, const string& contents) {
    write_temp_file(name, contents);
    Grid result = load_csv_file(name);
    remove(name.c_str());
    return result;
}

}  // namespace

int main() {
    const Grid fixture = load_csv_file("scores.csv");
    assert(fixture.size() == 5);
    assert(fixture[0] == (vector<string>{"name", "score", "group"}));
    assert(fixture[1] == (vector<string>{"Ada", "91", "A"}));
    assert(fixture[4] == (vector<string>{"Dina", "64", "C"}));
    cout << "Loaded CSV fixture (name, score, group):\n";
    for (size_t row = 1; row < fixture.size(); ++row) {
        cout << fixture[row][0] << ", " << fixture[row][1] << ", " << fixture[row][2] << '\n';
    }
    cout << "Data loader fixture test passed.\n";

    {
        bool threw_file_error = false;
        try {
            (void)load_csv_file("this_file_does_not_exist.csv");
        } catch (const runtime_error& error) {
            threw_file_error = true;
            assert(string(error.what()).find("Could not open CSV file") != string::npos);
        }
        assert(threw_file_error);
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

    // A trailing comma represents a final empty field.
    const Grid trailing_comma = load_from_text("tmp_trailing_comma.csv", "a,b,\n");
    assert(trailing_comma.size() == 1);
    assert(trailing_comma[0] == (vector<string>{"a", "b", ""}));

    // Current limitation: quoted fields are not supported.
    const Grid quoted = load_from_text("tmp_quoted.csv", "\"a,b\",c\n");
    assert(quoted[0].size() == 3);
    assert(quoted[0][0] == "\"a");
    assert(quoted[0][1] == "b\"");

    // The loader opens files in text mode: Windows translates CRLF, while
    // Unix preserves the carriage return in the final field.
    const Grid crlf = load_from_text("tmp_crlf.csv", "a,b\r\nc,d\r\n");
    assert(crlf.size() == 2);
#ifdef _WIN32
    assert(crlf[0][1] == "b");
#else
    assert(crlf[0][1] == "b\r");
#endif

    return 0;
}
