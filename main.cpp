
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int a, b, c, d, e, f;
    cin >> a >> b >> c >> d >> e >> f;
    
    // The maximum value for x (common value of hour, minute, second)
    int max_x = min({a, b, c});
    
    // Current time in seconds
    long long current_seconds = (long long)f * b * a + (long long)e * a + d;
    
    // Try each possible value of x from 0 to max_x-1
    for (int x = 0; x < max_x; x++) {
        // We need to find s such that:
        // 1. (d + s) % a == x  => s % a == (x - d % a + a) % a
        // 2. (e + (d + s) / a) % b == x
        // 3. (f + (e + (d + s) / a) / b) % c == x
        
        // First constraint: s ≡ (x - d) (mod a)
        long long remainder_a = ((x - d) % a + a) % a;
        
        // We'll check values of s that satisfy the first constraint
        // s = k * a + remainder_a, where k >= 0
        // We need to find the smallest k such that the other constraints are satisfied
        
        // Calculate how many complete minutes are added by adding remainder_a seconds
        long long minutes_added = (d + remainder_a) / a;
        long long new_e = e + minutes_added;
        
        // Second constraint: (new_e + k) % b == x
        // This means k % b == (x - new_e % b + b) % b
        long long remainder_b = ((x - new_e % b) + b) % b;
        
        // Now we need k ≡ remainder_b (mod b)
        // So k = m * b + remainder_b for some m >= 0
        // Therefore s = (m * b + remainder_b) * a + remainder_a
        
        // Calculate how many complete hours are added by adding k minutes
        long long hours_added = (new_e + remainder_b) / b;
        long long new_f = f + hours_added;
        
        // Third constraint: (new_f + m) % c == x
        // This means m % c == (x - new_f % c + c) % c
        long long remainder_c = ((x - new_f % c) + c) % c;
        
        // Now we need m ≡ remainder_c (mod c)
        // So m = n * c + remainder_c for some n >= 0
        // Therefore k = (n * c + remainder_c) * b + remainder_b
        // And s = ((n * c + remainder_c) * b + remainder_b) * a + remainder_a
        
        // The smallest s is when n = 0
        long long s = (remainder_c * b + remainder_b) * a + remainder_a;
        
        // We need s > 0 (we want the next time they coincide)
        if (s > 0) {
            // Verify this s actually works (due to potential overflow in intermediate calculations)
            long long total = current_seconds + s;
            long long new_seconds = total % a;
            long long new_minutes = (total / a) % b;
            long long new_hours = (total / a / b) % c;
            
            if (new_hours == x && new_minutes == x && new_seconds == x) {
                cout << s << endl;
                return 0;
            }
        }
    }
    
    // If no solution found with the mathematical approach, fall back to iteration
    // This shouldn't happen in a well-designed clock
    long long total_seconds = (long long)c * b * a;
    for (long long s = 1; s <= total_seconds; s++) {
        long long total = current_seconds + s;
        long long new_seconds = total % a;
        long long new_minutes = (total / a) % b;
        long long new_hours = (total / a / b) % c;
        
        if (new_hours == new_minutes && new_minutes == new_seconds) {
            cout << s << endl;
            return 0;
        }
    }
    
    // Last resort
    cout << total_seconds << endl;
    return 0;
}
