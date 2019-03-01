#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "items.h"

#define ROOM_VARIATIONS 5
#define ITEM_VARIATIONS 5

int main(void) {

    const char* item_possibilities[ROOM_VARIATIONS][ITEM_VARIATIONS][3] = {
        {
            {"Programming In C (3rd Edition)", "Could prove very useful for the exams", 1},
            {"The Linux Programming Interface", "Could prove very useful for the exams", 1},
            {"Discrete Mathematics: A Foundation for Computer Science", "Could prove very useful for the exams", 1},
            {"Introduction To Probability (2nd Edition)", "Could prove very useful for the exams", 1},
            {"Tying Knots for Dummies", "Could prove very useful after the exams", 1}
        },
        {
            {"Green and Blue Vest", "Worn by the King himself. (Armour)", 10},
            {"Plaque", "Official disbandment of global variables. (Shield)", 3},
            {"Flashdrive", "Completely implemented Project 2. No need for an extension. (Door Key)", 0},
            {"Gilbert Herndon", "Nick Huph.", -1},
            {"Baseball Hat", "Dat Dad Hat. (Armour)", 3}
        },
        {
            {"Empty Condom Wrapper", "Wrap your willie, don't be silly.", -1}, 
            {"Phone", "The only installed app is Discord, on light mode nontheless.", -1},
            {"Pee Mentor Sign", "Seems like some letters R missing. (Shield)", 1},
            {"Rotten Banana", "Just a rotten banana sitting on the ground.", -1},
            {"Katana", "From the weeb next door. (Weapon)", 10}
        },
        {
            {"General Tso's Peppers", "Now with extra chicken. (yes gope)", 5}, 
            {"Chicken Tenders", "Reeeee, give me tendies. (medium gope)", 3},
            {"Butter Knife", "Faint stains of jelly can be seen. (Weapon)", 6},
            {"Diet Coke", "No insulin required, diabetic friendly. (no gope)", 2},
            {"Canada Dry", "Frothy boi. (no gope)", 2}
        },
        {
            {"Pencil", "It's particularly sharp. (Weapon)", 3}, 
            {"Answer Sheet", "I hope this exam was scaled. (Door Key)", 0},
            {"Notebook", "Contains solutions for a CS240 quiz. (Door Key)", 0},
            {"Homework Solutions", "Homework Solutions - Seems correct, but then again, everything does. (Door Key)", 0},
            {"Cowboy Hat", "Often dawned by Jared. (Armour)", 5}
        }
    };
}