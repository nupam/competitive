#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct process{
	int at, bt, ct, tat, wt, rt, pid;

	process(int at=0, int bt=0, int pid=-1):at(at), bt(bt), rt(bt), pid(pid){}

	void  exit(int t){
		ct = t;
		rt = 0;
		tat = ct-at;
		wt = tat-bt;
	}

};

struct arrival_cmp{
	bool operator()(const process& a, const process& b){ //for making min heap based on at
		return a.at > b.at;
	}
};


int main(){
	int n; cout << "num Process: "; cin >> n;

	priority_queue<process, vector<process>, arrival_cmp> processes;

	for(int i=0; i<n; i++){
		int at, bt; cin >> at >> bt;
		processes.push(process(at, bt, i));
	}

	int quantum;
	cout << "Enter quantum: "; cin >> quantum;



	int t=processes.top().at;
	queue<process> q;
	while(!processes.empty() && processes.top().at==t){
		q.push(processes.top());
		processes.pop();
	}

	vector<process> done;

	while(!q.empty()){
		process curr = q.front(); q.pop();

		if(curr.rt<=quantum){
			cout << "executing " << curr.pid << " for " << curr.rt << "\n";
			t += curr.rt;
			curr.exit(t);
			done.push_back(curr);
		}
		else{
			cout << "executing " << curr.pid << " for " << quantum << "\n";
			curr.rt -= quantum;
			t += quantum;
		}

		while(!processes.empty() && processes.top().at < t){
			q.push(processes.top());
			processes.pop();
		}

		if(curr.rt) q.push(curr);

		while(!processes.empty() && processes.top().at == t){
			q.push(processes.top());
			processes.pop();
		}


		if(q.empty() && !processes.empty()){ //no more processes in active queue but more are comming
			t = processes.top().at;
			while(!processes.empty() && processes.top().at==t){
				q.push(processes.top());
				processes.pop();
			}
		}

	}

	cout << "done.size()" << done.size() << "\n";
	for(int i=0; i<done.size(); i++){
		cout << done[i].at << " " <<done[i].bt << " "<< done[i].rt << " " << done[i].tat << " " << done[i].wt << "\n";
	}
	double avg_wt = 0;
	for(int i=0; i<done.size(); i++){
		avg_wt += 1.0*done[i].wt/done.size();
	}

	cout << avg_wt << "\n";


}