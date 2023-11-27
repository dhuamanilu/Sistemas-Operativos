#include <bits/stdc++.h>
#define ll long long
#define FOR(i,a,b) for(long long (i)=(a);i<(b);i++)
using namespace std;
void solve(){
	ll n;
	cin>>n;
	vector<ll> a;
	FOR(i,0,n){
		ll x;
		cin>>x;
		a.pb(x);
	}
	ll ans=0;
	for(auto & e : a){
		ans+=e;
	}
	cout<<ans<<endl;
}
int main(){
	ll t;
	cin>>t;
	while(t--) solve();
	return 0;
}
