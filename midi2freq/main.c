/*
 This code is taken from The Audio Programming Book, Chapter 1, Listing 1.3
 It has been updated to use 'scanf("%d", &midinote)' instead of
 'gets()' as that function has been depricated and is dangerous to use.
*/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
int main(int argc, char* argv[]) {
    
    double semitone_ratio;
    double c0; //for frequency of MIDI Note 0
    double c5; //for frequency of Middle C
    double frequency; //...which we want to find
    int midinote = 150; //...given this note
    //setting midinote to arbitrary invalid value so that if user does not
    //enter an int, it will return with an error.
    char* choice = argv[1];
    double userfreq = 0;
    
    if(argc != 3){
        printf("midi2freq can convert a MIDI number to a frequency"
               " and vice versa.\nThe program takes a conversion type"
               "(m2f or f2m) and a value to convert (midi number or frequency)\n"
               "For example:\n\t./midi2freq m2f 21\n");
        return 1;
    }

    //calculate the required numbers
    semitone_ratio = pow(2, 1/12.0);
    //find Middle C, three semitones above low A = 220;
    c5 = 220.0 * pow(semitone_ratio, 3);
    //Midi Note 0 is C, 5 octaves below Middle C
    c0 = c5 * pow(0.5, 5);
    

    //Convert MIDI note to frequency
    if(strcmp(choice, "m2f") == 0){
        midinote = atoi(argv[2]);
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
        printf("\nMIDI Note %d has frequency %f\n", midinote, frequency);
    }
    if(strcmp(choice, "f2m") == 0){
        userfreq = atof(argv[2]);
        if(userfreq < 8.175799 || userfreq > 12543.853951){
            printf("\nThat frequency does not have a MIDI number.\n"
                   "Please enter a frequency between 8.175 and 12543.854\n");
            return 5;
        }
        double midinotedec = log(userfreq / c0) / log(semitone_ratio);
        midinote = log(userfreq / c0) / log(semitone_ratio);
        int variance = (midinotedec - midinote)*100;
        printf("\nThe closest MIDI note to %.2f is %d\n", userfreq, midinote);
        printf("with a variance of %d%%\n", variance);
    }
    return 0;
}
