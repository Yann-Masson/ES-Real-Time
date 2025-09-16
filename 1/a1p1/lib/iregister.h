//  Created by Mohammadreza Mousavi [mohmou] on 9/5/14.
//  Updated by Masoumeh Taromirad on 11/08/16.
//  Updated by Wagner Morais and Johannes van Esch on 28/08/18.
//  Copyright (c) 2014 by Mohammadreza Mousavi [mohmou]. All rights reserved.

#ifndef lab0_iregister_h
#define lab0_iregister_h

/**
 *  iRegister
 *  A lightweight structure representing a (nominal) 32-bit register and
 *  equipped with standard bit/nibble operations plus string conversion.
 *
 *  IMPORTANT IMPLEMENTATION NOTE:
 *  - The underlying type is 'int'. The code assumes (as is typical on the
 *    target platform) that 'int' is 32 bits. All operations treat the
 *    register as a 32-bit quantity.
 *  - Every API in this header performs parameter validation. On any
 *    contract violation (NULL pointer, out-of-range index/value), the
 *    implementation prints an error message to stderr and terminates the
 *    program via exit(1). No error codes are returned.
 */ 
typedef struct{
    int content;
} iRegister;


/** @brief Resets all the bits of the iRegister (to 0).
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


/** @brief Sets the i'th bit of the iRegister (to 1)
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


/** @brief Sets all the bits of the iRegister (to 1) 
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


/** @brief Returns the i'th bit of the iRegister as an integer (1 if it is set, or 0 otherwise)
 *
 *  @param i Is i'th bit of the iRegister to be returned
 * 
 *  @param r A pointer to a memory location of a iRegister data structure.
 *
 *  @return 1 if i'th bit is set, 0 if the bit is not set.
 *          (On invalid parameters the function prints an error and exits.)
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


/** @brief Sets the nibble (4 bits) at position 'pos' of the iRegister to 'value'.
 *
 * @param pos 0-based nibble index in the range [0..7], where:
 *            pos = 0 => bits 0-3 (least significant nibble)
 *            pos = 1 => bits 4-7
 *            ...
 *            pos = 7 => bits 28-31 (most significant nibble)
 *
 * @param value The 4-bit value (0-15) to assign to the specified nibble.
 *
 * @param r A pointer to an iRegister structure.
 *
 * @return void
 *
 * Pre-condition:
 * 0 <= pos <= 7
 * 0 <= value <= 15
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


/** @brief Returns the nibble (4 bits) at position 'pos'.
 *
 * @param pos 0-based nibble index in the range [0..7] (see assignNibble for mapping).
 *
 * @param r A pointer to an iRegister structure.
 *
 * @return The value of the specified nibble (0-15).
 *
 * Pre-condition:
 * 0 <= pos <= 7
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
 *         is either '1' if the corresponding bit is set, or '0' if the bit is not set.
 *         The string represents bits from most significant (bit 31) to least (bit 0).
 *
 * Lifetime / Reentrancy:
 *   The implementation uses a single static internal buffer; each call overwrites
 *   the previous result. Not thread-safe. Copy the string if you need to keep it.
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


/** @brief Shifts all the bits of the iRegister to the right by n places (fills with 0s on the left).
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
 * Note: The implementation accepts n == 32, which triggers a full clear in practice; however,
 *       in standard C, shifting a 32-bit int by 32 is technically undefined behavior. This
 *       code relies on typical target compiler behavior. Prefer 1..31 for portable code.
 *
 * test-cases:
 * 1. Allocate iRegister r, setBit(5, &r), shiftRight(2, &r), check getBit(3, &r) == 1.
 * 2. shiftRight(32, &r), check reg2str(r) == "000...0".
 */
void shiftRight(int, iRegister *);


/** @brief Shifts all the bits of the iRegister to the left by n places (fills with 0s on the right).
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
 * Note: As with shiftRight, n == 32 depends on target behavior and is outside strictly
 *       defined shift ranges for a 32-bit int. Use 1..31 for fully portable code.
 *
 * test-cases:
 * 1. Allocate iRegister r, setBit(2, &r), shiftLeft(2, &r), check getBit(4, &r) == 1.
 * 2. shiftLeft(32, &r), check reg2str(r) == "000...0".
 */
void shiftLeft(int, iRegister *);


/** @brief Resets (clears to 0) the i'th bit of the iRegister.
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
