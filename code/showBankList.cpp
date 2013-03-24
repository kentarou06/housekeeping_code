#include <iostream>
#include <fstream>
#include <cstdlib>
#include "picojson.h"
using namespace std;

const string base_url = "http://localhost:3000";
const string output   = "banklist_output";

int main(){

  string url = base_url + "/banks/bank_list/0.json";
  string command = "wget -q -O " + output + " \"" + url + "\"";
  //  cout << "command : " << command << endl;
  system(command.c_str());

  ifstream ifs( output.c_str() );
  picojson::value v;
  ifs >> v;

  picojson::array& a = v.get<picojson::array>();
  cout << "#banks = " << a.size() << endl;
  picojson::array::iterator it = a.begin();
  while( it != a.end() ){
    picojson::object& o = it -> get<picojson::object>();
    cout << " " << o["bankname"] << endl;
    it++;
  }

  return 0;
}
