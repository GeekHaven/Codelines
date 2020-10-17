#include<bits/stdc++.h>
using namespace std;
/* mod should be prime bcoz we are using fermat little theorem to calculate mmi
 * under the constraints I chooosed 18446744073709551557 as my prime
 * to hold this no. we need 64 bit ,uint64 can hold upto 1<<64 -1,
 * */ 
const uint64_t mod = ULLONG_MAX - 58;
/* prime closet to no. of alphabet is 31*/
const int p = 31;

/*if we use 31 as ,i call it index specifer,don't know the actual term ,and if the length
 *of string in long long (i.e 2147483647) ,index specifier goes to 31^2147483647 ,large 
 to hold by long long even we use the modulo , change the vector type to uint64
 */
vector<uint64_t> computeHash(string str){
	vector<uint64_t> hash_values(str.length());
	/* ------overflow-------,in hash_values[i] = (hash_values[i-1] + (str[i]-'a')*pp)%mod;
	 * and in pp = (pp * p)%mod;
	 * as 64 bit * 64 bit ,even uint64 can't hold
	 * arithmetic of these kind in c++ are generally not allowed 
	 * we need to boostlibrary or 
	 * some compiler GCC or Clang handle upto 128 bit through __int128/__uint128 
	 * important we dont have << operator supporting 128 bit you can't just cout
	 *as per problem we dont need that
	 * making __uint128 pp and using mod avoids the oveflow
	 * similarliy x ,computes the arithmetic under mod ,which keeps it under uint64
	 * */

	__uint128_t pp = 1;
	__uint128_t x;

	/*
	 * to avoid collision of abb ,abba kind ,it is preferable to index 'a' > 0
	 * i choosed a->2,b->3,...index pattren,earlier it was a->0,b->1,..
	 * typecasted the value to make things similar
	 * to avoid segmentation fault i started the loop from i=1,and precomputed hash_values[0]
	 * */
	hash_values[0] =(int)(str[0] - '_');
	pp = pp * p;
	
	for(long long int i=1;i<str.length();i++){
		x = (int)(str[i] - '_') * (pp);
		x %= mod;
		x += hash_values[i-1];
		x %= mod;
		hash_values[i] = x;
		pp = (pp * p);
		pp %= mod;
	}
	return hash_values;
}

/*
 *----------overflow in ,res=(res*a)%m and in a=(a*a)%m;
 modulo ^2 should be supported ,to avoid overflow
 as its 64 bit *64 bit making res and a as uint128 and use of modulo avoids overflow
 */
uint64_t binpow(__uint128_t a,__uint128_t b,__uint128_t m){
	__uint128_t res=1;
	while(b>0){
		if(b&1)
			res =(res*a)%m;
		a = (a*a)%m;
		b>>=1;
	}
	return res;
}

int main()
{
	/*
	 * char *str; will hold the addresss of char 
	 *strlen(cnst *str) takes null terminated string string as a argument 
	 * it will give error 
	 * i preferred to change it to  string str;and strlen(str) to str.length()
	 * */ 
	string str;cin>>str;
	/*
	 * prefix and suffix are quite analogus 
	 * both should be of uint64 as the max values hashpreffix and hashsuffix can be mod
	 * */
	vector<uint64_t> hash_prefix = computeHash(str);
	vector<uint64_t> hash_suffix(str.length()) ;
	
	/*
	 * since hashvalue is of type uint64 overflow will be in 
	 * hash_suffix[strlen(str)-i] = ((hash_prefix[i] - hash_prefix[i-1]) * binpow(binpow(p,i,mod),mod-2,mod))%mod;
	 * to avoid that we used uint128 x to comput under modulo and fit in uint64
	 * */
	__int128_t x;
	/*
	 *we doing reverse calculation with modulo so it hash_prefix[last] - last[last-i]
	 *can be negative ,so to modulo of negative we do like
	 *(a-b)%m = (a-b+m)%m;
	 * if b>a
	 *
	 *
	 * hash[last] = (x0 + x1 +x2 + x3)%m (say)
	 *hash[i] = (x1)%m(say) 
	 * then'
	 * (hash[i] + hashsuffix[i])%m = hash[last]
	 *
	 *solving the equation
	 *hashsuffix[i]  = ((hash[last]%m) - (hash[i]%m))%m

	 *here,
	 * hash == hashprefix */
	__uint128_t y;
	for(long long int i = str.length()-1;i>=0;i--){
		x = hash_prefix[str.length() - 1]%mod;
		x -=(hash_prefix[str.length() - i -1])%mod;
		if(x<0)
			x+=mod;
		x %=mod;
		y = x*binpow(binpow(p,str.length()-i,mod),mod-2,mod);
		y %= mod;
		hash_suffix[str.length()-i-1] = y;
	}
	/* hash_prefix & hash_suffix are uint64*/
	map <uint64_t,long long int> m_prefix;
	map <uint64_t,long long int> m_suffix;

	for(long long int i=0;i<str.length();i++){
		m_prefix[hash_prefix[i]]++;
		m_suffix[hash_suffix[i]]++;
	}
	
	/* int won't store long long * long long arithmetic 
	 * changed it to uint64
	 * */
	uint64_t ans = 0;
	for(auto it: m_prefix){
		long long int f1 = it.second;
		long long int f2 = m_suffix[it.first];
		/*
		 * if we found f2!=0 means common string ,
		 * and keep counting the previous common string thats why addition*/
		if(f2)
		ans += f1 * f2;
	}
	//cout<<"@@@"<<str.length()<<"\n";
	cout<<ans<<"\n";
}
/* above code was tested on gcc (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0
 * compiler
 * using the command g++ IIT2019046.cpp
 * followed by ./a.out
 * on 64-bit processor
 * */ 
