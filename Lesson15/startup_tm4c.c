/* Startup code for teh TM4C */

//Putting my vector table in location of memory has no standard syntax
//IAR uses an extension @ ".intvec" to define the section in the project.icf linker file
//const forces the compiler to put the new vector table into ROM
int const __vector_table[] @ ".intvec" = {
  0x20004000,
  0x9
};

