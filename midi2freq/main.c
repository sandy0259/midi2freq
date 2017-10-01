/*
 This code is taken from The Audio Programming Book, Chapter 1, Listing 1.3
 It has been updated to use 'scanf("%d", &midinote)' instead of
 'gets()' as that function has been depricated and is dangerous to use.
*/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
int main() {
    
    double semitone_ratio;
    double c0; //for frequency of MIDI Note 0
    double c5; //for frequency of Middle C
    double frequency; //...which we want to find
    int midinote = 150; //...given this note
    //setting midinote to arbitrary invalid value so that if user does not
    //enter an int, it will return with an error.
    int choice = 0;
    double userfreq = 0;

    //calculate the required numbers
    semitone_ratio = pow(2, 1/12.0);
    //find Middle C, three semitones above low A = 220;
    c5 = 220.0 * pow(semitone_ratio, 3);
    //Midi Note 0 is C, 5 octaves below Middle C
    c0 = c5 * pow(0.5, 5);
    printf("(1) Convert midi note to frequency\n"
           "(2) Convert frequency to midi note\n"
           "Choose a conversion: ");
    scanf("%d", &choice);
    if(choice != 1 && choice != 2){
        printf("Please enter 1 or 2\n");
        return 1;
    }
    //Convert MIDI note to frequency
    if(choice == 1){
        printf("Enter MIDI note (0-127):");
        scanf("%d", &midinote);
        //check for erroneous input
        if(midinote == 150){
            printf("Please enter a valid integer 0-127\n");
            return 2;
        }
        if(midinote < 0){
            printf("Please enter a valid integer 0-127\n");
            return 3;
        }
        if(midinote > 127){
            printf("Please enter a valid integer 0-127.\n");
            return 4;
        }
        //calculate a frequency for a given Midi Note Number
        frequency = c0 * pow(semitone_ratio, midinote);
        
        printf("MIDI Note %d has frequency %f\n", midinote, frequency);
    }
    if(choice == 2){
        printf("Enter frequency:");
        scanf("%lf", &userfreq);
        if(userfreq < 8.175799 || userfreq > 12543.853951){
            printf("That frequency does not have a MIDI number.\n"
                   "Please enter a frequency between 8.175 and 12543.854\n");
            return 5;
        }
        midinote = log(userfreq / c0) / log(semitone_ratio);
        printf("The closest MIDI note to %lf is %d\n", userfreq, midinote);
    }
    return 0;
}
