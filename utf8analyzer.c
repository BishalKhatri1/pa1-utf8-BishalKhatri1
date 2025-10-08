#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>// bool library
#include <string.h>

//Animal emojis
void is_animal_emoji_at(const char str[]){
        // Same concept as hw 1.5,1.16,1.17
        int char_num = 0;
        int i = 0;      // counting bytes
	int codepoint = 0;
        while(str[i] != '\0'){
                unsigned char first = (unsigned char) str[i];   // positive value
                int char_len = 0;

                // determing bytes and its character length by using hw 1.5 code & concept
                 if (first <= 0x7F) {
                        char_len = 1;       //1 byte
                 }
                 else if ((first & 0xE0) == 0xC0) {
                        char_len = 2;       //2 byte
                 }
                 else if ((first & 0xF0) == 0xE0) {
                        char_len = 3;       //3 byte
                 }
                 else if ((first & 0xF8) == 0xF0) {
                        char_len = 4;       //4 byte
                 }
                 else {
                        char_len = 1; 
                 }

                         if (char_len == 4){
                                 // reconstruct Unicode codepoint
                                  codepoint = ((first & 0x07) << 18) |
                                                 ((str[i+1] & 0x3F) << 12) |
                                                 ((str[i+2] & 0x3F) << 6) |
                                                 (str[i+3] & 0x3F);

                                 // check if codepoint is in animal ranges
                                 if ((codepoint >= 0x1F400 && codepoint <= 0x1F43F) ||
                                     (codepoint >= 0x1F980 && codepoint <= 0x1F9AE)) {
                               		printf("%d\n",codepoint);
                                 }
                         }
                i += char_len ; // for looping again
                char_num ++;  // increasing the index
      }
}


//Code points as decimal numbers
void codepoint_at(char str[]){
    
	int length = 0;
    unsigned char first = 0;
    int j = 0;// for loop
	 while(str[j] != '\n'){
	int32_t codepoint = 0;
	 unsigned char first = (unsigned char)str[j];
    	if (first <= 0x7F) { // ascii or 1 byte
       	length = 1;
	codepoint = first;
    }

    // Determine length from first byte
    if ((first & 0xE0) == 0xC0) {       // 2-byte
        length = 2;
        codepoint = first & 0x1F;
    } else if ((first & 0xF0) == 0xE0) { // 3-byte
        length = 3;
        codepoint = first & 0x0F;
    } else if ((first & 0xF8) == 0xF0) { // 4-byte
        length = 4;
        codepoint = first & 0x07;
    } else {
        // invalid byte
    }

    // for others bytes
    for (int i = 1; i < length; ++i) {
        unsigned char b = (unsigned char)str[j + i];

        codepoint = (codepoint << 6) | (b & 0x3F); // 10xxxxxx  & 0011F
    }
    printf("%d  ",codepoint);
    j += length;
 }

    printf("\n");
}


//Substring of the first 6 code points
void substring_of(const char str[],int start, int end) {
    //Implement utf8_substring in the body of this function!

	// Same concept as hw 1.5,1.16,1.17
	int char_num = 0;
	int i = 0; 	//counting bytes
	while(str[i] != '\0'){
		unsigned char first = (unsigned) str[i]; 	// positive value
		int char_len = 0;

		// determing bytes and its character length by using hw 1.5 code & concept
		 if (first <= 0x7F) {
            char_len = 1;	//1 byte
       	 } 
	 	 else if ((first & 0xE0) == 0xC0) {
            char_len = 2;	//2 byte
        }
	 	 else if ((first & 0xF0) == 0xE0) {
            char_len = 3;	//3 byte
        }
	 	 else if ((first & 0xF8) == 0xF0) {
            char_len = 4;	//4 byte
        }
	 	 else {
            break ;
        }
		 if (char_num >= start && char_num < end){
		 	for(int j = 0; j< char_len ; ++j){
			printf( "%c",str[i+j]) ;  // printing the character
			}
		 }
	i += char_len ; // for looping again
	char_num ++;  // increasing the index

       if (char_num >= end){
       break;
       }       
	
	}
	printf("\n");
}


	// bytes per codepoint
