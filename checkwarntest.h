#pragma once

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace std;

class checkwarntest : public CPPUNIT_NS :: TestFixture
{
	CPPUNIT_TEST_SUITE (checkwarntest);
	CPPUNIT_TEST (test11);
	CPPUNIT_TEST (test12);
	CPPUNIT_TEST (test13);
	CPPUNIT_TEST (test21);
	CPPUNIT_TEST (test22);
	CPPUNIT_TEST (test23);
	CPPUNIT_TEST (test31);
	CPPUNIT_TEST (test32);
	CPPUNIT_TEST (test33);
	CPPUNIT_TEST_SUITE_END ();

	public:
		void setUp (void);
		void tearDown (void);

	protected:
		void test11 (void);
		void test12 (void);
		void test13 (void);
		void test21 (void);
		void test22 (void);
		void test23 (void);
		void test31 (void);
		void test32 (void);
		void test33 (void);

	private:
	// add private values
};
