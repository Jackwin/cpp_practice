//#include <fstream>
//#include <string>
//#include <iostream>
//#include <iomanip>
#include <stdio.h>
//#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define HORIZONTAL_PIXEL (16 * 4 *4)
#define VERTICAL_LINE  (1)

//std::string mode1_name = "model1.txt";
#define PAGE_SIZE (4096 * 2)    //hex
//using namespace string;
char *CombinePatternName(char prefix[10], int pattern_seq, char format[10]);
FILE* OpenFile(char file_name[], char mode[]);
void CloseFile(FILE *fp);
int CalcualtePatternSize(FILE *fp);
char Hex2Char(int data);
int ReadHex(char pattern_name[], int start_pos);
void GenerateDMAPattern(char prefix[], int pattern_num, char format[], int h_pix, int line, int mode);
int ReadDMDPattern(char pattern_name[], int start_pos, int length);
int BitsToInt(char *char_ptr);
int DuplicateBit(int bit, int n);
bool GetBit(int data, int pos);
int SetBit(int data, int pos);
void PatternFill(char pattern_name[], int h_pix, int v_line);
//void CalcualtePatternSize(char * pattern_name, int pattern_size);
void DMAOperation(int pattern_num, char *prefix, char *format);
void SetDMADesTable(int num, long dest_addr, long src_addr, int size);
int one_line_pix_array[60] = { 0 };
int data_buf [4096 / 4];
int main(void){
    
    typedef struct DMD_DATA_UNIT {
        int data[8];
    }DATA_UNIT;
    /*
    ifstream file_in;
    ofstream outfile("out.dat", ofstream::out);
    if (!outfile) {
        cerr<<"Open error!"<<endl;
        exit(1);
    }
    
    FILE *fp = OpenFile("in.txt", "r");
    int len = CalcualtePatternSize(fp);
	fclose(fp);
    printf("Length is %d.\n ", len);
  */
    //outfile.seekp(0, ios::beg);g
	int num = 10;
	
	//outfile.write((char *)(&num), sizeof(num));
	
    DATA_UNIT dmd_data;
    //int lines = 1920 * 1080 / 256;
    int lines =1080;
	//GenerateDMAPattern("data", 2, ".txt", 1920, 1080, 3);
	FILE *fp = OpenFile("in.txt", "r");
	int len = CalcualtePatternSize(fp);
	CloseFile(fp);
	printf("Len is %d.\n", len);
    char c;
	int *int_p [400];
	//cout << sizeof(int) << endl;
	int pattern_size = 0;

	//int hex = ReadDMDPattern("in.txt", 0, 8);
	int hex = ReadHex("in.txt", 4);
	printf("hex is %x.\n", hex);
	hex = DuplicateBit(1, 4);
	printf("hex is %x.\n", hex);
	hex = DuplicateBit(1, 2);
	printf("hex is %x.\n", hex);

	PatternFill("in.txt", 64, 1);
    for (int k = 0; k < 10; k++) {
        printf("one_line_pix_array[%d] is %x.\n",k, one_line_pix_array[k]);
    }
    DMAOperation(1, "model","txt" );
	//CalcualtePatternSize("pattern_0.txt", pattern_size);

	// Set one DMA descriptor size is 4096 byte, corresponding to one PAGE size in Windows
	int dma_dt_num = (pattern_size % (4096 * 2) == 0) ? pattern_size / (4096 * 2) : (pattern_size / (4096 * 2) + 1);
	//cout << "Pattern size is " << pattern_size<< endl;
	//cout << "DMA descriptor number is " << dma_dt_num << endl;
	//for (int k = 0; k < 100 * 2 / 8; k++) {
		//*(int_p + k) = ReadDMDPattern(0, 0, "data.txt", 8 * k, 8);
		//cout << hex << *(int_p + k) << endl;
	//}
    
	//delete[] int_p;

	//
	
	//cout << *data_p;
	// (1920, 1080);
	/*
    for (int i = 0; i < lines; i++) {
        dmd_data.data[0] = i;
        dmd_data.data[1] = 0x00010203;

		if (i % 2 == 0) {
			data = 1;
			for (int k = 0; k < 1920; k++) {
				std::string s{ std::to_string(data) };
				outfile << s;
			}
			outfile << "\n";
		}
		else {
			data = 0;
			for (int k = 0; k < 1920; k++) {
				std::string s{ std::to_string(data) };
				outfile << s;
			}
			outfile << "\n";
		}

		
        for (int k = 2; k < 8; k++) {
            dmd_data.data[k] = dmd_data.data[k - 1] + 0x04040404;
        }
		
        //outfile.write((char *)(&dmd_data), sizeof(DATA_UNIT));
		//std::string s = std::to_string(num);
		//outfile << s;
    }
    */
    //outfile.close();
    
    return 1;
}

