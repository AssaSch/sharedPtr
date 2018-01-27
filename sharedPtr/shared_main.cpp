#include <stdio.h>
#include <string>
#include "SharedPtr.h"
#include "mu_test.h"
#include <exception>

using namespace std;

/*****************************************************************************/

UNIT(Ctor)
	
	SharedPtr<int> sp1(new int(5));
	
	ASSERT_THAT(*sp1 == 5);
	
END_UNIT

/*****************************************************************************/

UNIT(CopyCtor)
	
	SharedPtr<int> sp1(new int(5));
	SharedPtr<int> sp2(sp1);
	
	ASSERT_THAT(sp2 == sp1);
	
END_UNIT

/*****************************************************************************/

UNIT(equal)
	
	SharedPtr<int> sp1(new int(5));
	SharedPtr<int> sp2;
	
	sp2 = sp1;
	
	ASSERT_THAT(sp2 == sp1);
	
END_UNIT

/*****************************************************************************/

UNIT(not_equal)
	
	SharedPtr<int> sp1(new int(5));
	SharedPtr<int> sp2(new int(1));
	
	ASSERT_THAT(sp2 != sp1);
	
END_UNIT

/*****************************************************************************/

UNIT(Get_Raw_Ptr)
	
	SharedPtr<int> sp1(new int(5));
	int* ptr1 = sp1.GetRawPtr();
	
	ASSERT_THAT(*ptr1 == 5);
	
END_UNIT

/*****************************************************************************/

UNIT(Get_Count)
	
	SharedPtr<int> sp1(new int(5));
	SharedPtr<int> sp2(sp1);
	SharedPtr<int> sp3(sp1);
	
	ASSERT_THAT(sp3.GetCount() == 3);
	SharedPtr<int> sp4(new int(11));
	sp1 = sp4;
	ASSERT_THAT(sp3.GetCount() == 2);
	
END_UNIT

/*****************************************************************************/

UNIT(astrik)
	
	SharedPtr<int> sp1(new int(5));
	ASSERT_THAT(*sp1 == 5);
	SharedPtr<int> sp4(new int(11));
	ASSERT_THAT(*sp4 == 11);
	
END_UNIT

/*****************************************************************************/

UNIT(arrow)
	
	SharedPtr<string> sp1(new string("test"));
	
	ASSERT_THAT(! sp1->compare("test"));
	
END_UNIT

/*****************************************************************************/


/*****************************************************************************/
/*****************************************************************************/

TEST_SUITE(framework test)

	TEST(Ctor)
	TEST(CopyCtor)
	TEST(equal)
	TEST(not_equal)
	TEST(Get_Raw_Ptr)
	TEST(Get_Count)
	TEST(astrik)
	TEST(arrow)																			
		
END_SUITE

/*****************************************************************************/
/*****************************************************************************/
	
