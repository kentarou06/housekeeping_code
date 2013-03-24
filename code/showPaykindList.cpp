#include <iostream>
#include <fstream>
#include <cstdlib>
#include "picojson.h"
using namespace std;

const string base_url = "http://localhost:3000";
const string output   = "paykindlist_output";

int main(){
  string url = base_url + "/banks/paykind_list/0.json";
  string command = "wget -q -O " + output + " \"" + url + "\"";
  //  cout << "command : " << command << endl;
  system(command.c_str());

  ifstream ifs( output.c_str() );
  picojson::value v;
  ifs >> v;

  picojson::array& a = v.get<picojson::array>();
  picojson::array::iterator it = a.begin();
  cout << "#paykind = " << a.size() << endl;
  while( it != a.end() ){
    picojson::object& o = it -> get<picojson::object>();
    cout << " " << o["paykind"] << endl;
    it++;
  }

  return 0;
}
