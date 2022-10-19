//NTT code taken from someone else's submission on a similar problem on codechef.
//Search problem by tags and use tag number-theoretic-transfmtn and check for problems in which modulo
//998244353 is used.

#include<bits/stdc++.h>
#include <iostream>
using namespace std;


const long long modulo = 998244353;
const long long primitiveroot = 3;
long long array1[222222],array2[222222];

//done

long long powerfunction(long long x,long long y)
{long long res=1;x=x%modulo;if(x==0) return 0;while(y>0){if(y&1)res=(res*x)%modulo;y=y>>1;x=(x*x)%modulo;}return res;}
long long eulermultiplicativeinverse(long long n) {return powerfunction(n,modulo-2);} 
long long ncr(long long n, long long r) 
{if(n<r) return 0;return (array1[n]*((array2[r] * array2[n-r]) % modulo)) % modulo;}


void ntt(vector<long long>& a, vector<long long>& rt, vector<long long>& rev, long long n) 
{
	for (long long i = 0; i < n; ++i)
	if (i < rev[i]) swap(a[i], a[rev[i]]);
	
	for (long long k = 1; k < n; k *= 2)
	{
		for (long long i = 0; i < n; i += 2 * k) for (long long j = 0; j < k; ++j)
		{
			long long z = rt[j + k] * a[i + j + k] % modulo, &ai = a[i + j];
			a[i + j + k] = (z > ai ? ai - z + modulo : ai - z);
			ai += (ai + z >= modulo ? z - modulo : z);
	    }
	}
}

vector<long long> conv(const vector<long long>& a, const vector<long long>& b) 
{
	if (a.empty() || b.empty()) return {};
	long long s = a.size()+b.size()-1, B = 32 - __builtin_clz(s), n = 1 << B;
	vector<long long> L(a), R(b), out(n), rt(n, 1), rev(n);
	L.resize(n), R.resize(n);
	
	for (int i = 0; i < n; ++i) rev[i] = (rev[i / 2] | (i & 1) << B) / 2;
	
	long long curL = modulo / 2, inv = powerfunction(n, modulo - 2);
	
	for (long long k = 2; k < n; k *= 2) 
	{
		long long z[] = {1, powerfunction(primitiveroot, curL /= 2)};
		for (long long i = k; i < 2*k; ++i) rt[i] = rt[i / 2] * z[i & 1] % modulo;
	}
	ntt(L, rt, rev, n);
	ntt(R, rt, rev, n);
	for (long long i = 0; i < n; ++i) out[-i & (n-1)] = L[i] * R[i] % modulo * inv % modulo;
	ntt(out, rt, rev, n);
	return {out.begin(), out.begin() + s};
}

//done

int main() {
    
	long long n;scanf("%lld\n",&n);
	array1[0]=array1[1]=1;
	for(long long i=2;i<=n;i++) array1[i]=(array1[i-1]*i)%modulo;
	for(long long i=0;i<=n;i++) array2[i]=eulermultiplicativeinverse(array1[i]);
	
	long long occurence[33],prefixsumarray[n+1];
	memset(prefixsumarray,0,sizeof(prefixsumarray));
	memset(occurence,0,sizeof(occurence));
	for(long long i=1;i<=n;i++)
	{
	    long long number;
	    scanf("%lld",&number);
	    for(long long j=0;j<=30;j++) 
	    {
	        if(number%2) occurence[j]++;
	        number/=2;
	    }
	}
	
	long long poweroftwo=1ll;
	for(long long i=0;i<30;i++)
	{
	    vector<long long> onevector,zerovector;
	    for(long long j=0;j<=occurence[i];j++)
	        if(j%2) onevector.push_back(ncr(occurence[i],j));
	        else onevector.push_back(0ll);
	    for(long long j=0;j<=n-occurence[i];j++) zerovector.push_back(ncr(n-occurence[i],j));
	    vector<long long> productvector = conv(onevector,zerovector);
	    long long temp = productvector[0];
	    prefixsumarray[0] = (prefixsumarray[0]+temp)%modulo;
	    for(long long j=1;j<=n;j++)
	    {
	        temp=(temp+productvector[j])%modulo;
	        prefixsumarray[j]=(prefixsumarray[j]+((temp*poweroftwo)%modulo))%modulo;
	    }
	    poweroftwo=(poweroftwo*2)%modulo;
	}
	long long q;
	scanf("%lld\n",&q);
	for(long long l=0;l<q;l++)
	{
	    long long m;
	    scanf("%lld",&m);
	    printf("%lld\n",prefixsumarray[m]);
	}
	
	return 0;
}	
