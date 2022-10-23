# ------------------최단 경로-------------------- #
from collections import deque
import Subway_Information as si

# 최단경로 (환승 고려 x)
def shortest_route(start, end):
    que = deque([[start]])
    visited = [start]
    
    while que:
        
        route = que.popleft()
        node = route[-1]
        
        if node == end:
            return route

        for i in si.station_information.get(node).get('주변역'):
            if i not in visited:
                visited.append(i)
            else:
                continue
            new_route = list(route)
            new_route.append(i)
            que.append(new_route)