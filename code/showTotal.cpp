#include <iostream>
#include <fstream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include "picojson.h"
#include "bank.h"
using namespace std;

const string base_url = "http://localhost:3000";
const string output   = "totalize_output";

string maxLen(string &a, string &b){
  if( a.length() > b.length() )
    return a;
  return b;
}

int main(int argc, char** argv){
  if( argc < 3 ){
    cout << argv[0] << " [year] [month] ([bankname])" << endl;
    return 1;
  }
  string year = "";
  string month = "";
  string bankname = "";

  year += argv[1];
  month += argv[2];
  if( argc == 4 )
    bankname +=  argv[3];

  cout << "year     : " << year << endl
       << "month    : " << month << endl
       << "bankname : " << bankname << endl;

  string url = base_url + "/banks/totalize/0.json?"
    + "bankname=" + bankname
    + "&year=" + year
    + "&month=" + month;

  string command = "wget -q -O " + output + " \"" + url + "\"";
  //  cout << "command : " << command << endl;
  system(command.c_str());

  ifstream ifs( output.c_str() );
  picojson::value v;
  ifs >> v;

  vector<bank> banks;
  bank mxb;
  picojson::array& a = v.get<picojson::array>();
  picojson::array::iterator it = a.begin();
  while( it != a.end() ){
    picojson::object& o = it -> get<picojson::object>();

    bank b;
    b.parse( o );
    banks.push_back(b);

    mxb.bankname = maxLen( mxb.bankname, b.bankname );
    mxb.year = max( mxb.year, b.year );
    mxb.month = max( mxb.month, b.month );
    mxb.day = max( mxb.day, b.day );

    mxb.paykind = maxLen( mxb.paykind, b.paykind );
    mxb.payreason = maxLen( mxb.payreason, b.payreason );
    mxb.payment = max( mxb.payment, b.payment );

    mxb.putkind = maxLen( mxb.putkind, b.putkind );
    mxb.putreason = maxLen( mxb.putreason, b.putreason );
    mxb.putting = max( mxb.putting, b.putting );
    it++;
  }

  for( int i=0;i<(int)banks.size();i++ ){
    bank b = banks[i];
    printf("%*s %4d/%2d/%2d | %*s | %*s\t| %6d | %*s | %*s\t| %6d\n",
	   (int)mxb.bankname.length(), b.bankname.c_str(),
	   b.year, b.month, b.day,
	   (int)mxb.paykind.length(), b.paykind.c_str(),
	   (int)mxb.payreason.length(), b.payreason.c_str(),
	   b.payment,
	   (int)mxb.putkind.length(), b.putkind.c_str(),
	   (int)mxb.putreason.length(), b.putreason.c_str(),
	   b.putting
	   );
  }

  return 0;
}
