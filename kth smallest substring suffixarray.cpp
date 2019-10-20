#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct suffix{
	int index, rank[2];
	suffix(int i=0, int j=0, int k=0): index(i){
		rank[0]=j,rank[1]=k;
	}
	bool operator==(const suffix& b){
		return rank[0]==b.rank[0] && rank[1]==b.rank[1];
	}
	bool operator<(const suffix& b){
		return rank[0]<b.rank[0] || rank[0]==b.rank[0] && rank[1]<b.rank[1];
	}
};

vector<int> suffixArray(const string& s){
	vector<int> rank(s.size());
	if(s.size()<=1) return rank;
	const int l = s.size();
	vector<suffix> a;
	for(int i=0; i<l; i++) a.push_back(suffix(i, s[i], i+1<l?s[i+1]:-1));

	
	for(int counter=l+1, step=2; counter>0; counter>>=1, step<<=1){
		sort(a.begin(), a.end());
		vector<int> extra(l, 0);
		for(int i=1; i<l; i++){
			if(a[i]==a[i-1]) extra[i]=1;
			extra[i]+=extra[i-1];
		}

		for(int i=0; i<l; i++) rank[a[i].index] = i - extra[i];
		for(int i=0; i<l; i++) a[i] = suffix(i, rank[i], i+step<l?rank[i+step]:-1);
	}
	
	vector<int> ans(l);
	for(int i=0; i<l; i++) ans[rank[i]] = i;
	return ans;
}


vector<int> LCP(const string& s, vector<int> sa=vector<int>()){
	vector<int> lcp(s.size(), 0);
	if(s.size()<=1) return lcp;
	const int l = s.size();
	if(!sa.size()) sa = suffixArray(s);
	vector<int> invsa(l);

	for(int i=0;i<l; i++) invsa[sa[i]] = i;

	for(int i=0, k=0; i<l; i++){
		if(invsa[i]==l-1){
			k=0; continue;
		}

		int j = sa[invsa[i]+1];
		while(j+k<l && i+k<l && s[i+k]==s[j+k]) k++;
		lcp[invsa[i]] = k;
		if(k) k--;
	}

	for(int i=lcp.size()-1; i>0; i--) lcp[i] = lcp[i-1];
	lcp[0] = 0;

	return lcp;
}

void print(auto ar, string name=string()){
	if(name.size()) cout << name <<": ";
	for(int i=0,l=ar.size(); i<l; i++) cout << ar[i] << " ";
	cout << endl;
}

template <typename T> int lowerBound(const vector<T>& a, const T& v){
	int l=0, r=a.size();
	while(l<r){
		int m = l+r>>1;
		if(a[m]>=v) r=m;
		else l = m+1;
	}
	return l;
}

template <typename T> int upperBound(const vector<T>& a, const T& v){
	int l=0, r=a.size();
	while(l<r){
		int m = l+r>>1;
		if(a[m]<=v) l=m+1;
		else r = m;
	}
	return l;
}

int main(){
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	string s; cin >> s;
	int t; cin >> t;
	vector<int> sa = suffixArray(s), lcp = LCP(s, sa);
	//print(sa, "sa"), print(lcp, "lcp");

	vector<int> suffixRank(s.size(), 0);
	suffixRank[0] = s.size() - sa[0];
	for(int i=1, l=s.size(); i<l; i++)
		suffixRank[i] = suffixRank[i-1] + (l - sa[i] - lcp[i]);

	int total = 0;
	for(int i=0, l=s.size(); i<l; i++) total += lcp[i];
	total = (s.size()*(s.size()+1))/2 - total;


	while(t--){
		int in; cin >> in;
		int lb = lowerBound(suffixRank, in);
		if(in > total) cout << '\n';
		else cout << s.substr(sa[lb], in - suffixRank[lb-1] + lcp[lb]) << '\n';
	}
}
