
#include <iostream>
using namespace std;

int main() {
    int a, b, c, d, e, f;
    cin >> a >> b >> c >> d >> e >> f;
    
    // Current time in seconds
    long long current_seconds = (long long)f * b * a + (long long)e * a + d;
    
    // Total seconds in a day
    long long total_seconds = (long long)c * b * a;
    
    // We can optimize by checking only when seconds and minutes might match
    for (long long s = 1; s <= total_seconds; s++) {
        long long total = current_seconds + s;
        long long secs = total % a;
        long long mins = (total / a) % b;
        
        // If seconds and minutes don't match, skip to next possible match
        if (secs != mins) continue;
        
        long long hrs = (total / a / b) % c;
        
        // Check if all three match
        if (hrs == mins) {
            cout << s << endl;
            return 0;
        }
    }
    
    // In case no solution is found
    cout << total_seconds << endl;
    return 0;
}
