#pragma once
#include <cstring>
#include <inttypes.h>

#include <sstream>
#include <iomanip>

class Date {
private:
  union {
    uint8_t b[4];
    uint32_t l;
  } val;
public:
  uint32_t getval() const { return val.l; } 
  uint8_t getYear() const { return val.b[3]; }
  uint8_t getMonth() const { return val.b[2]; }
  uint8_t getDay() const { return val.b[1]; }
  uint8_t getDayofWeek() const { return val.b[0]; }
  Date(uint8_t y, uint8_t m, uint8_t d) {
    val.b[3] = y; val.b[2] = m; val.b[1] = d; val.b[0] = 0;	
  }
  Date() { val.l = 0;}
  friend bool operator==(Date& d1,Date&d2) { return d1.val.l == d2.val.l; }
  friend bool operator<(Date& d1,Date&d2) { return d1.val.l < d2.val.l; }
  friend bool operator>(Date& d1,Date&d2) { return d1.val.l > d2.val.l; }
  friend bool operator<=(Date& d1,Date&d2) { return !(d1>d2); }
  friend bool operator>=(Date& d1,Date&d2) { return !(d1<d2); }
  std::string dec02(int v) {
	std::stringstream ss;
	ss << std::setw(2) << std::right << std::setfill('0');
	ss << v ;
	return ss.str();
  }
  std::string str() {
	std::stringstream ss;
	ss << dec02(getYear()) << "-";
	ss << dec02(getMonth()) << "-" ;
	ss << dec02(getDay());
	return ss.str();
  }
};

class Time {
private:
  union {
    uint8_t b[4];
    uint32_t l;
  } val;
public:
  uint32_t getval() const { return val.l; }
  uint8_t getHour() const { return val.b[3]; }
  uint8_t getMin() const { return val.b[2]; }
  uint8_t getSecond() const { return val.b[1]; }
  uint8_t getMilSec() const { return val.b[0]; }
  Time(uint8_t h, uint8_t m, uint8_t s) {
    val.b[3] = h; val.b[2] = m; val.b[1] = s; val.b[0] = 0;	
  }
  Time() { val.l = 0;}
  friend bool operator==(Time& t1,Time&t2)  { return t1.val.l == t2.val.l; }
  friend bool operator<(Time& t1,Time&t2) { return t1.val.l < t2.val.l; }
  friend bool operator>(Time& t1,Time&t2) { return t1.val.l > t2.val.l; }
  friend bool operator<=(Time& t1,Time&t2) { return !(t1>t2); }
  friend bool operator>=(Time& t1,Time&t2) { return !(t1<t2); }
  std::string dec02(int v) {
	std::stringstream ss;
	ss << std::setw(2) << std::right << std::setfill('0');
	ss << v ;
	return ss.str();
  }
  std::string str() {
	std::stringstream ss;
	ss << dec02(getHour()) << ":" ;
	ss << dec02(getMin()) << ":" ;
	ss << dec02(getSecond());
	return ss.str();
  }
};

class DateTime {
private:
  Date d;
  Time t;
public:
  Date getDate() const { return d; }
  Time getTime() const { return t; }

  DateTime(Date date,Time time):d(date),t(time) {}
  DateTime() {}
  friend bool operator==(DateTime& dt1,DateTime& dt2) 
    { return (dt1.d == dt2.d) && (dt1.t == dt2.t) ; }
  friend bool operator<(DateTime& dt1,DateTime& dt2) 
    { return (dt1.d < dt2.d) || ((dt1.d == dt2.d) && (dt1.t < dt2.t)) ; }
  friend bool operator>(DateTime& dt1,DateTime& dt2) 
    { return (dt1.d > dt2.d) || ((dt1.d == dt2.d) && (dt1.t > dt2.t)) ; }
  friend bool operator<=(DateTime& dt1,DateTime& dt2) { return !(dt1>dt2); }
  friend bool operator>=(DateTime& dt1,DateTime& dt2) { return !(dt1<dt2); }
};

// センサ番号
#define X(n) (0x0000|(n))
#define Y(n) (0x4000|(n))
#define A(n) (0x8000|(n))
#define B(n) (0xC000|(n))
#define Number(v) ((v)&0xff)

class Sensor {
public:
  uint16_t no;

  Sensor() : no(0) {}
  Sensor(int n) : no(n) {}
  friend bool operator==(const Sensor& s1, const Sensor& s2) {
    return (s1.no == s2.no);
  }
  operator uint16_t() const { return no; }  
  std::string str() {
	std::stringstream ss;
	int n = Number(no);
	static char ca[]="XYAB";
	int k = ((no >> 14)&0x3);
	ss << ca[k] << n ;
	return ss.str();
  }
};

typedef Sensor Actuator;

template<class Elem>
class Array {
  int size;
  int count;
  Elem *value;
public:
  Array( int sz ):size(sz),count(0) { value = new Elem[sz]; }
  int getSize() { return size;}
  int getCount() { return count;}
  Elem& operator[]( int idx ) { return value[idx]; }
};

// センサ値
class SensorValue {
private:
  DateTime datetime;
  uint8_t v01[4];
  int16_t v16[4];
public:
  void setv01(int n, uint8_t c) { v01[n] = c; }
  void setv16(int n, int16_t s) { v16[n] = s; }
  uint8_t getv01(int n) const { return v01[n]; }
  int16_t getv16(int n) const { return v16[n]; }
  DateTime getDT() const { return datetime; }
  Date getDate() const { return datetime.getDate(); }
  Time getTime() const { return datetime.getTime(); }

