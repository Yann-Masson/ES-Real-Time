//  Created by Mohammadreza Mousavi [mohmou] on 9/5/14.
//  Updated by Masoumeh Taromirad on 11/08/16.
//  Updated by Wagner Morais and Johannes van Esch on 28/08/18.
//  Copyright (c) 2014 by Mohammadreza Mousavi [mohmou]. All rights reserved.

#ifndef lab0_iregister_h
#define lab0_iregister_h

/**
 *  iRegister
 *  An iRegister is a structure which represents an 32-bit register and
 *  is equipped with standard operations to modify and display them.
 */ 
typedef struct{
    int content;
} iRegister;


/** @brief resets all the bits of the iRegister (to 0).
 *   
 *  @param r A pointer to a memory location of a iRegister data structure.
 * 
 *  @return void
 * 
 *  Pre-condition: iRegister != NULL
 * 
 *  Post-condition: after resetAll(r) all the bits of iRegister are 0.
 * 
 *  properties: 
 *  after resetAll(r),  getBit(j, r) = 0 for all 0 <= j < 32.
 * 
 *  test-cases:
 *  1. Allocate iRegister r, set all bits with setAll(&r), then resetAll(&r), check reg2str(r) == "000...0".
 *  2. After resetAll(&r), getBit(i, &r) == 0 for i=0, 15, 31.
 */ 
void resetAll(iRegister *r);


/** @brief sets the i'th bit of the iRegister (to 1)
 * 
 *  @param i Is i'th bit of the iRegister to be set
 * 
 *  @param r A pointer to a memory location of a iRegister data structure.
 * 
 *  @return void
 * 
 *  Pre-condition: 0 <= i < 32 and iRegister != NULL
 * 
 *  Post-condition: after setBit(i, r) the i'th bit of iRegister is 1, all other bits remain unchanged
 * 
 *  properties:
 *  after setBit(i, r),  getBit(i, r) = 1
 *  if getBit(i, r) == 1 then  
 *      getBit(j, r) returns the same value for all 
 *  0 <= j < 32 and j != i before and after setBit(i, r)
 * 
 *  test-cases:
 *  1. Allocate iRegister r, resetAll(&r), setBit(5, &r), check getBit(5, &r) == 1.
 *  2. setBit(0, &r), setBit(31, &r), check reg2str(r) has '1' at positions 31 and 0.
 */
void setBit(int i, iRegister *r);


/** @brief sets all the bits of the iRegister (to 1) 
 * 
 *  @param r A pointer to a memory location of a iRegister data structure.
 * 
 *  @return void
 * 
 *  Pre-condition: iRegister != NULL
 * 
 *  Post-condition: after setAll(r) all the bits of iRegister are 1.
 * 
 *  properties: 
 *  after setAll(r),  getBit(j, r) = 1 for all 0 <= j < 32.
 * 
 *  test-cases:
 *  1. Allocate iRegister r, setAll(&r), check reg2str(r) == "111...1".
 *  2. After setAll(&r), getBit(i, &r) == 1 for i=0, 15, 31.
 */ 
void setAll(iRegister *r);


/** @brief returns the i'th bit of the iRegister as an integer (1 if it is set, or 0 otherwise)
 *
 *  @param i Is i'th bit of the iRegister to be returned
 * 
 *  @param r A pointer to a memory location of a iRegister data structure.
 *
 *  @return 1 if i'th bit is set, 0 if the bit is not set, -1 if there was an error. 
 *
 *  Pre-condition: 0 <= i < 32 and iRegister != NULL
 *
 *  properties:
 *  the return value after getBit(i, r) is the same value as directly reading the i'th bit from iRegister. 
 *
 *  test-cases:
 *  1. Allocate iRegister r, resetAll(&r), setBit(7, &r), check getBit(7, &r) == 1.
 *  2. getBit(0, &r) == 0 after resetAll(&r).
 */
int getBit(int i, iRegister *r);


/** @brief Sets the n nibble (4 bits) of the iRegister to value.
 *
 * @param pos Indicates which nibble to set: 1 for the least significant nibble (bits 0-3), 2 for the next nibble (bits 4-7)...
 *
 * @param value The 4-bit value (0-15) to assign to the specified nibble.
 *
 * @param r A pointer to an iRegister structure.
 *
 * @return void
 *
 * Pre-condition:
 * pos is between 0 and 7
 * 0 <= value < 16
 * r != NULL
 *
 * Post-condition:
 * Result is checked using getNibble(pos, r) == value
 *
 * Properties:
 * For pos=0: sets bits 0-3 to value, bits 4-31 remain unchanged
 * For pos=1: sets bits 4-7 to value, bits 0-3 and 8-31 remain unchanged
 * ...
 *
 * test-cases:
 * 1. Allocate iRegister r, resetAll(&r), assignNibble(0, 0xA, &r), check getNibble(0, &r) == 0xA.
 * 2. assignNibble(7, 0xF, &r), check getNibble(7, &r) == 0xF.
 */
