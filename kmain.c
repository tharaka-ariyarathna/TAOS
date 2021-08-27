 /* The C function */
    #include "io.h"
    #include "multiboot.h"
    #include "memory_segments.h"
    #include "interrupts.h"
    #include "keyboard.h"
    #include "pic.h"
   
    int sum_of_three(int arg1, int arg2, int arg3)
    {
        return arg1 + arg2 + arg3;
    }
    
    #define FB_GREEN     2
    #define FB_DARK_GREY 8
    
     char *fb = (char *) 0x000B8000 ;
    
    /** fb_write_cell:
     *  Writes a character with the given foreground and background to position i
     *  in the framebuffer.
     *
     *  @param i  The location in the framebuffer
     *  @param c  The character
     *  @param fg The foreground color
     *  @param bg The background color
     */
    void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg)
    {
        fb[i] = c;
        fb[i + 1] = ((fg & 0x0F) << 4) | (bg & 0x0F) ;
    }
    

    /* The I/O ports */
    #define FB_COMMAND_PORT         0x3D4
    #define FB_DATA_PORT            0x3D5

    /* The I/O port commands */
    #define FB_HIGH_BYTE_COMMAND    14
    #define FB_LOW_BYTE_COMMAND     15

    /** fb_move_cursor:
     *  Moves the cursor of the framebuffer to the given position
     *
     *  @param pos The new position of the cursor
     */
    void fb_move_cursor(unsigned short pos)
    {
        outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
        outb(FB_DATA_PORT,    ((pos >> 8) & 0x00FF));
        outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
        outb(FB_DATA_PORT,    pos & 0x00FF);
    }
    
void fb_write(char *buf, unsigned int len ){
     	unsigned int i = 0 ; //To track *buf
     	while(i < len){
     		*buf = *(buf+i)  ;
     		fb_write_cell(i*2, *buf ,FB_GREEN , FB_DARK_GREY ) ;
     		i++ ;
     		fb_move_cursor(i) ;
     	}
     }		
    
    void kmain(unsigned int ebx){
    	//segments_install_gdt()  ;
    	//interrupts_install_idt() ;
    	
    	multiboot_info_t *mbinfo = (multiboot_info_t *) ebx;
	multiboot_module_t* modules = (multiboot_module_t*) mbinfo->mods_addr; 
	unsigned int address_of_module = modules->mod_start;
  	
  	if((mbinfo->mods_count) == 1){
  		char text[] = "Operation successful" ;
  		fb_write(text , sizeof(text)) ;
  		
  		typedef void (*call_module_t)(void);
        	/* ... */
        	call_module_t start_program = (call_module_t) address_of_module;
        	start_program();
        	/* we'll never get here, unless the module code returns */

  	}else{
  		char text[] = "Operation failed" ;
  		fb_write(text , sizeof(text)) ;
  	}
       
    }
    

    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
