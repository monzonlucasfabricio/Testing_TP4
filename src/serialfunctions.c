#include "serialfunctions.h"

const char *lightson = "LON+ID";
const char *lightsoff = "LOFF+ID";
const char *working = "W+ID";
const char *notworking = "NW+ID";
const char *automatic = "AUT+ID";
const char *manual = "MAN+ID";

bool SerialDataInit(serialdata_t *serialdata)
{
    serialdata->newData = false;
    return true;
}

uint8_t RecvData(char *data, serialdata_t *serialdata)
{
    uint8_t op = 0;
    if (strcmp(serialdata->startMarker, data) == 0)
    {
        printf("RECIBI SOM\r\n");
        op = SOM_OP;
    }
    else if (strcmp(serialdata->endMarker, data) == 0)
    {
        printf("RECIBI EOM\r\n");
        op = EOM_OP;
    }
    return op;
}

bool AcumData(uint8_t op, char *data, serialdata_t *serialdata)
{
    static uint8_t index;
    static bool recvInProgress = false;
    bool ret;

    if (op == SOM_OP && recvInProgress == false)
    {
        recvInProgress = true;
        index = 0;
        ret = false;
    }
    if (op == EOM_OP && recvInProgress == true)
    {
        serialdata->receivedChars[index] = '\0';
        recvInProgress = false;
        serialdata->newData = true;
        index = 0;
        ret = true;
    }
    if (op == 0 && recvInProgress == true && op != EOM_OP)
    {
        serialdata->receivedChars[index] = *data;
        index++;
        if (index >= NUMCHARS)
        {
            index = NUMCHARS - 1;
        }
        ret = false;
    }
    return ret;
}

uint8_t CompareStrings(serialdata_t *serialdata)
{
    uint8_t option = 0;
    if (strcmp(serialdata->receivedChars, lightsoff) == 0)
    {
        option = 1;
    }
    else if (strcmp(serialdata->receivedChars, lightson) == 0)
    {
        option = 2;
    }
    else if (strcmp(serialdata->receivedChars, notworking) == 0)
    {
        option = 3;
    }
    else if (strcmp(serialdata->receivedChars, working) == 0)
    {
        option = 4;
    }
    else if (strcmp(serialdata->receivedChars, automatic) == 0)
    {
        option = 5;
    }
    else if (strcmp(serialdata->receivedChars, manual) == 0)
    {
        option = 6;
    }
    serialdata->newData = false;
    return option;
}
