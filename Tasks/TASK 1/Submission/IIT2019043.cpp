#include<bits/stdc++.h>
using namespace std;

const unsigned long long int mod = ((1<<63) - 1)*2 + 1;     //mod should be unsing long long int to handle such big value
const int p=26;             //p should be 26 as their are 26 letters in english alphabet
//takes a string and returns a vector which containts the hash values
//v[0] = hash(substr(0,1))
//v[1] = hash(substr(0,2))
//v[2] = hash(substr(0,3)) .... and so on
vector <long long int> computeHash(char *str)
{
    vector <long long int> hash_values(strlen(str));

    hash_values[0] = str[0] - 'a' + 1;      //we store hash_values[0] in prior
    long long int pp=26;                //then pp becomes 26
	for(int i=1;i<strlen(str);i++)      //as we already calculate i = 0 so, loop starts from i = 1;
	{
		hash_values[i] = (hash_values[i-1] + (str[i]-'a' +1)*pp)%mod;
		pp = (pp * p)%mod;
	}
	return hash_values;
	
}


//this a simple function of binary power and only change in the 
//function is to add unsined before long long int m
long long int binpow(long long int a,long long int b,unsigned long long int m)
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
	vector <long long int> hash_suffix(strlen(str)-1);
	
	//fix some error in thisfor loop
	for(long long int i=strlen(str);i>1;i--)
	{
		hash_suffix[strlen(str)-i] = ((hash_prefix[strlen(str) - 1] - hash_prefix[i-2])/binpow(p,i-1,mod))%mod;
	}
	
	map <long long int,long long int> m_prefix;
	map <long long int,long long int> m_suffix;
	
	for(int i=0;i<strlen(str)-1;i++)
	{
		m_prefix[hash_prefix[i]]++;
		m_suffix[hash_suffix[i]]++; //instead of m_prefix it should be m_suffix
	}
	
	int ans=0;
	
	for(auto it:m_prefix)
	{
		long long int f1=it.second;
		long long int f2=m_suffix[it.first];
		
		ans += f1 * f2; // + is missing to add all the answers
	}
	
	cout<<ans;
}
