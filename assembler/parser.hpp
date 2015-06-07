#include<string>
#include<iostream>
#include<vector>
#include<fstream>
#include<algorithm>
#define FOR(i,a,b) for(int i=(a); i<(b); ++i)
using namespace std;
class parser {
  private:
    int currentLineNumber;
    int currentCommandCount;
    string currentCommand;
    vector<string> instructions;
    void setInstructions(string input);
    static bool is_instruction(string line);
    static string remove_comment(string line);
    static void p(string s);
  public:
    parser(string input);
    bool hasMoreCommands();
    void advance();
    void restart();
    string commandType();
    string symbol();
    string dest();
    string comp();
    string jump();
    int getCommandCount();
};
parser::parser(string input){
  setInstructions(input);
  currentLineNumber = 0;
  currentCommandCount = 0;
  currentCommand = instructions[currentLineNumber];
}
void parser::setInstructions(string input){
  string line;
  ifstream infile;
  infile.open(input.c_str());
  if(infile.is_open()){
    while(getline(infile, line)){
      line = remove_comment(line);
      line.erase(remove_if(line.begin(), line.end(), ::isspace), line.end());
      if(is_instruction(line)){
        instructions.push_back(line);
      }
    }
  }
}
string parser::remove_comment(string line){
  string res;
  bool is_comment;
  FOR(i, 0, line.length()){
    if(line[i]=='/'){
      if( i+1<line.length() && line[i+1]=='/') break;
    }
    res += line[i];
  }
  return res;
}
bool parser::is_instruction(string line){
  if(line.length()==0) return false;
  return true;
}
bool parser::hasMoreCommands(){
  if(currentLineNumber+1<instructions.size()) return true;
  return false;
}
void parser::advance(){
  currentLineNumber++;
  currentCommand = instructions[currentLineNumber];
  if((commandType()=="A_COMMAND")||(commandType()=="C_COMMAND")){
    currentCommandCount++;
  }
}
void parser::restart(){
  currentLineNumber = 0;
  currentCommandCount = 0;
  currentCommand = instructions[currentLineNumber];
}
string parser::commandType(){
  if(currentCommand[0]=='@') return "A_COMMAND";
  FOR(i, 0, currentCommand.size()) if(currentCommand[i]=='='||currentCommand[i]==';') return "C_COMMAND";
  if(currentCommand[0]=='(' && currentCommand[currentCommand.size()-1]==')') return "L_COMMAND";
  return "INVALID INSTRUCTION";
}
string parser::symbol(){
  if(currentCommand[0]=='@') return currentCommand.substr(1, currentCommand.size()-1);
  if(currentCommand[0]=='(') return currentCommand.substr(1, currentCommand.size()-2);
  return "INVALID INSTRUCTION";
}
string parser::dest(){
  int dest_length = currentCommand.find('=');
  if(dest_length>0) return currentCommand.substr(0, dest_length);
  return "null";
}
string parser::comp(){
  int eq_loc = currentCommand.find('=');
  int semi_loc = currentCommand.find(';');
  if(eq_loc>0) return currentCommand.substr(eq_loc+1, currentCommand.size()-(eq_loc+1));
  if(semi_loc>0) return currentCommand.substr(0, semi_loc);
  return "INVALID INSTRUCTION";
}
string parser::jump(){
  int semi_loc = currentCommand.find(';');
  if(semi_loc>0) return currentCommand.substr(semi_loc+1, currentCommand.size()-(semi_loc+1));
  return "null";
}
int parser::getCommandCount(){
  return currentCommandCount;
}
void parser::p(string s){
  cout << s << "\n";
}
