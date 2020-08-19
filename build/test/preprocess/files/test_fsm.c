#include "build/temp/_test_fsm.c"
#include "src/serialfunctions.h"
#include "/var/lib/gems/2.5.0/gems/ceedling-0.30.0/vendor/unity/src/unity.h"


serialdata_t serialdata;



void setUp(void){



}













void test_setup_puerto_serie(void){

    SerialDataInit(&serialdata);

    UnityAssertEqualNumber((UNITY_INT)((

   0

   )), (UNITY_INT)((serialdata.newData)), (

   ((void *)0)

   ), (UNITY_UINT)(17), UNITY_DISPLAY_STYLE_INT);

}