  SensorValue() {}
  SensorValue(DateTime dt) : datetime(dt) {}
  SensorValue(uint8_t *a01, uint16_t *a16) {
    for (int i=0;i<4;i++) {
      v01[i] = a01[i]; v16[i] = a16[i];
    }
  }
};

typedef Array<SensorValue> SensorValueArray;

// 入力:カウンタ
class Counter {
public:
  uint16_t preset;
  uint16_t current;

  Counter():preset(0), current(0) {}
  Counter(int p, int c) : preset(p), current(c) {}
};

typedef Array<Counter> CounterArray;

// 入力・出力共有
typedef SensorValue RawValue;

typedef Array<RawValue> RawValueArray;

class Collection {
public:
  Sensor sensor;
  uint16_t duration; // sec

  Collection(): sensor(Sensor(0)), duration(0) {}
  Collection(int sn, int du) :
	sensor(Sensor(sn)), duration(du) {}
  std::string str() {
	std::stringstream ss;
	ss << sensor.str() << "=" << duration;
	return ss.str();
  }
};

typedef Array<Collection> CollectionArray;

class Condition {
public:
  Sensor no;  // 番号
  int16_t arg; // 値
  int op;  // >(1), =(2), <(3) のどれか

  Condition() {}
  Condition(int n, int a, int o=0): no(n),arg(a),op(o) {}
  friend bool operator==(const Condition& a1, const Condition& a2) {
    return (a1.no == a2.no) && (a1.arg == a2.arg) && (a1.op == a2.op);
  }
  std::string str() {
	std::stringstream ss;
	static char opa[] = " >=<";
	ss << no.str() << opa[op] << arg;
	return ss.str();
  }
};
// X1>3000 => { 0x0001, 3000, 1}

class Action : public Condition {
public:
  Action() {}
  Action(int n, int a): Condition(n,a,0) {} //opは使用せず
  friend bool operator==(const Action& a1, const Action& a2) {
    return (a1.no == a2.no) && (a1.arg == a2.arg) ;
  }
  std::string str() {
	std::stringstream ss;
	ss << no.str() << "=" << arg;
	return ss.str();
  }
};
// B1 = 1 => { 0xC001, 1, 0 }
 
class Warn {
public:
  Condition *cond;
  Action *act;

  Condition *getCondition() const { return cond; }
  Action    *getAction()    const { return act; }
  uint16_t getSensorNo()    const { return cond->no;}
   int16_t getSensorArg()   const { return cond->arg;}
  uint16_t getActuatorNo()  const { return act->no; }
   int16_t getActuatorArg() const { return act->arg;}
	
  Warn(): cond(0),act(0) {}
  Warn(Condition *c, Action *a): cond(c),act(a) {}
  std::string str() {
	  std::stringstream ss;
	  ss << cond->str() << ":" << act->str();
	  return ss.str();
  }
};

class WarnValue {
private:
  Warn *warn;
public:
  Condition cond;
  Action act;

  std::string message;
  void setWarn(Warn *w) { warn = w; }

  WarnValue() : message(""),warn(0) {}
  WarnValue(int sn,int sv,int an,int av): 
	cond(Condition(sn,sv)), act(Action(an,av)) {}
  std::string str() {
	std::stringstream ss;
	ss << cond.str() << " " << act.str();
	return ss.str();
  }
};

typedef Array<WarnValue> WarnValueArray;

typedef SensorValue CollectedValue;

typedef Array<CollectedValue> CollectedValueArray;

// 収集間隔の変化記録
class CollectedHistory {
private:
  DateTime datetime;
  CollectionArray *ary;
public:
  Date getDate() const { return datetime.getDate(); }
  Time getTime() const { return datetime.getTime(); }

  CollectedHistory() : ary(0) {}
  CollectedHistory(DateTime dt) : datetime(dt), ary(0) {}
};

typedef Array<CollectedHistory> CollectedHistoryArray;

// 出力・応答共有 : 1時間毎にファイル出力

class CollectedStore {
private:
  CollectedValueArray *value;
  CollectedHistoryArray *history;
public:
  CollectedValue& valueOf(int k) const { return (*value)[k]; }
  CollectedHistory& historyOf(int k) const { return (*history)[k]; }
  CollectedStore() : value(0), history(0) {}
  CollectedStore(
	CollectedValueArray *v, CollectedHistoryArray *h
	) : value(v), history(h) {}
};

// ビットベクタ
class BitVector {
private:
  uint32_t val;
  static const uint32_t mask[];
public:
  void set  (int n) { val |= mask[n]; }
  void reset(int n) { val &= ~mask[n]; }
  uint32_t getval() { return val; }

  BitVector() : val(0) {}

  std::string str() {
	static char b[10];
	int v=val;
	for (int i=0;i<8;i++) {
	  b[i] = (v&mask[i])?'*':'-';
	}
	b[8] = 0;
	return std::string(b);
  }
};

// 応答
class CheckedRequest {
private:
  static const uint32_t mask[];
public:
  DateTime begin;
  DateTime end;
  uint32_t interval; // sec
  BitVector vec16; // 収集するセンサ番号のビットベクタ
  BitVector vec01; // 同上

  void setvec16(int k)   {vec16.set(k); }
  void setvec01(int k)   {vec01.set(k); }
  void resetvec16(int k) {vec16.reset(k);}
  void resetvec01(int k) {vec01.reset(k);}

  CheckedRequest() {}
  CheckedRequest(DateTime &b,DateTime &e,uint32_t v) :
	begin(b), end(e), interval(v) {}
};

class FilteredCollectedStore {
private:
  CollectedStore *value;
  std::string message;
public:
  FilteredCollectedStore() : value(0),message("") {}
};
