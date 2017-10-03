#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <modbus.h>

#define SLAVE_ID 1
#define REGISTERS_ADDRESS_START 20
#define REGISTERS_NB 10
#define INPUT_REGISTERS_ADDRESS 0
#define INPUT_REGISTERS_NB 10

static uint16_t INPUT_REGISTERS_TAB[10] = {110,112,113,114,115,116,117,118,119,120};

int main(void)
{
    int s = -1;
    modbus_t *context;
    modbus_mapping_t *mb_mapping;
    int rc;
    int i;
    uint8_t *query;

    context = modbus_new_rtu("/dev/ttyUSB0", 9600 , 'N' , 8 , 1);
    if(context == NULL){
    	fprintf(stderr, "unable to create the libmodbus context\n");
    	return -1;
    }

    query = malloc(MODBUS_RTU_MAX_ADU_LENGTH);

    /*mb_mapping = modbus_mapping_new(10,10,10,10);*/
    /* The first value of each array is accessible from the 0 address. */
	mb_mapping = modbus_mapping_new(/*BITS_ADDRESS + BITS_NB*/0,
                                	/*INPUT_BITS_ADDRESS + INPUT_BITS_NB*/ 0,
                                	REGISTERS_ADDRESS_START + REGISTERS_NB,
                                	INPUT_REGISTERS_ADDRESS + INPUT_REGISTERS_NB);

    if(mb_mapping == NULL){
    	fprintf(stderr, "Failed to allocate the mapping: %s\n",
                modbus_strerror(errno));
        modbus_free(context);
        return -1;
    }

    modbus_set_slave(context, SLAVE_ID);

    /*The value for the second parameter could be MODBUS_RTU_RS485 or MODBUS_RTU_RS232*/
    /*int serialSet = modbus_rtu_set_serial_mode(context,MODBUS_RTU_RS485);
    if(serialSet != 0){
    	fprintf(stderr, "Failed to connect serially %s\n",
                modbus_strerror(errno));
        modbus_free(context);
        return -1;
    }*/

    /*The second parameter can be either MODBUS_RTU_RTS_UP or MODBUS_RTU_RTS_DOWN*/
    /*modbus_rtu_set_rts(context, MODBUS_RTU_RTS_DOWN);*/

    for (i=0; i < INPUT_REGISTERS_NB; i++) {
        mb_mapping->tab_input_registers[i] = INPUT_REGISTERS_TAB[i];;
    }

    for (;;) {
        do {
            rc = modbus_receive(context, query);
            /* Filtered queries return 0 */
        } while (rc == 0);

        /* The connection is not closed on errors which require on reply such as
           bad CRC in RTU. */
        if (rc == -1 && errno != EMBBADCRC) {
            /* Quit */
            break;
        }

        rc = modbus_reply(context, query, rc, mb_mapping);
        if (rc == -1) {
            break;
        }
    }
}

    