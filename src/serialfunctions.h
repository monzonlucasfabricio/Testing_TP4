#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#define NUMCHARS 50     //!< Number of characters for the Char received on Serial port */
#define SOM_OP 1
#define EOM_OP 2

typedef struct serialdata_t{
    bool            newData;
    char*           startMarker;
    char*           endMarker;
    char            rc;
    char            receivedChars[NUMCHARS];
}serialdata_t;

uint8_t CompareStrings(serialdata_t* serialdata);
uint8_t RecvData(char* data,serialdata_t* serialdata);
bool AcumData(uint8_t op,char* data,serialdata_t* serialdata);
bool SerialDataInit(serialdata_t *serialdata);