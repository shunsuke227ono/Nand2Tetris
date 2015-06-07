using namespace std;

#define FOR(i,a,b) for(int i=(a); i<(b); ++i)
#define EQ(a,b) (a).compare((b))==0 ? true : false
#define IFEQ(a,b) if(EQ((a), (b)))

class symbolTable{
  private:
    vector< vector<string> > table;
    int next_variable_address;
    static string s_of(int address);
    static vector<string> entry(string symbol, int address);
    void set_predefined_symbols();
  public:
    symbolTable();
    void addEntry(string symbol, int address);
    void addVarEntry(string symbol);
    bool contains(string symbol);
    int getAddress(string symbol);
    void printEntries();
};
symbolTable::symbolTable(){
  table.clear();
  next_variable_address = 16;
  set_predefined_symbols();
}
void symbolTable::set_predefined_symbols(){
  addEntry("SP", 0);
  addEntry("LCL", 1);
  addEntry("ARG", 2);
  addEntry("THIS", 3);
  addEntry("THAT", 4);
  FOR(i, 0, 16){ addEntry("R"+s_of(i), i); }
  addEntry("SCREEN", 16384);
  addEntry("KBD", 24576);
}
void symbolTable::addEntry(string symbol, int address){
  table.push_back(entry(symbol, address));
}
void symbolTable::addVarEntry(string symbol){
  table.push_back(entry(symbol, next_variable_address));
  next_variable_address++;
}
bool symbolTable::contains(string symbol){
  FOR(i, 0, table.size()){
    IFEQ(table[i][0], symbol) return true;
  }
  return false;
}
int symbolTable::getAddress(string symbol){
  FOR(i, 0, table.size()){
    IFEQ(table[i][0], symbol){
      int address;
      istringstream (table[i][1]) >> address;
      return address;
    }
  }
  return false;
}
vector<string> symbolTable::entry(string symbol, int address){
  vector<string> entry;
  entry.push_back(symbol);
  entry.push_back(s_of(address));
  return entry;
}
string symbolTable::s_of(int i){
  stringstream ss;
  ss << i;
  return ss.str();
}
void symbolTable::printEntries(){
  FOR(i, 0, table.size()){
    cout << "( " << table[i][0] << ", " << table[i][1] << ")" << "\n";
  }
}
