#ifndef INPUT_CPP
#define INPUT_CPP

#include <string>
#include <vector>
#include "../header/Base.h"
#include "../header/Input.h"
#include "Exec.cpp"
#include "DoubleAND.cpp"
#include "DoubleOR.cpp"
#include "Connector.cpp"
#include "Semicolon.cpp"
#include "Pipe.cpp"
#include "Append.cpp"
#include "Left.cpp"
#include "Right.cpp"
//#include "Parentheses.cpp"


Input::Input()
{
    
}

bool Input::execute()
{
    //cout << "OVER HERE" << endl;
    return v.at(v.size()- 1)->execute();
}

void Input::fillV(vector<string> x)
{
    string command = "";
    vector<Base*> finished;
    vector<Connector*> connectors;
    vector<string> compare;
    
    
    for (int i = 0; i < x.size(); ++i)
    {
        //CHECK IF ONLY COMMAND
        if(x.at(i) != ";" && x.at(i) != "&&" && x.at(i) != "||" && x.at(i) != "(" 
        && x.at(i) != ")" && x.at(i) != ">" && x.at(i) != "<" && x.at(i) != ">>" && x.at(i) != "|")
        {
            // if (i > 0)
            // {
            // if (x.at(i-1) != ">" && x.at(i-1) != ">>" && x.at(i-1) != "<")
            // {
            //     command = command + " " + x.at(i);
            //     cout << "current command is: " << command << endl;
            // }
            // else
            // {
            //     command = command + " " +x.at(i);
            //     cout << "current command is: " << command << endl;
            // }
            // }
            
            command = command + " " + x.at(i);
        }
        
        //CHECK IF A CONNECTOR
        if(x.at(i) == ";" || x.at(i) == "&&" || x.at(i) == "||" || x.at(i).at(0) == '(' 
        || x.at(i) == ">>"  || x.at(i) == ">" || x.at(i) == "<" || x.at(i) == "|")
        {
            //CHECK IF PARANTHESES
            if (x.at(i).at(0) == '(')
            {
                if (x.size() != 1)
                {
                    Input* inp = new Input();
                    vector<string> wizard;
                    wizard = parse(x.at(i).substr(1,x.at(i).size()-2));
                    inp->fillV(wizard);
                    finished.push_back(inp);
                }
                else
                {
                    string tester;
                    tester = x.at(i).substr(1, x.at(i).size()-2);
                    Exec* z = new Exec(tester);
                    finished.push_back(z);
                    if (connectors.size() ==0)
                    {
                        v.push_back(z);
                    }
                }
                command = "";
            
            }
            
            //CHECK IF >
            else if(x.at(i) == ">")
            {
                //cout << "should be >" << endl;
                if(i != 0)
                {
                if (x.at(i-1).at(0) != '(')
                {
                    //cout << "Pushing back :" << command << endl;
                    cout << "Exec{" << command << ") at >" << endl;
                    compare.push_back(command);
                    Exec* z = new Exec(command);
                    finished.push_back(z);
                }
                }
                Right* y = new Right();
                y->setRight(x.at(i+1));
                //cout << "Deleting : " << command << endl;
                command = "";
                v.push_back(y);
                connectors.push_back(y);
            }
            
            //CHECK IF >>
            else if(x.at(i) == ">>")
            {
                //cout << "should be >>" << endl;
                if(i != 0)
                {
                if (x.at(i-1).at(0) != '(')
                {
                    //cout << "Command is: " << command << endl;
                    cout << "Exec{" << command << ") at >>" << endl;
                    Exec* z = new Exec(command);
                    finished.push_back(z);
                }
                }
                Append* y = new Append();
                y->setRight(x.at(i+1));
                command = "";
                v.push_back(y);
                connectors.push_back(y);
                //cout << "END >> " << endl;
            }
            
            //CHECK IF <
            else if(x.at(i) == "<")
            {
                //cout << "should be <" << endl;
                if(i != 0)
                {
                if (x.at(i-1).at(0) != '(')
                {
                    cout << "Exec{" << command << ") at |" << endl;
                    compare.push_back(command);
                    Exec* z = new Exec(command);
                    finished.push_back(z);
                }
                }
                Left* y = new Left();
                y->setRight(x.at(i+1));
                command = "";
                v.push_back(y);
                connectors.push_back(y);
            }
            
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++ASSS 4
            
            //CHECK IF |
            else if(x.at(i) == "|")
            {
                //cout << "should be |" << endl;
                if(i != 0)
                {
                if (x.at(i-1).at(0) != '(')
                {
                    cout << "Exec{" << command << ") at |" << endl;
                    compare.push_back(command);
                    Exec* z = new Exec(command);
                    finished.push_back(z);
                }
                }
                Pipe* y = new Pipe();
                y->setRight(x.at(i+1));
                command = "";
                v.push_back(y);
                connectors.push_back(y);
            }
            
            //CHECK IF SEMICOLON
            else if(x.at(i) == ";" )
            {
                if(i != 0)
                {
                if (x.at(i-1).at(0) != '(')
                {
                    Exec* z = new Exec(command);
                    finished.push_back(z);
                }
                }
                command = "";
                Semicolon* y = new Semicolon;
                v.push_back(y);
                connectors.push_back(y);
            }
            
            //CHECK IF DOUBLE OR
            else if (x.at(i) == "||")
            {
                if(i != 0)
                {
                if (x.at(i-1).at(0) != '(')
                {
                    Exec* z = new Exec(command);
                    finished.push_back(z);
                }
                }
                command = "";
                DoubleOR* y = new DoubleOR;
                v.push_back(y);
                connectors.push_back(y);
            }
            
            //CHECK IF DOUBLE AND
            else if (x.at(i) == "&&")
            {
                if(i != 0)
                {
                if (x.at(i-1).at(0) != '(')
                {
                    Exec* z = new Exec(command);
                    finished.push_back(z);
                }
                }
                command = "";
                DoubleAND* y = new DoubleAND;
                v.push_back(y);
                connectors.push_back(y);
            }            
            
        }
        
        //CHECK IF END OF INPUT
        else if (i == x.size()-1 )
        {
            
            // cout << "connectors.size() = " << connectors.size() << endl;
            // cout << "finished.size() = " << finished.size() << endl;
            // cout << "v.size() = " << v.size() << endl;
            if (i > 0)
            {
                //cout << "here" << endl;
            if (x.at(i-1) != ">" && x.at(i-1) != ">>")
            {   
                Exec* z = new Exec(command);
                if (connectors.size() == 0)
                {
                    v.push_back(z);
                }
                finished.push_back(z);
            }
            }
            else
            {
                Exec* z = new Exec(command);
                if (connectors.size() == 0)
                {
                    v.push_back(z);
                }
                finished.push_back(z);
            }
                
               
        }
    }
    
    
    cout << "compare.size() = " << compare.size() << endl;
    cout << "connectors.size() = " << connectors.size() << endl;
    cout << "finished.size() = " << finished.size() << endl;
    cout << "v.size() = " << v.size() << endl;
    
    
    
    
    //left skewed tree
    
    for (int i = 0; i < connectors.size(); i++)
    {
        //cout << "Input.cpp: Tree Construction " << endl;
        if(i == 0)
        {
            if (connectors.at(i)->getid() <= 3)
            {
                connectors.at(0)->setLeft(finished.at(0));
                connectors.at(0)->setRight(finished.at(1));
            }
            else if(connectors.at(i)->getid() == 5 || connectors.at(i)->getid() == 6 
            || connectors.at(i)->getid() == 7 || connectors.at(i)->getid() == 8)
            {
                connectors.at(0)->setLeft(finished.at(0));
            }
        }
        else
        {
            if (connectors.at(i)->getid() <= 3)
            {
                connectors.at(i)->setLeft(connectors.at(i-1));
                connectors.at(i)->setRight(finished.at(i+1));
            }
            else if (connectors.at(i)->getid() == 5 || connectors.at(i)->getid() == 6 
            || connectors.at(i)->getid() == 7 || connectors.at(i)->getid() == 8)
            {
                cout << "Right Exec should be :" << compare.at(i) << endl;
                connectors.at(i)->setLeft(connectors.at(i-1));
                
            }
            
            
        }
        
    }
    // cout << "Got here after leftskew tree" << endl;
    // cout << "connectors.size() = " << connectors.size() << endl;
    // cout << "finished.size() = " << finished.size() << endl;
    // cout << "v.size() = " << v.size() << endl;
    
    //cout << "Input.cpp: Tree Construction END" << endl;
    
    
//=====================================================PARSE========================
    
}

vector<string> Input::parse(string x)
{
    vector<string> commands;
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
        else if(x.at(i) == ';' || x.at(i) == '|' || x.at(i) == '&')
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
                i++;
                commands.push_back("||");
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

    
    return commands;
    
    
}

#endif
 
