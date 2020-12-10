#include <iostream>
#include <string>
#include <vector>

#include "Connector.cpp"
#include "DoubleAND.cpp"
#include "DoubleOR.cpp"
#include "Semicolon.cpp"
#include "Input.cpp"
#include "Exec.cpp"
#include "Pipe.cpp"
#include "Append.cpp"
#include "Left.cpp"
#include "Right.cpp"
//#include "Parentheses.cpp"

using namespace std;

    vector<string> commands;
    void parse(string x);
    void createTree(Input* composite);
    
int main(){
    
    
    string userinput;
    
    for(;;)
    {
        Input* Test = new Input();
        cout << "$ ";
        getline(cin, userinput);
        
        parse(userinput);
        
        for(int i = 0; i < commands.size(); ++i)
        {
            cout << "commands.at(" << i << ") = " << commands.at(i) << endl;
        }
        
        createTree(Test);
        Test->execute();
        commands.clear();
        delete Test;
        
        
        // getline(cin, userinput);
        
        // Exec* x = new Exec(" read");
        
        // Left* right = new Left();
        // right->setLeft(x);
        // right->setRight("right");
        // right->execute();
        
        
    }
    
    
}

void parse(string x)
{
    //cout << "ran" << endl;
    int snip = 0;
    int count = 0;
    int snap = 0;
    for (int i = 0; i < x.size(); ++i)
    {
        if(x.at(i) == '#')
        {
            break;
        }
        if(x.at(i) == '\"')
        {
            //cout << "found quote" << endl;
            int quotesize = 0;
            for(int j = i + 1; j < x.size(); ++j)
            {
                quotesize++;
                count++;
                if (x.at(j) == '\"')
                {
                    //cout << "found second quote" << endl;
                    //cout << x.substr(snip + 1,quotesize - 1) << endl;
                    commands.push_back(x.substr(snip,quotesize + 1));
                    break;
                }
            }
            //advances for loop by the quotationed command
            for (int z = 0; z < quotesize + 1; ++z)
            {
                i++;
            }
            //count twice to keep track of missing quotes
            count++;
            count++;
            snip = count;
            snap = 0;
        }
        
        //parsing parentheses
        
        else if (x.at(i) == '(')
        {
            int parenthesized = 0;
            for(int j = i + 1; j < x.size(); ++j)
            {
                parenthesized++;
                count++;
                if (x.at(j) == ')')
                {
                    commands.push_back(x.substr(snip,parenthesized + 1));
                    break;
                }
            }
            
            for (int z = 0; z < parenthesized + 1; ++z)
            {
                i++;
            }
            
            count++;
            count++;
            snip = count;
            snap = 0;
            
            
        }
        
        
        //assumes first detected "&" and "|"" implies a double 
        else if(x.at(i) == ';' || x.at(i) == '|' || x.at(i) == '&' || x.at(i) == '>' || x.at(i) == '<')
        {
            if(x.at(i) == ';')
            {
                if(x.substr(snip,snap) != "")
                {
                    commands.push_back(x.substr(snip,snap));
                }
                commands.push_back(";");
                count++;
                snip = count;
                snap = 0;
            }
            else if(x.at(i) == '&')
            {
                i++;
                commands.push_back("&&");
                count++;
                count++;
                snip = count;
                snap = 0;
            }
            else if(x.at(i) == '|')
            {
                if (x.size() != 0)
                {
               if (x.at(i+1) == '|')
                {
                    i++;
                    i++;
                    commands.push_back("||");
                    count++;
                    count++;
                    count++;
                    snip = count;
                    snap = 0;
                }
                else
                {
                    i++;
                    commands.push_back("|");
                    count++;
                    count++;
                    snip = count;
                    snap = 0;
                }
                }
            }
            else if(x.at(i) == '>')
            {
                //cout << "main.parse() begin" << endl;
                if(x.size() != 0)
                {
                if (x.at(i+1) == '>')
                {
                    i++;
                    i++;
                    commands.push_back(">>");
                    count++;
                    count++;
                    count++;
                    snip = count;
                    snap = 0;
                }
                else
                {
                    i++;
                    commands.push_back(">");
                    count++;
                    count++;
                    snip = count;
                    snap = 0;
                }
                }
                //cout << "main.parse() end" << endl;
            }
            else if(x.at(i) == '<')
            {
                i++;
                commands.push_back("<");
                count++;
                count++;
                snip = count;
                snap = 0;
            }
            
        }
        else if (x.at(i) != ' ')
        {
            count++;
            snap++;
            if (i == x.size()-1)
            {
                //cout << "Pushing x.substr(" << snip << "," << snap << ") = " << x.substr(snip,snap)<< endl;
                commands.push_back(x.substr(snip,snap));
            }
        }
        else if (x.at(i) == ' ')
        {
            count++;
            //cout << "Pushing x.substr(" << snip << "," << snap << ") = " << x.substr(snip,snap)<< endl;
            if (x.substr(snip,snap) != "")
            {
                commands.push_back(x.substr(snip,snap));
            }
            snip = count;
            //snip++;
            snap = 0;
        }
        
        //cout << "(" << i << ") " << "Pushing x.substr(" << snip << "," << snap << ") = " << x.substr(snip,snap)<< endl;
        //cout << "snip = " << snip << " and snap = " << snap << endl;
    }
    
    
    
    //cout << "main.cpp: parse() end"<< endl;
}


void createTree(Input* composite)
{
    //cout << "fillv begin" << endl;
    composite->fillV(commands);
    //cout << "fillV end" << endl;
    //cout << "main.cpp: createTree() end"<< endl;
}
