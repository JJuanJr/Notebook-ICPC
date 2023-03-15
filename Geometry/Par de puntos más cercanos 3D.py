from math import dist
def find_closest(points):
    n = len(points)
    if n <= 1: return float("inf")
    if n == 2: return dist(*points)
    left, right = points[:n // 2], points[n // 2:]
    d = min(find_closest(left), find_closest(right))
    strip = sorted((*rest, a) for a, *rest in points if abs(a - points[n // 2][0]) < d)
    for i, p in enumerate(strip):
        for q in strip[i + 1:]:
            if abs(p[0] - q[0]) > d: break
            d = min(d, dist(p, q))
    return d
print(find_closest(sorted(tuple(map(int, input().split())) for _ in range(int(input())))))
