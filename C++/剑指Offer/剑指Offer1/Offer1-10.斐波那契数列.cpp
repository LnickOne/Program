#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class Solution
{
public:
    int fib(int n)
    {
        if (n <= 1)
        {
            return n;
        }
        vector<int> dp(n + 1);
        dp[0] = 0;
        dp[1] = 1;
        for (int i = 2; i <= n; i += 1)
        {
            dp[i] = (dp[i - 1] + dp[i - 2]) % 1000000007;
        }
        return dp[n];
    }
};

int main()
{
    cout << Solution().fib(5) << endl;
    cout << Solution().fib(10) << endl;
    return 0;
}
