/**
Predictive parsing where the parsing table is hard coded

Grammar used : Arithmetic expressions on integers using + , * operators

parsing table

i == a single integer

    (   )  +  *   i   $
E  TX   -  -  -  TX   -
T  (E)  -  -  -  iY   -
X  -    0  +E -   -   0
Y  -    0  0  *T  -   0

**/
#include <bits/stdc++.h>

using namespace std;
typedef vector<int> vi;
typedef long long int lli;
typedef vector<lli> vli;


map<char, map<char,vector<char> > > parsing_table;
void set_up_table()
{
    parsing_table['E']['(']= vector<char>{'T', 'X'};
    parsing_table['E']['i']= vector<char>{'T', 'X'};
    parsing_table['T']['(']= vector<char>{'(', 'E' , ')'};
    parsing_table['T']['i']= vector<char>{'i', 'Y'};
    parsing_table['X'][')']= vector<char>{0};
    parsing_table['X']['+']= vector<char>{'+', 'E'};
    parsing_table['X']['$']= vector<char>{0};
    parsing_table['Y'][')']= vector<char>{0};
    parsing_table['Y']['+']= vector<char>{0};
    parsing_table['Y']['*']= vector<char>{'*', 'T'};
    parsing_table['Y']['$']= vector<char>{0};
}

bool is_nonterminal(char c)
{
    set<char> s = {'E' , 'T' , 'X' , 'Y'};
    if(s.find(c)!=s.end())
        return true;

    return false;
}

void push_array(stack<char> &s , const vector<char> &a)
{
    int n = a.size();
    for(int i=n-1;i>=0;i--)
    {
        if(a[i]!=0)
            s.push(a[i]);
    }
}

bool parse(const vector<char> &token)
{
    stack<char> s;
    s.push('$');
    s.push('E');

    int len = token.size();
    int i = 0;
    while(!s.empty())
    {
        char t = token[i];
        if(is_nonterminal(s.top()))
        {
            char X= s.top();
            if(parsing_table[X].find(t)!=parsing_table[X].end())
            {
                s.pop();
                push_array(s,parsing_table[X][t]);
            }
            else
                return false;
        }
        else
        {
            if(s.top() == t)
            {
                s.pop();
                i++;
            }
            else
                return false;
        }
    }

    return true;
}

int main()
{
    set_up_table();
    vector<char> tokens;
    while(true)
    {
        tokens.clear();
        while(true)
        {
            char c;
            cin>>c;
            tokens.push_back(c);
            if(c == '$')
                break;
        }
        bool ans = parse(tokens);
        if(ans == true)
            cout<<"Accepted!!"<<endl;
        else
            cout<<"Not accepted :("<<endl;
    }


}

