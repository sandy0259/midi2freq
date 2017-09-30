
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
int main() {
    
    double semitone_ratio;
    double c0; //for frequency of MIDI Note 0
    double c5; //for frequency of Middle C
    double pow(double, double);
    double frequency; //...which we want to find
    int midinote; //...given this note
    char message[256];
    char* result;
    
    //calculate the required numbers
    semitone_ratio = pow(2, 1/12.0);
    //find Middle C, three semitones above low A = 220;
    c5 = 220.0 * pow(semitone_ratio, 3);
    //Midi Note 0 is C, 5 octaves below Middle C
    c0 = c5 * pow(0.5, 5);
    
    printf("Enter MIDI note (0-127):");
    //the book uses gets() which is dangerous if you don't know
    //exactly how big the entry will be. Modern compilers will
    //warn that this is a dangerous function, but they will still
    //support it.
    //instead use: fgets(<#char *restrict#>, <#int#>, <#FILE *#>)
    //if getting input from stdio, use 'stdin' for the third argument
    result = fgets(message, 8, stdin);
    if(result == NULL){
        printf("There was an error reading the input.\n");
        return 1;
    }
    if(message[0] == '\0'){
        printf("Have a nice day.\n");
        return 1;
    }
    
    if(strlen(message) > 4){
        printf("Number must be between 0-127.\n");
        return 1;
    }
    
    midinote = atoi(message);
    
    if(midinote < 0){
        printf("Sorry - %s is a bad MIDI note number\n", message);
        return 1;
    }
    if(midinote > 127){
        printf("Sorry - %s is beyond the MIDI range.\n", message);
        return 1;
    }
    //calculate a frequency for a given Midi Note Number
    frequency = c0 * pow(semitone_ratio, midinote);
   
    printf("MIDI Note %d has frequency %f\n", midinote, frequency);

    return 0;
}
