#include <fstream>
#include <string>
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

std::string mode1_name = "model1.txt";
#define PAGE_SIZE (4096 * 2)    //hex
//using namespace string;

void GenerateDMAPattern(int h_pix, int line, int mode, int pattern_num);
int ReadDMDPattern(int h_pix, int line, string pattern_name, int start_pos, int length);
int BitsToInt(char *char_ptr);
void CalcualtePatternSize(string pattern_name, int &pattern_size);
void DMAOperation(int pattern_num, string pattern_name_prefix);
void SetDMADesTable(int num, long dest_addr, long src_addr, int size);
int *data_buf = new int[4096 / 4];
int main(void){
    
    typedef struct DMD_DATA_UNIT {
        int data[8];
    }DATA_UNIT;

    ifstream file_in;
    ofstream outfile("out.dat", ofstream::out);
    if (!outfile) {
        cerr<<"Open error!"<<endl;
        exit(1);
    }

    //outfile.seekp(0, ios::beg);g
	int num = 10;
	
	//outfile.write((char *)(&num), sizeof(num));
	
    DATA_UNIT dmd_data;
    //int lines = 1920 * 1080 / 256;
    int lines =1080;
	//GenerateDMAPattern(80, 1080, 3, 40);
	
    char c;
	int *int_p = new int[400];
	cout << sizeof(int) << endl;
	int pattern_size = 0;
	//CalcualtePatternSize("pattern_0.txt", pattern_size);

	// Set one DMA descriptor size is 4096 byte, corresponding to one PAGE size in Windows
	int dma_dt_num = (pattern_size % (4096 * 2) == 0) ? pattern_size / (4096 * 2) : (pattern_size / (4096 * 2) + 1);
	cout << "Pattern size is " << pattern_size<< endl;
	cout << "DMA descriptor number is " << dma_dt_num << endl;
	for (int k = 0; k < 100 * 2 / 8; k++) {
		*(int_p + k) = ReadDMDPattern(0, 0, "data.txt", 8 * k, 8);
		cout << hex << *(int_p + k) << endl;
	}
    
	delete[] int_p;

	DMAOperation(2,"pattern_");
	
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
    outfile.close();
    return 1;
}

// mode 1:-  2: | 3: =
void GenerateDMAPattern(int h_pix, int line, int mode, int pattern_num) {
   
    for (int k = 0; k < pattern_num; k++) {
		string pattern_name("pattern_");
		int pattern_name_len = pattern_name.length();
        pattern_name.insert(pattern_name_len, to_string(k));
		pattern_name.insert(pattern_name.length(), ".txt");
        ofstream outfile(pattern_name, ofstream::out);
        char char_vec[8];
        if (!outfile) {
            cerr << pattern_name << endl;
            exit(1);
        }
        switch (mode)
        {
        case 1:
            for (int i = 0; i < line; i++) {
                if ((i >(line / 2 - line / 12)) && (i  < (line / 2 + line / 12))) {
                    for (int k = 0; k < h_pix; k++) {
                        char_vec[k % 4] = 1;
                        if (k % 4 == 3) {  // bits to hex
                            int s = BitsToInt(char_vec);
                            outfile << hex << s;
                        }
                    }
                    outfile << "\n";
                }
                else {
                    for (int k = 0; k < h_pix; k++) {
                        char_vec[k % 4] = 0;
                        if (k % 4 == 3) {
                            int s = BitsToInt(char_vec);
                            outfile << hex << s;
                        }
                    }
                    outfile << "\n";
                }
            }
            outfile.close();
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
                        outfile << hex << s;
                    }
                }
                outfile << "\n";
            }
            outfile.close();
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
                        outfile << hex << s;
                    }
                }
                outfile << "\n";
            }
        default:
            break;
        }
    }
   
}

/*Func: Read 8 hex and combine them to int 
Param: length must be the multiples of 8
*/

