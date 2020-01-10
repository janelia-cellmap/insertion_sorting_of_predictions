#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <algorithm>

using namespace std;
int insertion_sort_i=1, insertion_sort_j;
ofstream outfile;

const char kPathSeparator =
#ifdef _WIN32
                            '\\';
#else
                            '/';
#endif


void printAndWrite(char const* buffer){
	printf("%s",buffer);
	outfile<<buffer;
}

void printCurrentOrder(string *sorted_samples, int sample_counts) {
	char buffer[100];
	sprintf(buffer, "Sorted Order (i = %d, j = %d):\n", insertion_sort_i, insertion_sort_j);
	printAndWrite(buffer);
	string sorted_samples_string = "";
	for (int i = 0; i < sample_counts; i++) {
		sorted_samples_string += sorted_samples[i] + "\n";
	}
	sorted_samples_string+="\n";
	printAndWrite(sorted_samples_string.c_str());
}


bool needToSwap(string *sorted_samples, int sample_counts) {
	while (1) {
		char buffer[100];
		sprintf(buffer, "Is %s better than %s? Enter y or n (or q to quit): ", sorted_samples[insertion_sort_j - 1].c_str(), sorted_samples[insertion_sort_j].c_str());
		printAndWrite(buffer);
		string answer;
		cin >> answer;
		outfile<<answer<<"\n";
		if (answer == "y") {
			sprintf(buffer, "Swapping %s and %s.\n", sorted_samples[insertion_sort_j - 1].c_str(), sorted_samples[insertion_sort_j].c_str());
			printAndWrite(buffer);
			swap(sorted_samples[insertion_sort_j - 1], sorted_samples[insertion_sort_j]);
			printCurrentOrder(sorted_samples, sample_counts);
			return true;
		} else if (answer == "n") {
			printCurrentOrder(sorted_samples, sample_counts);
			return false;
		} else if (answer == "q"){
			sprintf(buffer, "Next Iteration To Check (i = %d, j = %d)\n", insertion_sort_i, insertion_sort_j);
			printAndWrite(buffer);
			outfile.close();
			exit(0);
		} else{
			printf("Invalid response.\n");
		}
	}
}

void interactiveInsertionSort(string * sorted_samples, int sample_counts, bool indices_provided) {
	bool first_loop = true;
	while (insertion_sort_i < sample_counts) {

		if(!(first_loop && indices_provided)){
			insertion_sort_j = insertion_sort_i;
		}

		first_loop = false;

		while (insertion_sort_j > 0 && needToSwap(sorted_samples, sample_counts)) {
			insertion_sort_j = insertion_sort_j - 1;
		}
		insertion_sort_i = insertion_sort_i + 1;
	}
}

int getIntBetweenCharacters(string str, string start, string stop){
	unsigned first_index = str.find(start)+3;
	unsigned last_index = str.find(stop);
	return stoi( str.substr(first_index,last_index-first_index));
}

bool doesFileExist(const char *filename)
{
    std::ifstream infile(filename);
    return infile.good();
}

int main(int argc, char **argv) {
	if (argc<2){
		printf("Need to provide a filename with a list of predictions.\n");
		return 0;
	}

	string filename = argv[1];
	string line;
	ifstream myfile(filename);


	bool indices_provided = false;
	int sample_counts = 0;
	string sorted_samples[500]; //assumes max of 500
	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			if(line.find("Next Iteration") != string::npos){
				insertion_sort_i = getIntBetweenCharacters(line, "i =",",");
				insertion_sort_j = getIntBetweenCharacters(line, "j =",")");
				indices_provided = true;
			}
			else if (line.find("Order ") != string::npos ) {
				sample_counts = 0;
				if(line.find("i =") != string::npos){
					insertion_sort_i = getIntBetweenCharacters(line, "i =",",");
					insertion_sort_j = getIntBetweenCharacters(line, "j =",")");
					indices_provided = true;
				}
			} else if(line=="" || line.find("?") != string::npos ) {//then are non-sample lines
				continue;
			}
			else{
				sorted_samples[sample_counts] = line;
				sample_counts++;
			}
		}

		myfile.close();
	} else{
		printf("Unable to open file %s.\n", filename.c_str());
		return 0;
	}


	string output_filename = "";
    if(filename.find("_sorted_results.txt") == string::npos){//not in there
    	int idx0 = filename.rfind(kPathSeparator);
    	int idx1 = filename.rfind(".");
		output_filename = filename.substr(0,idx0+1) + filename.substr(idx0+1, idx1-idx0-1) + "_sorted_results.txt";
		if (doesFileExist(output_filename.c_str())) {
			printf("WARNING: Output file %s already exists!\nContinue (y/n)? ",
					output_filename.c_str());
			string answer;
			cin >> answer;
			if (answer != "y") {
				printf("Exiting\n");
				return 0;
			}
		}
		outfile.open(output_filename);
    }
    else{
    	output_filename = filename;
		outfile.open(output_filename, std::ios_base::app);
    }
	printf("\n");

	printCurrentOrder(sorted_samples, sample_counts);
	interactiveInsertionSort(sorted_samples, sample_counts, indices_provided);
	printAndWrite("Sorting complete!\n");
	outfile.close();
	return 0;
}
