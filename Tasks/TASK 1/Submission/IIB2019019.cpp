#include<bits/stdc++.h>
using namespace std;

const unsigned long long int mod = (1<<64)-59; //value of mod must be prime (1<<64)-59 is a prime and within constraint. use of unsigned to hold large size number.
const int p=31;      // closest prime number around number of alphabets.
//takes a string and returns a vector which containts the hash values
//v[0] = hash(substr(0,1))
//v[1] = hash(substr(0,2))
//v[2] = hash(substr(0,3)) .... and so on
vector <long long int> computeHash(string str)
{
	
	vector <long long int> hash_values(str.length());
    hash_values[0]=str[0]-'a'+1;  // proir setting value of hash_values[0] to calculate further values adding 1 to avoid dealing with zero in case of "a" ,"aa",....
	long long int pp=31;    // initial value of pp =1 after first step value of pp=(1*31)%mod=31
	for(int i=1;i<str.length();i++) //staring from i=1 to avoid runtime error as in this case i=0 , index of hash_values[i-1] will become -1 
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
	string str;cin>>str; //in C++ , char* they are constant array of char. we can't define this as const we have to take input from user.
	
	vector < long long int> hash_prefix = computeHash(str);
    vector <unsigned long long int> hash_suffix(str.length()-1); // total number of suffix will be str.length()-1
	
	for(long long int i=str.length();i>1;i--) // fix some errors to calculate hash_suffix
	{
		hash_suffix[str.length()-i] = ((hash_prefix[str.length()-1] - hash_prefix[i-2])/binpow(p,i-1,mod))%mod;    // hash_prefix[str.length()-1] will contain whole string hash number , calculating hash_suffix vector by using already calculate hash_prefix vector.
	} // for finding length of string we will use str.length()
	map <long long int,long long int> m_prefix;
	map <long long int,long long int> m_suffix;
	
	for(int i=0;i<str.length()-1;i++)
	{
		m_prefix[hash_prefix[i]]++;
		m_suffix[hash_suffix[i]]++;  //hash_suffix value will be calculated in m_suffix map to that we could check later the presence of same substring
	}
	long long ans=0;  // changed datatype to long long to hold large size number.
	
	for(auto it:m_prefix)
	{
		long long int f1=it.second;
		long long int f2=m_suffix[it.first];
		
		ans += f1 * f2;   // adding + operator to calculate total number of prefixes which are also suffix.
		
	}
	
	cout<<ans;
}
