#include <iostream>
#include <sstream>

#include "checkwarn.h"

inline int checkArg(bool f, int r)
{
	return (f) ? r : 0;
}

// 使い方
// errno = checkwarn(...);
// result = writeWarn(errno,...);
int checkwarn(const Warn& inwarn, const RawValue& invalue)
{
	int16_t v = invalue.getv16(0);
	Condition *c = inwarn.getCondition();
	int16_t a = c->arg;
	int16_t o = c->op;

	switch (o){
		case 1: checkArg(v>a , errnoGT);break;
		case 2: checkArg(v==a, errnoEQ);break;
		case 3: checkArg(v<a , errnoLT);break;
		default: break;
	}
}

// 使い方
// 
int writeWarn(int errno, const RawValue& invalue, WarnValue& outvalue)
{
	if (errno > 0){
		string str = messages[errno];
		outvalue.message = str;
	} else {
//		outvalueを生成
	}
	return 0;
}
