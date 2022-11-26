#define BOOST_TEST_MODULE BinaryTreeDict_Tests
#include <boost/test/included/unit_test.hpp>

// // Uncomment the below macros enable dynamic linking.
// // You will also need to comment-out the `single-header' macros above.
#define BOOST_TEST_DYN_LINK \
#define BOOST_TEST_MODULE BinaryTreeDict_Tests
#include <boost/test/unit_test.hpp>

////////////////////////////////////////////////////////////////////////////////

#include <string>
#include "BinaryTreeDict.h"

////////////////////////////////////////////////////////////////////////////////

// Utility Functions

void isPresent(BinaryTreeDict & dict, int k, std::string i)
{
    std::string* p_i = dict.lookup(k);
    BOOST_CHECK_MESSAGE(p_i, std::to_string(k) + " is missing");
    if (p_i)
    {
        BOOST_CHECK_MESSAGE(*p_i == i,
                            std::to_string(k) + " should be " + i + ", but found " + *p_i);
    }
}

void isAbsent(BinaryTreeDict & dict, int k)
{
    BOOST_CHECK_MESSAGE(dict.lookup(k) == nullptr,
                        std::to_string(k) + " should be absent, but is present.");
}

void insertTestData(BinaryTreeDict & dict)
{
    dict.insert(22,"Jane");
    dict.insert(22,"Mary");
    dict.insert(0,"Harold");
    dict.insert(9,"Edward");
    dict.insert(37,"Victoria");
    dict.insert(4,"Matilda");
    dict.insert(26,"Oliver");
    dict.insert(42,"Elizabeth");
    dict.insert(19,"Henry");
    dict.insert(4,"Stephen");
    dict.insert(24,"James");
    dict.insert(-1,"Edward");
    dict.insert(31,"Anne");
    dict.insert(23,"Elizabeth");
    dict.insert(1,"William");
    dict.insert(26,"Charles");
}

////////////////////////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_SUITE( Lookup_Insert_Tests )

    BOOST_AUTO_TEST_CASE( EmptyLookup )
    {
        BinaryTreeDict dict;
        isAbsent(dict,1);
    }

    BOOST_AUTO_TEST_CASE( SingleInsert )
    {
        BinaryTreeDict dict;
        dict.insert(22,"Mary");
    }

    BOOST_AUTO_TEST_CASE( SingleInsertLookup )
    {
        BinaryTreeDict dict;
        dict.insert(22,"Mary");
        isPresent(dict,22,"Mary");
    }

    BOOST_AUTO_TEST_CASE( SingleOverwriteLookup )
    {
        BinaryTreeDict dict;
        dict.insert(22,"Jane");
        dict.insert(22,"Mary");
        isPresent(dict,22,"Mary");
    }

    BOOST_AUTO_TEST_CASE( MultipleInsert )
    {
        BinaryTreeDict dict;
        insertTestData(dict);
    }

    BOOST_AUTO_TEST_CASE( MultipleInsertLookupPresent )
    {
        BinaryTreeDict dict;
        insertTestData(dict);

        isPresent(dict,22,"Mary");
        isPresent(dict,4,"Stephen");
        isPresent(dict,9,"Edward");
        isPresent(dict,1,"William");
        isPresent(dict,0,"Harold");
        isPresent(dict,24,"James");
        isPresent(dict,26,"Charles");
        isPresent(dict,19,"Henry");
        isPresent(dict,31,"Anne");
        isPresent(dict,23,"Elizabeth");
        isPresent(dict,37,"Victoria");
        isPresent(dict,42,"Elizabeth");
        isPresent(dict,-1,"Edward");
    }

    BOOST_AUTO_TEST_CASE( MultipleInsertLookupAbsent )
    {
        BinaryTreeDict dict;
        insertTestData(dict);

        isAbsent(dict,2);
        isAbsent(dict,3);
        isAbsent(dict,-4);
        isAbsent(dict,56);
        isAbsent(dict,30);
    }

