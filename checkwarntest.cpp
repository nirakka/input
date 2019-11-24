#include <iostream>
#include <sstream>

#include "checkwarn.h"
#include "checkwarntest.h"

CPPUNIT_TEST_SUITE_REGISTRATION (checkwarntest);

static Condition cond01 = Condition(X(1),3000,1); // >
static Condition cond02 = Condition(X(1),3000,2); // ==
static Condition cond03 = Condition(X(1),3000,3); // <

static Action act = Action(B(1),1);
static Warn inwarn01(&cond01,&act);
static Warn inwarn02(&cond02,&act);
static Warn inwarn03(&cond03,&act);

// 要素0は使用せず
static Warn*      inwarnTbl[]  = { 0, &inwarn01, &inwarn02, &inwarn03 };
static uint8_t  a01[] = { 0, 0, 0, 0};
static uint16_t a16_01[] = { 2500, 0, 0, 0 };
static uint16_t a16_02[] = { 3000, 0, 0, 0 };
static uint16_t a16_03[] = { 3500, 0, 0, 0 };

static RawValue invalue01(a01, a16_01);
static RawValue invalue02(a01, a16_02);
static RawValue invalue03(a01, a16_03);

static RawValue *values01[] = { 0, &invalue01, &invalue02, &invalue03 };
static int      results01[] = { 0,          0,          0,    errnoGT };

static RawValue *values02[] = { 0, &invalue01, &invalue02, &invalue03 };
static int      results02[] = { 0,          0,    errnoEQ,          0 };

static RawValue *values03[] = { 0, &invalue01, &invalue02, &invalue03 };
static int      results03[] = { 0,    errnoLT,          0,          0 };

// 2次元の表
static RawValue** invalueTbl[] = { 0, values01,  values02,  values03  };
static int*	      resultsTbl[] = { 0, results01, results02, results03 };

void checkwarntest :: setUp (void)
{
	// set up test environment (initializing objects)
}

void checkwarntest :: tearDown (void) 
{
	// finally delete objects
}

inline void testXY(int x,int y)
{
  CPPUNIT_ASSERT_EQUAL ( resultsTbl[x][y], checkwarn(*inwarnTbl[x], *invalueTbl[x][y]));
}

void checkwarntest :: test11 (void) { testXY(1,1); }
void checkwarntest :: test12 (void) { testXY(1,2); }
void checkwarntest :: test13 (void) { testXY(1,3); }
void checkwarntest :: test21 (void) { testXY(2,1); }
void checkwarntest :: test22 (void) { testXY(2,2); }
void checkwarntest :: test23 (void) { testXY(2,3); }
void checkwarntest :: test31 (void) { testXY(3,1); }
void checkwarntest :: test32 (void) { testXY(3,2); }
void checkwarntest :: test33 (void) { testXY(3,3); }