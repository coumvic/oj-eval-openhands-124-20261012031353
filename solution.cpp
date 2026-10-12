#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class SegmentTree {
private:
    vector<int> tree;
    vector<int> lazy;
    int n;
    
    void build(const vector<int>& arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
        } else {
            int mid = (start + end) / 2;
            build(arr, 2 * node, start, mid);
            build(arr, 2 * node + 1, mid + 1, end);
            tree[node] = max(tree[2 * node], tree[2 * node + 1]);
        }
    }
    
    void push(int node, int start, int end) {
        if (lazy[node] != 0) {
            tree[node] += lazy[node];
            if (start != end) {
                lazy[2 * node] += lazy[node];
                lazy[2 * node + 1] += lazy[node];
            }
            lazy[node] = 0;
        }
    }
    
    int query_max(int node, int start, int end, int l, int r) {
        push(node, start, end);
        if (start > r || end < l) {
            return 0;
        }
        if (start >= l && end <= r) {
            return tree[node];
        }
        int mid = (start + end) / 2;
        return max(query_max(2 * node, start, mid, l, r),
                  query_max(2 * node + 1, mid + 1, end, l, r));
    }
    
    void update_range(int node, int start, int end, int l, int r, int val) {
        push(node, start, end);
        if (start > r || end < l) {
            return;
        }
        if (start >= l && end <= r) {
            lazy[node] += val;
            push(node, start, end);
            return;
        }
        int mid = (start + end) / 2;
        update_range(2 * node, start, mid, l, r, val);
        update_range(2 * node + 1, mid + 1, end, l, r, val);
        tree[node] = max(tree[2 * node], tree[2 * node + 1]);
    }
    
public:
    SegmentTree(const vector<int>& arr) {
        n = arr.size();
        tree.resize(4 * n);
        lazy.resize(4 * n, 0);
        build(arr, 1, 0, n - 1);
    }
    
    int query_max(int l, int r) {
        return query_max(1, 0, n - 1, l, r);
    }
    
    void update_range(int l, int r, int val) {
        update_range(1, 0, n - 1, l, r, val);
    }
};

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int x, k, p;
    cin >> x >> k >> p;
    
    // We need x-1 segments for x stations
    vector<int> seats_used(x - 1, 0);
    SegmentTree st(seats_used);
    
    for (int i = 0; i < p; i++) {
        int u, v, n;
        cin >> u >> v >> n;
        
        // Convert to 0-based indexing for segments
        u--; v--;
        
        // Query maximum seats used in range [u, v-1]
        int max_used = st.query_max(u, v - 1);
        
        if (max_used + n <= k) {
            // Book the seats by adding n to all segments in range
            st.update_range(u, v - 1, n);
            cout << "T\n";
        } else {
            cout << "N\n";
        }
    }
    
    return 0;
}