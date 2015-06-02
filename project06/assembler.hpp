#include<bitset>
#include<sstream>
#include "parser.hpp"
#include "code.hpp"

using namespace std;

class assembler {
  private:
    static void p(string s){ cout << s << "\n"; }
//    static string symb, dest, comp, jump;
  public:
    static void translate(string input);
};
void assembler::translate(string input){
  parser parsered_input(input);
  string hackfile_name = input.substr(0, input.length()-4) + ".hack";
  ofstream hackfile(hackfile_name.c_str());
  while(true){
    string commandType = parsered_input.commandType();
    if(commandType=="A_COMMAND" || commandType=="L_COMMAND"){
      string symb = parsered_input.symbol();
      int int_symb;
      istringstream (symb) >> int_symb;
      bitset<16> bit_symb(int_symb);
      hackfile << bit_symb << "\n";
    }else if(commandType=="C_COMMAND"){
      string dest = code::dest(parsered_input.dest());
      string comp = code::comp(parsered_input.comp());
      string jump = code::jump(parsered_input.jump());
      hackfile << "111"+comp+dest+jump << "\n";
    }
    if(parsered_input.hasMoreCommands()){
      parsered_input.advance();
    }else{
      break;
    }
  }
  hackfile.close();
}
