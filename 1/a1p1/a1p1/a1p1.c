/*
    Part of the Real-Time Embedded Systems course at Halmstad University
    Copyright (c) 2017, Sebastian Kunze <sebastian.kunze@hh.se>
    All rights reserved.
	Wagner de Morais (Wagner.deMorais@hh.se)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "uart.h"
#include "iregister.h"

void printRegisterState(const char* operation, iRegister r) {
    printf("=== %s ===\n", operation);
    printf("Valeur décimale: %d\n", r.content);
    printf("Valeur hexadécimale: 0x%08X\n", r.content);
    printf("Représentation binaire: %s\n", reg2str(r));
    printf("Bits:  31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10  9  8  7  6  5  4  3  2  1  0\n");
    printf("\n");
}

void testResetAll() {
    printf("\n################ TEST RESET ALL ################\n");
    iRegister r;
    r.content = 0xFFFFFFFF; // Initialiser avec tous les bits à 1
    
    printRegisterState("Avant resetAll (tous les bits à 1)", r);
    resetAll(&r);
    printRegisterState("Après resetAll", r);
    
    // Vérification
    printf("Vérification: tous les bits doivent être à 0\n");
    for (int i = 0; i < 32; i++) {
        if (getBit(i, &r) != 0) {
            printf("ERREUR: Le bit %d n'est pas à 0!\n", i);
        }
    }
    printf("Test resetAll: TERMINÉ\n\n");
}

void testSetBit() {
    printf("\n################ TEST SET BIT ################\n");
    iRegister r;
    resetAll(&r);
    
    printRegisterState("État initial (tous bits à 0)", r);
    
    // Test de setBit pour différentes positions
    int testBits[] = {0, 5, 15, 31};
    int numTests = sizeof(testBits) / sizeof(testBits[0]);
    
    for (int i = 0; i < numTests; i++) {
        setBit(testBits[i], &r);
        char operation[50];
        sprintf(operation, "Après setBit(%d)", testBits[i]);
        printRegisterState(operation, r);
        
        // Vérification
        printf("Vérification: getBit(%d) = %d\n", testBits[i], getBit(testBits[i], &r));
        printf("\n");
    }
    printf("Test setBit: TERMINÉ\n\n");
}

void testSetAll() {
    printf("\n################ TEST SET ALL ################\n");
    iRegister r;
    resetAll(&r);
    
    printRegisterState("Avant setAll (tous bits à 0)", r);
    setAll(&r);
    printRegisterState("Après setAll", r);
    
    // Vérification
    printf("Vérification: tous les bits doivent être à 1\n");
    for (int i = 0; i < 32; i++) {
        if (getBit(i, &r) != 1) {
            printf("ERREUR: Le bit %d n'est pas à 1!\n", i);
        }
    }
    printf("Test setAll: TERMINÉ\n\n");
}

void testGetBit() {
    printf("\n################ TEST GET BIT ################\n");
    iRegister r;
    resetAll(&r);
    
    // Définir un pattern spécifique
    setBit(0, &r);
    setBit(7, &r);
    setBit(15, &r);
    setBit(31, &r);
    
    printRegisterState("Registre avec bits 0, 7, 15, 31 définis", r);
    
    // Tester getBit pour tous les bits
    printf("Test de getBit pour tous les bits:\n");
    for (int i = 0; i < 32; i++) {
        int bitValue = getBit(i, &r);
        printf("Bit %2d: %d", i, bitValue);
        if (i == 0 || i == 7 || i == 15 || i == 31) {
            printf(" (attendu: 1)");
        } else {
            printf(" (attendu: 0)");
        }
        printf("\n");
    }
    printf("Test getBit: TERMINÉ\n\n");
}

void testResetBit() {
    printf("\n################ TEST RESET BIT ################\n");
    iRegister r;
    setAll(&r);
    
    printRegisterState("État initial (tous bits à 1)", r);
    
    // Test de resetBit pour différentes positions
    int testBits[] = {0, 8, 16, 31};
    int numTests = sizeof(testBits) / sizeof(testBits[0]);
    
    for (int i = 0; i < numTests; i++) {
        resetBit(testBits[i], &r);
        char operation[50];
        sprintf(operation, "Après resetBit(%d)", testBits[i]);
        printRegisterState(operation, r);
        
        // Vérification
        printf("Vérification: getBit(%d) = %d\n", testBits[i], getBit(testBits[i], &r));
        printf("\n");
    }
    printf("Test resetBit: TERMINÉ\n\n");
}

void testNibbleFunctions() {
    printf("\n################ TEST NIBBLE FUNCTIONS ################\n");
    iRegister r;
    resetAll(&r);
    
    printRegisterState("État initial (tous bits à 0)", r);
    
    // Test assignNibble et getNibble
    printf("Test de assignNibble et getNibble:\n");
    
    // Assigner différentes valeurs aux nibbles
    int testValues[] = {0xA, 0x5, 0xF, 0x3, 0x7, 0x1, 0xE, 0x9};
    
    for (int pos = 0; pos < 8; pos++) {
        assignNibble(pos, testValues[pos], &r);
        char operation[50];
        sprintf(operation, "Après assignNibble(%d, 0x%X)", pos, testValues[pos]);
        printRegisterState(operation, r);
        
        // Vérification
        int value = getNibble(pos, &r);
        printf("Vérification: getNibble(%d) = 0x%X (attendu: 0x%X)\n", pos, value, testValues[pos]);
        printf("\n");
    }
    
    // Afficher tous les nibbles
    printf("Résumé de tous les nibbles:\n");
    for (int pos = 0; pos < 8; pos++) {
        printf("Nibble %d (bits %d-%d): 0x%X\n", pos, pos*4, pos*4+3, getNibble(pos, &r));
    }
    printf("Test nibbles: TERMINÉ\n\n");
}

void testShiftFunctions() {
    printf("\n################ TEST SHIFT FUNCTIONS ################\n");
    iRegister r;
    resetAll(&r);
    
    // Créer un pattern pour tester les shifts
    setBit(5, &r);
    setBit(10, &r);
    setBit(20, &r);
    setBit(25, &r);
    
    printRegisterState("Pattern initial (bits 5, 10, 20, 25)", r);
    
    // Test shiftLeft
    printf("--- Test shiftLeft ---\n");
    iRegister rLeft = r; // Copie pour test
    shiftLeft(3, &rLeft);
    printRegisterState("Après shiftLeft(3)", rLeft);
    
    printf("Vérification du shift left:\n");
    printf("Les bits originaux 5, 10, 20, 25 devraient maintenant être aux positions 8, 13, 23, 28\n");
    printf("Bit 8: %d, Bit 13: %d, Bit 23: %d, Bit 28: %d\n", 
           getBit(8, &rLeft), getBit(13, &rLeft), getBit(23, &rLeft), getBit(28, &rLeft));
    printf("\n");
    
    // Test shiftRight
    printf("--- Test shiftRight ---\n");
    iRegister rRight = r; // Copie pour test
    shiftRight(2, &rRight);
    printRegisterState("Après shiftRight(2)", rRight);
    
    printf("Vérification du shift right:\n");
    printf("Les bits originaux 5, 10, 20, 25 devraient maintenant être aux positions 3, 8, 18, 23\n");
    printf("Bit 3: %d, Bit 8: %d, Bit 18: %d, Bit 23: %d\n", 
           getBit(3, &rRight), getBit(8, &rRight), getBit(18, &rRight), getBit(23, &rRight));
    printf("\n");
    
    printf("Test shifts: TERMINÉ\n\n");
}

void testComplexScenarios() {
    printf("\n################ TEST SCÉNARIOS COMPLEXES ################\n");
    iRegister r;
    
    // Scénario 1: Manipulation séquentielle
    printf("--- Scénario 1: Manipulation séquentielle ---\n");
    resetAll(&r);
    printRegisterState("1. État initial", r);
    
    setAll(&r);
    printRegisterState("2. Après setAll", r);
    
    resetBit(15, &r);
    resetBit(16, &r);
    printRegisterState("3. Après reset des bits 15 et 16", r);
    
    shiftRight(4, &r);
    printRegisterState("4. Après shiftRight(4)", r);
    
    // Scénario 2: Test avec nibbles
    printf("--- Scénario 2: Manipulation par nibbles ---\n");
    resetAll(&r);
    
    // Créer le pattern 0xDEADBEEF
    assignNibble(0, 0xF, &r); // Nibble 0: F
    assignNibble(1, 0xE, &r); // Nibble 1: E
    assignNibble(2, 0xE, &r); // Nibble 2: E
    assignNibble(3, 0xB, &r); // Nibble 3: B
    assignNibble(4, 0xD, &r); // Nibble 4: D
    assignNibble(5, 0xA, &r); // Nibble 5: A
    assignNibble(6, 0xE, &r); // Nibble 6: E
    assignNibble(7, 0xD, &r); // Nibble 7: D
    
    printRegisterState("Pattern 0xDEADBEEF créé par nibbles", r);
    
    printf("Vérification nibble par nibble:\n");
    for (int i = 0; i < 8; i++) {
        printf("Nibble %d: 0x%X\n", i, getNibble(i, &r));
    }
    
    printf("Test scénarios complexes: TERMINÉ\n\n");
}

int main() {
    printf("========================================\n");
    printf("    TEST COMPLET DE LA LIBRAIRIE IREGISTER\n");
    printf("========================================\n");
    
    // Exécuter tous les tests
    testResetAll();
    testSetBit();
    testSetAll();
    testGetBit();
    testResetBit();
    testNibbleFunctions();
    testShiftFunctions();
    testComplexScenarios();
    
    printf("========================================\n");
    printf("    TOUS LES TESTS SONT TERMINÉS\n");
    printf("========================================\n");
    
    return 0;
}