int ReadDMDPattern(int h_pix, int line, string pattern_name, int start_pos, int length) {
    char c;
	int buf[8];
	int line_cnt = 0;
	int offset;
	int data;
	ifstream infile(pattern_name);
	if (!infile.is_open()) {
		cout << "Error opening file";
		exit(1);
	}
    int pos = start_pos;
	while (!infile.eof()) {
		infile.seekg(pos,ios::beg);
        infile.get(c);
        if (infile.fail())
        {
            break;
        }
		// Next line
        if (c == 10) {
			line_cnt++;
			pos++;
        }
		else {
			// Change from ASCII to integer
			if ('0' <= c && c <= '9')
				c = c - '0';
			else if ('A' <= c  && c <= 'F')
				c = c - 'A' + 10;
			else if ('a' <= c  && c<= 'f')
				c = c - 'a' + 10;

			buf[(pos - line_cnt) % 8] = (int)c;
			if ((pos - line_cnt) % 8 == 7) {
				offset = (pos - line_cnt) / 8;
				data = (buf[0] << 28) + (buf[1] << 24) + (buf[2] << 20) + (buf[3] << 16) + (buf[4] << 12) + (buf[5] << 8) + (buf[6] << 4) + buf[7];
			}
			if ((pos - line_cnt) == (start_pos + length - 1)) break;
			pos++;
		}
	}
	infile.close();
	return data;
}

int BitsToInt(char *char_ptr) {
    int data_char = 0;

    for (int i = 0; i < 4; i++) {
        data_char = data_char | (*(char_ptr + i)) << (3 - i);
    }
    return data_char;
}

// Count the pattern size in the unit of half-byte(4-bit)
void CalcualtePatternSize(string pattern_name, int &pattern_size) {
	string str; 
	ifstream infile(pattern_name);
	if (!infile.is_open()) {
		cout << "Error opening file";
		exit(1);
	}

	while (getline(infile, str)) {
		pattern_size = pattern_size + str.length();
	}
	infile.close();
}

void SetDMADesTable(int num, long dest_addr, long src_addr, int size) {
	cout << "Set the DMA Descriptor Table for the pattern" << endl;
	cout << "des_addr is " << hex << dest_addr << endl;
	cout << "size is " << dec << size << endl;

}

void DMAOperation(int pattern_num, string pattern_name_prefix) {
	int *buf = new int[PAGE_SIZE / 8];
	int pattern_size = 0;
	int next_pattern_size = 0;
	long des_addr = 0;
	int dma_dt_cnt = 0;
	for (int k = 0; k < pattern_num; k++) {
		pattern_size = 0;
		// The maximum number of DMA DT is 128, starting from 0 to 127
		string pattern_name;
		pattern_name.insert(0, pattern_name_prefix + to_string(k) + ".txt");
		cout << pattern_name << endl;
		CalcualtePatternSize(pattern_name, pattern_size);
		// One page corresponds to one DMA Descriptor Table
		int page_num = (pattern_size % PAGE_SIZE == 0) ? (pattern_size / PAGE_SIZE) : (pattern_size / PAGE_SIZE + 1);
		cout << "page_num is " << dec << page_num << endl;
		cout << "patten_size is " << dec << pattern_size << endl;
			// Read the pattern to construct the DMA Descriptor Table
		for (int page_cnt = 0; page_cnt < page_num; page_cnt++) {
			// SMG apply a memory buffer
			//for (int m = 0; m < (PAGE_SIZE / 8); m++) {
			//	buf[m] = ReadDMDPattern(0, 0, pattern_name, m * 8, (m + 1) * 8);
		//	}
			// Less than or equal to PAGE_SIZE
			if (page_cnt == (page_num - 1)) {
				int data_size = pattern_size - (page_num - 1) * PAGE_SIZE; // The remaining data
				// FPGA DDR memory data width is 256-bit. pattern_size is the number of hex.
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
					cout << "Launch DMA operation" << endl;
					cout << "dma_dt_cnt is " << dma_dt_cnt << endl;
					cout << "Current pattern is " << pattern_name << endl;
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
			cout << "dma_dt_cnt is " << dma_dt_cnt << endl;
			dma_dt_cnt = dma_dt_cnt + 1;
			if (dma_dt_cnt == 128) {
				//Launch DMA operation
				cout << "---------------------" << endl;
				cout << "Launch DMA operation" << endl;
				cout << "Current pattern is " << pattern_name << endl;
				//cout << "dma_dt_cnt is " << dma_dt_cnt << endl;
				dma_dt_cnt = 0;
			}
		}
	}

}

void LightPix(int x, int y) {

}