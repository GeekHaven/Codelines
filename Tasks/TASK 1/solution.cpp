#include<bits/stdc++.h>
using namespace std;

const long long int mod = (1<<64);
const int p=22;
//takes a string and returns a vector which containts the hash values
//v[0] = hash(substr(0,1))
//v[1] = hash(substr(0,2))
//v[2] = hash(substr(0,3)) .... and so on
vector <long long int> computeHash(char *str)
{
	
	vector <long long int> hash_values(strlen(str));
	long long int pp=1;

	for(int i=0;i<strlen(str);i++)
	{
		hash_values[i] = (hash_values[i-1] + (str[i]-'a')*pp)%mod;
		pp = (pp * p)%mod;
	}
	return hash_values;
	
}

long long int binpow(long long int a,long long int b,long long int m)
{
	long long int res=1;
	while(b>0)
	{
		if(b&1)
		res=(res*a)%m;
		a=(a*a)%m;
		b>>=1;
	}
	return res;
}


int main()
{
	char *str;cin>>str;
	
	vector <long long int> hash_prefix = computeHash(str);
	vector <long long int> hash_suffix(strlen(str));
	
	for(long long int i=strlen(str)-1;i>=0;i--)
	{
		hash_suffix[strlen(str)-i] = ((hash_prefix[i] - hash_prefix[i-1]) * binpow(binpow(p,i,mod),mod-2,mod))%mod;
	}
	
	map <long long int,long long int> m_prefix;
	map <long long int,long long int> m_suffix;
	
	for(int i=0;i<strlen(str);i++)
	{
		m_prefix[hash_prefix[i]]++;
		m_prefix[hash_suffix[i]]++;
	}
	
	int ans=0;
	
	for(auto it:m_prefix)
	{
		long long int f1=it.second;
		long long int f2=m_suffix[it.first];
		
		ans = f1 * f2;
		
	}
	
	cout<<ans;
}
	
	
