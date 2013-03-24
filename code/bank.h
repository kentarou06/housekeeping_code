#include <string>
#include "picojson.h"
using namespace std;

const string SETTING_FILENAME = "bank_setting.txt";

class bank{
 public:
  int id;
  string created_at;
  string updated_at;

  string bankname;
  int year, month, day;

  string paykind, payreason;
  int payment;

  string putkind, putreason;
  int putting;

  void parse(picojson::object& o);
};

inline void bank::parse(picojson::object& o){
  id = (int)o["id"].get<double>();
  created_at = o["created_at"].to_str();
  updated_at = o["updated_at"].to_str();

  bankname = o["bankname"].to_str();
  year = (int)o["year"].get<double>();
  month = (int)o["month"].get<double>();
  day = (int)o["day"].get<double>();

  paykind = o["paykind"].to_str();
  payreason = o["payreason"].to_str();
  payment = (int)o["payment"].get<double>();

  putkind = o["putkind"].to_str();
  putreason = o["putreason"].to_str();
  putting = (int)o["putting"].get<double>();
}
