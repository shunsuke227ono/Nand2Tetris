#define EQ(a,b) (a).compare((b))==0 ? true : false
#define IFEQ(a,b) if(EQ((a), (b)))
using namespace std;

class code {
  public:
    static string dest(string d);
    static string comp(string c);
    static string jump(string j);
};
string code::dest(string d){
  IFEQ(d, "M") return "001";
  IFEQ(d, "D") return "010";
  IFEQ(d, "MD") return "011";
  IFEQ(d, "A") return "100";
  IFEQ(d, "AM") return "101";
  IFEQ(d, "AD") return "110";
  IFEQ(d, "AMD") return "111";
  IFEQ(d, "null") return "000";
  return "INVALID DEST";
}
string code::comp(string c){
  IFEQ(c, "0") return "0101010";
  IFEQ(c, "1") return "0111111";
  IFEQ(c, "-1") return "0111010";
  IFEQ(c, "D") return "0001100";
  IFEQ(c, "A") return "0110000";
  IFEQ(c, "!D") return "0001101";
  IFEQ(c, "!A") return "0110001";
  IFEQ(c, "-D") return "0001111";
  IFEQ(c, "-A") return "0110011";
  IFEQ(c, "D+1") return "0011111";
  IFEQ(c, "A+1") return "0110111";
  IFEQ(c, "D-1") return "0001110";
  IFEQ(c, "A-1") return "0110010";
  IFEQ(c, "D+A") return "0000010";
  IFEQ(c, "D-A") return "0010011";
  IFEQ(c, "A-D") return "0000111";
  IFEQ(c, "D&A") return "0000000";
  IFEQ(c, "D|A") return "0010101";
  IFEQ(c, "M") return "1110000";
  IFEQ(c, "!M") return "1110001";
  IFEQ(c, "-M") return "1110011";
  IFEQ(c, "M+1") return "1110111";
  IFEQ(c, "M-1") return "1110010";
  IFEQ(c, "D+M") return "1000010";
  IFEQ(c, "D-M") return "1010011";
  IFEQ(c, "M-D") return "1000111";
  IFEQ(c, "D&M") return "1000000";
  IFEQ(c, "D|M") return "1010101";
  return "INVALID COMP";
}
string code::jump(string j){
  IFEQ(j, "JGT") return "001";
  IFEQ(j, "JEQ") return "010";
  IFEQ(j, "JGE") return "011";
  IFEQ(j, "JLT") return "100";
  IFEQ(j, "JNE") return "101";
  IFEQ(j, "JLE") return "110";
  IFEQ(j, "JMP") return "111";
  IFEQ(j, "null") return "000";
  return "INVALID JUMP";
}