void bytes_per_code(char string[]) {
	// uint8_t == unsigned int 8 bits
	int i = 0;
	uint8_t first = 0;
	int length = 0;
    int32_t codepoint = 0;
	while (string[i] != '\n'){ //fgets have new line before \0
	uint8_t first = (uint8_t) string[i];// get first byte positive
    	if (first <= 0x7F) { // ascii or 1 byte
        length =  1;
    }
// i just use HW 1.5 code and adjusted it little bit 
    

    // Determine length from first byte
    if ((first & 0xE0) == 0xC0) {       // 2-byte
        length = 2;
       // codepoint = first & 0x1F;
    } else if ((first & 0xF0) == 0xE0) { // 3-byte
        length = 3;
       // codepoint = first & 0x0F;
    } else if ((first & 0xF8) == 0xF0) { // 4-byte
        length = 4;
       // codepoint = first & 0x07;
    } else{
	    
    } 
    printf("%d ",length); 
    i += length;
}
	printf("\n");
}

	//Number of code points
int32_t num_of_codepoints(char str[]) {
	// same concept as Hw 1.6 & Hw 1.16   
	int sum = 0;
       	int i = 0;
	while( str[i] != '\0'){		// looping to the end
	unsigned char first  = (unsigned char)str[i];	// assing everytime
    	if (first <= 0x7F) { // ascii or 1 byte
	i++;			// looping once for 1 byte 
    }
    

    // Determine length from first byte
	else if ((first & 0xE0) == 0xC0) {       // 2-byte
        i += 2;
    } else if ((first & 0xF0) == 0xE0) { // 3-byte
        i+= 3;
 
    } else if ((first & 0xF8) == 0xF0) { // 4-byte
        i+= 4;
        
    } else {
        return 0; // invalid start byte
    }
	sum ++;
	}

	return sum  ;
}


        //for checking valid ascii
bool  is_ascii(char string[]) {
        int length = 0;
        while ( string[length] != '\0'){
                if (string[length] < 0 || string[length] >127){
                        return false;
                }
                length ++;
        }
        return true;
}

        // function for making uppercase
int32_t capitalize_ascii(char str[]) {
        // function arugment will work as pointer in C language
        int count = 0;
        for(int i = 0; str[i] != '\0' ; ++i){
                if ( str[i] >= 'a' && str[i] <= 'z'){
                        str[i] -= 32;
                }
        }
        return 0;

}

int main(int argc, char** argv) {
        char buffer[100];
        uint8_t ascii_or_not;//for checking valid ASCII
        int32_t making_uppercase; //for making Uppercase
        printf("%s"," Enter a UTF-8 encoded string: ");
        while(1) {
                char* maybe_eof = fgets(buffer, 99, stdin);
                if(maybe_eof == NULL) { break; }

                // for checking valid ASCII
                ascii_or_not = is_ascii(buffer);
                printf ("Valid ASCII: %s\n", ascii_or_not ? "true" :"false" );//tenary operator shorter version of if & else

                //for making uppercase letters
                making_uppercase = capitalize_ascii(buffer);
                printf("%s", buffer);

		//for length in bytes
		printf("Length in bytes : %zu\n",strlen(buffer));

		//Num of code points
		 printf("Number of code points : %d\n",num_of_codepoints(buffer) );

		 //Bytes per code point
		 printf("Bytes per code point : ");
		 bytes_per_code(buffer);

		  //Substring of the first 6 code points
                 printf("Substring of the first 6 code points : ");
                 substring_of(buffer, 0 ,6);

		 //Code points as decimal numbers
		 printf("Code points as decimal numbers : ");
                 codepoint_at(buffer);

		 //ANimal emoji
		 printf("Animal emojis : ");
		is_animal_emoji_at(buffer);
        }}

