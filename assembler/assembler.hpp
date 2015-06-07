#include<bitset>
#include<sstream>
#include<ctype.h>
#include "parser.hpp"
#include "code.hpp"
#include "symbol_table.hpp"

using namespace std;

class assembler {
  private:
    static void p(string s){ cout << s << "\n"; }
    static int i_of(string s); 
    static bitset<16> bin_of(int s); 
  public:
    static void translate(string input);
};
void assembler::translate(string input){
  parser parsered_input(input);

  symbolTable symbol_table;
  while(true){
    string commandType = parsered_input.commandType();
    if(commandType=="L_COMMAND"){
      string symb = parsered_input.symbol();
      if(!symbol_table.contains(symb)){
        symbol_table.addEntry(symb, parsered_input.getCommandCount()+1);
      }
    }
    if(parsered_input.hasMoreCommands()){
      parsered_input.advance();
    }else{
      break;
    }
  }
  parsered_input.restart();
  string hackfile_name = input.substr(0, input.length()-4) + ".hack";
  ofstream hackfile(hackfile_name.c_str());
  while(true){
    string commandType = parsered_input.commandType();
    if(commandType=="A_COMMAND"){
      string symb = parsered_input.symbol();
      if(isdigit(symb[0])){
        int symb_address = i_of(symb);
        hackfile << bin_of(symb_address) << "\n";
      }else{
        if(!symbol_table.contains(symb)){
          symbol_table.addVarEntry(symb);
        }
        int symb_address = symbol_table.getAddress(symb);
        hackfile << bin_of(symb_address) << "\n";
      }
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
int assembler::i_of(string s){
  int i;
  istringstream (s) >> i;
  return i;
}
bitset<16> assembler::bin_of(int i){
  bitset<16> bit_symb(i);
  return bit_symb;
}
