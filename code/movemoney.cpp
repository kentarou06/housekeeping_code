#include <iostream>
#include <cstdlib>
#include "utility.h"
#include "bank.h"
using namespace std;

const string base_url = "http://localhost:3000";
const string put_output = "putmoney_output";
const string pay_output   = "paymoney_output";

void input(string show, string &value){
  string tmp;
  cout << show << " default(" << value << ") :";
  getline(cin, tmp);
  if( tmp != "" )
    value = tmp;
}

int main(){
  setting st(SETTING_FILENAME);

  string from_bankname = st.get_string("from_bankname","");
  string to_bankname = st.get_string("to_bankname","");
  string year = st.get_string("year","");
  string month = st.get_string("month","");
  string day = st.get_string("day","");
  string putkind, putting, putreason;
  string paykind, payment, payreason;
  string buf;

  cout << "bank から bank への出金プログラム" << endl;

  input("from bankname(str)", from_bankname);
  st.set_string("from_bankname", from_bankname);
  input("to bankname(str)", to_bankname);
  st.set_string("to_bankname", to_bankname);

  input("year(int)", year);
  st.set_string("year",year);
  input("month(int)", month);
  st.set_string("month", month);
  input("day(int)", day);
  st.set_string("day", day);

  input("money(int)", putting );
  payment = putting;

  putkind   = "他銀行から入金";
  putreason = from_bankname + " から入金";
  paykind   = "他銀行へ出金";
  payreason = to_bankname + " へ出金";

  st.write();

  string put_url = base_url +"/banks/putmoney/0?"
    + "bankname=" + to_bankname
    + "&year=" + year + "&month=" + month + "&day=" + day
    + "&putkind=" + putkind
    + "&putting=" + putting
    + "&putreason=" + putreason;
  string put_command = "wget -q -O " + put_output
    + " \"" + put_url + "\"";
  //  cout << "put command : " << put_command << endl;
  system(put_command.c_str());


  string pay_url = base_url +"/banks/paymoney/0?"
    + "bankname=" + from_bankname
    + "&year=" + year + "&month=" + month + "&day=" + day
    + "&paykind=" + paykind
    + "&payment=" + payment
    + "&payreason=" + payreason;
  string pay_command = "wget -q -O " + pay_output
    + " \"" + pay_url + "\"";
  //  cout << "pay command : " << pay_command << endl;
  system(pay_command.c_str());

  return 0;
}
