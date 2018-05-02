/*
 * acc_test.c 
 * This is a script to unittest max.c using the CUnit interface.
 * The command to run the script is the following
 * 
 * gcc -Wall -c AccelerationMagnitude.c main.c 
 * gcc -Wall -L/usr/local/lib -o acc_test acc_test.c acc.o -lcunit
 *
*/


#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"
//#include "CUnit/Automated.h"
//#include "CUnit/Console.h"

#include <stdio.h>
#include <stdlib.h>

#include "AccelerationMagnitude.h"
#include "DataLoader.h"

/* Test Suite setup and cleanup functions: */

int init_suite(void)
{
  return 0;
}
int clean_suite(void)
{
  return 0;
}

/************* Test case functions ****************/

void magnitude_of_6_3_2_is_7(void) {
  CU_ASSERT_EQUAL(calculateMagnitude(6, 3, 2) , 7);
}

void initialize_struct_accelerometer(void) {
  Signal signal_arr[1] = {
    {.t = 10, .x=6., .y=3., .z=2.}
  };  
  CU_ASSERT_EQUAL( signal_arr[0].t , 10);
  CU_ASSERT_EQUAL( signal_arr[0].x , 6);
  CU_ASSERT_EQUAL( signal_arr[0].y , 3);
  CU_ASSERT_EQUAL( signal_arr[0].z , 2);
}

void spatial_data_is_commutative_for_magnitude(void) {
  CU_ASSERT_EQUAL(calculateMagnitude(3, 6, 2), calculateMagnitude(6, 2, 3));
}

void length_of_accelerometer_struct(void){
  Signal signal_arr[2] = {
    {.t = 10, .x=6., .y=3., .z=2.},
    {.t = 10, .x=6., .y=3., .z=2.}
  };
  size_t length = sizeof(signal_arr)/sizeof(signal_arr[0]);
  CU_ASSERT_EQUAL(length , 2);
}

void readCSV_line15(void) {
  Signal signal_arr[7024];
  char filepath[20];
  strcpy(filepath, "data/AccData.csv");
  readCSV(filepath, signal_arr, 0, 7024);
  CU_ASSERT_EQUAL( signal_arr[14].t , 141);
  CU_ASSERT_EQUAL( signal_arr[14].x , 1031.25);
  CU_ASSERT_EQUAL( signal_arr[14].y , 31.25);
  CU_ASSERT_EQUAL( signal_arr[14].z , -62.5);
}

void repeat_magnitude_calculation_should_not_change_result(void) {
  double mag_a[7024];
  double mag_b[7024];
  char filepath[20];
  strcpy(filepath, "data/AccData.csv");

  calculateMagnitudeFromCSV(filepath, mag_a, 7024, 1);

  calculateMagnitudeFromCSV(filepath, mag_b, 7024, 1);
  calculateMagnitudeFromCSV(filepath, mag_b, 7024, 1);

  CU_ASSERT_DOUBLE_EQUAL( mag_a[1], 1003.9, 0.1);
  CU_ASSERT_EQUAL( mag_a[1], mag_b[1]);
  CU_ASSERT_EQUAL( mag_a[500], mag_b[500]);
  CU_ASSERT_EQUAL( mag_a[3000], mag_b[3000]);
  CU_ASSERT_EQUAL( mag_a[3001], mag_b[3001]);
  CU_ASSERT_EQUAL( mag_a[3500], mag_b[3500]);
  CU_ASSERT_EQUAL( mag_a[4000], mag_b[4000]);
  CU_ASSERT_EQUAL( mag_a[6000], mag_b[6000]);
}

void calculateMagnitudeFromCSV_tested_with_differnt_nsplits(void) {
  double a[7024];
  double b[7024];
  double c[7024];
  char filepath[20];
  strcpy(filepath, "data/AccData.csv");

  calculateMagnitudeFromCSV(filepath, a, 7024, 1);
  calculateMagnitudeFromCSV(filepath, b, 7024, 5);
  calculateMagnitudeFromCSV(filepath, c, 7024, 50);

  CU_ASSERT_DOUBLE_EQUAL( a[1], 1003.9, 0.1);
  CU_ASSERT_DOUBLE_EQUAL( a[1], b[1], 0.1);
  CU_ASSERT_DOUBLE_EQUAL( a[1], b[1], 0.1);

  CU_ASSERT_DOUBLE_EQUAL( a[300], 1032.2, 0.1);
  CU_ASSERT_DOUBLE_EQUAL( a[300], b[300], 0.1);
  CU_ASSERT_DOUBLE_EQUAL( b[300], c[300], 0.1);

  CU_ASSERT_DOUBLE_EQUAL( a[6000], 897.588, 0.1);
  CU_ASSERT_DOUBLE_EQUAL( a[6000], b[6000], 0.1);
  CU_ASSERT_DOUBLE_EQUAL( b[6000], c[6000], 0.1);

  CU_ASSERT_DOUBLE_EQUAL( a[7023], 1033.61, 0.1);
  CU_ASSERT_DOUBLE_EQUAL( a[7023], b[7023], 0.1);
  CU_ASSERT_DOUBLE_EQUAL( b[7023], c[7023], 0.1);
}

/************* Test Runner Code goes here **************/

int main ( void ){
   CU_pSuite pSuite = NULL;
   /* initialize the CUnit test registry */
   if ( CUE_SUCCESS != CU_initialize_registry() )
      return CU_get_error();

   /* add a suite to the registry */
   pSuite = CU_add_suite( "csv_reader_test_suite", init_suite, clean_suite );
   if ( NULL == pSuite ) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* add the tests to the suite */
   if ( (NULL == CU_add_test(pSuite, "magnitude_of_6_3_2_is_7", magnitude_of_6_3_2_is_7)) ||
        (NULL == CU_add_test(pSuite, "initialize_struct_accelerometer", initialize_struct_accelerometer)) ||
        (NULL == CU_add_test(pSuite, "spatial_data_is_commutative_for_magnitude", spatial_data_is_commutative_for_magnitude)) ||
        (NULL == CU_add_test(pSuite, "length_of_accelerometer_struct", length_of_accelerometer_struct)) ||
        (NULL == CU_add_test(pSuite, "readCSV_line15", readCSV_line15)) |
        (NULL == CU_add_test(pSuite, "repeat_magnitude_calculation_should_not_change_result", repeat_magnitude_calculation_should_not_change_result)) ||
        (NULL == CU_add_test(pSuite, "calculateMagnitudeFromCSV_tested_with_differnt_nsplits", calculateMagnitudeFromCSV_tested_with_differnt_nsplits))  
      )
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // Run all tests using the basic interface
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   printf("\n");
   CU_basic_show_failures(CU_get_failure_list());
   printf("\n\n");
/*
   // Run all tests using the automated interface
   CU_automated_run_tests();
   CU_list_tests_to_file();

   // Run all tests using the console interface
   CU_console_run_tests();
*/
   /* Clean up registry and return */
   CU_cleanup_registry();
   return CU_get_error();
}