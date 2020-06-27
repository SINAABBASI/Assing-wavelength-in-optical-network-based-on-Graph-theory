#include <bits/stdc++.h>
using namespace std;
#define MAX 222
#define inf 1000000000
#define ll long long
#define endl '\n'
#define fr first
#define sc second

int n,m,k,x[MAX],y[MAX],w[MAX];
vector<pair<pair<int,int>,int> > req;
vector<pair<int,int> > g[MAX];

priority_queue<pair<int,int> > pq;
int dis[MAX][MAX];
void dik(int a){
	pq.push({0,a});
	dis[a][a]=0;
	while(pq.size()){
		int u=pq.top().sc;
		pq.pop();
		for(auto i : g[u]){
			int v=i.fr;
			int weight=w[i.sc];
			if(dis[a][v]> dis[a][u]+weight){
				dis[a][v]= dis[a][u]+weight;
				pq.push({-dis[a][v],v});
			}
		}
	}
	// for(int i = 0; i < n ; i++)cout<<dis[i]<<endl;
	// return dis[b];
	return;
}

int countEdge[2*MAX],parId[2*MAX],par[MAX];
long double dynamicDis[MAX];
priority_queue<pair<long double,int> > pqq;

int maxDistance=0,maxChannel=0,channelNum=0;



long double huristicFun(int edgeId){
	return pow(1.1,1.0*(countEdge[edgeId]+1.0*k*max(0,countEdge[edgeId]-10))/10);
	// return 1;
}

void printPath(int st,int cur){
	if(cur!=st){
		printPath(st,par[cur]);
		countEdge[parId[cur]]++;
		channelNum=max(channelNum,countEdge[parId[cur]]);
		maxChannel=max(maxChannel,countEdge[parId[cur]]);
	}
	///Show path
	// cout<<cur<<" ";
}

void dik(int a,int b){
	for(int i = 0; i < n ; i++)dynamicDis[i]=inf,dis[a][i]=inf, par[i]=i;
	for(int i = 0; i < m ; i++)parId[i]=-1;
	pqq.push({0,a});
	dynamicDis[a]=0;
	dis[a][a]=0;
	while(pqq.size()){
		int u=pqq.top().sc;
		pqq.pop();
		for(auto i : g[u]){
			int v=i.fr;
			long double weight=huristicFun(i.sc)*w[i.sc];
			if(dynamicDis[v] > dynamicDis[u]+weight){
				dynamicDis[v] = dynamicDis[u]+weight;
				dis[a][v]= dis[a][u]+w[i.sc];
				par[v]=u;
				parId[v]=i.sc;
				pqq.push({-dynamicDis[v],v});
			}
		}
	}
	maxDistance=max(dis[a][b],maxDistance);
	channelNum=0;
	//showPath
	// cout<<"Path "<<a<<"->"<<b<< ":";
	printPath(a,b);
	// cout<<endl;
	// cout<<"Dis: "<<dis[a][b]<<right<<setw(10)<<" channelInUse: "<<channelNum<<endl;
	// cout<<endl;
}


bool cmp(pair<pair<int,int>,int > a,pair<pair<int,int> ,int> b){
	return dis[a.fr.fr][a.fr.sc] < dis[b.fr.fr][b.fr.sc];
}
int main() {

	clock_t tStart = clock();
		
	cin>>n>>m;
	for(int i= 0; i < m; i++){
		cin>>x[i]>>y[i]>>w[i];
		g[x[i]].push_back({y[i],i});
		g[y[i]].push_back({x[i],i});
	}

	memset(dis,127,sizeof dis);
	for(int i = 0; i < n ; i++)dik(i);

	int a,sum=0;
	for(int i = 1; i < n ; i++){
		for(int j = 0; j < i; j++){
			cin>>a;
			a*=1;
			sum+=a;
			if(a){
				req.push_back({{j,i},a});
			}
		}
	}
	sort(req.begin(), req.end(),cmp);
	reverse(req.begin(), req.end());
	// for(auto i : req){
	// 	cerr<<i.fr.fr<<" "<<i.fr.sc<<" "<<dis[i.fr.fr][i.fr.sc]<<endl;
	// }
	k=0;

	for(;k<=10;k++){
		memset(countEdge,0,sizeof countEdge);
		maxDistance=0,maxChannel=0,channelNum=0;
		for(auto i : req){
			for(int j = 0; j < i.sc ;j++){
				// cout<<i.fr.fr<<i.fr.sc<<endl;
				dik(i.fr.fr,i.fr.sc);
			}
		}
		cout<<"Husristic K:"<<k<<endl;
		cout<<"maxChannel : "<<maxChannel<<endl;
		cout<<"maxDistance: "<<maxDistance<<endl;
		cout<<endl;
	}

	cout<<"Total request: "<<sum<<endl;
	printf("Time taken: %.5fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
	return 0;
}