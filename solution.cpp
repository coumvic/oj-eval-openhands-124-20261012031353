#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int x, k, p;
    cin >> x >> k >> p;
    
    // seats_used[i] represents the number of seats used on segment i to i+1
    // We need x-1 segments for x stations
    vector<int> seats_used(x, 0);
    
    for (int i = 0; i < p; i++) {
        int u, v, n;
        cin >> u >> v >> n;
        
        // Check if booking is possible
        bool can_book = true;
        for (int j = u; j < v; j++) {
            if (seats_used[j] + n > k) {
                can_book = false;
                break;
            }
        }
        
        if (can_book) {
            // Book the seats
            for (int j = u; j < v; j++) {
                seats_used[j] += n;
            }
            cout << "T\n";
        } else {
            cout << "N\n";
        }
    }
    
    return 0;
}