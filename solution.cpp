#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int x, k, p;
    scanf("%d %d %d", &x, &k, &p);
    
    // seats_used[i] represents the number of seats used on segment i+1 to i+2
    // We need x-1 segments for x stations
    vector<int> seats_used(x - 1, 0);
    
    for (int i = 0; i < p; i++) {
        int u, v, n;
        scanf("%d %d %d", &u, &v, &n);
        
        // Check if booking is possible
        bool can_book = true;
        for (int j = u; j < v; j++) {
            if (seats_used[j-1] + n > k) {
                can_book = false;
                break;
            }
        }
        
        if (can_book) {
            // Book the seats
            for (int j = u; j < v; j++) {
                seats_used[j-1] += n;
            }
            printf("T\n");
        } else {
            printf("N\n");
        }
    }
    
    return 0;
}