#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>

#include "globl.h"

/* sprintf(buf,"%08x") と等価 */
std::string fmt32(uint32_t v)
{
	std::stringstream ss;
	ss << std::hex << std::setw(8) << std::setfill('0') << v;
	return ss.str();
}

/* sprintf(buf,"%04x") と等価 */
std::string fmt16(uint16_t v)
{
	std::stringstream ss;
	ss << std::hex << std::setw(4) << std::setfill('0') << v;
	return ss.str();
}

static	SensorValueArray sva(10);
static	CounterArray ca(8);

// RawValue, CollectedValueも同一
void useSensorValue(void)
{
	SensorValue sv;
	sv.setv16(0,0x1000);
	sva[0] = sv;

	std::cout << std::string(__FUNCTION__) << ":";
	std::cout << fmt16(sva[0].getv16(0)) << std::endl;
}

void useCounter(void)
{
	Counter c0(10,3);
	ca[0] = c0;
	
	std::cout << std::string(__FUNCTION__) << ":";
	std::cout << fmt16(ca[0].preset ) << " ";	
	std::cout << fmt16(ca[0].current) << std::endl;
}

static	Collection col(X(1),10);
static	Condition cond(X(1),3000,1);
static	Action act(B(1),1);
static	Warn wa(&cond,&act);

static	CollectionArray cla(10);

static	RawValueArray rva(10);
static	WarnValueArray wva(10);

void useCollection(void)
{
	cla[0] = col;

	std::cout << std::string(__FUNCTION__) << ":";
	std::cout << fmt16(cla[0].sensor) << " ";
	std::cout << fmt16(cla[0].duration) << " # ";
	std::cout << cla[0].str() << std::endl;
}

void useCondition(void)
{
	std::cout << std::string(__FUNCTION__) << ":";
	std::cout << fmt16(cond.no) << " ";
	std::cout << fmt16(cond.arg) << " # ";
	std::cout << cond.str() << std::endl;
}

void useAction(void)
{
	std::cout << std::string(__FUNCTION__) << ":";
	std::cout << fmt16(act.no) << " ";
	std::cout << fmt16(act.arg) << " # " ;
	std::cout << act.str() << std::endl;
}

void useWarn(void)
{
	std::cout << std::string(__FUNCTION__) << ":";
	std::cout << fmt16(wa.getSensorNo()) << " ";
	std::cout << fmt16(wa.getSensorArg()) << " ";
	std::cout << fmt16(wa.getActuatorNo()) << " ";
	std::cout << fmt16(wa.getActuatorArg()) << " # ";
	std::cout << wa.str() << std::endl;
}

void useWarnValue(void)
{
	WarnValue wv(X(1),3400,B(1),1);
	wv.setWarn(&wa);
	wva[0] = wv;

	std::cout << std::string(__FUNCTION__) << ":";
	std::cout << fmt16(wva[0].cond.no) << " ";
	std::cout << fmt16(wva[0].cond.arg) << " " ;
	std::cout << fmt16(wva[0].act.no) << " ";
	std::cout << fmt16(wva[0].act.arg) << " # " ;
	std::cout << wva[0].str() << std::endl;
}

static	CollectedValueArray cva(10);
static	CollectedHistoryArray cha(10);

void useCollectedStore(void)
{
	DateTime dt0(Date(19,12,1),Time(12, 0,0));
	DateTime dt1(Date(19,12,1),Time(12,30,0));

	CollectedValue cv0(dt0);
	CollectedValue cv1(dt1);
	cv0.setv16(0,2000);
	cv1.setv16(0,4000);

	cva[0] = cv0; cva[1] = cv1;

	CollectedHistory ch0(dt0);
	CollectedHistory ch1(dt1);

	cha[0] = ch0; cha[1] = ch1;
	
	CollectedStore cs(&cva,&cha);

	std::cout << std::string(__FUNCTION__) << ":v[";
	std::cout << "X1=" << fmt16(cs.valueOf(0).getv16(0)) << " ";
	std::cout << "X1=" << fmt16(cs.valueOf(1).getv16(0)) << "] h[";
	std::cout << "time=" << cs.historyOf(0).getTime().str() << " ";
	std::cout << "time=" << cs.historyOf(1).getTime().str() << "]";
	std::cout << std::endl;
}

static	CheckedRequest cr;
static	FilteredCollectedStore fcs;

const uint32_t BitVector::mask[] =
	{ 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 };

void useCheckedRequest(void)
{
	DateTime dtB(Date(19,12,1),Time(12,30,0));
	DateTime dtE(Date(19,12,1),Time(13,50,0));
	CheckedRequest cr(dtB,dtE,600); // 10min

	cr.setvec16(0); // X1
	cr.setvec16(1); // X2
	
	std::cout << std::string(__FUNCTION__) << ":";
	std::cout << fmt32(cr.begin.getTime().getval()) << " ";
	std::cout << fmt32(cr.end.getTime().getval()) << " ";
	std::cout << fmt16(cr.interval) << " # ";
	std::cout << cr.vec16.str() << " ";
	std::cout << cr.vec01.str() << " ! ";

	cr.resetvec16(0); // reset X1
	std::cout << cr.vec16.str() << std::endl;
}

void useFilteredCollectedStore(void)
{

}

int main(void)
{
	useSensorValue();
	useCounter();
	useCollection();
	useCondition();
	useAction();
	useWarn();
	useWarnValue();
	useCollectedStore();
	useCheckedRequest();
	useFilteredCollectedStore();
}