BOOST_AUTO_TEST_SUITE_END()

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_SUITE( Move_Constructor_Tests )

    BOOST_AUTO_TEST_CASE( MoveConstructorFullyMoves )
    {
        BinaryTreeDict dict1;
        insertTestData(dict1);

        BinaryTreeDict dict2(std::move(dict1));

        isPresent(dict2,22,"Mary");
        isPresent(dict2,4,"Stephen");
        isPresent(dict2,9,"Edward");
        isPresent(dict2,1,"William");
        isPresent(dict2,0,"Harold");
        isPresent(dict2,24,"James");
        isPresent(dict2,26,"Charles");
        isPresent(dict2,19,"Henry");
        isPresent(dict2,31,"Anne");
        isPresent(dict2,23,"Elizabeth");
        isPresent(dict2,37,"Victoria");
        isPresent(dict2,42,"Elizabeth");
        isPresent(dict2,-1,"Edward");
    }

    BOOST_AUTO_TEST_CASE( MoveConstructorSteals )
    {
        BinaryTreeDict* dictPtr;
        {
            BinaryTreeDict dict1;
            insertTestData(dict1);

            dictPtr = new BinaryTreeDict(std::move(dict1));

            isAbsent(dict1,22);
            isAbsent(dict1,4);
            isAbsent(dict1,9);
            isAbsent(dict1,1);
            isAbsent(dict1,0);
            isAbsent(dict1,24);
            isAbsent(dict1,26);
            isAbsent(dict1,19);
            isAbsent(dict1,31);
            isAbsent(dict1,23);
            isAbsent(dict1,37);
            isAbsent(dict1,42);
            isAbsent(dict1,-1);

            // dict1 gets deleted here
        }

        isPresent(*dictPtr,22,"Mary");
        isPresent(*dictPtr,4,"Stephen");
        isPresent(*dictPtr,9,"Edward");
        isPresent(*dictPtr,1,"William");
        isPresent(*dictPtr,0,"Harold");
        isPresent(*dictPtr,24,"James");
        isPresent(*dictPtr,26,"Charles");
        isPresent(*dictPtr,19,"Henry");
        isPresent(*dictPtr,31,"Anne");
        isPresent(*dictPtr,23,"Elizabeth");
        isPresent(*dictPtr,37,"Victoria");
        isPresent(*dictPtr,42,"Elizabeth");
        isPresent(*dictPtr,-1,"Edward");

        delete dictPtr;
    }

BOOST_AUTO_TEST_SUITE_END()

////////////////////////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_SUITE( Copy_Assignment_Tests )

    BOOST_AUTO_TEST_CASE( CopyAssignmentFullyCopies )
    {
        BinaryTreeDict dict1;
        insertTestData(dict1);

        BinaryTreeDict dict2;
        dict2 = dict1;

        isPresent(dict2,22,"Mary");
        isPresent(dict2,4,"Stephen");
        isPresent(dict2,9,"Edward");
        isPresent(dict2,1,"William");
        isPresent(dict2,0,"Harold");
        isPresent(dict2,24,"James");
        isPresent(dict2,26,"Charles");
        isPresent(dict2,19,"Henry");
        isPresent(dict2,31,"Anne");
        isPresent(dict2,23,"Elizabeth");
        isPresent(dict2,37,"Victoria");
        isPresent(dict2,42,"Elizabeth");
        isPresent(dict2,-1,"Edward");
    }

    BOOST_AUTO_TEST_CASE( CopyAssignmentOverwrites )
    {
        BinaryTreeDict dict1;
        insertTestData(dict1);

        BinaryTreeDict dict2;
        dict2.insert(22,"Jane");
        dict2.insert(2,"William");

        dict1 = dict2;

        isAbsent(dict1,4);
        isAbsent(dict1,9);
        isAbsent(dict1,1);
        isAbsent(dict1,0);
        isAbsent(dict1,24);
        isAbsent(dict1,26);
        isAbsent(dict1,19);
        isAbsent(dict1,31);
        isAbsent(dict1,23);
        isAbsent(dict1,37);
        isAbsent(dict1,42);
        isAbsent(dict1,-1);

        isPresent(dict1,2,"William");
        isPresent(dict1,22,"Jane");
    }

    BOOST_AUTO_TEST_CASE( CopyAssignmentDoesNotReverseCopy )
    {
        BinaryTreeDict dict1;
        insertTestData(dict1);

        BinaryTreeDict dict2;

        dict2.insert(22,"Jane");
        dict2.insert(2,"William");

        dict2 = dict1;

        isAbsent(dict1,2);
    }

    BOOST_AUTO_TEST_CASE( CopyAssignmentIsDeep )
    {
        BinaryTreeDict dict1;
        insertTestData(dict1);

        BinaryTreeDict dict2;
        dict2 = dict1;

        dict1.insert(2,"William");
        isPresent(dict1,2,"William");
        isAbsent(dict2,2);

        dict2.insert(3,"Henry");
        isPresent(dict2,3,"Henry");
        isAbsent(dict1,3);

        //dict1.remove(24);
        isAbsent(dict1,24);
        isPresent(dict2,24,"James");

        //dict2.remove(26);
        isAbsent(dict2,26);
        isPresent(dict1,26,"Charles");
    }


    BOOST_AUTO_TEST_CASE( CopySelfAssignment )
    {
        BinaryTreeDict dict;
        insertTestData(dict);

        dict = dict;
        isPresent(dict,24,"James");
        isPresent(dict,26,"Charles");
        isAbsent(dict,2);
    }

BOOST_AUTO_TEST_SUITE_END()

////////////////////////////////////////////////////////////////////////////////