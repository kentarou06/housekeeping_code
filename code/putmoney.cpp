#include <iostream>
#include <cstdlib>
#include "utility.h"
#include "bank.h"
using namespace std;

const string base_url = "http://localhost:3000";
const string output   = "putmoney_output";
const string missStr = "continue";

bool input(string show, string &value){
  string tmp;
  cout << show << " default(" << value << ") :";
  getline(cin, tmp);
  if( tmp != "" )
    value = tmp;
  return value == missStr;
}

int main(int argc, char** argv){
  setting st(SETTING_FILENAME);
  string bankname = st.get_string("bankname","");
  string year = st.get_string("year","");
  string month = st.get_string("month","");
  string day = st.get_string("day","");
  string putkind = st.get_string("putkind","");
  string putting = st.get_string("putting","");
  string putreason = st.get_string("putreason","");
  string buf;
  bool _b=true,  _y=true, _m=true, _d=true, _p=true;

  for( int i=1;i<argc;i++ ){
    for( int j=0;argv[i][j]!='\0';j++ ){
      switch( argv[i][j] ){
      case 'b':_b=false; input("bankname(str)",bankname); break;
      case 'y':_y=false; input("year(int)", year); break;
      case 'm':_m=false; input("month(int)", month); break;
      case 'd':_d=false; input("day(int)", day); break;
      case 'p':_p=false; input("putkind(str)", putkind); break;
      }
    }
  }

  cout << "bank への入金プログラム" << endl;
  cout << "b, y, m, d, p を引数に追加すると，"
       << "bankname, year, month, day, putkind の入力が1回になる．" << endl;
  cout << "終了するには Ctr + c を押してください" << endl
       << "入力をミスした場合，" << missStr << "と入力" << endl << endl;
  while( true ){
    if( ( _b && input("bankname(str)",bankname) ) ||
	( _y &&	input("year(int)", year) ) ||
	( _m && input("month(int)", month) ) ||
	( _d && input("day(int)", day) )||
	( _p && input("putkind(str)", putkind) )||
	input("putreason(str)", putreason) ||
	input("putting(int)", putting) ){
      cout << endl;
      continue;
    }
    st.set_string("bankname", bankname);
    st.set_string("year", year);
    st.set_string("month", month);
    st.set_string("day", day);
    st.set_string("putkind", putkind);
    st.set_string("putreason", putreason);
    st.set_string("putting", putting);
    st.write();

    string url = base_url +"/banks/putmoney/0?"
      + "bankname=" + bankname
      + "&year=" + year + "&month=" + month + "&day=" + day
      + "&putkind=" + putkind
      + "&putting=" + putting
      + "&putreason=" + putreason;

    string command = "wget -q -O " + output + " \"" + url + "\"";
    //    cout << "command : " << command << endl;
    cout << "saving..." << endl << endl;
    system(command.c_str());
  }

  return 0;
}
