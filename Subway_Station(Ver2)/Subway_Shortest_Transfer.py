# 최소 환승
from collections import deque
from collections import defaultdict
import Subway_Information as si
import Subway_Transfer as st

def shortest_transfer(start, end, i = 0):
    transfer_route = defaultdict(deque) 
    transfer_route[0].append([start])
    visited = [start]
    idx = 0
    
    while True:
        
        try:
            route = transfer_route[idx].popleft()
        except IndexError:
           idx = idx + 1
           continue 
       
        node = route[-1]  
        
        if node == end :
            return route 
        
        for j in si.station_information.get(node).get('주변역'):
            if j not in visited:
                visited.append(j)
                new_route = list(route)
                new_route.append(j)
                i = st.transfer_dict(new_route)
                transfer_route[i].append(new_route)
                
                if new_route[-1] == end and i < 2:
                    return new_route
            else:
                continue