// mode 1:-  2: | 3: =
void GenerateDMAPattern(char prefix[], int pattern_num, char format[], int h_pix, int line, int mode) {
   
    for (int k = 0; k < pattern_num; k++) {
        // Generate the pattern name
        char pattern_name[30];
        strcpy(pattern_name, prefix);
		printf("prefix is %s.\n", prefix);
        char num[6];
        itoa(pattern_num, num, 10);
        strcat(pattern_name, num);
        strcat(pattern_name, format);

		printf("pattern name is %s.\n", pattern_name);
		FILE *fp = OpenFile(pattern_name, "w");
		char char_vec[4];
        switch (mode)
        {
        case 1:
            for (int i = 0; i < line; i++) {
                if ((i >(line / 2 - line / 12)) && (i  < (line / 2 + line / 12))) {
                    for (int k = 0; k < h_pix; k++) {
                        char_vec[k % 4] = 1;
                        if (k % 4 == 3) {  // bits to hex
                            int s = BitsToInt(char_vec);
							char c = Hex2Char(s);
							fputc(c, fp);
                        }
                    }
					fputs('\n', fp);
                }
                else {
                    for (int k = 0; k < h_pix; k++) {
                        char_vec[k % 4] = 0;
                        if (k % 4 == 3) {
                            int s = BitsToInt(char_vec);
							char c = Hex2Char(s);
							fputc(c, fp);
                        }
                    }
					fputs('\n', fp);
                }
            }
			CloseFile(fp);
            break;
        case 2:
            for (int i = 0; i < line; i++) {
                for (int k = 0; k < h_pix; k++) {
                    if (k >(h_pix / 2 - line / 12) && (k >(h_pix / 2 + line / 12))) {
                        char_vec[k % 4] = 1;
                    }
                    else {
                        char_vec[k % 4] = 0;

                    }
                    if (k % 4 == 3) {
                        int s = BitsToInt(char_vec);
						char c = Hex2Char(s);
						fputc(c, fp);
                    }
                }
				fputc('\n', fp);
            }
			CloseFile(fp);
            break;
        case 3:
            for (int i = 0; i < line; i++) {
                for (int k = 0; k < h_pix; k++) {
                    if (0 <= i  && i <= line / 4 || ((line / 4) * 3 <= i && i <= line)) {
                        char_vec[k % 4] = k % 2;
                    }
                    else {
                        char_vec[k % 4] = 0;
                    }
                    if (k % 4 == 3) {
                        int s = BitsToInt(char_vec);
						char c = Hex2Char(s);
						fputc(c, fp);
                    }
                }
				fputc('\n', fp);
			}
			CloseFile(fp);
			break;
        default:
            break;
        }
    }
   
}

/*Func: Read 8 hex and combine them to int 
Param: length must be the multiples of 8
*/

int ReadDMDPattern(char pattern_name[], int start_pos, int length) {
    char ch = 0;
	int buf[8];
	int line_cnt = 0;
	int offset;
	int data;

    FILE *fp = OpenFile(pattern_name, "r");
    int pos = start_pos;
	while (ch != EOF) {
        fseek(fp, pos, SEEK_SET); // the beginning of the file
		//infile.seekg(pos,ios::beg);
        //infile.get(c);
		ch = fgetc(fp);
        //getc(ch);
        if (ch == "\n")
        {
            break;
        }
		// Next line
        if (ch == '\n') {
			line_cnt++;
			pos++;
        }
		else {
			// Change from ASCII to integer
			if ('0' <= ch && ch <= '9')
				ch = ch - '0';
			else if ('A' <= ch  && ch <= 'F')
				ch = ch - 'A' + 10;
			else if ('a' <= ch  && ch <= 'f')
				ch = ch - 'a' + 10;

			buf[(pos - line_cnt) % 8] = (int)ch;
			if ((pos - line_cnt) % 8 == 7) {
				offset = (pos - line_cnt) / 8;
				data = (buf[0] << 28) + (buf[1] << 24) + (buf[2] << 20) + (buf[3] << 16) + (buf[4] << 12) + (buf[5] << 8) + (buf[6] << 4) + buf[7];
			}
			if ((pos - line_cnt) == (start_pos + length - 1)) break;
			pos++;
		}
	}
    CloseFile(fp);
	return data;
}

