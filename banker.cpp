#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
using namespace std;
int numberOfProcesses = 0;
int numberOfResources = 0;
int ProcessNumberForNewRequest;

// Function to find the system is in safe state or not
bool isSafe(vector<int>& processes, vector<int>& AvalibleMatrix, vector<vector<int>>& maxMatrix,
	vector<vector<int>>& allocationMatrix, vector<vector<int>>& needMatrix,bool newReq)
{
	vector<bool>finish(numberOfProcesses, 0);
	vector<int>safeSeq(numberOfProcesses);
	vector<int>work(numberOfResources, 0);
	for (int i = 0; i < numberOfResources; i++)
		work[i] = AvalibleMatrix[i];
	int count = 0;
	while (count < numberOfProcesses)
	{
		bool found = false;
		for (int p = 0; p < numberOfProcesses; p++)
		{
			if (finish[p] == 0)
			{
				int j;
				for (j = 0; j < numberOfResources; j++)
					if (needMatrix[p][j] > work[j])
						break;
				if (j == numberOfResources)
				{
					for (int k = 0; k < numberOfResources; k++)
						work[k] += allocationMatrix[p][k];
					safeSeq[count++] = p;
					finish[p] = 1;
					found = true;
				}
			}
		}
		if (found == false)
		{
			cout << "System is not in safe state";
			return false;
		}
	}
	if (!newReq) {
		cout << "Yes, Safe State < ";
		for (int i = 0; i < numberOfProcesses; i++)
			cout << "p"<<safeSeq[i] << ", ";
		cout << " >" << endl;
	}
	else {
		cout << "Yes, Request can be granted with Safe State, Safe state  <p" << ProcessNumberForNewRequest << "req, ";
		for (int i = 0; i < numberOfProcesses; i++)
			cout <<"p"<< safeSeq[i] << ", ";
		cout << " >" << endl;
	}
	return true;
}

