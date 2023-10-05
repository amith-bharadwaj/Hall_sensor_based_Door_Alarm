# Hall sensor based Door Alarm

## Functionality of the system

A Hall sensor-based door alarm system is an electronic security device designed to monitor and detect the opening or closing of a door. It utilizes a Hall effect sensor, a specialized transducer that responds to changes in magnetic fields. In this context, the Hall sensor is strategically positioned in close proximity to a magnet that is affixed to either the door or the door frame. When the door is closed, the magnet aligns with the Hall sensor, creating a stable magnetic field. However, when the door is opened, the magnet moves away, causing a disruption in the magnetic field. This alteration triggers the Hall sensor to register a change in its output state. The system is programmed to recognize this transition and respond by activating an alarm, in the form of a buzzer alert. This setup serves as a simple yet effective means of enhancing security by providing an immediate alert in the event of unauthorized entry or tampering with the door. 

## Working of Hall sensor 

A Hall sensor operates based on the Hall effect, where a voltage is generated across a conductor when subjected to a perpendicular magnetic field and an electric current. In a Hall sensor, a semiconductor chip responds to changes in a nearby magnetic field. When the magnetic field changes, it creates a voltage variation in the chip, which is then used to detect the presence, strength, and polarity of the magnetic field. This makes Hall sensors invaluable in various applications, from detecting door movement in security systems to precise control in motor applications.

