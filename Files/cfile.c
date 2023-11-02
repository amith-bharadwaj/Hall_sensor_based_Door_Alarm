//#include <stdio.h>
//#include<stdlib.h>

int main() {

      //printf("entering main function\n");
      int control;
      int hall_sensor;
      int buzzer=0;
      int buzzer_reg = buzzer*4;
      int led=0;
      int led_reg = led*8;
      int mask = 0xFFFFFFF3;
      
      //int reg_check,control_check,sensor_check,test_reg;
   	    
 asm volatile(
	
	"and x30, x30, %2\n\t"	 
	"or x30, x30, %0\n\t" 
	"or x30, x30, %1\n\t"
	:
	:"r"(buzzer_reg), "r"(led_reg), "r"(mask)
	:"x30"
      );
	
		/* asm volatile(
		"addi x30, x30, 0\n\t"
		:"=r"(reg_check)
		:
		:"x30"
	);
	
 	//printf("reg_check is %d\n",reg_check);
        //printf("hall_sensor = %d, control=%d, buzzer = %d, led=%d\n", hall_sensor,control, buzzer_reg,led_reg);
       */ 
        		   	
//int k;
//for(k=0;k<1;k++)
   //printf("entering the while loop\n");
  while(1) 
  {
	  asm volatile(
        	"andi %0, x30, 1\n\t"
	        :"=r"(control)
		:
		:
 	);  
 	
/*
	asm volatile(
    	"addi %0, x30, 0\n\t"
    	:"=r"(control_check)
    	:
    	:"x30"
    	);
    	//printf("control_check = %d\n",control_check);
    	//printf("control value = %d\n",control);
        */
	 	
	 	 
         //control = 0;
        //printf("control value is updated as  %d\n",control);
         
      if (control) {   

              //printf("control is 1 therefore inside if loop \n");            
              
		asm volatile(
        		"andi %0, x30, 2\n\t"
			:"=r"(hall_sensor)
        		:
        		:
	 	);  
   /*
 	        asm volatile(
    		  "addi %0, x30, 0\n\t"
    		  :"=r"(sensor_check)
    		  :
    		  :"x30"
    		);
	        //printf("sensor_check = %d\n",sensor_check);
	

 */
              
             // hall_sensor =0;
	        if(hall_sensor){
           //printf("hall sensor is 1 therefore inside if loop\n");
           //printf("Door Open!, Buzzer = ON, led =ON\n");
           
	
	            buzzer = 1;
	            led = 1;  	
	  } 
	  
	  else {
             //printf("hall sensor is 0 therefore else is executed\n");                          
             //printf("Door Closed, Buzzer = OFF , led = OFF\n ");

	    buzzer =0;
	    led=0;
	    
	    }
	    

//Updating registers for buzzer and led
    
	buzzer_reg = buzzer*4;
	led_reg = led*8;
	
	asm volatile(
	    "and x30, x30, %2\n\t"
	    "or x30, x30, %0 \n\t"
            "or x30, x30, %1 \n\t"
	    :
	    :"r"(buzzer_reg), "r"(led_reg), "r"(mask)
            :"x30"
          );	          
                   
  /*               
  asm volatile(
    	"addi %0, x30, 0\n\t"
    	:"=r"(test_reg)
    	:
    	:"x30"
    	);
    	//printf("test_reg = %d\n",test_reg);
    //printf("hall_sensor = %d, control =%d, buzzer = %d,  led=%d\n",hall_sensor,control,buzzer_reg,led_reg);
*/

        }
 } 

 return 0;
}
