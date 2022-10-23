# 최소 환승
from collections import deque
from collections import defaultdict
import Subway_Information as si

def transfer(route):
    
    if len(route) < 2:
        return 0
    
    # 출발점의 호선을 기억하는 함수
    def select_start_line(route, idx):
        start_line = si.station_information[route[idx]]['호선']
        
        # 출발점의 호선이 2개 이상일 경우
        if len(start_line) > 1:
            start_line = "".join([i for i in start_line if i in si.station_information[route[idx + 1]]['호선']])
        else:
            start_line = "".join(start_line)
        
        return start_line
    
    start_line = select_start_line(route, 0)
    
    # 환승 발생
    transfer_cnt = 0
    for idx, station in enumerate(route):
        if start_line not in si.station_information[station]['호선']:
            start_line = select_start_line(route, idx-1)
            transfer_cnt += 1
    
    return transfer_cnt

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
                i = transfer(new_route)
                transfer_route[i].append(new_route)
                
                if new_route[-1] == end and i < 2:
                    return new_route
            else:
                continue