int main()
{
	int reset = 0;
	do {
#pragma region Process_Input
		cout << "**************************** " << endl;
		cout << "Enter Number of processes.. : ";
		string n="";
		getline(cin, n);
		while (n.empty() || stoi(n) <= 0)
		{
			cout << " ***ERROR!*** Number of process can't be an empty value OR negative value OR 0!!" << endl;
			cout << "Enter Number of processes.. : ";
			getline(cin, n);
		}
		numberOfProcesses = stoi(n);
		cout << "**************************** " << endl << endl;
#pragma endregion

#pragma region initialize_processes
		vector<int>processes, processes_copy;
		for (int i = 0; i < numberOfProcesses; i++)
		{
			processes.emplace_back(i);
			processes_copy.emplace_back(i);
		}
#pragma endregion

#pragma region ResourcesInput
		cout << "**************************** " << endl;
		cout << "Enter Number of Resources.. : ";
		string m;
		getline(cin, m);
		while (m.empty() || stoi(m) <= 0)
		{
			cout << " ***ERROR!!*** Number of Resources can't be an empty value OR negative value OR 0!!" << endl;
			cout << "Enter Number of Resources.. : ";
			getline(cin, m);
		}
		numberOfResources = stoi(m);
		cout << "**************************** " << endl << endl;
#pragma endregion

		string input = "";

#pragma region Avalible_Matrix
		cout << "**************************** " << endl;
		cout << "Enter the Avalible Matrix.. " << endl;
		vector<int>AvalibleMatrix, AvalibleMatrix_copy(numberOfResources, 0);
		for (int i = 0; i < numberOfResources; i++)
		{
			input;
			int avalibleValue = 0;
			cout << "Number of avalible instances of Resource number [" << i << "] equales >> ";
			getline(cin, input);
			while (input.empty() || stoi(input) < 0)
			{
				cout << " ***ERROR!!*** Number of avalible instances of Resource can't be an empty value OR negative value!!" << endl;
				cout << "Number of avalible instances of Resource number [" << i << "] equales >> ";
				getline(cin, input);
			}
			avalibleValue = stoi(input);
			AvalibleMatrix.emplace_back(avalibleValue);
			AvalibleMatrix_copy.emplace_back(avalibleValue);
		}
		cout << "**************************** " << endl << endl;
#pragma endregion

#pragma region Maximum_Matrix
		cout << "**************************** " << endl;
		cout << "Enter the Maximum Matrix.. " << endl;
		vector<vector<int>>MaximumMatrix(numberOfProcesses, vector<int>(numberOfResources));
		vector<vector<int>>MaximumMatrix_copy(numberOfProcesses, vector<int>(numberOfResources));
		for (int i = 0; i < numberOfProcesses; i++)
			for (int j = 0; j < numberOfResources; j++)
			{
				MaximumMatrix.emplace_back(0);
				MaximumMatrix_copy.emplace_back(0);
			}
		for (int i = 0; i < numberOfProcesses; i++)
		{
			for (int j = 0; j < numberOfResources; j++)
			{
				input = "";
				int MaxValue = 0;
				cout << "Maximum value of instances that process [" << i << "] might request from resource [" << j << "] equales >> ";
				getline(cin, input);
				while (input.empty() || stoi(input) < 0)
				{
					cout << " ***ERROR!!*** Maximum value of instances can't be an empty value OR negative value!!" << endl;
					cout << "Maximum value of instances that process [" << i << "] might request from resource [" << j << "] equales >> ";
					getline(cin, input);
				}
				MaxValue = stoi(input);
				MaximumMatrix[i][j] = MaxValue;
				MaximumMatrix_copy[i][j] = MaxValue;
			}
			cout << "---------------------------------------------------------------------------------------------------" << endl;
		}
		cout << "**************************** " << endl << endl;
#pragma endregion

#pragma region Allocation_Matrix
		cout << "**************************** " << endl;
		cout << "Enter the Allocation Matrix.. " << endl;
		vector<vector<int>>AllocationMatrix(numberOfProcesses, vector<int>(numberOfResources));
		vector<vector<int>>AllocationMatrix_copy(numberOfProcesses, vector<int>(numberOfResources));
		for (int i = 0; i < numberOfProcesses; i++)
			for (int j = 0; j < numberOfResources; j++)
			{
				AllocationMatrix.emplace_back(0);
				AllocationMatrix_copy.emplace_back(0);
			}
		for (int i = 0; i < numberOfProcesses; i++)
		{
			for (int j = 0; j < numberOfResources; j++)
			{
				input = "";
				int AllocatedValue = 0;
				cout << "Process [" << i << "] is currently allocates from resource [" << j << "] a number of instances equales >> ";
				getline(cin, input);
				while (input.empty() || stoi(input) < 0)
				{
					cout << " ***ERROR!!*** Allocation value of instances can't be an empty value!!" << endl;
					cout << "Process [" << i << "] is currently allocates from resource [" << j << "] a number of instances equales >> ";
					getline(cin, input);
				}
				AllocatedValue = stoi(input);
				AllocationMatrix[i][j] = AllocatedValue;
				AllocationMatrix_copy[i][j] = AllocatedValue;
			}
			cout << "-------------------------------------------------------------------------------------------------------" << endl;
		}
		cout << "**************************** " << endl << endl;
#pragma endregion

#pragma region Need_Matrix
		cout << "The Need Matrix is : " << endl;
		vector<vector<int>>needMatrix(numberOfProcesses, vector<int>(numberOfResources));
		vector<vector<int>>needMatrix_copy(numberOfProcesses, vector<int>(numberOfResources));
		for (int i = 0; i < numberOfProcesses; i++)
			for (int j = 0; j < numberOfResources; j++)
			{
				needMatrix.emplace_back(0);
				needMatrix_copy.emplace_back(0);
			}
		for (int i = 0; i < numberOfProcesses; i++)
		{
			for (int j = 0; j < numberOfResources; j++)
			{
				needMatrix.emplace_back(0);
				needMatrix_copy.emplace_back(0);
			}
		}
		for (int i = 0; i < numberOfProcesses; i++)
			for (int j = 0; j < numberOfResources; j++)
			{
				needMatrix[i][j] = MaximumMatrix[i][j] - AllocationMatrix[i][j];
				needMatrix_copy[i][j] = MaximumMatrix[i][j] - AllocationMatrix[i][j];
			}

		for (int i = 0; i < numberOfProcesses; i++)
		{
			for (int j = 0; j < numberOfResources; j++)
			{
				cout << needMatrix[i][j] << " ";
			}
			cout << endl;
		}
#pragma endregion


		bool safe = false;
		int question;

		cout << "If you need to know the state of the system Enter 1 " << endl;
		cout << "If you don't, Enter 0 " << endl;
		cout << ">> ";
		cin >> question;
		if (question == 1)
		{
			safe = isSafe(processes, AvalibleMatrix, MaximumMatrix, AllocationMatrix, needMatrix, false);
			if (safe == true)
			{
				int inquiry;
				string inquiryS="";
				cout << endl << "To check a new resource request allocation Enter >> 1 " << endl;
				cout << "If you don't, Enter >> 0 " << endl;
				getline(cin,inquiryS);
				while (inquiryS.empty())
				{
					cout << "**ERROR** THIS IS FIELD CANNOT BE EMPTY, ALSO YOU CANNOT ENTER PROCESS NUMBER OUT OF RANGE!!" << endl;
					cout << endl << "To check a new resource request allocation Enter >> 1 " << endl;
					cout << "If you don't, Enter >> 0 " << endl;
					getline(cin, inquiryS);
				}
				inquiry = stoi(inquiryS);
				if (inquiry == 1)
				{
					while (inquiry == 1)
					{
						//initialize all data structures we are gonna use because we need to handle the new request with the main data not the modified data due to the previous request
						// for (int i = 0; i < numberOfResources; i++)
						// {
						// 	AvalibleMatrix_copy[i] = AvalibleMatrix[i];
						// 	processes_copy[i] = processes[i];
						// }
						// for (int i = 0; i < numberOfProcesses; i++)
						// {
						// 	for (int j = 0; j < numberOfResources; j++)
						// 	{
						// 		needMatrix_copy[i][j] = needMatrix[i][j];
						// 		AllocationMatrix_copy[i][j] = AllocationMatrix[i][j];
						// 		MaximumMatrix_copy[i][j] = MaximumMatrix[i][j];
						// 	}
						// }
						string processNumberS="";
						cout << "**************** NOTE that our processes indexed from 0 to n not from 1 to n ***************" << endl;
						cout << "Enter the process number that you need to check to allocate resources for it >> ";
						getline(cin,processNumberS);
						while(processNumberS.empty()||stoi(processNumberS)<0||stoi(processNumberS)>=numberOfProcesses)
						{
							cout << "******ERROR*** PLEASE ENTER NUMBER THAT IN RANGE OF PROCESSES YOU ENTERED AT BEGGINING!!!" << endl;
							cout << "Enter the process number that you need to check to allocate resources for it >> ";
							getline(cin,processNumberS);
						}
						ProcessNumberForNewRequest=stoi(processNumberS);

						vector<int>newRequest(numberOfResources, 0);
						cout << "************************************************" << endl;
						cout << " Enter values of request for each resource.." << endl;
						cout << "*************************************************" << endl;
						for (int i = 0; i < numberOfResources; i++)
						{
							string requestValueS="";
							int requestValue;
							cout << "Desired number of instances from resource [" << i << "] you need to allocate is >> ";
							getline(cin,requestValueS);
							while(requestValueS.empty()||stoi(requestValueS)<0){
								cout<<"ERROR, please enter right value!!"<<endl;
								cout << "Desired number of instances from resource [" << i << "] you need to allocate is >> ";
								getline(cin,requestValueS);
							}
							requestValue=stoi(requestValueS);
							newRequest[i] = requestValue;
						}
						int checkFlag = 1;
						for (int i = 0; i < numberOfResources; i++)
						{
							if (newRequest[i] <= needMatrix[ProcessNumberForNewRequest][i] && newRequest[i] <= AvalibleMatrix[i])
							{
								checkFlag = 1;
							}
							else
							{
								checkFlag = 0;
								break;
							}
						}
						if (checkFlag == 1)
						{
							for (int i = 0; i < numberOfResources; i++)
							{
								AvalibleMatrix[i] = AvalibleMatrix[i] - newRequest[i];
								needMatrix[ProcessNumberForNewRequest][i] = needMatrix[ProcessNumberForNewRequest][i] - newRequest[i];
								AllocationMatrix[ProcessNumberForNewRequest][i] = AllocationMatrix[ProcessNumberForNewRequest][i] + newRequest[i];
							}
							isSafe(processes, AvalibleMatrix, MaximumMatrix, AllocationMatrix, needMatrix, true);
						}
						else
						{
							cout << "This request cannot be granted!.." << endl;
						}

						cout << endl << "To check a new resource request allocation Enter 1 " << endl;
						cout << "If you don't, Enter 0 " << endl;
						cin >> inquiry;
						for (int i = 0; i < numberOfResources; i++)
						{
							AvalibleMatrix[i] = AvalibleMatrix[i] + newRequest[i];
							needMatrix[ProcessNumberForNewRequest][i] = needMatrix[ProcessNumberForNewRequest][i] + newRequest[i];
							AllocationMatrix[ProcessNumberForNewRequest][i] = AllocationMatrix[ProcessNumberForNewRequest][i] - newRequest[i];
						}
						if(inquiry==0)
						{
							cout << "To Reset session and start without running program again,  Enter >> 1" << endl;
							cout << "To End session and to start you need to run program again, Enter >> 0" << endl;
							cin >> reset;
							if (reset == 0)
							{
								cout << "Session is End!" << endl;
								exit;
							}					
						}						
						// if(inquiry==0){reset=1;}
					}
				}
				else if(inquiry==0)
				{
					cout << "To Reset session and start without running program again,  Enter >> 1" << endl;
					cout << "To End session and to start you need to run program again, Enter >> 0" << endl;
					cin >> reset;
					if (reset == 0)
					{
						cout << "Session is End!" << endl;
						exit;
					}
				}
			}
		}
		else
		{
			cout << "So, you can't enquiry if system can grant any additional requests or not, you now have 2 options, to reset the session from scratch, or End session" << endl;
			cout << "To Reset session, Enter >> 1" << endl;
			cout << "To End session,   Enter >> 0" << endl;
			cin >> reset;
			if (reset == 0)
			{
				cout << "Session is End!" << endl;
				exit;
			}
		}
	}while (reset);
	return 0;
}