//Read a type data from the file and return the corresponding hex value
int ReadHex(char pattern_name[], int start_pos) {
	char ch = 0;
	int line_cnt = 0;
	int offset;
	int data = 0;
	int pos = start_pos;
	FILE *fp = OpenFile(pattern_name, "r");
	while (ch != EOF) {
		fseek(fp, start_pos, SEEK_SET); // the beginning of the file								
		ch = fgetc(fp);
		// Next line
		if (ch == '\n') {
			line_cnt++;
			pos++;
		}
		else {
			// Change from ASCII to integer
			if ('0' <= ch && ch <= '9')
				ch = ch - '0';
			else if ('A' <= ch  && ch <= 'F')
				ch = ch - 'A' + 10;
			else if ('a' <= ch  && ch <= 'f')
				ch = ch - 'a' + 10;
			data = (int)ch;
		}
		CloseFile(fp);
		return data;
	}
}

int BitsToInt(char *char_ptr) {
    int data_char = 0;

    for (int i = 0; i < 4; i++) {
        data_char = data_char | (*(char_ptr + i)) << (3 - i);
    }
    return data_char;
}

// Count the pattern size in the unit of half-byte(4-bit)
int CalcualtePatternSize(FILE *fp) {
    int len = 0;
    char ch = 0;
    ch = fgetc(fp);
    while (ch != EOF) {
        ch = fgetc(fp);
        if (ch != '\n')
            len++;
    }
    return len;
}

void SetDMADesTable(int num, long dest_addr, long src_addr, int size) {
    printf("   Set the DMA Descriptor Table for the pattern.\n");
    printf("The destination addres is %x, size is %d byte.\n", dest_addr, size);
}

void DMAOperation(int pattern_num, char *prefix, char *format) {
	int next_pattern_size = 0;
	long des_addr = 0;
	int dma_dt_cnt = 0;
	for (int k = 0; k < pattern_num; k++) {
        char pattern_name[30];
        strcpy(pattern_name, prefix);
        char num[6];
        itoa(pattern_num, num, 10);
        strcat(pattern_name, num);
        printf("pattern name is %s.\n", pattern_name);
        strcat(pattern_name, ".");
        strcat(pattern_name, format);
        printf("pattern name is %s.\n", pattern_name);
        FILE *fp = OpenFile(pattern_name, "r");
		// The maximum number of DMA DT is 128, starting from 0 to 127
		int pattern_size = CalcualtePatternSize(fp);
        CloseFile(fp);
		// One page corresponds to one DMA Descriptor Table
		int page_num = (pattern_size % PAGE_SIZE == 0) ? (pattern_size / PAGE_SIZE) : (pattern_size / PAGE_SIZE + 1);
        printf("page_num is %d, pattern_size is %d.\n", page_num, pattern_size);
			// Read the pattern to construct the DMA Descriptor Table
		for (int page_cnt = 0; page_cnt < page_num; page_cnt++) {
			// Less than or equal to PAGE_SIZE(The last portion of data)
			if (page_cnt == (page_num - 1)) {
				int data_size = pattern_size - (page_num - 1) * PAGE_SIZE; // The remaining data
				// FPGA DDR memory data width is 256-bit. pattern_size is calculated in the unit of hex.
				int times_of_256bit = data_size / (256 / 4);
				//cout << "Set the DMA Descriptor Table for the pattern" << endl;
				SetDMADesTable(dma_dt_cnt, des_addr, 0, data_size/2);
				//Update the des_addr
				if (data_size % (256 / 4)) {
					des_addr = des_addr + times_of_256bit - 1;
				}
				else {
					des_addr = des_addr + times_of_256bit;
				}
				// When the last pattern reaches, start DMA operation
				if (k == (pattern_num - 1)) {
                    printf("------------ launch DMA operation ----------------");
                    printf("Current pattern is %s.\n", pattern_name);
					dma_dt_cnt = 0;
					break;
				}
			}
			else {
				int data_size = PAGE_SIZE;
				int times_of_256bit = PAGE_SIZE / (256 / 4);
					
				SetDMADesTable(dma_dt_cnt, des_addr, 0, data_size/2);
				//Update the des_addr
				des_addr = des_addr + times_of_256bit;
			}
			// Increase the DMA DT 
			dma_dt_cnt = dma_dt_cnt + 1;
			if (dma_dt_cnt == 128) {
				//Launch DMA operation
                printf("------------ launch DMA operation ----------------");
                printf("Current pattern is %s.\n", pattern_name);
				//cout << "dma_dt_cnt is " << dma_dt_cnt << endl;
				dma_dt_cnt = 0;
			}
		}
	}

}

