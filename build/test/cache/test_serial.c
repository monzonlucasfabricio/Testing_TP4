#include "build/temp/_test_serial.c"
#include "src/serialfunctions.h"
#include "/var/lib/gems/2.5.0/gems/ceedling-0.30.0/vendor/unity/src/unity.h"
serialdata_t serialdata;



void setUp(void)

{

    

   _Bool 

        retval = SerialDataInit(&serialdata);

    serialdata.startMarker = "<";

    serialdata.endMarker = ">";

    memset(serialdata.receivedChars, 0,sizeof(serialdata.receivedChars));

}















void test_setup_puerto_serie(void)

{

    printf("1)Test de inicio de la variable newData\r\n");

    UnityAssertEqualNumber((UNITY_INT)((

   0

   )), (UNITY_INT)((serialdata.newData)), (

   ((void *)0)

   ), (UNITY_UINT)(33), UNITY_DISPLAY_STYLE_INT);

}





void test_recibo_char_SOM(void)

{

    printf("2)Test de validacion de SOM\r\n");

    uint8_t ret;

    char *val = "<";

    ret = RecvData(val, &serialdata);

    UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((ret)), (

   ((void *)0)

   ), (UNITY_UINT)(43), UNITY_DISPLAY_STYLE_INT);

}





void test_recibo_char_EOM(void)

{

    printf("3)Test de validacion de EOM\r\n");

    uint8_t ret;

    char *val = ">";

    ret = RecvData(val, &serialdata);

    UnityAssertEqualNumber((UNITY_INT)((2)), (UNITY_INT)((ret)), (

   ((void *)0)

   ), (UNITY_UINT)(53), UNITY_DISPLAY_STYLE_INT);

}





void test_recibo_char_otro(void)

{

    printf("4)Test recibo cualquier dato\r\n");

    uint8_t ret;

    char *val = "l";

    ret = RecvData(val, &serialdata);

    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((ret)), (

   ((void *)0)

   ), (UNITY_UINT)(63), UNITY_DISPLAY_STYLE_INT);

}





void test_recibo_cualquier_mensaje(void)

{

    printf("5)Test recibo mensaje\r\n");





    char *val = "<";

    uint8_t ret = RecvData(val, &serialdata);

    

   _Bool 

        retacum = AcumData(ret, val, &serialdata);

    UnityAssertEqualNumber((UNITY_INT)((

   0

   )), (UNITY_INT)((retacum)), (

   ((void *)0)

   ), (UNITY_UINT)(75), UNITY_DISPLAY_STYLE_INT);





    char *val1 = "k";

    uint8_t ret1 = RecvData(val1, &serialdata);

    

   _Bool 

        retacum1 = AcumData(ret1, val1, &serialdata);

    UnityAssertEqualNumber((UNITY_INT)((

   0

   )), (UNITY_INT)((retacum1)), (

   ((void *)0)

   ), (UNITY_UINT)(81), UNITY_DISPLAY_STYLE_INT);





    char *val2 = ">";

    uint8_t ret2 = RecvData(val2, &serialdata);

    

   _Bool 

        retacum2 = AcumData(ret2, val2, &serialdata);

    UnityAssertEqualNumber((UNITY_INT)((

   1

   )), (UNITY_INT)((retacum2)), (

   ((void *)0)

   ), (UNITY_UINT)(87), UNITY_DISPLAY_STYLE_INT);





    UnityAssertEqualString((const char*)(("k")), (const char*)((serialdata.receivedChars)), (

   ((void *)0)

   ), (UNITY_UINT)(90));

}





void test_recibir_comando(void)

{

    printf("6)Test recibo comando\r\n");

    serialdata.newData = 

                        0

                             ;

    char *comando = "<LON+ID>";

    for (uint8_t i = 0; i < strlen(comando); i++)

    {

        uint16_t c = comando[i] + '\0';

        printf("%i)%s\r\n",i,&c);

        uint8_t ret = RecvData(&c, &serialdata);

        

       _Bool 

            retacum = AcumData(ret, &c, &serialdata);

    }

    UnityAssertEqualString((const char*)(("LON+ID")), (const char*)((serialdata.receivedChars)), (

   ((void *)0)

   ), (UNITY_UINT)(106));

}





void test_recibir_comando_opcion(void)

{

    printf("7)Test recibo comando opcion\r\n");

    serialdata.newData = 

                        0

                             ;

    char *comando = "<LOFF+ID>";

    for (uint8_t i = 0; i < strlen(comando); i++)

    {

        uint16_t c = comando[i] + '\0';

        printf("%i)%s\r\n",i,&c);

        uint8_t ret = RecvData(&c, &serialdata);

        

       _Bool 

            retacum = AcumData(ret, &c, &serialdata);

    }

    UnityAssertEqualString((const char*)(("LOFF+ID")), (const char*)((serialdata.receivedChars)), (

   ((void *)0)

   ), (UNITY_UINT)(122));





    uint8_t retCom = CompareStrings(&serialdata);

    UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((retCom)), (

   ((void *)0)

   ), (UNITY_UINT)(126), UNITY_DISPLAY_STYLE_INT);

}
