#include <iostream>

#define TEXTTABLE_ENCODE_MULTIBYTE_STRINGS
#define TEXTTABLE_USE_EN_US_UTF8

#include "TextTable.h"

using namespace std;


class Table
{
public:
    typedef std::vector< std::string > Row;
    Table(char horizontal, char vertical) :
        _horizontal(horizontal),
        _vertical(vertical)
    {_maxWidth = 0; }
    void add(string const & content)
    {
        _current.push_back(content);
    }
    void endOfRow()
    {
        _rows.push_back(_current);
        _current.assign(0, "");
    }
    void widthOfCols()
    {
        if (_rows.empty()) return;
        int rows = _rows.size();
        int cols = _rows[0].size();
        _widths.resize(cols);
        for (int i = 0; i < cols; ++i)
        {
            int width = 0;
            for (int j = 0; j < rows; ++j)
            {
                width = max(width, (int)_rows[j][i].length());
            }
            _widths[i] = width + 1;
            _maxWidth += _widths[i] + 1;
        }
    }
    void print()
    {
        int rows = _rows.size();
        int cols = _rows[0].size();
        cout << setfill(_horizontal);
        cout << setw(_maxWidth) << "" << _vertical << endl;
        cout << setfill(' ');
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                cout << _vertical << setw(_widths[j]) << left << _rows[i][j];
                if (j == cols - 1)
                    cout << _vertical << endl;
            }
            cout << setfill(_horizontal);
            cout << setw(_maxWidth) << "" << _vertical << endl;
            cout << setfill(' ');
        }
    }
private:
    char _horizontal;
    char _vertical;
    int _maxWidth;
    Row _current;
    vector<Row> _rows;
    vector<int> _widths;
};



int main()
{
    Table t( '-', '|');

    t.add( "" );
    t.add( "Sex" );
    t.add( "Age" );
    t.endOfRow();

    t.add( "Moses" );
    t.add( "male" );
    t.add( "4556" );
    t.endOfRow();

    t.add( "Jesus" );
    t.add( "male" );
    t.add( "2016" );
    t.endOfRow();

    t.add( "Debora" );
    t.add( "female" );
    t.add( "3001" );
    t.endOfRow();

    t.add( "doan manh toan" );
    t.add( "male" );
    t.add( "25" );
    t.endOfRow();
    t.widthOfCols();
    t.print();

    return 0;
}
