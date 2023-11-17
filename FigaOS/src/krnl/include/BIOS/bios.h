/** @file bios.c
 *  Copyright (c) 2023 FigaSystems
 *  Bios interrupts and other bios related functions
 *  @author Daniil Dunaef
 *  @date 15-Nov-2023
 *  @bug No current bugs found
*/



#ifndef _BIOS_
#define _BIOS_

/** @brief Switches to Protected mode (32 bits) [asm function]
 *  @param void Nothing
 *  @return Nothing
*/
extern 
void 
to_pm(
    void
    );

/** @brief Checks for A20 Line
 *  @param void Nothing
 *  @return Nothing
*/
extern
void
checkA20(
    void
    );

/** @brief Disables the bios interrupts
 *  @param void Nothing
 *  @return Nothing
*/
void 
cli(
    void
    );

/** @brief Enables the bios interrupts
 *  @param void Nothing
 *  @return Nothing
*/
void 
sti(
    void
    );

/** @brief Switches to Protected mode (32 bits)
 *  @param void Nothing
 *  @return Nothing
*/
void 
switch_to_PM(
    void
    );

#endif