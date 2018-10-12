#include <iostream>
#include <stdlib.h>
#include "util.h"
#include "omp.h"
#include <stdio.h>
#include <sys/time.h>
using namespace std;

int main(int argc, char *argv[]) {

	// Combine the fasta files in the directory
	// directory path must end with '/'
	// the combined file will be ./tmp.fa

	double sec,usec,t;
	struct timeval t1,t2;
	gettimeofday(&t1,NULL);
	//string dir_path = "./data/x90_97/";
	string dir_path = argv[1];
//	cout<<dir_path <<endl;
	vector<string> files = listFastaFiles(dir_path);
//	if(files.size() > 1)
//	{
		combineFastaFile(dir_path, files);

//	t2=time(NULL);
//	cout<<"time for combine fasta file: "<<t2-t1<<endl;
//	m0 = (double)(t2-t1);
	
//	t1=time(NULL);
	// 1. Call CUDA ClustalW to generate a guide tree for the combined fasta file
	// start = omp_get_wtime();
		system("./cuda_clustalw2 -QUIET -INFILE=./tmp.fa -NEWTREE=./combined.dnd");
//	}
//	else
//	{
//		string tree ="./cuda_clustalw2 -QUIET -INFILE="+dir_path +files[0]+" -NEWTREE=./combined.dnd";
 //               system(tree.c_str());
//	}
//	system("./clustalw2 -QUIET -INFILE=./tmp.fa -NEWTREE=./combined.dnd");  
//	t2 = time(NULL);
//	m1=(double)(t2-t1);
//	cout<<"time 1and 2:"<<m1<<endl;  
	//end = omp_get_wtime();
	//  printf("time step 1(cuda): %f\n", end-start);

	// 2. Call ClustalW to do the rest steps of MSA
	//  start = omp_get_wtime();
//	t1=time(NULL);
	//    #pragma omp parallel for
	for(int i = 0; i < files.size(); i++) {
//		string tree ="./clustalw2 -QUIET -INFILE="+dir_path +files[i]+" -NEWTREE=./combined.dnd";
//		string tree ="./cuda_clustalw2 -QUIET -INFILE="+dir_path +files[i]+" -NEWTREE=./combined.dnd";
//		system(tree.c_str());
//		string cmd = "./clustalw2 -ALIGN -QUIET -USETREE=./combined.dnd -INFILE="+dir_path +files[i];
		string cmd = "./cuda_clustalw2 -ALIGN -QUIET -USETREE=./combined.dnd -INFILE="+dir_path +files[i];
		system(cmd.c_str());
	}
	gettimeofday(&t2,NULL);
	sec = (double)(1000000L*(t2.tv_sec-t1.tv_sec));
	usec = (double)((t2.tv_usec-t1.tv_usec));
	t = (double)((sec+usec)/1000000);
	cout<<"time 3:"<<t<<endl;
	cout<<"total time:"<<t<<endl;
	// end = omp_get_wtime();
	// printf("time step 3(openmp): %f\n", end-start);

	return 0;
}