void assignNibble(int pos, int value, iRegister *r);


/** @brief Get the first (for pos=0) or the second (for pos=7) four bits of iRegister content.
 *
 * @param pos Indicates which nibble to get: 1 for the least significant nibble (bits 0-3), 2 for the next nibble (bits 4-7).
 *
 * @param r A pointer to an iRegister structure.
 *
 * @return The value of the specified nibble (0-15).
 *
 * Pre-condition:
 * pos is between 0 and 7
 * r != NULL
 *
 * Properties:
 * For pos=0: returns bits 0-3
 * For pos=1: returns bits 4-7
 * ...
 *
 * test-cases:
 * 1. Allocate iRegister r, resetAll(&r), assignNibble(2, 0x5, &r), check getNibble(2, &r) == 0x5.
 * 2. getNibble(0, &r) == 0 after resetAll(&r).
 */
int getNibble(int pos, iRegister *r);


/** @brief Returns a pointer to an array of 32 characters representing the bits of the iRegister (33 including the null terminator).
 *
 * @param r An iRegister structure (passed by value)
 *
 * @return A pointer to a null-terminated string of 32 characters, where each character
 *         is either '1' (ASCII 49) if the corresponding bit is set, or '0' (ASCII 48)
 *         if the bit is not set. The string represents bits from most significant (bit 31)
 *         to least significant (bit 0).
 *
 * Properties:
 * If bit i is set in r.content, then returned_string[31-i] == '1'
 * If bit i is not set in r.content, then returned_string[31-i] == '0'
 * The returned string is null-terminated
 *
 * test-cases:
 * 1. Allocate iRegister r, resetAll(&r), check reg2str(r) == "000...0".
 * 2. setAll(&r), check reg2str(r) == "111...1".
 * 3. setBit(0, &r), check reg2str(r)[31] == '1'.
 */
char *reg2str(iRegister r);


/** @brief Shifts all the bits of the iRegister to the right by n places (appends 0 from the left)
 *
 * @param n The number of positions to shift right (1 <= n <= 32)
 *
 * @param r A pointer to a memory location of a iRegister data structure.
 *
 * @return void
 *
 * Pre-condition:
 * 1 <= n <= 32
 * r != NULL
 *
 * Post-condition:
 * All bits are shifted right by n positions
 * The leftmost n bits become 0
 *
 * Properties:
 * After shiftRight(n, r), bit i contains the value that was previously in bit (i+n)
 * For i+n > 31, bit i becomes 0
 *
 * test-cases:
 * 1. Allocate iRegister r, setBit(5, &r), shiftRight(2, &r), check getBit(3, &r) == 1.
 * 2. shiftRight(32, &r), check reg2str(r) == "000...0".
 */
void shiftRight(int, iRegister *);


/** @brief Shifts all the bits of the iRegister to the left by n places (appends 0 from the right)
 *
 * @param n The number of positions to shift left (1 <= n <= 32)
 *
 * @param r A pointer to a memory location of a iRegister data structure.
 *
 * @return void
 *
 * Pre-condition:
 * 1 <= n <= 32
 * r != NULL
 *
 * Post-condition:
 * All bits are shifted left by n positions
 * The rightmost n bits become 0
 *
 * Properties:
 * After shiftLeft(n, r), bit i contains the value that was previously in bit (i-n)
 * For i-n < 0, bit i becomes 0
 *
 * test-cases:
 * 1. Allocate iRegister r, setBit(2, &r), shiftLeft(2, &r), check getBit(4, &r) == 1.
 * 2. shiftLeft(32, &r), check reg2str(r) == "000...0".
 */
void shiftLeft(int, iRegister *);


/** @brief Resets the i'th bit of the iRegister (to 0)
 *
 *  @param i Is i'th bit of the iRegister to be reset
 * 
 *  @param r A pointer to a memory location of a iRegister data structure.
 * 
 *  @return void
 * 
 *  Pre-condition: 0 <= i < 32 and iRegister != Null
 * 
 *  Post-condition: after reset(i, r) the i'th bit of iRegister is 0, all other 
 *  bits remain unchanged
 *  properties: 
 *  after resetBit(i, r),  getBit(i, r) = 0
 *  if getBit(i, r) == 0 then  
 *    getBit(j, r) returns the same value for all 
 *  0 <= j < 32 and j <> i before and after resetBit(i, r)
 * 
 *  test-cases: 
 *  1,2,3. Allocate memory to an iRegister r
 *  first do resetAll(&r),
 *  then set the i'th bit of &x by setBit(i, &r) for i = 0, 15 and 23 and then
 *  display the result after each and every call by 
 *    printf("%s",reg2str(r)) 
 */
void resetBit(int i, iRegister *r);

#endif
