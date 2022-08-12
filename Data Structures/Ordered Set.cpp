#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ost;
//.find_by_order(k) k-esimo elemento, si k >= size() .end()
//.order_of_key(x) cuantos ki < x
