//https://slaystudy.com/c-merge-sort-vector/

#include <iostream>
#include <vector>
#include <unistd.h> //get num cores & get pid
#include <fstream> //read in file
#include <sstream> //break up the string into ints
#include <stdlib.h> //get proc info



void MergeSortedIntervals(std::vector<int>& v, int s, int m, int e) {
	
	std::vector<int> temp;

	int i, j;
	i = s;
	j = m + 1;

	while (i <= m && j <= e) {
		if (v[i] <= v[j]) {
			temp.push_back(v[i]);
			++i;
		}
		else {
			temp.push_back(v[j]);
			++j;
		}
	}
	while (i <= m) {
		temp.push_back(v[i]);
		++i;
	}
	while (j <= e) {
		temp.push_back(v[j]);
		++j;
	}
	for (int i = s; i <= e; ++i)
		v[i] = temp[i - s];
}

void MergeSort(std::vector<int>& v, int s, int e) {
	if (s < e) {
		int m = (s + e) / 2;
		MergeSort(v, s, m);
		MergeSort(v, m + 1, e);
		MergeSortedIntervals(v, s, m, e);
	}
}

int main(int argc, char **argv) {

    std::vector<int> numbers_vector;

    std::ifstream read("/home/william/CS_5573/mergesort_project/random_numbers_10M");
    if (read.is_open()) {
        std::string file_as_string;
        getline(read, file_as_string);            
        std::stringstream s_stream(file_as_string);
        while (s_stream.good())
        {
            std::string substr;
            getline(s_stream,substr,',');
            numbers_vector.push_back(stoi(substr));
        }
    }
	else {
		printf("Error opening file");
	}

	MergeSort(numbers_vector, 0, numbers_vector.size() - 1);

	auto arg = argv[1];
	int process_id = getpid();
	std::string proc_as_string = std::to_string(process_id);
	//std::string calling_proc_as_string = std::to_string(arg);
	std::string location_as_string = "/home/william/CS_5573/project/results/";
	std::string file_location = location_as_string + proc_as_string + ".txt";

	std::ofstream write_file;
	write_file.open(file_location);
	write_file << argv[1] << "\n";
	write_file.close();

	system("cat /proc/$PPID/stat >> /home/william/CS_5573/project/results/${PPID}.txt");
	system("cat /proc/$PPID/status >> /home/william/CS_5573/project/results/${PPID}.txt");
	system("cat /proc/$PPID/schedstat >> /home/william/CS_5573/project/results/${PPID}.txt");
	system("echo q | htop -C | aha --line-fix | html2text -width 999 | grep -v \"F1Help\" | grep -v \"xml version=\" >> /home/william/CS_5573/project/results/${PPID}.txt");
	system("top -b -n1 | head -n 30 >> /home/william/CS_5573/project/results/${PPID}.txt");
	system("ps -eo pid,tid,class,rtprio,ni,pri,psr,pcpu,pmem,comm | head -n 1 >> /home/william/CS_5573/project/results/${PPID}.txt");
	system("ps -eo pid,tid,class,rtprio,ni,pri,psr,pcpu,pmem,comm | grep merge_sort >> /home/william/CS_5573/project/results/${PPID}.txt");
	
	printf("\nSort Process: ppid: %d   pid: %d\n", getppid(), getpid());

    return 0;
}