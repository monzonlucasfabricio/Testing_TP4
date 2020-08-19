#include "unity.h"
#include "serialfunctions.h"

#define LONCMD "<LON+ID>"
#define LOFFCMD "<LOFF+ID>"

/*
*   Recibo un char y comparo si es un SOM o EOM
*   Recibo un char y lo voy acumulando en un buffer si no es SOM o EOM
*   Comparo el buffer completo que recibi con un string
*   Recibo un uint8_t que debe ser una opcion
*/

serialdata_t serialdata;

void setUp(void)
{
    bool retval = SerialDataInit(&serialdata);
    serialdata.startMarker = "<";
    serialdata.endMarker = ">";
    memset(serialdata.receivedChars, 0,sizeof(serialdata.receivedChars));
}

/*void test_falla(void){
    TEST_FAIL_MESSAGE("Ceedling esta en funcionamiento"); //Prueba de funcionamiento
}
*/

/* Test de prueba de inicializacion */
void test_setup_puerto_serie(void)
{
    printf("1)Test de inicio de la variable newData\r\n");
    TEST_ASSERT_EQUAL(false, serialdata.newData);
}

/* Test de recepcion de un Start of message */
void test_recibo_char_SOM(void)
{
    printf("2)Test de validacion de SOM\r\n");
    uint8_t ret;
    char *val = "<";
    ret = RecvData(val, &serialdata);
    TEST_ASSERT_EQUAL(1, ret);
}

/* Test de recepcion de un End of message */
void test_recibo_char_EOM(void)
{
    printf("3)Test de validacion de EOM\r\n");
    uint8_t ret;
    char *val = ">";
    ret = RecvData(val, &serialdata);
    TEST_ASSERT_EQUAL(2, ret);
}

/* Test de recepcion de cualquier caracter */
void test_recibo_char_otro(void)
{
    printf("4)Test recibo cualquier dato\r\n");
    uint8_t ret;
    char *val = "l";
    ret = RecvData(val, &serialdata);
    TEST_ASSERT_EQUAL(0, ret);
}

/* Test de recepcion de un mensaje con SOM y EOM */
void test_recibo_cualquier_mensaje(void)
{
    printf("5)Test recibo mensaje\r\n");

    // Envio un SOM (START OF MESSAGE)
    char *val = "<";
    uint8_t ret = RecvData(val, &serialdata);
    bool retacum = AcumData(ret, val, &serialdata);
    TEST_ASSERT_EQUAL(false, retacum);

    // Envio un string cualquiera
    char *val1 = "k";
    uint8_t ret1 = RecvData(val1, &serialdata);
    bool retacum1 = AcumData(ret1, val1, &serialdata);
    TEST_ASSERT_EQUAL(false, retacum1);

    // Envio un EOM (END OF MESSAGE)
    char *val2 = ">";
    uint8_t ret2 = RecvData(val2, &serialdata);
    bool retacum2 = AcumData(ret2, val2, &serialdata);
    TEST_ASSERT_EQUAL(true, retacum2);

    // Comparo el buffer recibido
    TEST_ASSERT_EQUAL_STRING("k", serialdata.receivedChars);
}

/* Test de recepcion de un comando */
void test_recibir_comando(void)
{
    printf("6)Test recibo comando\r\n");
    serialdata.newData = false;
    char *comando = LONCMD;
    for (uint8_t i = 0; i < strlen(comando); i++)
    {
        uint16_t c = comando[i] + '\0';
        printf("%i)%s\r\n",i,&c);
        uint8_t ret = RecvData(&c, &serialdata);
        bool retacum = AcumData(ret, &c, &serialdata);
    }
    TEST_ASSERT_EQUAL_STRING("LON+ID", serialdata.receivedChars);
}


void test_recibir_comando_opcion(void)
{
    printf("7)Test recibo comando opcion\r\n");
    serialdata.newData = false;
    char *comando = LOFFCMD;
    for (uint8_t i = 0; i < strlen(comando); i++)
    {
        uint16_t c = comando[i] + '\0';
        printf("%i)%s\r\n",i,&c);
        uint8_t ret = RecvData(&c, &serialdata);
        bool retacum = AcumData(ret, &c, &serialdata);
    }
    TEST_ASSERT_EQUAL_STRING("LOFF+ID", serialdata.receivedChars);

    // Comparo el string recibido con la opcion 5
    uint8_t retCom = CompareStrings(&serialdata);
    TEST_ASSERT_EQUAL(1, retCom);
}