![image](https://github.com/amith-bharadwaj/Hall_sensor_based_Door_Alarm/assets/84613258/1af6ecc5-39c7-4b08-a334-40916aa5762d)

## Block Diagram

![image](https://github.com/amith-bharadwaj/Hall_sensor_based_Door_Alarm/assets/84613258/2db483ca-2c8e-4313-b2eb-daa7a3ec7052)

## Schematic

![image](https://github.com/amith-bharadwaj/Hall_sensor_based_Door_Alarm/assets/84613258/408eeda4-4e64-4084-9224-1efe63478635)

## C Program

```
#include <stdio.h>

int BUZZER, LED;

void alarm() {
    BUZZER = 1;
    LED = 1;
    printf("Door Open! Magnet not Detected\n");

    // Activate the alarm (sound buzzer, turn on LED)
    int buzzer_temp;
    buzzer_temp = BUZZER * 2;
    asm(
        "or x30, x30, %0\n\t"
        : "=r"(buzzer_temp)
    );

    int led_reg;
    led_reg = LED * 2;
    asm(
        "or x30, x30, %0\n\t"
        : "=r"(led_reg)
    );
}

void turnOffAlarm() {
    BUZZER = 0;
    LED = 0;
    printf("Door closed Magnet Detected\n");

    // Turn off the alarm (stop buzzer, turn off LED)
    int buzzer_temp;
    buzzer_temp = BUZZER * 2;
    asm(
        "or x30, x30, %0\n\t"
        : "=r"(buzzer_temp)
    );

    int led_reg;
    led_reg = LED * 2;
    asm(
        "or x30, x30, %0\n\t"
        : "=r"(led_reg)
    );
}

int main() {


    int hallSensorState = 0;

    while(1) {
    
    	asm(
            "andi %0, x30, 1"
            : "=r"(hallSensorState)
        );
        // Read the state of the Hall sensor
        // hallSensorState = DigitalRead(HALL_SENSOR_PIN);

        // Check if magnetic field is not detected meaning door open
        if (hallSensorState == 0) {
            alarm(); // Activate the alarm
        }
        else {
            turnOffAlarm();
        }
    }

    return 0;
}
```
## Assembly Code

```
new.o:     file format elf32-littleriscv


Disassembly of section .text:

00000000 <alarm>:
   0:	fe010113          	add	sp,sp,-32
   4:	00112e23          	sw	ra,28(sp)
   8:	00812c23          	sw	s0,24(sp)
   c:	02010413          	add	s0,sp,32
  10:	000007b7          	lui	a5,0x0
  14:	00100713          	li	a4,1
  18:	00e7a023          	sw	a4,0(a5) # 0 <alarm>
  1c:	000007b7          	lui	a5,0x0
  20:	00100713          	li	a4,1
  24:	00e7a023          	sw	a4,0(a5) # 0 <alarm>
  28:	000007b7          	lui	a5,0x0
  2c:	00078513          	mv	a0,a5
  30:	00000097          	auipc	ra,0x0
  34:	000080e7          	jalr	ra # 30 <alarm+0x30>
  38:	000007b7          	lui	a5,0x0
  3c:	0007a783          	lw	a5,0(a5) # 0 <alarm>
  40:	00179793          	sll	a5,a5,0x1
  44:	fef42623          	sw	a5,-20(s0)
  48:	00ff6f33          	or	t5,t5,a5
  4c:	fef42623          	sw	a5,-20(s0)
  50:	000007b7          	lui	a5,0x0
  54:	0007a783          	lw	a5,0(a5) # 0 <alarm>
  58:	00179793          	sll	a5,a5,0x1
  5c:	fef42423          	sw	a5,-24(s0)
  60:	00ff6f33          	or	t5,t5,a5
  64:	fef42423          	sw	a5,-24(s0)
  68:	00000013          	nop
  6c:	01c12083          	lw	ra,28(sp)
  70:	01812403          	lw	s0,24(sp)
  74:	02010113          	add	sp,sp,32
  78:	00008067          	ret

0000007c <turnOffAlarm>:
  7c:	fe010113          	add	sp,sp,-32
  80:	00112e23          	sw	ra,28(sp)
  84:	00812c23          	sw	s0,24(sp)
  88:	02010413          	add	s0,sp,32
  8c:	000007b7          	lui	a5,0x0
  90:	0007a023          	sw	zero,0(a5) # 0 <alarm>
  94:	000007b7          	lui	a5,0x0
  98:	0007a023          	sw	zero,0(a5) # 0 <alarm>
  9c:	000007b7          	lui	a5,0x0
  a0:	00078513          	mv	a0,a5
  a4:	00000097          	auipc	ra,0x0
  a8:	000080e7          	jalr	ra # a4 <turnOffAlarm+0x28>
  ac:	000007b7          	lui	a5,0x0
  b0:	0007a783          	lw	a5,0(a5) # 0 <alarm>
  b4:	00179793          	sll	a5,a5,0x1
  b8:	fef42623          	sw	a5,-20(s0)
  bc:	00ff6f33          	or	t5,t5,a5
  c0:	fef42623          	sw	a5,-20(s0)
  c4:	000007b7          	lui	a5,0x0
  c8:	0007a783          	lw	a5,0(a5) # 0 <alarm>
  cc:	00179793          	sll	a5,a5,0x1
  d0:	fef42423          	sw	a5,-24(s0)
  d4:	00ff6f33          	or	t5,t5,a5
  d8:	fef42423          	sw	a5,-24(s0)
  dc:	00000013          	nop
  e0:	01c12083          	lw	ra,28(sp)
  e4:	01812403          	lw	s0,24(sp)
  e8:	02010113          	add	sp,sp,32
  ec:	00008067          	ret

000000f0 <main>:
  f0:	fe010113          	add	sp,sp,-32
  f4:	00112e23          	sw	ra,28(sp)
  f8:	00812c23          	sw	s0,24(sp)
  fc:	02010413          	add	s0,sp,32
 100:	fe042623          	sw	zero,-20(s0)

00000104 <.L6>:
 104:	001f7793          	and	a5,t5,1
 108:	fef42623          	sw	a5,-20(s0)
 10c:	fec42783          	lw	a5,-20(s0)
 110:	00079863          	bnez	a5,120 <.L4>
 114:	00000097          	auipc	ra,0x0
 118:	000080e7          	jalr	ra # 114 <.L6+0x10>
 11c:	fe9ff06f          	j	104 <.L6>

00000120 <.L4>:
 120:	00000097          	auipc	ra,0x0
 124:	000080e7          	jalr	ra # 120 <.L4>
 128:	fddff06f          	j	104 <.L6>

```
## Number of Unique Instructions

```
Number of different instructions: 15
List of unique instructions:
mv
auipc
jalr
j
ret
nop
sw
bnez
lui
or
and
add
li
lw
sll

```
