from collections import deque
import pandas
import Station_Information as si
from Subway_csv import st_line_name as sl

'''
환승이 불필요한 경우
- 출발역의 라인과 도착역의 라인이 동일한 경우.

조건0.
-> 같은 호선에서만 이동 (dfs)

환승이 필요한 경우
- 출발역의 라인과 도착역의 라인이 다른 경우.
- 환승 1번, 2번, 그 이상의 경우로 구분.

조건1. 환승 1번인 경우
-> 출발 역을 기준으로 투 포인터 적용
-> 포인터를 움직여 환승역의 라인과 도착 역의 라인이 겹치는 역을 탐색
-> 탐색한 역에서 dfs(조건0)진행

조건2. 환승 2번인 경우
-> 출발 역을 기준으로 투 포인터 적용
-> 포인터를 움직여 환승역에서 dfs(조건1)을 실행
-> 포인터를 끝까지 움직여 리스트 길이 비교 후, 가장 길이가 짧은 경로 선택

조건3. 환승 3번 이상인 경우
-> 환승 3번이상인 경우는 존재하긴 하나, api에서 제공하는 라인들의 경우
   독립된 라인이 없기에 경우의 수가 극소수이다. 
-> 환승 3번의 경우, 마찬가지로 투 포인터로 움직여, 환승역에서 dfs(조건2) 부를 시,
환승 3번의 조건이 충족됨, 4번, 5번도 마찬가지.
'''

# 환승이 불필요한 경우(dfs)
def shortest_route_dfs(start, end, st_line):
    st_deque = deque([[start]])
    visited = [start]
    
    while st_deque:
        st_route = st_deque.popleft()
        st_node = st_route[-1]
        
        if st_node == end:
            return st_route
        
        for st in si.st_infor.get(st_node).get('주변역'):
            # 같은 라인에서 역 이동(깊이 탐색)
            if st_line not in si.st_infor.get(st).get('호선'):
                continue
            if st not in visited:
                visited.append(st)
                route = list(st_route)
                route.append(st)
                st_deque.append(route)

# 환승이 필요한 경우(투 포인터 + dfs), 조건1
def shortest_route_dfs_1(start, end):
    st_line_name = {i:j for j, i in sl.items()}
    line_list = [int(st_line_name.get(line)) for line in si.st_infor.get(start).get('호선')]
    left_short_route = right_short_route = shortest_route = [0 for _ in range(50)]
    
    # 호선별 전체역 리스트
    for line in line_list:
        st_list = list(si.st_df.loc[si.st_df['SUBWAY_ID'] == line].STATN_NM)
        
        # 투 포인터
        left = st_list.index(start) - 1
        right = st_list.index(start) + 1
        left_visited, right_visited = [start], [start]
        
        while left >= 0 or right < len(st_list):
            
            if left >= 0:
                for line in si.st_infor.get(st_list[left]).get('호선'):
                    if line in si.st_infor.get(end).get('호선'):
                        route = shortest_route_dfs(st_list[left], end, line)
                        left_visited.pop()
                        route = left_visited + route
                        left_short_route = min(left_short_route, route, key=len)
                    if st_list[left] not in left_visited:
                        left_visited.append(st_list[left])
                        
            if right < len(st_list):
                for line in si.st_infor.get(st_list[right]).get('호선'):
                    if line in si.st_infor.get(end).get('호선'):
                        route = shortest_route_dfs(st_list[right], end, line)
                        right_visited.pop()
                        route = right_visited + route
                        right_short_route = min(right_short_route, route, key=len)
                    if st_list[right] not in right_visited:
                        right_visited.append(st_list[right])
            
            left -= 1
            right += 1
            
            shortest_route = min(shortest_route ,left_short_route, right_short_route, key=len)
    return shortest_route

# 환승이 필요한 경우(투 포인터 + dfs), 조건2
def shortest_route_dfs_2(start, end):
    st_line_name = {i:j for j, i in sl.items()}
    line_list = [int(st_line_name.get(line)) for line in si.st_infor.get(start).get('호선')]
    left_short_route = right_short_route = shortest_route = [0 for _ in range(50)]
     
    # 호선별 전체역 리스트
    for line in line_list:
        st_list = list(si.st_df.loc[si.st_df['SUBWAY_ID'] == line].STATN_NM)
        
        # 투 포인터
        left = st_list.index(start) - 1
        right = st_list.index(start) - 1
        left_visited, right_visited = [start], [start]
        
        while left >= 0 or right < len(st_list):
            
            if left >= 0:
                for line in si.st_infor.get(st_list[left]).get('호선'):
                    if (line not in si.st_infor.get(start).get('호선')) and (line not in si.st_infor.get(end).get('호선')):
                        route = shortest_route_dfs_1(st_list[left], end)
                        route = left_visited + route
                        left_short_route = min(left_short_route, route, key=len)
                    if st_list[left] not in left_visited:
                        left_visited.append(st_list[left])
            
            if right < len(st_list):
                for line in si.st_infor.get(st_list[right]).get('호선'):
                    if (line not in si.st_infor.get(start).get('호선')) and (line not in si.st_infor.get(end).get('호선')):
                        route = shortest_route_dfs_1(st_list[right], end)
                        route = right_visited + route
                        right_short_route = min(right_short_route, route, key=len)
                        print(right_short_route)
                    if st_list[right] not in left_visited:
                        right_visited.append(st_list[right])
                        
            left -= 1
            right += 1
            
        shortest_route = min(shortest_route, left_short_route, right_short_route, key=len)
    return shortest_route

# 조건1,2번이 없을 경우(bfs), 조건3
def shortest_route_bfs_3(start, end):
    st_deque = deque([[start]])
    visited = [start]
    
    while st_deque:
        st_deque = deque([dele for dele in st_deque if len(dele) < 30])
        
        st_route = st_deque.popleft()
        st_node = st_route[-1]
        
        if st_node == end:
            return st_route
        try:
            for st in si.st_infor.get(st_node).get('주변역'):
                if st not in visited:
                    visited.append(st)
                    route = list(st_route)
                    route.append(st)
                    st_deque.append(route)
        except:
            pass