void LightPix(int x, int y) {

}

FILE* OpenFile(char file_name[], char mode[]) {
    FILE *fp = NULL;
	//printf("file_name is %s, mode is %s.\n", file_name, mode);
    fp = fopen(file_name, mode);
    if (fp == NULL) {
        printf("Fail to open the file %s.\n", file_name);
        exit(1);
    }
	//printf("Open successfully.\n");
    return fp;;
}
void CloseFile(FILE *fp) {
    fclose(fp);

}

char *CombinePatternName(char prefix[10], int pattern_seq, char format[10]) {
    char pattern_name[30];
    strcpy(pattern_name, prefix);
	printf("pattern name is %s.\n", pattern_name);
    char num[6];
    itoa(pattern_seq, num, 10);
    strcat(pattern_name, num);
	printf("pattern name is %s.\n", pattern_name);
    strcat(pattern_name, format);
	printf("pattern name is %s.\n", pattern_name);
    return pattern_name;
}

char Hex2Char(int data) {
	char ch = '0';
	if (0 <= data && data <= 9) {
		ch = data + 48;
	}
	else if (10 <= data && data <= 15) {
		ch = data + 'a' - 10;
	}
	else {
		printf("No valid Hex data.\n");
	}
	
	return ch;
}

// The maximum fill size is (64-1)
void PatternFill(char pattern_name[], int h_pix, int v_line) {
	 // The memory space to store one line 1920 pixels. 1920/32
	int h_fill_size = HORIZONTAL_PIXEL / h_pix - 1;
	int v_fill_size = VERTICAL_LINE / v_line - 1;
	/*
	for (int i = 0; i < h_pix / 4; i++) {
		int hex = ReadHex(pattern_name, i * 4);
		if (hex != 10)
			for (int k = 0; k < 4; k++) {
				int data = DuplicateBit(GetBit(hex, k), (h_fill_size + 1));
			}
	}
	*/
	int index = 0;
    int duplicate = HORIZONTAL_PIXEL / h_pix;
   // if (HORIZONTAL_PIXEL == h_pix) {

   // }
   // else {
        for (int i = 0; i < h_pix / 4; i++) {
            int hex = ReadHex(pattern_name, i);
            printf("hex from the file is %x.\n", hex);
            // Loop for the 4 bits in a hex
            for (int k = 0; k < 4; k++) {
                int bit = GetBit(hex, 3 - k); // Get the bit from the most-left to right
                printf("i is %d, k is %d, bit is %d.\n", i, k, bit);
                if (bit == 1) {
                    // Duplicate the bit
                    for (int m = 0; m < HORIZONTAL_PIXEL / h_pix; m++) {
                        one_line_pix_array[index / 32] = SetBit(one_line_pix_array[index / 32], (31 - ((i * 4 + k) * duplicate + m)));
                        index++;
                    }
                }
                else {
                    // The bit is default 0. No need to fill 0
                    index = index + HORIZONTAL_PIXEL / h_pix;
                }
            }
        }
   // }
	
}

// The maximum duplication number is 31
// The bit is only 1 or 0, output n bit. 
// Assume bit = 1, n = 4, output = f
int DuplicateBit(int bit, int n) {
	int data = 1;
	if (bit == 1 && n > 1) {
		for (int i = 1; i < n; i++) {
			data = (data << 1) | data;
		}
		return data;
	}
	else if (bit == 1 && n == 1) {
		return data;
	}
	else if (bit == 0) {
		return 0;
	}
	
}
// pos starts from 0.
bool GetBit(int data, int pos) {
	return ((data >> pos) & 1);
}

// Set '1' in the pos
int SetBit(int data,  int pos) {
	int val = data;
	val = val | (1 << pos);
	return val;
}