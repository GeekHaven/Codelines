#include<bits/stdc++.h>
using namespace std;

const long long int mod = 1e9+9;
const int p=31;
//takes a string and returns a vector which containts the hash values
//v[0] = hash(substr(0,1))
//v[1] = hash(substr(0,2))
//v[2] = hash(substr(0,3)) .... and so on
vector <long long int> computeHash(string str)
{
	
	vector <long long int> hash_values(str.length());
    hash_values[0]=str[0]-'a'+1;
	long long int pp=31;
	for(int i=1;i<str.length();i++)
	{
		hash_values[i] = (hash_values[i-1] + (str[i]-'a'+1)*pp)%mod;
		pp = (pp * p)%mod;
	}
	return hash_values;
	
}
long long binpow(unsigned long long a,unsigned long long b,unsigned long long m) {
    a %= m;
    long long res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}

int main()
{
	string str;cin>>str;
	
	vector < long long int> hash_prefix = computeHash(str);
    vector <unsigned long long int> hash_suffix(str.length()-1);
	
	for(long long int i=str.length();i>1;i--)
	{
		hash_suffix[str.length()-i] = ((hash_prefix[str.length()-1] - hash_prefix[i-2]) * binpow(binpow(p,i-1,mod),mod- 
       2,mod))%mod;
	}
	map <long long int,long long int> m_prefix;
	map <long long int,long long int> m_suffix;
	
	for(int i=0;i<str.length()-1;i++)
	{
		m_prefix[hash_prefix[i]]++;
		m_suffix[hash_suffix[i]]++;
	}
	long long ans=0;
	
	for(auto it:m_prefix)
	{
		long long int f1=it.second;
		long long int f2=m_suffix[it.first];
		
		ans += f1 * f2;
		
	}
	
	cout<<ans;
}