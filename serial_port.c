include "serial_port.h"

    void serial_configure_baud_rate(unsigned short com, unsigned short divisor)
    {
        outb(SERIAL_LINE_COMMAND_PORT(com),
             SERIAL_LINE_ENABLE_DLAB);
        outb(SERIAL_DATA_PORT(com),
             (divisor >> 8) & 0x00FF);
        outb(SERIAL_DATA_PORT(com),
             divisor & 0x00FF);
    }
    
     
    
  /** serial_configure_line:
     *  Configures the line of the given serial port. The port is set to have a
     *  data length of 8 bits, no parity bits, one stop bit and break control
     *  disabled.
     *
     *  @param com  The serial port to configure
     */
    void serial_configure_line(unsigned short com)
    {
        /* Bit:     | 7 | 6 | 5 4 3 | 2 | 1 0 |
         * Content: | d | b | prty  | s | dl  |
         * Value:   | 0 | 0 | 0 0 0 | 0 | 1 1 | = 0x03
         */
        outb(SERIAL_LINE_COMMAND_PORT(com), 0x03);
    }
    
/** serial_configure_line:
     *  Configures the line of the given serial port. The port is set to have a
     *  data length of 8 bits, no parity bits, one stop bit and break control
     *  disabled.
     *
     *  @param com  The serial port to configure
     */
    
void serial_configure_fifo_buffer(unsigned short com)
    {
        /* Bit:     | 7 | 6 | 5 4 3 | 2 | 1 0 |
         * Content: | d | b | prty  | s | dl  |
         * Value:   | 0 | 0 | 0 0 0 | 0 | 1 1 | = 0x03
         */
        outb(SERIAL_FIFO_COMMAND_PORT(com), 0xC7);
    } 

 void serial_configure_modem(unsigned short com)
    {
        /* Bit:     | 7 | 6 | 5 4 3 | 2 | 1 0 |
         * Content: | d | b | prty  | s | dl  |
         * Value:   | 0 | 0 | 0 0 0 | 0 | 1 1 | = 0x03
         */
        outb(SERIAL_MODEM_COMMAND_PORT(com),  0x03);
    } 
   
 int serial_is_transmit_fifo_empty(unsigned int com)
    {
        /* 0x20 = 0010 0000 */
        return inb(SERIAL_LINE_STATUS_PORT(com)) & 0x20;
    }   
    
void serial_write_byte(unsigned short port, char byteData) {
  	outb(port, byteData);
}  
    
 void serial_configure(unsigned short port , unsigned int baudRate){
 	serial_configure_baud_rate(port , baudRate) ;
 	serial_configure_line(port) ;
 	serial_configure_fifo_buffer(port) ;
 	serial_configure_modem(port) ;
 }
 
 void serial_write(unsigned short com , char *buf , unsigned short len){
 	unsigned int i = 0 ;
 	
 	while(i < len){
 		if(serial_is_transmit_fifo_empty(com)){
 			*buf = *(buf+i)  ;
 			serial_write_byte(com , *buf) ;
 			i++ ;
 		}
 	}
 }
