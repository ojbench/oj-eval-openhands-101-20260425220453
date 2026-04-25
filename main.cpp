
#include <iostream>
using namespace std;

int main() {
    int a, b, c, d, e, f;
    cin >> a >> b >> c >> d >> e >> f;
    
    // Total seconds in a day
    long long total_seconds = (long long)c * b * a;
    
    // Current time in seconds
    long long current_seconds = (long long)f * b * a + (long long)e * a + d;
    
    // Try each second from current time + 1 up to one full day
    for (long long s = 1; s <= total_seconds; s++) {
        long long total = current_seconds + s;
        
        // Calculate the new time components
        long long new_seconds = total % a;
        long long new_minutes = (total / a) % b;
        long long new_hours = (total / a / b) % c;
        
        // Check if all three are equal
        if (new_hours == new_minutes && new_minutes == new_seconds) {
            cout << s << endl;
            return 0;
        }
    }
    
    // In case no solution is found (shouldn't happen in a well-designed clock)
    cout << total_seconds << endl;
    return 0;
}
